<?php

/**
 * Preprocess variables for node-project.tpl.php
 */
function openpublish_node_project_preprocess(&$vars) {
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
  
}