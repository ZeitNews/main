<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _op_audio_node_info() {
  $items = array(
    'audio' => array(
      'name' => t('Audio'),
      'module' => 'features',
      'description' => t('Audio content can be entered by referencing an external source, or by uploading a local audio file into the CMS.'),
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
