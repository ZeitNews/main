<?php
// $Id: views_plugin_style_lineage_nested.inc,v 1.1.2.11 2010/09/19 19:21:23 xjm Exp $

/**
 * @file
 * Views style plugin that allows a view to be rendered as a nested list,
 * based on Lineage's term hierarchy.
 */


/**
 * Define a base starting depth for nesting headers.
 * We use 3 (for <h3> tags) because <h1> and <h2> are generally page titles.
 */
define('LINEAGE_START_DEPTH', 3);


/**
 * Implements views_plugin_style.
 */
class views_plugin_style_lineage_nested extends views_plugin_style_list {
  function respond_to_filter($filter) {
    $allowed = array(
      'views_handler_filter_term_node_tid',
      'views_handler_filter_term_node_tid_depth',
      'views_handler_argument_term_node_tid',
      'views_handler_argument_term_node_tid_depth',
    );
    if (in_array($filter, $allowed)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  function options_form(&$form, &$form_state) {

    // Assemble a list of Taxonomy Lineage fields.
    $nesting_options = array('' => '[None]');
    foreach ($this->display->handler->get_handlers('field') as $field => $handler) {
      // Only include lineage fields.
      if ($handler->definition['handler'] == 'lineage_handler_field') {
        if ($label = $handler->label()) {
          $nesting_options[$field] = $label;
        }
        else {
          $nesting_options[$field] = $handler->ui_name();
        }
      }
    }

    // Assemble a list of Taxonomy filters and arguments
    $filter_options = array('' => '[None]');
    foreach ($this->display->handler->get_handlers('filter') as $filter => $handler) {
      if ($this->respond_to_filter($handler->definition['handler'])) {
        $filter_options['Filters']['f_' . $filter] = $handler->ui_name();
      }
    }
    foreach ($this->display->handler->get_handlers('argument') as $arg => $handler) {
      if ($this->respond_to_filter($handler->definition['handler'])) {
        $filter_options['Arguments']['a_' . $arg] = $handler->ui_name();
      }
    }



    $options = parent::options_form($form, $form_state);
    if (sizeof($nesting_options) > 1) { // one option is [None]
      $form['nesting'] = array(
        '#type' => 'select',
        '#title' => t('Nesting Field'),
        '#options' => $nesting_options,
        '#default_value' => $this->options['nesting'],
        '#description' => t(
          'Select the Lineage field that will control the nesting.'
        ),
      );

      $h_options = array(0 => t('default'));
      for ($i = 1; $i <= 6; $i++) {
        $h_options[$i] = "<h$i>";
      }

      $default_header = $this->options['start_depth']
        ? $this->options['start_depth']
        : 0;

      $form['start_depth'] = array(
        '#type' => 'select',
        '#title' => 'Top-level header',
        '#options' => $h_options,
        '#default_value' => $default_header,
        '#description' => t(
          'Header tag to use for the top-level term in the nesting.  If %default is selected, the plugin will choose the header level based on the properties of your view.',
          array('%default' => $h_options[0])
        ),
      );

      if (sizeof($filter_options) > 1) { // one option is [None]
        $form['filter'] = array(
          '#type' => 'select',
          '#title' => 'Set top level with filter or argument',
          '#options' => $filter_options,
          '#default_value' => $this->options['filter'],
          '#description' => t(
            "If selected, the nesting will begin with the term set by this argument or filter, and headers for parent terms will be hidden.  (Filters and arguments are listed in the same order as in your view.)  This feature is experimental."
          ),
        );
      }
    }
  }

  function render() {
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }

    $output = '';

    // First group the rows according to the grouping field, if specified.
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);

    foreach ($sets as $title => $records) {
      if ($this->uses_row_plugin()) {
        $rendered = array();
        foreach ($records as $row_index => $row) {
          $this->view->row_index = $row_index;
          $rendered[$row_index] = $this->row_plugin->render($row);
        }
      }

      // If the user specified a filter for the nesting, remove other levels.
      $term_name = FALSE;
      if ($this->options['filter']) {
        
        // Option is either a filter or an argument, marked by f and a.
        // If it's an argument
        if ($arg_name = strstr($this->options['filter'], "a_")) {
          $arg_name = substr($arg_name, 2);
          $arg = $this->display->handler->handlers['argument'][$arg_name];
          $term = $arg->argument;
        }
        // If it's a filter
        elseif ($filter_name = strstr($this->options['filter'], "f_")) {
          $filter_name = substr($filter_name, 2);
          $filter = $this->display->handler->handlers['filter'][$filter_name];
          $terms = $filter->value;
          $term = array_pop($terms);
        }
        
        if (is_numeric($term)) {
          $term_obj = taxonomy_get_term($term);
          $term_name = $term_obj->name;
        }
        else {
          $term_name = $term;
        }
      } 
 
     // Now, nest each grouping by the nesting field.
      $nested_set = $this->render_nesting($records, $rendered, $this->options['nesting'], $term_name);

      // Determine the starting depth of the header.
      // If the user has defined a start depth, use that.
      if ($this->options['start_depth']) {
        $depth = $this->options['start_depth'];
      }
      // Otherwise, decide based on default and whether a grouping is set.
      else {
        $depth = LINEAGE_START_DEPTH;
      }
      
      // @todo Provide theming.
      $output .= 
        $this->nested_list(
          $nested_set, 
          $title, 
          $this->options['type'], 
          $depth
        );
      
    }
    unset($this->view->row_index);
    return $output;
  }

  function render_nesting($records, $rendered, $nesting_field = '', $term_name = FALSE) {
    $nested_sets = array();
    if (isset($this->view->field[$nesting_field])) {
      $field_alias = $this->view->field[$nesting_field]->field_alias;
    }

    if ($field_alias) {
      foreach ($records as $index => $row) {
        $nesting = '';
        // @todo Avoid using eval().

        $lineage = $row->$field_alias;
        // If a filter term was passed, remove the lineage before the term.
        if ($term_name) {
          $lineage = strstr($lineage, $term_name);
          if ($lineage) {
            $lineage = substr($lineage, strlen($term_name)+1); // +1 for \n
          }
        }
        
        // Strip weights from the lineage, if any.
        if ($lineage) {
          $lineage = explode("\n", $lineage);
          foreach ($lineage as $key => $value) {
            if ($value) {
              $lineage[$key] = lineage_strip_weight($value);
            }
          }
          $lineage = implode("\n", $lineage);
        }
          
        // Add the row to the array.
        $eval = "\$nested_sets"
          . "['"
          . str_replace("\n", "']['", addslashes($lineage) . $index)
          . "']"
          . " = \$rendered[\$index];";
        eval($eval);
      }
    }
    else {
      // Create a single group with an empty grouping field.
      $nested_sets[''] = $records;
    }

    return $nested_sets;
  }

  function header($header, $depth) {
    // Use a header tag if possible; else use a class indicating header depth.
    if ($depth <= 6) {
      return "<h$depth>" . stripslashes($header) . "</h$depth>\n";
    }
    else {
      return "<span class=\"h$depth\">$header</span>\n";
    }
  }

  function nested_list($rows, $header, $type, $depth = 1) {
    $output = "";
    if (!empty($header)) {
      $output .=  $this->header($header, $depth);
      $depth++;
    }

    $output .=  "<$type>\n";

    foreach ($rows as $key => $row) {
      $output .=  "<li>\n"; // @todo Add classes.
      // If the next child is an array of rows, recurse.
      if (is_array($row) || is_object($row)) {
        // @todo Allow type to vary per list? (And how would we store that?)
        $output .= $this->nested_list($row, $key, $type, $depth);
      }
      else {
        $output .=  $row;
      }
      $output .=  "</li>\n";
    }

    $output .=  "</$type>\n";

    return $output;
  }
}