<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_editors_choice_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function op_editors_choice_node_info() {
  $items = array(
    'editors_choice' => array(
      'name' => t('Editor\'s Choice'),
      'module' => 'features',
      'description' => t('This type of content can be created for display as a block on the Homepage, right sidebar and other sections.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Custom HTML'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function op_editors_choice_views_api() {
  return array(
    'api' => '2',
  );
}
