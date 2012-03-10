<?php

/**
 * Implementation of hook_strongarm().
 */
function op_videos_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_video';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '2',
    'revision_information' => '6',
    'author' => '5',
    'options' => '8',
    'comment_settings' => '9',
    'menu' => '-2',
    'taxonomy' => '-4',
    'path' => '11',
    'attachments' => '10',
    'scheduler_settings' => '4',
    'workflow' => '3',
  );

  $export['content_extra_weights_video'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'flowplayer3_mediaplayer';
  $strongarm->value = array(
    'clip' => array(
      'autoPlay' => 'false',
      'autoBuffering' => 'false',
      'scaling' => 'scale',
      'start' => '',
      'duration' => '',
      'accelerated' => 'false',
      'bufferLength' => '',
      'provider' => '',
      'fadeInSpeed' => '',
      'fadeOutSpeed' => '',
      'linkUrl' => '',
      'linkWindow' => '_blank',
      'live' => 'false',
      'cuePointMultiplier' => '',
    ),
    'controls' => array(
      'backgroundGradient' => 'medium',
      'progressGradient' => 'medium',
      'bufferGradient' => 'none',
      'sliderGradient' => 'none',
      'autoHide' => 'fullscreen',
      'play' => 'true',
      'volume' => 'true',
      'mute' => 'true',
      'time' => 'true',
      'stop' => 'false',
      'playlist' => 'false',
      'fullscreen' => 'true',
      'scrubber' => 'true',
    ),
    'canvas' => array(
      'height' => '375',
      'width' => '500',
      'backgroundImage' => '',
      'backgroundRepeat' => 'repeat',
      'backgroundGradient' => 'low',
      'border' => '',
      'borderRadius' => '',
    ),
  );

  $export['flowplayer3_mediaplayer'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'flowplayer3_mediaplayer_file';
  $strongarm->value = 'flowplayer-3.1.5.swf';

  $export['flowplayer3_mediaplayer_file'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'flowplayer3_mediaplayer_stream_plugin';
  $strongarm->value = 'flowplayer.rtmp-3.1.3.swf';

  $export['flowplayer3_mediaplayer_stream_plugin'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_video';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
    2 => 'premium',
  );

  $export['node_options_video'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_touch_video';
  $strongarm->value = 1;

  $export['scheduler_touch_video'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_video';
  $strongarm->value = 1;

  $export['scheduler_video'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'swftools_flv_display';
  $strongarm->value = 'flowplayer3_mediaplayer';

  $export['swftools_flv_display'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'swftools_flv_display_list';
  $strongarm->value = 'flowplayer3_mediaplayer';

  $export['swftools_flv_display_list'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'swftools_media_display_list';
  $strongarm->value = 'flowplayer3_mediaplayer';

  $export['swftools_media_display_list'] = $strongarm;
  return $export;
}
