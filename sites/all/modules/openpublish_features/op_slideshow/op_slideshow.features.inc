<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_slideshow_ctools_plugin_api() {
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
 * Implementation of hook_imagecache_default_presets().
 */
function op_slideshow_imagecache_default_presets() {
  $items = array(
    'slideshow_image' => array(
      'presetname' => 'slideshow_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '490',
            'height' => '300',
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
function op_slideshow_node_info() {
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

/**
 * Implementation of hook_views_api().
 */
function op_slideshow_views_api() {
  return array(
    'api' => '2',
  );
}
