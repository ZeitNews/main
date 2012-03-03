<?php
// $Id: topichubs.views.inc,v 1.1.2.1 2009/09/02 12:00:22 inadarei Exp $
/**
 * @file
 * Provide views handlers for topichubs
 */

/**
 * Implementation of hook_views_data()
 */
function topichubs_views_data() {
  $data = array();

  $data['topichub']['table']['group']  = t('Topic Hub');
  $data['topichub']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'tid',
    ),
  );

  // nid field
  $data['topichub']['nid'] = array(
    'title' => t('Expression'),
    'real field' => 'tid',
    'help' => t('The Node id of the Topic Hub'),
    'filter' => array(
      'handler' => 'topichubs_handler_filter_topichub_nid',
    ),
    'argument' => array(
      'handler' => 'topichubs_handler_argument_topichub_nid',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function topichubs_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'topichubs') . '/views/handlers',
    ),
    'handlers' => array(
      // filters
      'topichubs_handler_filter_topichub_nid' => array(
        'parent' => 'views_handler_filter',
      ),
      // arguments
      'topichubs_handler_argument_topichub_nid' => array(
        'parent' => 'views_handler_argument',
      ),
    ),
  );
}



