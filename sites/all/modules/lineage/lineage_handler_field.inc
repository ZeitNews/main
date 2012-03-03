<?php
// $Id: lineage_handler_field.inc,v 1.1.2.5 2010/07/25 14:59:02 xjm Exp $

/**
 * @file
 * Views field plugin for lineage's field handler.
 */

/**
 * Field handler for Taxonomy: Hierarchy.
 */
class lineage_handler_field extends views_handler_field {
  /**
   * Provide formatting options for the field.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $field = $this->content_field;
    $options = $this->options;

    $form['lineage'] = array(
      '#type' => 'fieldset',
      '#title' => t("Lineage string formatting options"),
    );

    $form['lineage']['strip_weights'] = array(
      '#type' => 'checkbox',
      '#title' => t('Strip weights'),
      '#default_value' => $options['lineage']['strip_weights'],
      '#description' => t("The raw lineage entries begin with a number indicating the term weight (for term ordering).  Check to remove weights for display."),
    );

    $form['lineage']['machine_safe']= array(
      '#type' => 'checkbox',
      '#title' => t('Machine-safe'),
      '#default_value' => $options['lineage']['machine_safe'],
      '#description' => t("Reformats the lineage strings for use in machine-readable contexts.  Be sure to use an appropriate term delimiter (below) and prefix text (above) if you wish this to be a CSS class name; CSS class names must begin with a letter."),
    );

    $form['lineage']['prefix'] = array(
      '#type' => 'textfield',
      '#title' => t('Term prefix'),
      '#default_value' => $options['lineage']['prefix'],
      '#description' => t("Appended before each term name in the lineage.  You may include HTML."),
    );

    $form['lineage']['suffix'] = array(
      '#type' => 'textfield',
      '#title' => t('Term suffix'),
      '#default_value' => $options['lineage']['suffix'],
      '#description' => t("Appended before each term name in the lineage.  You may include HTML."),
    );

    $form['lineage']['delimiter'] = array(
      '#type' => 'textfield',
      '#title' => t('Delimiter between terms'),
      '#default_value' => $options['lineage']['delimiter'],
      '#description' => t("Use %linebreak_code for line breaks.", array('%linebreak_code' => '\n')),
    );
  }


  /**
   * Render the field.
   */
  function render($values) {
    $options = $this->options ? $this->options : array();
    if ($options['lineage']) {
        extract($options['lineage']);
    }

    $lineage_string = $values->{$this->field_alias};

    if ($lineage_string == '') {
      return '';
    }

    // Split hierarchy string into hierarchical path pieces.
    // Term entries are separated by \n; trim so we don't add empty pieces.
    $term_strings = explode("\n", trim($lineage_string));

    // Compose the rendered hierarchy according to handler form options.

    if ($strip_weights) {
      $term_strings = array_map("lineage_strip_weight", $term_strings);
    }

    if ($machine_safe) {
      // Replace non-alphanumeric characters with a hyphen.
      $non_alphanumeric = '/[^a-zA-Z0-9]+/ ';
      $term_strings = preg_replace($non_alphanumeric, '-', $term_strings);
    }

    if ($prefix || $suffix) {
      foreach ($term_strings as $key => $term_string) {
        $term_string = $prefix . $term_string . $suffix;
        $term_strings[$key] = $term_string;
      }
    }

    // The user may enter "\n" for a linebreak delimiter;
    // replace with actual linebreak character.
    $delimiter = str_replace("\\n", "\n", $delimiter);

    $rendered = implode($delimiter, $term_strings);

    // Be sure to validate and sanitize markup since we allow HTML.
    return filter_xss_admin($rendered);
  }
}

