<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _op_image_node_info() {
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
