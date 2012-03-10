<?php

/**
 * Implementation of hook_strongarm().
 */
function op_audio_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_audio';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '2',
    'revision_information' => '6',
    'author' => '5',
    'options' => '7',
    'comment_settings' => '10',
    'menu' => '-2',
    'taxonomy' => '-4',
    'path' => '9',
    'attachments' => '8',
    'workflow' => '4',
  );

  $export['content_extra_weights_audio'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_audio';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
    2 => 'premium',
  );

  $export['node_options_audio'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'swftools_mp3_display';
  $strongarm->value = 'onepixelout';

  $export['swftools_mp3_display'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'swftools_mp3_display_list';
  $strongarm->value = 'flowplayer3_mediaplayer';

  $export['swftools_mp3_display_list'] = $strongarm;
  return $export;
}
