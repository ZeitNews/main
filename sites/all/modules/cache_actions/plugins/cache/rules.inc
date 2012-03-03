<?php

/**
 * @file
 * Provides a simple time-based caching option for panel panes.
 */

// Plugin definition
$plugin = array(
  'title' => t('Rules-based cache'),
  'description' => t('Use rules and Cache Actions to determine when to clear the cache.'),
  'cache get' => 'cache_actions_rules_cache_get_cache',
  'cache set' => 'cache_actions_rules_cache_set_cache',
  'cache clear' => 'cache_actions_rules_cache_clear_cache',
  'cache clear pane' => 'cache_actions_rules_cache_clear_pane_cache',
  'settings form' => 'cache_actions_rules_cache_settings_form',
  'settings form submit' => 'cache_actions_rules_cache_settings_form_submit',
  'defaults' => array(
    'granularity' => 'none',
    'language' => 1
  ),
);

/**
 * Get cached content.
 */
function cache_actions_rules_cache_get_cache($conf, $display, $args, $contexts, $pane = NULL) {
  $cid = cache_actions_rules_cache_get_id($conf, $display, $args, $contexts, $pane);
  $cache = cache_get($cid, 'cache');
  if (!$cache) {
    return FALSE;
  }
  return $cache->data;
}

/**
 * Set cached content.
 */
function cache_actions_rules_cache_set_cache($conf, $content, $display, $args, $contexts, $pane = NULL) {
  $cid = cache_actions_rules_cache_get_id($conf, $display, $args, $contexts, $pane);
  cache_set($cid, $content);
}

/**
 * Clear cached content.
 * @param $display the display object. If this object has a property named
 * clear_pane, then that pane will be cleared.
 */
function cache_actions_rules_cache_clear_cache($display) {
  $cid = 'rc';
  // Add some text if this is a pane, so that we don't clear all panes when
  // we clear a panel pane.
  if (isset($display->clear_pane)) {
    $cid .= ':p';
  }
  if (is_numeric($display->did) && $display->did) {
    $cid .= ':' . $display->did;
  }
  else {
    // Add the cache key if this is an in-code display.
    $cid .= ':' . $display->cache_key;
  }
  // If this is a mini panel then we have the owner property. Let's
  // use the machine name for those.
  if (isset($display->owner)) {
    $cid .= ':' . $display->owner->name;
  }
  // If we have a pane specified, then append that to the key as well.
  if (isset($display->clear_pane)) {
    $cid .= ':' . $display->clear_pane->pid;
  }
  cache_clear_all($cid, 'cache', TRUE);
}

/**
 * Figure out an id for our cache based upon input and settings.
 */
function cache_actions_rules_cache_get_id($conf, $display, $args, $contexts, $pane) {
  $id = 'rc';
  // Add some text if this is a pane, so that we don't clear all panes when
  // we clear a panel pane.
  if ($pane) {
    $id .= ':p';
  }
  if (is_numeric($display->did) && $display->did) {
    $id .= ':' . $display->did;
  }
  else {
    // Add the cache key if this is an in-code display.
    $id .= ':' . $display->cache_key;
  }
  // If this is a mini panel then we have the owner property. Let's
  // use the machine name for those.
  if (isset($display->owner)) {
    $id .= ':' . $display->owner->name;
  }
  if ($pane) {
    $id .= ':' . $pane->pid;
  }

  if (user_access('view pane admin links')) {
    $id .= ':adm';
  }

  switch ($conf['granularity']) {
    case 'args':
      foreach ($args as $arg) {
        // Arguments can be many things, but we only consider the ones that are string values.
        if (is_string($arg)) {
          $id .= ':' . $arg;
        }
      }
      break;

    case 'context':
      if (!is_array($contexts)) {
        $contexts = array($contexts);
      }
      foreach ($contexts as $context) {
        if (isset($context->argument)) {
          $id .= ':' . $context->argument;
        }
      }
  }
  // Add cache for individual language.
  if ($conf['language']) {
    global $language;
    $id .= ':' . $language->language;
  }
  $cache->conf = $conf;
  $cache->display = $display;
  $cache->args = $args;
  $cache->contexts = $contexts;
  $cache->pane = $pane;
  $cache->key = $id;

  // Let other modules alter the cache key.
  drupal_alter('cache_actions_panels_cache_key', $cache);
  return $cache->key;
}

function cache_actions_rules_cache_settings_form($conf, $display, $pid) {
  $form['granularity'] = array(
    '#title' => t('Granularity'),
    '#type' => 'select',
    '#options' => array(
      'args' => t('Arguments'),
      'context' => t('Context'),
      'none' => t('None'),
    ),
    '#description' => t('If "arguments" are selected, this content will be cached per individual argument to the entire display; if "contexts" are selected, this content will be cached per unique context in the pane or display; if "neither" there will be only one cache for this pane.'),
    '#default_value' => $conf['granularity'],
  );
  $form['language'] = array(
    '#title' => t('Cache per language'),
    '#type' => 'checkbox',
    '#default_value' => $conf['language'],
    '#description' => t('Select this if you want to cache content per language'),
  );
  return $form;
}

