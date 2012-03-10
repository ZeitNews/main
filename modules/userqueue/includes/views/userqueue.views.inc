<?php
// $Id: $

/**
 * @file userqueue.views.inc
 * Provides support for the Views module.
 */



function userqueue_views_handlers() {
  return array(
  'info' => array(
    'path' => drupal_get_path('module', 'userqueue') .'/includes/views',
    ),
    'handlers' => array(
      'userqueue_handler_argument_uqid' => array(
         'parent' => 'views_handler_argument_numeric',
       ),
      'userqueue_handler_field_queue_tab' => array(
        'parent' => 'views_handler_field_node_link',
      ),
      'userqueue_handler_filter_in_queue' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
      'userqueue_handler_relationship_userqueue' => array(
        'parent' => 'views_handler_relationship',
      ),
    ),
  );
}
/**
 * Implementation of hook_views_data()
 */
function userqueue_views_data() {
  $data = array();

  // ----------------------------------------------------------------
  // userqueue_user table
  $data['userqueue_user']['table']['group'] = t('Userqueue');

  // The nodequeue_nodes table is how nodequeue connects to the
  // rest of the world, but we will only join it in via relationship.

  // position
  $data['userqueue_user']['weight'] = array(
    'title' => t('Position'),
    'help' => t('The position of the user within a queue.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['userqueue_user']['uqid'] = array(
    'title' => t('Queue ID'),
    'help' => t('The ID of the queue the user belongs to.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'userqueue_handler_argument_uqid',
      'name field' => 'title',
      'name table' => 'userqueue',
      'empty field name' => t('No queue'),
    ),
  );

  // specialized is null/is not null filter
  $data['userqueue_user']['in_queue'] = array(
    'title' => t('In queue'),
    'help' => t('Filter to ensure a user IS or IS NOT in the related queue'),
    'filter' => array(
      'handler' => 'userqueue_handler_filter_in_queue',
      'label' => t('In queue'),
    ),
  );

  // ----------------------------------------------------------------
  // nodequeue_queue table
  $data['userqueue']['table']['group'] = t('Userqueue');

  // For use with the relationship.
  $data['userqueue']['table']['join'] = array(
    'userqueue_user' => array(
      'left_field' => 'uqid',
      'field' => 'uqid',
    ),
  );

  $data['userqueue']['title'] = array(
    'title' => t('Queue title'),
    'help' => t('The title of the userqueue.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_data_alter().
 */
function userqueue_views_data_alter(&$data) {
  // queue relationship
  $data['users']['userqueue_rel'] = array(
    'group' => t('Userqueue'),
    'title' => t('Queue'),
    'help' => t('Create a relationship to a userqueue.'),
    'real field' => 'uid',
    'relationship' => array(
      'handler' => 'userqueue_handler_relationship_userqueue',
      'base' => 'userqueue_user',
      'field' => 'uid',
      'label' => t('queue'),
    ),
  );

  // links
  $data['users']['userqueue_links'] = array(
    'group' => t('Userqueue'),
    'title' => t('Add/remove links'),
    'help' => t('Display add/remove links for all eligible userqueues. Note that this performs a user_load so could add many extra queries to a view.'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'userqueue_handler_field_links',
    ),
  );

  $data['users']['userqueue_queue_tab'] = array(
    'group' => t('Userqueue'),
    'title' => t('Link to tab'),
    'help' => t('Display add/remove links for all eligible userqueues. Note that this performs a user_load so could add many extra queries to a view.'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'userqueue_handler_field_queue_tab',
    ),
  );

  // all queues
  $data['users']['userqueue_all_queues'] = array(
    'group' => t('Userqueue'),
    'title' => t('All queues'),
    'help' => t('Display all queues a user is a member of.'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'userqueue_handler_field_all_queues',
    ),
  );
}
