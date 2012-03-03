<?php
// $Id: lineage.views.inc,v 1.1.2.6 2010/03/05 16:24:33 xjm Exp $

/**
 * @file
 * Interface between lineage.module and views.module.
 */

/**
 * Implementation of hook_views_data().
 */
function lineage_views_data() {
  $tables['term_lineage'] = array(
    'table' => array(
      'group' => t('Taxonomy'),
      'join' => array(
        'node' => array(
          'left_table' => 'term_node',
          'left_field' => 'tid',
          'field' => 'tid',
        ),
        'term_data' => array(
          'left_field' => 'tid',
          'field' => 'tid',
        ),
      ),
    ),
    'lineage' => array(
      'title' => t("Hierarchy"),
      'field' => array(
        'handler' => 'lineage_handler_field',
        'click sortable' => TRUE,
        'help' => t('Taxonomy lineage hierarchy'),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'depth' => array(
      'title' => t("Depth"),
      'field' => array(
        'handler' => 'views_handler_field',
        'help' => t('Taxonomy lineage depth'),
      ),
    ),
  );

  return $tables;
}

/**
 * Implementation of hook_views_handlers().
 */
function lineage_views_handlers() {
  return array(
    'handlers' => array(
      'lineage_handler_field' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}


/**
 * Implements hook_views_plugins().
 */
function lineage_views_plugins() {
  return array(
    'style' => array( // Declare the nested list style plugin.
      'lineage_nested' => array(
        'title' => t('Lineage nested list'),
        'theme' => 'views_view_lineage_nested',
        'help' => t('Displays rows in a nested list, grouped by term lineage'),
        'handler' => 'views_plugin_style_lineage_nested',
        'uses row plugin' => TRUE,
        'uses fields' => TRUE,
        'uses grouping' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'parent' => 'list',
      ),
    )
  );
}