<?php

/**
 * Implementation of hook_strongarm().
 */
function op_editors_choice_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_editors_choice';
  $strongarm->value = 0;

  $export['comment_anonymous_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_editors_choice';
  $strongarm->value = '3';

  $export['comment_controls_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_editors_choice';
  $strongarm->value = '4';

  $export['comment_default_mode_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_editors_choice';
  $strongarm->value = '1';

  $export['comment_default_order_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_editors_choice';
  $strongarm->value = '50';

  $export['comment_default_per_page_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_editors_choice';
  $strongarm->value = '0';

  $export['comment_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_editors_choice';
  $strongarm->value = '0';

  $export['comment_form_location_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_editors_choice';
  $strongarm->value = '1';

  $export['comment_preview_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_editors_choice';
  $strongarm->value = '1';

  $export['comment_subject_field_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_editors_choice';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-3',
    'revision_information' => '0',
    'author' => '1',
    'options' => '2',
    'comment_settings' => '5',
    'language' => '-1',
    'translation' => '4',
    'menu' => '-4',
    'path' => '3',
  );

  $export['content_extra_weights_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_editors_choice';
  $strongarm->value = '0';

  $export['language_content_type_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_editors_choice';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodeblock_editors_choice';
  $strongarm->value = '1';

  $export['nodeblock_editors_choice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_editors_choice';
  $strongarm->value = '0';

  $export['upload_editors_choice'] = $strongarm;
  return $export;
}
