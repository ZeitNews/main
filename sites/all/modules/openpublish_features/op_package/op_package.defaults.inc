<?php

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _op_package_content_default_fields() {
  $fields = array();

  // Exported field: field_center_intro
  $fields[] = array(
    'field_name' => 'field_center_intro',
    'type_name' => 'package',
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
          '_error_element' => 'default_value_widget][field_center_intro][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Intro Text',
      'weight' => '23',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_center_main_image
  $fields[] = array(
    'field_name' => 'field_center_main_image',
    'type_name' => 'package',
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
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => 'jpg jpeg png gif',
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
      'imagecrop' => 0,
      'imagecrop_presets' => array(
        'author_photo' => 0,
      ),
      'filefield_sources' => array(
        'remote' => 'remote',
        'imce' => 'imce',
        'reference' => 0,
      ),
      'label' => 'Main Image',
      'weight' => '24',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_center_related
  $fields[] = array(
    'field_name' => 'field_center_related',
    'type_name' => 'package',
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
    'multiple' => '3',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'article' => 'article',
      'audio' => 'audio',
      'blog' => 'blog',
      'event' => 'event',
      'resource' => 'resource',
      'video' => 'video',
      'feed' => 0,
      'feeditem' => 0,
      'op_image' => 0,
      'package' => 0,
      'page' => 0,
      'story' => 0,
      'topichub' => 0,
      'twitter_item' => 0,
      'panel' => FALSE,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => NULL,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_center_related][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Related Content',
      'weight' => '27',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_center_title
  $fields[] = array(
    'field_name' => 'field_center_title',
    'type_name' => 'package',
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
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_center_title][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Column Title',
      'weight' => '22',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_embedded_audio
  $fields[] = array(
    'field_name' => 'field_embedded_audio',
    'type_name' => 'package',
    'display_settings' => array(
      'weight' => '-4',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
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
    'type' => 'emaudio',
    'required' => '0',
    'multiple' => '0',
    'module' => 'emaudio',
    'active' => '1',
    'widget' => array(
      'audio_width' => '425',
      'audio_height' => '350',
      'audio_autoplay' => '',
      'preview_width' => '425',
      'preview_height' => '350',
      'preview_autoplay' => '',
      'thumbnail_width' => '120',
      'thumbnail_height' => '90',
      'thumbnail_default_path' => '',
      'providers' => array(
        '1' => 1,
        '0' => 1,
        'custom_url' => FALSE,
        'odeo' => FALSE,
        'podcastalley' => FALSE,
        'podomatic' => FALSE,
      ),
      'default_value' => array(
        '0' => array(
          'embed' => '',
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Embedded Audio',
      'weight' => '-2',
      'description' => '',
      'type' => 'emaudio_textfields',
      'module' => 'emaudio',
    ),
  );

  // Exported field: field_embedded_video
  $fields[] = array(
    'field_name' => 'field_embedded_video',
    'type_name' => 'package',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
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
    'type' => 'emvideo',
    'required' => '0',
    'multiple' => '0',
    'module' => 'emvideo',
    'active' => '1',
    'widget' => array(
      'video_width' => '425',
      'video_height' => '350',
      'video_autoplay' => '',
      'preview_width' => '425',
      'preview_height' => '350',
      'preview_autoplay' => '',
      'thumbnail_width' => '120',
      'thumbnail_height' => '90',
      'thumbnail_default_path' => '',
      'thumbnail_link_title' => 'See video',
      'providers' => array(
        '1' => 1,
        '0' => 1,
        'archive' => FALSE,
        'ustream' => FALSE,
        'ustreamlive' => FALSE,
        'yahoomusic' => FALSE,
        'youtube' => FALSE,
        'zzz_custom_url' => FALSE,
      ),
      'default_value' => array(
        '0' => array(
          'embed' => '',
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Embedded Video',
      'weight' => '25',
      'description' => '',
      'type' => 'emvideo_textfields',
      'module' => 'emvideo',
    ),
  );

  // Exported field: field_left_intro
  $fields[] = array(
    'field_name' => 'field_left_intro',
    'type_name' => 'package',
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
          '_error_element' => 'default_value_widget][field_left_intro][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Intro Text',
      'weight' => '20',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_left_related
  $fields[] = array(
    'field_name' => 'field_left_related',
    'type_name' => 'package',
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
      'article' => 'article',
      'audio' => 'audio',
      'blog' => 'blog',
      'event' => 'event',
      'resource' => 'resource',
      'video' => 'video',
      'feed' => 0,
      'feeditem' => 0,
      'op_image' => 0,
      'package' => 0,
      'page' => 0,
      'story' => 0,
      'topichub' => 0,
      'twitter_item' => 0,
      'panel' => FALSE,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => NULL,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_left_related][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Related Content',
      'weight' => '21',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_right_intro
  $fields[] = array(
    'field_name' => 'field_right_intro',
    'type_name' => 'package',
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
          '_error_element' => 'default_value_widget][field_right_intro][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Intro Text',
      'weight' => '20',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_right_related
  $fields[] = array(
    'field_name' => 'field_right_related',
    'type_name' => 'package',
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
      'article' => 'article',
      'audio' => 'audio',
      'blog' => 'blog',
      'event' => 'event',
      'resource' => 'resource',
      'video' => 'video',
      'feed' => 0,
      'feeditem' => 0,
      'op_image' => 0,
      'package' => 0,
      'page' => 0,
      'story' => 0,
      'topichub' => 0,
      'twitter_item' => 0,
      'panel' => FALSE,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => NULL,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_right_related][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Related Content',
      'weight' => '21',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Translatables
  array(
    t('Column Title'),
    t('Embedded Audio'),
    t('Embedded Video'),
    t('Intro Text'),
    t('Main Image'),
    t('Related Content'),
  );

  return $fields;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _op_package_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "noderelationships" && $api == "default_node_relationships") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_noderelationships_default_settings().
 */
function _op_package_noderelationships_default_settings() {
  $export = array();
  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'package';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_center_related';
  $noderelationships_default_setting->settings = 'a:2:{s:25:"search_and_reference_view";s:35:"noderelationships_noderef:page_grid";s:20:"create_and_reference";s:20:"field_center_related";}';
  $noderelationships_default_setting->export_key = 'package__field_center_related';
  $export['package__field_center_related'] = $noderelationships_default_setting;

  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'package';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_left_related';
  $noderelationships_default_setting->settings = 'a:2:{s:25:"search_and_reference_view";s:35:"noderelationships_noderef:page_grid";s:20:"create_and_reference";s:18:"field_left_related";}';
  $noderelationships_default_setting->export_key = 'package__field_left_related';
  $export['package__field_left_related'] = $noderelationships_default_setting;

  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'package';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_right_related';
  $noderelationships_default_setting->settings = 'a:2:{s:25:"search_and_reference_view";s:35:"noderelationships_noderef:page_grid";s:20:"create_and_reference";s:19:"field_right_related";}';
  $noderelationships_default_setting->export_key = 'package__field_right_related';
  $export['package__field_right_related'] = $noderelationships_default_setting;

  return $export;
}
