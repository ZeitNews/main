<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _op_videos_node_info() {
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
