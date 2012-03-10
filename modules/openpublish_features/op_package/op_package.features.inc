<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_package_ctools_plugin_api() {
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
function op_package_node_info() {
  $items = array(
    'package' => array(
      'name' => t('Package'),
      'module' => 'features',
      'description' => t('News packages are sets of topical information based around one relevant event or topic. Examples might include an election, or coverage of the war in Iraq.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
