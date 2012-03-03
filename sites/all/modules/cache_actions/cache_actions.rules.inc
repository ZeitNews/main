<?php

/**
 * @file
 * This file provides the rules integration for this module.
 */

/**
 * Implementation of hook_rules_action_info().
 */
function cache_actions_rules_action_info() {
  // Actions that works for everyone
  $actions = array(
    'cache_actions_action_clear_cache' => array(
      'label' => t('Clear cache bins'),
      'arguments' => array(
        'tables' => array(
           'type' => 'value',
           'label' => t('Cache tables'),
           'description' => t('Specify which cache tables you want to clear here. 
             Separate the tables with spaces. You can use * to clear all tables')),
      ),
      'module' => 'Cache Actions',
    ),
    'cache_actions_action_clear_cache_cid' => array(
      'label' => t('Clear a specific cache cid'),
      'arguments' => array(
        'table' => array(
          'type' => 'value',
          'label' => t('Cache tables'),
          'description' => t('The cache table where the cid is')
         ),
         'cid' => array(
           'type' => 'string',
           'label' => t('Cache cid'),
           'description' => t('The cid to clear')
         ),
         'wildcard' => array(
           'type' => 'boolean',
           'label' => t('Use wildcard'),
           'description' => t('Use wildcards. This means you will be clearing 
             all cids that partially matches.')
        ),
      ),
      'module' => 'Cache Actions',
    ),
    'cache_actions_action_clear_css_js_cache' => array(
      'label' => t('Clear the css and js cache'),
      'module' => 'Cache Actions',
    ),
  );
  // If the views module is available, then we can clear the cache of individual views.
  if (module_exists('views')) {
    $actions['cache_actions_action_clear_views_cache'] = array(
      'label' => t('Clear the cache for specific views'),
      'arguments' => array(
        'view' => array(
          'type' => 'value',
          'label' => t('View'),
          'description' => t('Specify the views you want to clear.')),
      ),
      'module' => 'Cache Actions',
    );
    $actions['cache_actions_action_clear_views_display_cache'] = array(
      'label' => t('Clear the cache for views displays'),
      'arguments' => array(
        'displays' => array(
          'type' => 'value',
          'label' => t('Displays'),
          'description' => t('Select the displays you want to clear.')
        ),
      ),
      'module' => 'Cache Actions',
    );
  }

  // If the page manager module is available, then we can clear the cache of panel pages.
  if (module_exists('page_manager')) {
    $actions['cache_actions_action_clear_panels_page_cache'] = array(
      'label' => t('Clear the cache for panel page variants'),
      'arguments' => array(
        'panel' => array(
          'type' => 'value',
          'label' => t('Panel page'),
          'description' => t('Specify the panel page you want to clear.')
        ),
      ),
      'module' => 'Cache Actions',
    );

    $actions['cache_actions_action_clear_panels_pane_cache'] = array(
      'label' => t('Clear the cache for panel page panes'),
      'arguments' => array(
        'panel' => array(
          'type' => 'value',
          'label' => t('Panel page'),
          'description' => t('Specify the panel page you want to clear.')
        ),
        'panes' => array(
          'type' => 'value',
          'label' => t('Panel page'),
          'description' => t('The pane to clear')
        ),
      ),
      'module' => 'Cache Actions',
    );
  }

  // If the mini panels module is available, then we can clear the cache of mini panels.
  if (module_exists('panels_mini')) {
    $actions['cache_actions_action_clear_panels_mini_cache'] = array(
      'label' => t('Clear the cache for a specific mini panel variants'),
      'arguments' => array(
        'panel' => array(
          'type' => 'value',
          'label' => t('Panel page'),
          'description' => t('Specify the mini panel you want to clear.')
        ),
      ),
      'module' => 'Cache Actions',
    );
    $actions['cache_actions_action_clear_panels_mini_pane_cache'] = array(
      'label' => t('Clear the cache for mini panel panes'),
      'arguments' => array(
        'panel' => array(
          'type' => 'value',
          'label' => t('Panel page'),
          'description' => t('Specify the mini panel you want to clear.')
        ),
        'panes' => array(
          'type' => 'string',
          'label' => t('Panel panes'),
          'description' => t('Specify the mini panes you want to clear.')
        ),
      ),
      'module' => 'Cache Actions',
    );
  }

  // If varnish module is available, then we can clear specific varnish pages.
  if (module_exists('varnish')) {
    $actions['cache_actions_action_clear_varnish_page'] = array(
      'label' => t('Clear paths cached in varnish'),
      'arguments' => array(
        'paths' => array(
          'type' => 'string',
          'label' => t('Varnish paths'),
          'description' => t('The cached paths')
        ),
      ),
      'module' => 'Cache Actions',
    );

    $actions['cache_actions_action_clear_varnish_cache'] = array(
      'label' => t('Clear all paths cached in varnish for this site'),
      'module' => 'Cache Actions',
    );
  }
  return $actions;
}

/**
 * The form for the clear panel page action
 * @param array $settings
 * @param $form the form
 */
function cache_actions_action_clear_panels_page_cache_form($settings, &$form) {
  $available_handlers = _cache_actions_get_panels_handlers();
  $form['settings']['panel'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Panel Variants'),
    '#options' => $available_handlers,
    '#default_value' => $settings['panel'],
    '#description' => t('The panel page to be cleared.
     Only panel pages which have the simple cache enabled will be shown here.'),
  );
  // Let's make sure the action can't be added if there are no applicable panel pages.
  if (!count($available_handlers)) {
    form_set_error('panel', t('This action is not applicable, since there are no panel pages with caching enabled.'));
    $form['submit']['#disabled'] = TRUE;
  }
}

/**
 * Get all existing handlers from page manager. This is the ugliest function
 * in the whole module =)
 * @param bool $panes set this to true if you want the function to return
 * an array consisting of the panels and the panes.
 * @return the handlers.
 */
function _cache_actions_get_panels_handlers($panes = FALSE) {
  $available_handlers = array();
  $available_panes = array();
  $js_structure = array();
  // First, get all tasks. This corresponds to all types of page manager pages
  // that can be used, for for instance pages, node view, node edit...
  $tasks = page_manager_get_tasks();
  foreach ($tasks as $task) {
    // Subtasks are tasks that are created under the primary tasks, for instance
    // a custom page the user has created.
    $subtasks = page_manager_get_task_subtasks($task);
    // If we have subtasks, then that's what we're after.
    if (count($subtasks)) {
      foreach ($subtasks as $subtask) {
        // Subtasks have handlers. These can for instance correspond to a panel variant.
        $handlers = page_manager_load_task_handlers($task, $subtask['name']);
        foreach ($handlers as $handler) {
          // handlers have plugins, in this case we need to get the plugin for
          // this handler.
          $plugin = page_manager_get_task_handler($handler->handler);
          $title = page_manager_get_handler_title($plugin, $handler, $task, $subtask['name']);
          $available_handlers[$subtask['admin title']][$handler->name . ':'. $handler->task . ':'. $handler->subtask] = $title;

          // If we want to fetch the panes as well, then go ahead.
          if ($panes) {
            list($handler_panes, $pane_js) = _cache_actions_load_panes($handler, $title, TRUE);
            $available_panes += $handler_panes;
            $js_structure += $pane_js;
          }
        }
      }
    }
    // Otherwise let's use the task.
    else {
      $handlers = page_manager_load_task_handlers($task);
      if (count($handlers)) {
        foreach ($handlers as $handler) {
          $plugin = page_manager_get_task_handler($handler->handler);
          $title = page_manager_get_handler_title($plugin, $handler, $task, $subtask['name']);
          // If not, then we have an in-code display. Save off the name, so we can get it.
          $available_handlers[$task['admin title']][$handler->name . ':'. $handler->task] = $title;
          if ($panes) {
            list($handler_panes, $pane_js) = _cache_actions_load_panes($handler, $title, TRUE);
            $available_panes += $handler_panes;
            $js_structure += $pane_js;
          }
        }
      }
    }
  }
  // Return an array if we want the panes.
  if ($panes) {
    return array($available_handlers, $available_panes, $js_structure);
  }

  // Otherwise just return the handlers.
  return $available_handlers;
}

function _cache_actions_load_panes($handler, $handler_title, $js = FALSE) {
  ctools_include('plugins', 'panels');
  $available_panes = array();
  $js_panes = array();
  if (isset($handler->conf['did'])) {
    $display = panels_load_display($handler->conf['did']);
  }
  else {
    $display = $handler->conf['display'];
  }
  if (isset($display->content)) {
    foreach ($display->content as $pane) {
      if ($pane->cache['method'] == 'rules') {
        // We can't satisfy a context here, so we only get the title if no context is set.
        if (empty($pane->configuration['context'])) {
          $pane_title = panels_get_pane_title($pane);
        }
        else {
          $pane_title = $pane->subtype;
        }
        $available_panes[$handler_title][$pane->pid] = $pane_title;
        $js_panes[$handler->name . ':' . $handler->task . (!empty($handler->subtask) ? ':' . $handler->subtask : '')][$pane->pid] = $pane_title;
      }
    }
  }
  if ($js) {
    return array($available_panes, $js_panes);
  }
  return $available_panes;
}

function cache_actions_action_clear_panels_pane_cache_form($settings, &$form) {
  if (module_exists('panels') && module_exists('page_manager')) {
    drupal_add_js(drupal_get_path('module', 'cache_actions') . '/js/cache_actions.js');
    list($available_handlers, $available_panes, $js_structure) = _cache_actions_get_panels_handlers(TRUE);

    $js_settings['variants'] = $js_structure;
    drupal_add_js($js_settings, 'setting');

    $form['settings']['panel'] = array(
        '#type' => 'select',
        '#title' => t('Panel Variants'),
        '#options' => $available_handlers,
        '#default_value' => $settings['panel'],
        '#description' => t('The panel page to be cleared.
     Only panel pages which have caching enabled will be shown here.'),
    );

    $form['settings']['panes'] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#title' => t('Panel Panes'),
        '#options' => $available_panes,
        '#default_value' => $settings['panes'],
        '#description' => t('The panel page to be cleared.
     Only panel pages which have caching enabled will be shown here.'),
    );

    // Let's make sure the action can't be added if there are no applicable panel pages.
    if (!count($available_handlers)) {
      form_set_error('panel', t('This action is not applicable, since there are no panel pages with caching enabled.'));
      $form['submit']['#disabled'] = TRUE;
    }
  }
}

/**
 * The form for the clear mini panels cache action
 * @param array $settings
 * @param $form the form
 */
function cache_actions_action_clear_panels_mini_cache_form($settings, &$form) {
  if (module_exists('panels_mini')) {
    $available_panels = array();
    $mini_panels = panels_mini_load_all();

    foreach ($mini_panels as $mini_panel) {
      if ($mini_panel->display->cache['method'] != 'none') {
        $available_panels[$mini_panel->name] = $mini_panel->name;
      }
    }
    $form['settings']['panel'] = array(
      '#type' => 'select',
      '#title' => t('Mini Panel'),
      '#multiple' => TRUE,
      '#options' => $available_panels,
      '#default_value' => $settings['panel'],
      '#description' => t('The mini panel to be cleared.
       Only mini panels which have the simple cache enabled will be shown here.'),
    );

    // Let's make sure the action can't be added if there are no applicable mini panels.
    if (!count($available_panels)) {
      form_set_error('panel', t('This action is not applicable, since there are no mini panels with caching enabled.'));
      $form['submit']['#disabled'] = TRUE;
    }
  }
}

/**
 * The form for the clear mini panels cache action
 * @param array $settings
 * @param $form the form
 */
function cache_actions_action_clear_panels_mini_pane_cache_form($settings, &$form) {
  if (module_exists('panels_mini')) {
    drupal_add_js(drupal_get_path('module', 'cache_actions') . '/js/cache_actions.js');
    $available_panels = array();
    $available_panes = array();
    $js_structure = array();
    ctools_include('plugins', 'panels');
    $mini_panels = panels_mini_load_all();
    foreach ($mini_panels as $mini_panel) {
      $available_panels[$mini_panel->name] = $mini_panel->name;
      foreach ($mini_panel->display->content as $pane) {
        // The panes must have rule-based caching on in order for invalidation
        // to work properly.
        if ($pane->cache['method'] == 'rules') {
          $pane_title = panels_get_pane_title($pane);
          $available_panes[$mini_panel->name][$pane->pid] = $pane_title;
        }
      }
    }

    $js_settings['variants'] = $available_panes;
    drupal_add_js($js_settings, 'setting');

    $form['settings']['panel'] = array(
        '#type' => 'select',
        '#title' => t('Mini Panel'),
        '#multiple' => FALSE,
        '#options' => $available_panels,
        '#default_value' => $settings['panel'],
        '#required' => TRUE,
        '#description' => t('The mini panel to be cleared.
     Only mini panels which have the simple cache enabled will be shown here.'),
    );

    $form['settings']['panes'] = array(
        '#type' => 'select',
        '#title' => t('Panel pane'),
        '#multiple' => TRUE,
        '#required' => TRUE,
        '#options' => $available_panes,
        '#default_value' => $settings['panes'],
        '#description' => t('The mini panel to be cleared.
     Only mini panels which have the simple cache enabled will be shown here.'),
    );

    // Let's make sure the action can't be added if there are no applicable mini panels.
    if (!count($available_panels)) {
      form_set_error('panel', t('This action is not applicable, since there are no mini panels with caching enabled.'));
      $form['submit']['#disabled'] = TRUE;
    }
  }
}

function cache_actions_action_clear_varnish_page_form($settings, &$form) {
  $form['settings']['paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths'),
    '#default_value' => $settings['paths'],
    '#description' => t('Enter one page per line as Drupal paths,
      <front> is the front page. You can use regular expressions as understood
      by varnish on every line.'),
  );
}

/**
 * Clear the cache of the specified panel page.
 * @param int $did the display id
 */
function cache_actions_action_clear_panels_page_cache($handlers) {
  if (module_exists('page_manager') && module_exists('panels')) {
    // If this is an array, then this is one of the new rules.
    if (is_array($handlers)) {
      ctools_include('plugins', 'panels');
      foreach ($handlers as $handler) {
        if (is_numeric($handler)) {
          $display = panels_load_display($handler);
        }
        else {
          $display = _cache_actions_get_display_from_key($handler);
        }
        if (is_object($display)) {
          panels_clear_cached_content($display);
        }
        else {
          watchdog('cache_actions', "The panel variant %panel doesn't exist.
            You need to look over your rules and see if there's any rules
            involving that panel.", array('%panel' => $handler), WATCHDOG_ERROR);
        }
      }
    }
    // Otherwise we are dealing with a rule from 1.x
    else {
      $display = panels_load_display($handlers);
      if (is_object($display)) {
        panels_clear_cached_content($display);
      }
      else {
        watchdog('cache_actions', "The panel variant %panel doesn't exist.
            You need to look over your rules and see if there's any rules
            involving that panel.", array('%panel' => $handler), WATCHDOG_ERROR);
      }
    }
  }
}

/**
 * Get a display out of a key specified in the UI.
 * @param string $key the key
 * @return panels_display a display.
 */
function _cache_actions_get_display_from_key($key) {
  list($handler, $task, $subtask) = explode(':', $key);
  $task = page_manager_get_task($task);
  $handler = page_manager_load_task_handler($task, $subtask, $handler);
  // In-code handlers have the displays attached to them.
  if (isset($handler->conf['display'])) {
    $display = $handler->conf['display'];
  }
  // Otherwise we're dealing with a database display.
  elseif (isset($handler->conf['did'])) {
    $display = panels_load_display($handler->conf['did']);
  }
  _cache_actions_get_cache_key($handler, $display);
  return $display;
}

/**
 * Clear the cache of panes in a mini panel.
 * @param string $handler the handler
 * @param array $panes the panes to clear.
 */
function cache_actions_action_clear_panels_pane_cache($handler, $panes) {
  if (module_exists('page_manager')) {
    ctools_include('plugins', 'panels');
    if (!is_numeric($handler)) {
      $display = _cache_actions_get_display_from_key($handler);
    }
    else {
      $display = panels_load_display($handler);
    }
    if (is_array($panes) && isset($display->content)) {
      foreach ($panes as $pane_id) {
        foreach ($display->content as $pane) {
          if ($pane->pid == $pane_id && !empty($pane->cache['method'])) {
            _cache_actions_clear_pane_cache($pane, $display);
          }
        }
      }
    }
  }
}

/**
 * Create a unique cache key in the same way as panels does for it's
 * internal cache. This is a sure way to get unique cache ids for both
 * in-code displays and database displays.
 * @param $handler
 * @param $display
 */
function _cache_actions_get_cache_key($handler, &$display) {
  $task_name = page_manager_make_task_name($handler->task, $handler->subtask);
  $display->cache_key = 'panel_context:' . $task_name . ':' . $handler->name;
}

/**
 * Clear the content of a pane.
 * @param $pane the pane to clear
 * @param $display the display it belongs to.
 */
function _cache_actions_clear_pane_cache($pane, $display) {
  // Clearing panes can't be used with any other plugin than the rules plugin.
  if ($pane->cache['method'] == 'rules') {
    $function = panels_plugin_get_function('cache', $pane->cache['method'], 'cache clear');
    // Specify the pane to clear. This is specific for the rules plugin.
    $display->clear_pane = $pane;
    if ($function) {
      $function($display);
    }
  }
}

/**
 * Clear the cache of the specified mini panel.
 * @param array $mini_panels the name of the mini panels.
 */
function cache_actions_action_clear_panels_mini_cache($mini_panels) {
  if (module_exists('panels_mini')) {
    ctools_include('plugins', 'panels');
    foreach ($mini_panels as $name) {
      $panel = panels_mini_load($name);
      // Don't load a display if we already have it.
      if (isset($panel->display)) {
        $display = $panel->display;
      }
      else {
        $display = panels_load_display($panel->did);
      }
      if (is_object($display)) {
        panels_clear_cached_content($display);
      }
      else {
        watchdog('cache_actions', "The mini panel variant %panel doesn't exist.
          You need to look over your rules and see if there's any rules
          involving that panel.", array('%panel' => $display), WATCHDOG_ERROR);
      }
    }
  }
}

function cache_actions_action_clear_panels_mini_pane_cache($mini_panel, $panes) {
  if (module_exists('panels_mini')) {
    ctools_include('plugins', 'panels');
    $mini = panels_mini_load($mini_panel);
      if (is_object($mini)) {
      // We need to add the owner name, since this is included when it is cached.
      $mini->display->owner->id = $mini->name;
      foreach ($panes as $pid) {
        foreach ($mini->display->content as $pane) {
          if ($pane->pid == $pid) {
            _cache_actions_clear_pane_cache($pane, $mini->display);
          }
        }
      }
    }
    else {
      watchdog('cache_actions', "The mini panel %panel doesn't exist.
        You need to look over your rules and see if there's any rules
        involving that panel.", array('%panel' => $mini_panel), WATCHDOG_ERROR);
    }
  }
}

function cache_actions_action_clear_varnish_page($paths) {
  if (module_exists('varnish')) {
    $paths = preg_split("/(\r\n?|\n)/", $paths);
    // Since varnish don't understand things like <front>, we need to
    // Replace that with something it does understand. If <front> exists more than
    // once, we ignore it, since the cache will be cleared anyway.
    if (($key = array_search('<front>', $paths)) !== FALSE) {
      $paths[$key] = '';
    }
    varnish_expire_cache($paths);
  }
}

/**
 * Clear out the varnish cache completely.
 */
function cache_actions_action_clear_varnish_cache() {
  if (module_exists('varnish')) {
    varnish_flush_caches();
  }
}

/**
 * Action to clear cache configuration form.
 */
function cache_actions_action_clear_cache_form($settings, &$form) {
  $settings += array('tables' => '');
  $cache_bins = _cache_actions_get_cache_bins();
  $form['settings']['tables'] = array(
    '#type' => 'select',
    '#title' => t('Cache bins'),
    '#multiple' => TRUE,
    '#required' => TRUE,
    '#options' => $cache_bins,
    '#default_value' => $settings['tables'],
    '#description' => t('The cache bins to be cleared.'),
  );
}

/**
 * Action to clear cache cid configuration form.
 */
function cache_actions_action_clear_cache_cid_form($settings, &$form) {
  $cache_bins = _cache_actions_get_cache_bins();
  $form['settings']['table'] = array(
    '#type' => 'select',
    '#title' => t('Cache bin'),
    '#required' => TRUE,
    '#options' => $cache_bins,
    '#default_value' => $settings['table'],
    '#description' => t('The cache bins to be cleared.'),
  );

  $form['settings']['wildcard'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use wildcard'),
    '#default_value' => $settings['wildcard'],
  );
}

/**
 * Form for the clear view action.
 */
function cache_actions_action_clear_views_cache_form($settings, &$form) {
  $settings += array('view' => '');
  $views = views_get_all_views();

  $views_names = array();
  foreach ($views as $view) {
    $views_names[$view->name] = $view->name;
  }
  $form['settings']['view'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $views_names,
    '#default_value' => $settings['view'],
    '#title' => 'View',
  );
  // Let's make sure the action can't be added if there are no views.
  if (!count($views)) {
    form_set_error('view', t('This action is not applicable,
      since you don\'t have any views'));
    $form['submit']['#disabled'] = TRUE;
  }
}

/**
 * Form for the clear view action.
 */
function cache_actions_action_clear_views_display_cache_form($settings, &$form) {
  if (module_exists('views')) {
    $settings += array('displays' => '');
    $views = views_get_all_views();
    $displays = array();
    foreach ($views as $view) {
      $displays[$view->name] = array();
      foreach ($view->display as $display) {
        // Only list views that actually is shown.
        if ($display->id != 'default') {
          $displays[$view->name][$view->name . ':' . $display->id] = (!empty($display->title) ? $display->title : $display->id);
        }
      }
    }
    $form['settings']['displays'] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#options' => $displays,
        '#default_value' => $settings['displays'],
        '#description' => t('Select which displays you want to clear here.
    Note that this only works as expected when you use the
    rules cache plugin for views, otherwise the whole view will be
    cleared.'),
        '#title' => 'View',
    );
    // Let's make sure the action can't be added if there are no views.
    if (!count($views)) {
      form_set_error('view', t('This action is not applicable,
      since you don\'t have any views'));
      $form['submit']['#disabled'] = TRUE;
    }
  }
}

/**
 * This action clears the cache of a specific view.
 * @param array $views the views to clear.
 */
function cache_actions_action_clear_views_cache($views) {
  if (module_exists('views')) {
    views_include_handlers();
    module_load_include('inc', 'views', 'plugins/views_plugin_cache');
    // Is this an array?
    if (is_array($views)) {
      foreach ($views as $view) {
        _cache_actions_clear_view($view);
      }
    }
    else {
      // Otherwise it's probably an old rule from 1.x, let's just handle that.
      _cache_actions_clear_view($views);
    }
  }
}

/**
 * This action clears the cache of a specific view display.
 * @param array $views the views to clear.
 */
function cache_actions_action_clear_views_display_cache($views) {
  if (module_exists('views')) {
    $loaded_views = array();
    views_include_handlers();
    module_load_include('inc', 'views', 'plugins/views_plugin_cache');
    if (is_array($views)) {
      foreach ($views as $entry) {
        list($view_name, $display_id) = explode(':', $entry);
        // Let´s make sure we don't load views unnecessarily.
        if (!isset($loaded_views[$view_name])) {
          $loaded_views[$view_name] = views_get_view($view_name);
        }
        // Check to see that the display has a caching plugin. If it doesn't add the default caching plugin.
        $display = $loaded_views[$view_name]->display[$display_id];
        if (!isset($display->display_options['cache']['type'])) {
          $display->display_options['cache']['type'] = $loaded_views[$view_name]->display['default']->display_options['cache']['type'];
        }
        // And then clear the cache.
        _cache_actions_clear_view_display($loaded_views[$view_name], $display);
      }
    }
  }
}

/**
 * Clear out a view and it's displays.
 * @param string $view the view machine name
 */
function _cache_actions_clear_view($view) {
  $view = views_get_view($view);
  if (is_object($view)) {
    // Go through all displays and clear the cache.
    foreach ($view->display as $display) {
      // If we don't have our own cache plugin, then we need to copy
      // the cache settings from default.
      if (!isset($display->display_options['cache']) && isset($view->display['default'])) {
        $display->display_options['cache'] = $view->display['default']->display_options['cache'];
      }
      _cache_actions_clear_view_display($view, $display);
    }
  }
  else {
    watchdog('cache_actions', "The view %view doesn't exist.
    You need to look over your rules and see if there's any rules
    involving that view.", array('%view' => $handler), WATCHDOG_ERROR);
  }
}
/**
 * Clear out a specific display in a view.
 */
function _cache_actions_clear_view_display($view, $display) {
  // We use the cache plugin to clear the cache.
  $cache_plugin = views_get_plugin('cache', $display->display_options['cache']['type']);
  // If we have a cache plugin, then initiate it and flush the cache.
  if (isset($cache_plugin)) {
    $cache_plugin->init($view, $display);
    $cache_plugin->cache_flush();
  }
}
/**
 * This action that clears all cache tables specified.
 * @param $tables the tables to be cleared
 */
function cache_actions_action_clear_cache($tables) {
  $cache_tables = _cache_actions_get_cache_bins();

  // Support rules from 1.x.
  if (is_string($tables)) {
    $tables = explode(',', $tables);
  }

  foreach ($tables as $table) {
    if (in_array($table, $cache_tables)) {
      cache_clear_all('*', $table, TRUE);
    }
  }
}

/**
 * This action clears a specific cache sid in a cache bin.
 * @param $table the table where the cid should reside.
 * @param $cid the cache cid to clear
 * @param $wildcard wether or not to use wildcard invalidation.
 */
function cache_actions_action_clear_cache_cid($table, $cid, $wildcard) {
  cache_clear_all($cid, $table, $wildcard);
}

/**
 * This action clears the css and js cache.
 */
function cache_actions_action_clear_css_js_cache() {
  // Change query-strings on css/js files to enforce reload for all users.
  _drupal_flush_css_js();
  drupal_clear_js_cache();
  drupal_clear_css_cache();
}

/**
 * Get all cache bins available.
 */
function _cache_actions_get_cache_bins() {
  $cache_bins = array('cache' => 'cache', 'cache_block' => 'cache_block',
    'cache_filter' => 'cache_filter', 'cache_page' => 'cache_page');
  foreach (module_invoke_all('flush_caches') as $cache_bin) {
    $cache_bins[$cache_bin] = $cache_bin;
  }
  return $cache_bins;
}
