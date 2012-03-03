<?php

/**
 * Implementation of hook_strongarm().
 */
function op_article_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_article';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '1',
    'revision_information' => '12',
    'author' => '11',
    'options' => '13',
    'comment_settings' => '16',
    'menu' => '-1',
    'taxonomy' => '-3',
    'path' => '15',
    'attachments' => '14',
    'scheduler_settings' => '9',
    'workflow' => '10',
  );

  $export['content_extra_weights_article'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_article';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
    2 => 'premium',
  );

  $export['node_options_article'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_article';
  $strongarm->value = 1;

  $export['scheduler_article'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_touch_article';
  $strongarm->value = 1;

  $export['scheduler_touch_article'] = $strongarm;
  return $export;
}
