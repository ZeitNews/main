<?php

/**
 * Implementation of hook_content_default_fields().
 */
function op_article_content_default_fields() {
  $fields = array();

  // Exported field: field_deck
  $fields['article-field_deck'] = array(
    'field_name' => 'field_deck',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '-4',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
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
          '_error_element' => 'default_value_widget][field_deck][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Deck',
      'weight' => '-4',
      'description' => 'A small headline running below the main headline; also called a drop head.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_main_image
  $fields['article-field_main_image'] = array(
    'field_name' => 'field_main_image',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '5',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
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
      '0' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      '1' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
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
    'description_field' => '0',
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
      'custom_title' => 1,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'imagecrop' => 1,
      'imagecrop_presets' => array(
        '400xY' => '400xY',
      ),
      'filefield_sources' => array(
        'remote' => 'remote',
        'imce' => 'imce',
        'reference' => 0,
      ),
      'filefield_source_autocomplete' => NULL,
      'filefield_source_attach_path' => NULL,
      'filefield_source_attach_absolute' => NULL,
      'filefield_source_attach_mode' => NULL,
      'label' => 'Main Image',
      'weight' => '4',
      'description' => 'Appears at the top of detail pages and as a thumbnail on list pages.',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_main_image_credit
  $fields['article-field_main_image_credit'] = array(
    'field_name' => 'field_main_image_credit',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '7',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
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
          '_error_element' => 'default_value_widget][field_main_image_credit][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Main Image Credit',
      'weight' => '6',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_op_author
  $fields['article-field_op_author'] = array(
    'field_name' => 'field_op_author',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
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
      'slideshow' => 0,
      'topichub' => 0,
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
      'weight' => '-2',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_op_documentcloud_doc
  $fields['article-field_op_documentcloud_doc'] = array(
    'field_name' => 'field_op_documentcloud_doc',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '2',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
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
    'type' => 'document_cloud_doc',
    'required' => '0',
    'multiple' => '1',
    'module' => 'document_cloud',
    'active' => '1',
    'viewer_height' => '600',
    'viewer_width' => '980',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
          '_error_element' => 'value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'DocumentCloud Document',
      'weight' => '2',
      'description' => 'Create a link to a DocumentCloud document and allow users to view it on your site.  Example: http://www.documentcloud.org/documents/<document id>.html.',
      'type' => 'document_cloud_doc',
      'module' => 'document_cloud',
    ),
  );

  // Exported field: field_op_related_mmedia
  $fields['article-field_op_related_mmedia'] = array(
    'field_name' => 'field_op_related_mmedia',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '8',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
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
      'audio' => 'audio',
      'op_image' => 'op_image',
      'slideshow' => 'slideshow',
      'video' => 'video',
      'article' => 0,
      'author' => 0,
      'blog' => 0,
      'event' => 0,
      'feed' => 0,
      'feeditem' => 0,
      'package' => 0,
      'page' => 0,
      'panel' => 0,
      'resource' => 0,
      'topichub' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_op_related_mmedia][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Related Multimedia',
      'weight' => '7',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_related_content
  $fields['article-field_related_content'] = array(
    'field_name' => 'field_related_content',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '9',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
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
      'blog' => 'blog',
      'audio' => 0,
      'author' => 0,
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
          '_error_element' => 'default_value_widget][field_related_content][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Related Content',
      'weight' => '8',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_show_author_info
  $fields['article-field_show_author_info'] = array(
    'field_name' => 'field_show_author_info',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '3',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
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
    'allowed_values' => '0
Show Author Info?',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 0,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Show Author Info?',
      'weight' => '3',
      'description' => 'Show author information (such as name, picture and bio) after the article. (The author must be a site user with profile information.)',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_teaser
  $fields['article-field_teaser'] = array(
    'field_name' => 'field_teaser',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '4',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
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
          '_error_element' => 'default_value_widget][field_teaser][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Teaser',
      'weight' => 0,
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_thumbnail_image
  $fields['article-field_thumbnail_image'] = array(
    'field_name' => 'field_thumbnail_image',
    'type_name' => 'article',
    'display_settings' => array(
      'weight' => '6',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 1,
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
    'description_field' => '0',
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
      'filefield_source_autocomplete' => NULL,
      'filefield_source_attach_path' => NULL,
      'filefield_source_attach_absolute' => NULL,
      'filefield_source_attach_mode' => NULL,
      'label' => 'Thumbnail Image',
      'weight' => '5',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Author(s)');
  t('Deck');
  t('DocumentCloud Document');
  t('Main Image');
  t('Main Image Credit');
  t('Related Content');
  t('Related Multimedia');
  t('Show Author Info?');
  t('Teaser');
  t('Thumbnail Image');

  return $fields;
}
