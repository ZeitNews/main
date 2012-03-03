<?php
// $Id: audiofield_formatter.inc,v 1.22 2011/01/31 17:55:44 tamerzg Exp $:
/**@file
 * Theme function for 'embedded' audio.
 */
function theme_audiofield_formatter_audiofield_embedded($element) {
  global $user;
  //Don't render player if there is no file.
  if (!$element['#item']['filepath']) {
    return '';
  }

  $info = pathinfo($element['#item']['filename']);
  $op = $info['extension'];
  $audiofile=file_create_url($element['#item']['filepath']);
  $output= audiofield_get_player($audiofile, $op);
  
  if (!empty($element['#item']['data']['description'])) {
    $output .= '<div class="audio-description">' . $element['#item']['data']['description'].'</div>';
  }
  
  //If user is file owner check for download permission and display download link
  if ($user->uid==$element['#item']['uid'] && user_access('download own audio files')) {
    $output .= '<div class="audio-download"><b>Download:</b>' . theme('filefield_file', $element['#item']) . '</div>';
  }
  elseif (user_access('download all audio files')) {
    //If user has permission to download all audio files, then display download link
    $output .= '<div class="audio-download"><b>Download:</b>' . theme('filefield_file', $element['#item']) . '</div>';
  }

  return $output;
}

/** 
 * TODO:Theme function for popup audiofield field formatter. 
 */
 /*
function theme_audiofield_formatter_audiofield_popup($element) {
  
  return $output;
}
*/