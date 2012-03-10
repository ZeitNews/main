<?php
// $Id: node-op_image.tpl.inc,v 1.1.2.4 2010/04/01 21:21:08 inadarei Exp $

/**
 * Preprocess variables for node-op_image.tpl.php
 */
function openpublish_node_op_image_preprocess(&$vars) {
  
  // Credit
  if ($vars['field_op_image_credit'][0]['view']) {
    $vars['credit'] = $vars['field_op_image_credit'][0]['view'];
  }
  
  // Embedded image
  if ($vars['field_op_embedded_image'][0]['value']) {
    $vars['main_image'] = $vars['field_op_embedded_image'][0]['view'];
  }
  
  // Main image
  if ($vars['field_image_image'][0]['filepath']) {
    $vars['credit'] = $vars['field_op_image_credit'][0]['view'];
    $main_image_alt  = $vars['field_image_image'][0]['data']['alt'];
    $main_image_title = $vars['field_image_image'][0]['data']['title'];
    $vars['main_image'] = theme('imagecache_imagelink', '960xY', $vars['field_image_image'][0]['filepath'], $main_image_alt, $main_image_title);
  }
  
  $vars['related_terms_links'] = openpublish_related_terms_links($vars['node']->taxonomy);
}