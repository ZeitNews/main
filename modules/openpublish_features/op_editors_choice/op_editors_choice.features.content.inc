<?php

/**
 * Implementation of hook_content_default_fields().
 */
function op_editors_choice_content_default_fields() {
  $fields = array();

  // Exported field: field_ec_featured_nodes
  $fields['editors_choice-field_ec_featured_nodes'] = array(
    'field_name' => 'field_ec_featured_nodes',
    'type_name' => 'editors_choice',
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
      'page' => 'page',
      'resource' => 'resource',
      'slideshow' => 'slideshow',
      'video' => 'video',
      'author' => 0,
      'editors_choice' => 0,
      'feed' => 0,
      'feeditem' => 0,
      'op_image' => 0,
      'package' => 0,
      'panel' => 0,
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
          '_error_element' => 'default_value_widget][field_ec_featured_nodes][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Featured Node',
      'weight' => '6',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Featured Node');

  return $fields;
}
