<?php
// $Id: node-video.tpl.inc,v 1.1.2.4 2010/04/12 04:30:34 inadarei Exp $

/**
 * Preprocess variables for node-video.tpl.php
 */
function openpublish_node_video_preprocess(&$vars) {
  // Embedded video file
  if ($vars['field_embedded_video'][0]['embed']) {
    $vars['video_file'] = $vars['field_embedded_video'][0]['view'];
  }
  
  if ($vars['field_flash_file'][0]['filepath']) {
    $vars['video_file'] = swf($vars['field_flash_file'][0]['filepath']);
  }
  
  // Authors
  if ($vars['field_op_author'][0]['view']) {
    $vars['authors'] = '';
    foreach ($vars['field_op_author'] as $author) {
      $vars['authors'] .= $author['view'] . ', ';
    }
    $vars['authors'] = trim($vars['authors'], ', ');
  }  
  
  // Body value
  $vars['node_body'] = $vars['node']->content['body']['#value'];
  
  $vars['related_terms_links'] = openpublish_related_terms_links($vars['node']->taxonomy); 
}
