<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _op_slideshow_node_info() {
  $items = array(
    'slideshow' => array(
      'name' => t('Slideshow'),
      'module' => 'features',
      'description' => t('Slideshow is a content type that contains a set of images.'),
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
