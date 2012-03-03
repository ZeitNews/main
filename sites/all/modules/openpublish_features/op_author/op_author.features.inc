<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_author_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function op_author_imagecache_default_presets() {
  $items = array(
    'author_photo' => array(
      'presetname' => 'author_photo',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecrop',
          'action' => 'imagecrop_javascript',
          'data' => array(
            'width' => '70',
            'height' => '70',
            'xoffset' => 'center',
            'yoffset' => 'center',
            'resizable' => 1,
            'disable_if_no_data' => 1,
          ),
        ),
        '1' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '70',
            'height' => '',
            'upscale' => 1,
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function op_author_node_info() {
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

/**
 * Implementation of hook_views_api().
 */
function op_author_views_api() {
  return array(
    'api' => '2',
  );
}
