<?php
// $Id: node-audio.tpl.inc,v 1.1.2.4 2010/04/16 01:51:40 inadarei Exp $

/**
 * Preprocess variables for node-audio.tpl.php
 */
function openpublish_node_audio_preprocess(&$vars) {
  
  // Use SWFtools if this is a custom URL for an audio file
  if ($vars['field_embedded_audio'][0]['embed']) {
    $vars['audio_file'] = $vars['field_embedded_audio'][0]['view'];
    if ($vars['field_embedded_audio'][0]['provider'] == 'custom_url' && strpos($vars['field_embedded_audio'][0]['value'], 'mp3')) {
      $vars['audio_file'] = swf($vars['field_embedded_audio'][0]['value']);
    }
  }
  
  // Authors
  if ($vars['field_op_author'][0]['view']) {
    $vars['authors'] = '';
    foreach ($vars['field_op_author'] as $author) {
      $vars['authors'] .= $author['view'] . ', ';
    }
    $vars['authors'] = trim($vars['authors'], ', ');
  }  
  
  
  if ($vars['field_audio_file'][0]['filepath']) {
    $vars['audio_file'] = swf($vars['field_audio_file'][0]['filepath']);
  }
  
  $vars['related_terms_links'] = openpublish_related_terms_links($vars['node']->taxonomy);
}