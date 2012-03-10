<?php

/**
 * @file
 * This panel contains a pane that uses rules based caching. It is used to test
 * the clearing of the cache for an individual panel pane.
 */

$page = new stdClass;
$page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
$page->api_version = 1;
$page->name = 'cache_actions_test_panel_pane';
$page->task = 'page';
$page->admin_title = 'Cache Actions Test Panel Pane';
$page->admin_description = 'Cache Actions test panel';
$page->path = 'cache-actions-test-panel-pane';
$page->access = array();
$page->menu = array();
$page->arguments = array();
$page->conf = array();
$page->default_handlers = array();
$handler = new stdClass;
$handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
$handler->api_version = 1;
$handler->name = 'page_cache_actions_test_panel_pane_panel_context';
$handler->task = 'page';
$handler->subtask = 'cache_actions_test_panel_pane';
$handler->handler = 'panel_context';
$handler->weight = 0;
$handler->conf = array(
  'title' => 'Cache actions Test Panel Pane variant 1',
  'no_blocks' => 0,
  'pipeline' => 'standard',
  'css_id' => '',
  'css' => '',
  'contexts' => array(),
  'relationships' => array(),
);
$display = new panels_display;
$display->api_version = 1;
$display->layout = 'onecol';
$display->layout_settings = array();
$display->panel_settings = array(
  'style_settings' => array(
    'default' => NULL,
    'middle' => NULL,
  ),
);
$display->cache = array(
  'method' => '0',
  'settings' => array(),
);
$display->title = '';
$display->content = array();
$display->panels = array();
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-1';
  $pane->panel = 'middle';
  $pane->type = 'views_panes';
  $pane->subtype = 'cache_actions_test_view_pane-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array(
    'method' => 'rules',
    'settings' => array(
      'granularity' => 'none',
    ),
  );
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-1'] = $pane;
  $display->panels['middle'][0] = 'new-1';
$display->hide_title = PANELS_TITLE_FIXED;
$display->title_pane = 'new-1';
$handler->conf['display'] = $display;
$page->default_handlers[$handler->name] = $handler;
$handler = new stdClass;
$handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
$handler->api_version = 1;
$handler->name = 'page_cache_actions_test_panel_pane_panel_context_2';
$handler->task = 'page';
$handler->subtask = 'cache_actions_test_panel_pane';
$handler->handler = 'panel_context';
$handler->weight = 1;
$handler->conf = array(
  'title' => 'Cache actions Test Panel Pane variant 2',
  'no_blocks' => 0,
  'pipeline' => 'standard',
  'css_id' => '',
  'css' => '',
  'contexts' => array(),
  'relationships' => array(),
);
$display = new panels_display;
$display->api_version = 1;
$display->layout = 'onecol';
$display->layout_settings = array();
$display->panel_settings = array(
  'style_settings' => array(
    'default' => NULL,
    'middle' => NULL,
  ),
);
$display->cache = array(
  'method' => 'rules',
  'settings' => array(
    'granularity' => 'none',
  ),
);
$display->title = '';
$display->content = array();
$display->panels = array();
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-1';
  $pane->panel = 'middle';
  $pane->type = 'views_panes';
  $pane->subtype = 'cache_actions_test_view_pane-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-1'] = $pane;
  $display->panels['middle'][0] = 'new-1';
$display->hide_title = PANELS_TITLE_FIXED;
$display->title_pane = 'new-1';
$display->owner = new stdClass;
$display->owner->id = 'cache_actions_test_panel_pane';
$handler->conf['display'] = $display;
$page->default_handlers[$handler->name] = $handler;
