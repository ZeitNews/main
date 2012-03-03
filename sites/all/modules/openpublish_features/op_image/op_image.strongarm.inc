<?php

/**
 * Implementation of hook_strongarm().
 */
function op_image_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_op_image';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
    2 => 'premium',
  );

  $export['node_options_op_image'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_op_image';
  $strongarm->value = 1;

  $export['scheduler_op_image'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_touch_op_image';
  $strongarm->value = 1;

  $export['scheduler_touch_op_image'] = $strongarm;
  return $export;
}
