<?php

/**
 * Implementation of hook_strongarm().
 */
function op_author_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_author';
  $strongarm->value = 0;

  $export['scheduler_author'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_touch_author';
  $strongarm->value = 0;

  $export['scheduler_touch_author'] = $strongarm;
  return $export;
}
