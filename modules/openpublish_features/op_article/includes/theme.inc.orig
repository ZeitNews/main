<?php

define ('OP_ARTICLE_MULTIPLE_AUTHORS', '#MUTLIPLE#');

/**
 * Implementation of module_preprocess_views_view_fields
 */
function op_article_preprocess_views_view_fields(&$vars) { 
  $view = $vars['view'];
    
  if ($view->name != 'articles') {
    return;
  }
  
  if (!empty($vars['fields']['title_2']) && $vars['fields']['title_2']->content == OP_ARTICLE_MULTIPLE_AUTHORS) {
    $vars['fields']['title_1']->content .= '&nbsp;' . t('et al.');
    unset($vars['fields']['title_2']);
  }  
}

/**
 * Implementation of module_preprocess_views_view_field.
 * Used here to add RDFa properties to certain field level tags.
 */
function op_article_preprocess_views_view_field(&$vars) {
  $view = $vars['view'];
  
  if ($view->name != 'articles') {
    return;
  }
  
  switch ($vars['field']->real_field) {
    case 'title':
      // Author node title
      if (strpos($vars['field']->field_alias, 'op_author') !== FALSE) {
        $vars['rdfa_author'] = _openpublish_get_rdfa_author($vars['row']->node_node_data_field_op_author_title, $vars['row']->node_node_data_field_op_author_nid);        
      }
      else {
        // Article node title
        $vars['rdfa_title'] = _openpublish_get_rdfa_title($vars['row']->node_title, $vars['row']->nid);
      }
      break;

    case 'created':
      $vars['rdfa_created'] = _openpublish_get_rdfa_date($vars['row']->node_created, $vars['field']->original_value);
      break;
      
    default:
      $vars['output'] = $vars['field']->advanced_render($vars['row']);
      break;
  } 
}

/**
 * template_preprocess_views_view_unformatted implementation
 */
function op_article_preprocess_views_view_unformatted(&$vars) {
  $view     = $vars['view'];
  $rows     = $vars['rows'];

  if ($view->name != 'articles') {
    return;
  }
  
  $vars['classes'] = array();
  // Set up striping values.
  foreach ($rows as $id => $row) {
    $vars['rdfa_about_links'][$id] = url('node/' . $view->result[$id]->nid);
    
    $row_classes = array();
    $row_classes[] = 'views-row';
    $row_classes[] = 'views-row-' . ($id + 1);
    $row_classes[] = 'views-row-' . ($id % 2 ? 'even' : 'odd');
    if ($id == 0) {
      $row_classes[] = 'views-row-first';
    }
    if ($id == count($rows) -1) {
      $row_classes[] = 'views-row-last';
    }
    // Flatten the classes to a string for each row for the template file.
    $vars['classes'][$id] = implode(' ', $row_classes);
  }
}