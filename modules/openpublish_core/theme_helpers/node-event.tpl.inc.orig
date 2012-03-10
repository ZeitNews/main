<?php
// $Id: node-event.tpl.inc,v 1.1.2.3 2010/04/12 04:30:34 inadarei Exp $

/**
 * Preprocess variables for node-event.tpl.php
 */
function openpublish_node_event_preprocess(&$vars) {
  
  // Main image
  if ($vars['field_main_image'][0]['filepath']) {
    $vars['main_image_credit'] = $vars['field_main_image_credit'][0]['view'];
    $vars['main_image_title']  = $vars['field_main_image'][0]['data']['title'];
    $vars['main_image_desc'] = $vars['field_main_image'][0]['data']['description'];
    $vars['main_image'] = theme('imagecache', '400xY',$vars['field_main_image'][0]['filepath'], $vars['main_image_title'], $vars['main_image_title']);  
  }
  
  // Body value
  $vars['node_body'] = $vars['node']->content['body']['#value'];
  
  // Event Date
  $vars['event_date_raw'] = $vars['node']->field_event_date[0];
  $vars['event_date'] = content_format('field_event_date', $vars['node']->field_event_date[0]);
  
  $vars['related_terms_links'] = openpublish_related_terms_links($vars['node']->taxonomy);
}
