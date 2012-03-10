<?php

/**
 * @file
 * This file contains the rules for the testing.
 */

/**
 * Implementation of hook_rules_defaults().
 * Below are the rules needed for the testing.
 */
function cache_actions_test_rules_defaults() {
  return array(
    'rules' =>
      array(
        'rules_cache_actions_test_clear_cid' =>
          array(
            '#type' => 'rule',
            '#set' => 'event_node_presave',
            '#label' => 'Cache Actions Test Clear Cache Cid',
            '#active' => 1,
            '#weight' => '0',
            '#categories' =>
            array('Cache Actions Tests'),
            '#status' => 'default',
            '#conditions' =>
            array(),
            '#actions' =>
            array(
              array(
                '#type' => 'action',
                '#settings' =>
                array(
                  'table' => 'cache_cache_actions_test',
                  'cid' => 'dummy',
                  'wildcard' => 0,
                ),
                '#name' => 'cache_actions_action_clear_cache_cid',
                '#info' =>
                array(
                  'label' => 'Clear a specific cache cid',
                  'arguments' =>
                  array(
                    'table' =>
                    array(
                      'type' => 'string',
                      'label' => 'Cache tables',
                      'description' => 'The cache table where the cid is',
                    ),
                    'cid' =>
                    array(
                      'type' => 'string',
                      'label' => 'Cache cid',
                      'description' => 'The cid to clear',
                    ),
                    'wildcard' =>
                    array(
                      'type' => 'boolean',
                      'label' => 'Use wildcard',
                      'description' => 'Use wildcards. This means you will be clearing all cids that partially matches.',
                    ),
                  ),
                  'module' => 'Cache Actions',
                ),
                '#weight' => 0,
              ),
            ),
            '#version' => 6003,
          ),
      'rules_cache_actions_test_clear_panel_pane' =>
        array(
          '#type' => 'rule',
          '#set' => 'event_node_presave',
          '#label' => 'Cache Actions Test Clear Panel Pane',
          '#active' => 1,
          '#weight' => '0',
          '#categories' =>
          array(
            0 => 'Cache Actions Tests',
          ),
          '#status' => 'default',
          '#version' => 6003,
          '#conditions' =>
          array(
          ),
          '#actions' =>
          array(
            0 =>
            array(
              '#type' => 'action',
              '#settings' =>
              array(
                'panel' => 'page_cache_actions_test_panel_pane_panel_context:page:cache_actions_test_panel_pane',
                'panes' =>
                array(
                  'new-1' => 'new-1',
                ),
              ),
              '#name' => 'cache_actions_action_clear_panels_pane_cache',
              '#info' =>
              array(
                'label' => 'Clear the cache for panel page panes',
                'arguments' =>
                array(
                  'panel' =>
                  array(
                    'type' => 'string',
                    'label' => 'Panel page',
                    'description' => 'Specify the panel page you want to clear.',
                  ),
                  'panes' =>
                  array(
                    'type' => 'string',
                    'label' => 'Panel page',
                    'description' => 'The pane to clear',
                  ),
                ),
                'module' => 'Cache Actions',
              ),
              '#weight' => 0,
            ),
          ),
        ),
      'rules_cache_actions_test_clear_css_js' =>
      array(
        '#type' => 'rule',
        '#set' => 'event_node_presave',
        '#label' => 'Cache Actions Test Clear css and js',
        '#active' => 1,
        '#weight' => '0',
        '#categories' =>
        array(
          0 => 'Cache Actions Tests',
        ),
        '#status' => 'default',
        '#conditions' =>
        array(
        ),
        '#actions' =>
        array(
          0 =>
          array(
            '#weight' => 0,
            '#info' =>
            array(
              'label' => 'Clear the css and js cache',
              'module' => 'Cache Actions',
            ),
            '#name' => 'cache_actions_action_clear_css_js_cache',
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_cache_actions_test_clear_bin' =>
        array(
          '#type' => 'rule',
          '#set' => 'event_node_presave',
          '#label' => 'Cache Actions Test Clear Bin',
          '#active' => 1,
          '#weight' => '0',
          '#categories' =>
          array(
            0 => 'Cache Actions Tests',
          ),
          '#status' => 'default',
          '#conditions' =>
          array(
          ),
          '#actions' =>
          array(
            array(
              '#weight' => 0,
              '#type' => 'action',
              '#settings' =>
              array(
                'tables' =>
                array(
                  'cache_cache_actions_test' => 'cache_cache_actions_test',
                ),
              ),
              '#name' => 'cache_actions_action_clear_cache',
              '#info' =>
              array(
                'label' => 'Clear cache bins',
                'arguments' =>
                array(
                  'tables' =>
                  array(
                    'type' => 'string',
                    'label' => 'Cache tables',
                    'description' => 'Specify which cache tables you want to clear here. Separate the tables with spaces. You can use * to clear all tables',
                  ),
                ),
                'module' => 'Cache Actions',
              ),
            ),
          ),
          '#version' => 6003,
        ),
      'rules_cache_actions_test_clear_mini_panel_pane' =>
        array(
          '#type' => 'rule',
          '#set' => 'event_node_presave',
          '#label' => 'Cache Actions Test Clear Mini Panel Pane',
          '#active' => 1,
          '#weight' => '0',
          '#categories' =>
          array(
            0 => 'Cache Actions Tests',
          ),
          '#status' => 'default',
          '#conditions' =>
          array(
          ),
          '#actions' =>
          array(
            array(
              '#weight' => 0,
              '#info' =>
              array(
                'label' => 'Clear the cache of mini panel panes',
                'arguments' =>
                array(
                  'panel' =>
                  array(
                    'type' => 'string',
                    'label' => 'Panel page',
                    'description' => 'Specify the mini panel you want to clear.',
                  ),
                  'panes' =>
                  array(
                    'type' => 'string',
                    'label' => 'Panel panes',
                    'description' => 'Specify the mini panes you want to clear.',
                  ),
                ),
                'module' => 'Cache Actions',
              ),
              '#name' => 'cache_actions_action_clear_panels_mini_pane_cache',
              '#settings' =>
              array(
                'panel' => 'cache_actions_test_mini_panel_pane',
                'panes' =>
                array(
                  'new-1' => 'new-1',
                ),
              ),
              '#type' => 'action',
            ),
          ),
          '#version' => 6003,
        ),
      'rules_cache_actions_test_clear_mini_panel' =>
        array(
          '#type' => 'rule',
          '#set' => 'event_node_presave',
          '#label' => 'Cache Actions Test Clear Mini Panel',
          '#active' => 1,
          '#weight' => '0',
          '#categories' =>
          array('Cache Actions Tests'),
          '#status' => 'default',
          '#conditions' =>
          array(),
          '#actions' =>
          array(
            array(
              '#weight' => 0,
              '#info' =>
              array(
                'label' => 'Clear the cache of a specific mini panel',
                'arguments' =>
                array(
                  'panel' =>
                  array(
                    'type' => 'string',
                    'label' => 'Panel page',
                    'description' => 'Specify the mini panel you want to clear.',
                  ),
                ),
                'module' => 'Cache Actions',
              ),
              '#name' => 'cache_actions_action_clear_panels_mini_cache',
              '#settings' =>
              array(
                'panel' =>
                array(
                  'cache_actions_test_mini_panel' => 'cache_actions_test_mini_panel',
                ),
              ),
              '#type' => 'action',
            ),
          ),
          '#version' => 6003,
        ),
      'rules_cache_actions_test_clear_panel' =>
        array(
          '#type' => 'rule',
          '#set' => 'event_node_presave',
          '#label' => 'Cache Actions Test Clear Panel',
          '#active' => 1,
          '#weight' => '0',
          '#categories' =>
          array('Cache Actions Tests'),
          '#status' => 'default',
          '#conditions' =>
          array(),
          '#actions' =>
          array(
            array(
              '#weight' => 0,
              '#info' =>
              array(
                'label' => 'Clear the cache of panel page variants',
                'arguments' =>
                array(
                  'panel' =>
                  array(
                    'type' => 'string',
                    'label' => 'Panel page',
                    'description' => 'Specify the panel page you want to clear.',
                  ),
                ),
                'module' => 'Cache Actions',
              ),
              '#name' => 'cache_actions_action_clear_panels_page_cache',
              '#settings' =>
              array(
                'panel' =>
                array(
                  'page_cache_actions_test_panel_panel_context:page:cache_actions_test_panel' => 'page_cache_actions_test_panel_panel_context:page:cache_actions_test_panel',
                ),
              ),
              '#type' => 'action',
            ),
          ),
          '#version' => 6003,
        ),
      'rules_cache_actions_test_clear_view' =>
        array(
          '#type' => 'rule',
          '#set' => 'event_node_presave',
          '#label' => 'Cache Actions Test Clear View',
          '#active' => 1,
          '#weight' => '0',
          '#categories' =>
          array(
            0 => 'Cache Actions Tests',
          ),
          '#status' => 'default',
          '#conditions' =>
          array(
          ),
          '#actions' =>
          array(
            array(
              '#weight' => 0,
              '#info' =>
              array(
                'label' => 'Clear the cache of specific views',
                'arguments' =>
                array(
                  'view' =>  array(
                    'type' => 'string',
                    'label' => 'View',
                    'description' => 'Specify the views you want to clear.',
                  ),
                ),
                'module' => 'Cache Actions',
              ),
            '#name' => 'cache_actions_action_clear_views_cache',
            '#settings' => array(
              'view' => array(
                'cache_actions_test_view' => 'cache_actions_test_view',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}
