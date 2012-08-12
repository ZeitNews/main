<?php
// $Id: node-resource.tpl.inc,v 1.1.2.1 2010/03/10 18:50:13 inadarei Exp $

/**
 * Preprocess variables for node-resource.tpl.php
 */
function openpublish_node_resource_preprocess(&$vars) {
  // Main Image
  if ($vars['field_main_image'][0]['filepath']) {
    $vars['main_image_credit'] = $vars['field_main_image_credit'][0]['view'];
    $main_image_title  = $vars['field_main_image'][0]['data']['title'];
    $main_image_desc = $vars['field_main_image'][0]['data']['description'];
    if ($vars['field_main_image_link'][0]['value'] == '1') {
      $vars['main_image'] = theme('imagecache_imagelink', 'body_image', $vars['field_main_image'][0]['filepath'], $vars['field_main_image_credit'][0]['view'], 'Click to enlarge.', $attributes = NULL);
    } else {
      $vars['main_image'] = theme('imagecache', 'body_image', $vars['field_main_image'][0]['filepath'], $vars['field_main_image_credit'][0]['view'], $title = '', $attributes = NULL, $getsize = TRUE, $absolute = TRUE);
    }
  }
  
  $vars['related_terms_links'] = openpublish_related_terms_links($vars['node']->taxonomy);

  // Body value
  // Not using.
  $vars['node_body'] = $vars['node']->content['body']['#value'];
  
  // Authors
  // Not using.
  if ($vars['field_op_author'][0]['view']) {
    $str_author = t('By') . ' ';
    foreach ($vars['field_op_author'] as $author) {
      $str_author .= $author['view'] . ', ';
    }
    $vars['authors'] = trim($str_author, ', ');
    
  }
  
  // The field is now named field_link (no "s") because I had deleted it.
  // Not using this anyway.
  if (is_array($vars['field_links']) && !empty($vars['field_links'])) {
    foreach($vars['field_links'] as $link) {
      $vars['resource_links'][] = $link['view'];
    }
  }
  
}