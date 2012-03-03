<?php

/**
 * Implementation of hook_strongarm().
 */
function op_resource_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_resource';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '1',
    'revision_information' => '5',
    'author' => '4',
    'options' => '6',
    'comment_settings' => '8',
    'menu' => '-1',
    'taxonomy' => '-2',
    'path' => '7',
    'attachments' => '9',
    'scheduler_settings' => '2',
    'workflow' => '3',
  );

  $export['content_extra_weights_resource'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_resource';
  $strongarm->value = 1;

  $export['scheduler_resource'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_touch_resource';
  $strongarm->value = 0;

  $export['scheduler_touch_resource'] = $strongarm;
  return $export;
}
