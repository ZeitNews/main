<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_image_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function op_image_node_info() {
  $items = array(
    'op_image' => array(
      'name' => t('Image'),
      'module' => 'features',
      'description' => t('Images can be uploaded into the CMS and used in a variety of capacities.'),
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
