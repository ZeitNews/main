<?php

/**
 * @file
 * This mini panel has caching enabled and is used to test the clearing of a
 * whole mini panel pane.
 */

$mini = new stdClass;
$mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
$mini->api_version = 1;
$mini->name = 'cache_actions_test_mini_panel';
$mini->category = 'Cache Actions Test';
$mini->title = 'Cache Actions Test Mini Panel';
$mini->admin_description = 'A test mini panel';
$mini->requiredcontexts = array();
$mini->contexts = array();
$mini->relationships = array();
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
$display->owner = new stdClass;
$display->owner->id = 'cache_actions_test_mini_panel';
$display->panels = array();
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-1';
  $pane->panel = 'middle';
  $pane->type = 'views_panes';
  $pane->subtype = 'cache_actions_test_view-panel_pane_1';
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
$display->title_pane = '0';
$mini->display = $display;
