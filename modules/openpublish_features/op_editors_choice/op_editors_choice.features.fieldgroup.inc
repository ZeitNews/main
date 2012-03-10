<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function op_editors_choice_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_ec_featured_nodes
  $groups['editors_choice-group_ec_featured_nodes'] = array(
    'group_type' => 'standard',
    'type_name' => 'editors_choice',
    'group_name' => 'group_ec_featured_nodes',
    'label' => 'Featured Nodes',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => 'Note: if any custom HTML is entered this referenced content will be ignored.',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-2',
    'fields' => array(
      '0' => 'field_ec_featured_nodes',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Featured Nodes');

  return $groups;
}
