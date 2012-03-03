<?php

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _op_slideshow_content_default_fields() {
  $fields = array();

  // Exported field: field_op_author
  $fields[] = array(
    'field_name' => 'field_op_author',
    'type_name' => 'slideshow',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'author' => 'author',
      'article' => 0,
      'audio' => 0,
      'blog' => 0,
      'event' => 0,
      'feed' => 0,
      'feeditem' => 0,
      'op_image' => 0,
      'package' => 0,
      'page' => 0,
      'panel' => 0,
      'resource' => 0,
      'topichub' => 0,
      'twitter_item' => 0,
      'video' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_op_author][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Author(s)',
      'weight' => '-3',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_op_slideshow_images
  $fields[] = array(
    'field_name' => 'field_op_slideshow_images',
    'type_name' => 'slideshow',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'op_image' => 'op_image',
      'article' => 0,
      'audio' => 0,
      'author' => 0,
      'blog' => 0,
      'event' => 0,
      'feed' => 0,
      'feeditem' => 0,
      'package' => 0,
      'page' => 0,
      'panel' => 0,
      'resource' => 0,
      'slideshow' => 0,
      'topichub' => 0,
      'twitter_item' => 0,
      'video' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_op_slideshow_images][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Gallery Images',
      'weight' => 0,
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_op_slideshow_thumb
  $fields[] = array(
    'field_name' => 'field_op_slideshow_thumb',
    'type_name' => 'slideshow',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '0',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'imagecrop' => NULL,
      'imagecrop_presets' => NULL,
      'label' => 'Thumbnail',
      'weight' => '-2',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_teaser
  $fields[] = array(
    'field_name' => 'field_teaser',
    'type_name' => 'slideshow',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '1',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '5',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          'format' => '1',
          '_error_element' => 'default_value_widget][field_teaser][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Teaser',
      'weight' => '1',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Translatables
  array(
    t('Author(s)'),
    t('Gallery Images'),
    t('Teaser'),
    t('Thumbnail'),
  );

  return $fields;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _op_slideshow_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "noderelationships" && $api == "default_node_relationships") {
    return array("version" => 1);
  }
  else if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_imagecache_default_presets().
 */
function _op_slideshow_imagecache_default_presets() {
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
 * Helper to implementation of hook_noderelationships_default_settings().
 */
function _op_slideshow_noderelationships_default_settings() {
  $export = array();
  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'slideshow';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_op_author';
  $noderelationships_default_setting->settings = 'a:3:{s:25:"search_and_reference_view";s:36:"noderelationships_noderef:page_table";s:20:"create_and_reference";s:15:"field_op_author";s:23:"translate_and_reference";s:15:"field_op_author";}';
  $noderelationships_default_setting->export_key = 'slideshow__field_op_author';
  $export['slideshow__field_op_author'] = $noderelationships_default_setting;

  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'slideshow';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_op_slideshow_images';
  $noderelationships_default_setting->settings = 'a:3:{s:25:"search_and_reference_view";s:36:"noderelationships_noderef:page_table";s:20:"create_and_reference";s:25:"field_op_slideshow_images";s:23:"translate_and_reference";s:25:"field_op_slideshow_images";}';
  $noderelationships_default_setting->export_key = 'slideshow__field_op_slideshow_images';
  $export['slideshow__field_op_slideshow_images'] = $noderelationships_default_setting;

  return $export;
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _op_slideshow_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_slideshow';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
    '2' => 'premium',
  );

  $export['node_options_slideshow'] = $strongarm;
  return $export;
}
