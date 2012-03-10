<?php

/**
 * Implementation of hook_strongarm().
 */
function op_slideshow_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_slideshow';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
    2 => 'premium',
  );

  $export['node_options_slideshow'] = $strongarm;
  return $export;
}
