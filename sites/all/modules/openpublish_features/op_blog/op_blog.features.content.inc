<?php

/**
 * Implementation of hook_content_default_fields().
 */
function op_blog_content_default_fields() {
  $fields = array();

  // Exported field: field_op_author
  $fields['blog-field_op_author'] = array(
    'field_name' => 'field_op_author',
    'type_name' => 'blog',
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
      'weight' => '-4',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_op_documentcloud_doc
  $fields['blog-field_op_documentcloud_doc'] = array(
    'field_name' => 'field_op_documentcloud_doc',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => '1',
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

  // Exported field: field_show_author_info
  $fields['blog-field_show_author_info'] = array(
    'field_name' => 'field_show_author_info',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => '-1',
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
      'weight' => '-1',
      'description' => 'Show author information (such as name, picture and bio) after the article. (The author must be a site user with profile information.)',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_teaser
  $fields['blog-field_teaser'] = array(
    'field_name' => 'field_teaser',
    'type_name' => 'blog',
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
          'format' => '2',
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

  // Translatables
  // Included for use with string extractors like potx.
  t('Author(s)');
  t('DocumentCloud Document');
  t('Show Author Info?');
  t('Teaser');

  return $fields;
}
