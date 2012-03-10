<?php

/**
 * @file
 * This view is used to test the clearing of views.
 */
$view = new view;
$view->name = 'cache_actions_test_view';
$view->description = '';
$view->tag = '';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'rules',
));
$handler->override_option('row_plugin', 'node');
$handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
$handler->override_option('pane_title', '');
$handler->override_option('pane_description', '');
$handler->override_option('pane_category', array(
  'name' => 'View panes',
  'weight' => 0,
));
$handler->override_option('allow', array(
  'use_pager' => FALSE,
  'items_per_page' => FALSE,
  'offset' => FALSE,
  'link_to_view' => FALSE,
  'more_link' => FALSE,
  'path_override' => FALSE,
  'title_override' => FALSE,
  'exposed_form' => FALSE,
  'fields_override' => FALSE,
));
$handler->override_option('argument_input', array());
$handler->override_option('link_to_view', 0);
$handler->override_option('inherit_panels_path', 0);
$handler = $view->new_display('block', 'Block', 'block_1');
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->override_option('path', 'cache-actions-test-view');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
