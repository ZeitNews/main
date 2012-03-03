<?php

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _op_imagecrop_config_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _op_imagecrop_config_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imagecrop_field_presets';
  $strongarm->value = array(
    'field_thumbnail_image' => array(
      '0' => 'thumbnail',
    ),
    'field_author_photo' => array(
      '0' => 'author_photo',
    ),
    'field_main_image' => array(
      '0' => '400xY',
      '1' => 'spotlight_homepage',
      '2' => 'thumbnail',
    ),
    'field_op_slideshow_thumb' => array(
      '0' => 'thumbnail',
    ),
    'field_associate_photo' => array(
      '0' => 'author_photo',
    ),
    'field_media_thumbnail' => array(
      '0' => 'thumbnail',
    ),
    'field_promo_image' => array(
      '0' => 'promo',
    ),
  );

  $export['imagecrop_field_presets'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imagecrop_fields';
  $strongarm->value = array(
    '7' => 'field_thumbnail_image',
    '9' => 'field_main_image',
    '10' => 'field_op_slideshow_thumb',
    '11' => 'field_associate_photo',
    '16' => 'field_promo_image',
    '17' => 'field_media_thumbnail',
    '18' => 'field_author_photo',
  );

  $export['imagecrop_fields'] = $strongarm;
  return $export;
}
