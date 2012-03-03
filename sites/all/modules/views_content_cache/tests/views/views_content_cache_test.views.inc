<?php

/**
 * Implementation of hook_views_plugins().
 */
function views_content_cache_test_views_plugins() {
  return array(
    'cache' => array(
      'views_content_cache_test' => array(
        'path' => drupal_get_path('module', 'views_content_cache_test') . '/views',
        'title' => t('Content-based'),
        'help' => t('Advanced content based caching options for views.'),
        'handler' => 'views_content_cache_test_plugin_cache',
        'parent' => 'views_content_cache',
        'uses options' => TRUE,
      ),
    ),
  );
}
