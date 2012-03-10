<?php
// $Id$
/**
 * @file
 * Views integration for MTA Taki module.
 */

/**
 * Implementation of hook_views_data().
 */
function tagorder_views_data() {
  $data = array();

  // tid field
  $data['term_node']['tagorder'] = array(
    'title' => t('Term ID'),
    'help' => t('The taxonomy term ID'),
    'field' => array(
      'title' => t('All terms in Tag Order'),
      'help' => t('Display all taxonomy terms associated with a node from specified vocabularies.'),
      'handler' => 'views_handler_field_tagorder_node_tid',
      'skip base' => 'term_data',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_term_node_tid',
      'name table' => 'term_data',
      'name field' => 'name',
      'empty field name' => t('Uncategorized'),
      'numeric' => TRUE,
      'skip base' => 'term_data',
    ),
    'filter' => array(
      'title' => t('Term'),
      'handler' => 'views_handler_filter_term_node_tid',
      'hierarchy table' => 'term_hierarchy',
      'numeric' => TRUE,
      'skip base' => 'term_data',
      'allow empty' => TRUE,
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function tagorder_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'tagorder') . '/views',
    ),
    'handlers' => array(
      'views_handler_field_tagorder_node_tid' => array(
        'parent' => 'views_handler_field_term_node_tid',
      ),
    ),
  );
}
