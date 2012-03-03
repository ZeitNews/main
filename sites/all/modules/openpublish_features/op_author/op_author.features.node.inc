<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _op_author_node_info() {
  $items = array(
    'author' => array(
      'name' => t('Author'),
      'module' => 'features',
      'description' => t('Author can be associated with a Drupal user, but can also be a contributing author that does not have Drupal login to your website.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'has_body' => '1',
      'body_label' => t('Bio'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
