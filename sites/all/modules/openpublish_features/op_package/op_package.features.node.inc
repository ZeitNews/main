<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _op_package_node_info() {
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
