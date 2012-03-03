<?php

/**
 * @file
 * This file contains a wrapper for the mini panel which is used to surf into
 * in order to test the caching functionality of the mini panel.
 */

$page = new stdClass;
$page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
$page->api_version = 1;
$page->name = 'cache_actions_test_mini_panel_wrapper';
$page->task = 'page';
$page->admin_title = 'Cache Actions Test Mini Panel Wrapper';
$page->admin_description = '';
$page->path = 'cache-actions-test-mini-panel-wrapper';
$page->access = array();
$page->menu = array();
$page->arguments = array();
$page->conf = array();
$page->default_handlers = array();
$handler = new stdClass;
$handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
$handler->api_version = 1;
$handler->name = 'page_cache_actions_test_mini_panel_wrapper_panel_context';
$handler->task = 'page';
$handler->subtask = 'cache_actions_test_mini_panel_wrapper';
$handler->handler = 'panel_context';
$handler->weight = 0;
$handler->conf = array(
  'title' => 'Panel',
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
$display->cache = array();
$display->title = '';
$display->content = array();
$display->panels = array();
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-1';
  $pane->panel = 'middle';
  $pane->type = 'panels_mini';
  $pane->subtype = 'cache_actions_test_mini_panel';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
  );
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
$display->title_pane = '0';
$handler->conf['display'] = $display;
$page->default_handlers[$handler->name] = $handler;
