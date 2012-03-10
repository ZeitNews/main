<?php

/**
 * Implementation of hook_strongarm().
 */
function op_event_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_event';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '0',
    'revision_information' => '3',
    'author' => '1',
    'options' => '5',
    'comment_settings' => '7',
    'menu' => '-2',
    'taxonomy' => '-4',
    'path' => '8',
    'attachments' => '6',
    'workflow' => '9',
  );

  $export['content_extra_weights_event'] = $strongarm;
  return $export;
}
