<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_defaults_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function op_defaults_imagecache_default_presets() {
  $items = array(
    '400xY' => array(
      'presetname' => '400xY',
      'actions' => array(
        '0' => array(
          'weight' => '-1',
          'module' => 'imagecrop',
          'action' => 'imagecrop_javascript',
          'data' => array(
            'width' => '400',
            'height' => '200',
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
            'width' => '400',
            'height' => '',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'featured_image' => array(
      'presetname' => 'featured_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '200',
            'height' => '',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'package_featured' => array(
      'presetname' => 'package_featured',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '425',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'spotlight_homepage' => array(
      'presetname' => 'spotlight_homepage',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '345',
            'height' => '',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'thumbnail' => array(
      'presetname' => 'thumbnail',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '100',
            'height' => '',
            'upscale' => 1,
          ),
        ),
      ),
    ),
  );
  return $items;
}
