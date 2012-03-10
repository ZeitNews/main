<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_resource_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "noderelationships" && $api == "default_node_relationships") {
    return array("version" => 1);
  }
  elseif ($module == "noderelationships" && $api == "noderelationships") {
    return array("version" => 1);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function op_resource_node_info() {
  $items = array(
    'resource' => array(
      'name' => t('Resource'),
      'module' => 'features',
      'description' => t('Resources are links, files, documents and other items of interest to readers. This content type is intended to provide a flexible mechanism for providing content that doesn\'t fit other content types, and can be differentiated from others via flexible categorization.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function op_resource_views_api() {
  return array(
    'api' => '2',
  );
}
