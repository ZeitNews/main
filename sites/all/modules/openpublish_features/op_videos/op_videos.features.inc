<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_videos_ctools_plugin_api() {
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
function op_videos_node_info() {
  $items = array(
    'video' => array(
      'name' => t('Video'),
      'module' => 'features',
      'description' => t('Video content can be entered by referencing an external source, like YouTube, or by uploading a local video file into the CMS.'),
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
