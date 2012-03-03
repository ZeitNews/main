<?php

/**
 * Preprocess variables for node-project.tpl.php
 */
function openpublish_node_project_preprocess(&$vars) {
  // Main image
  if ($vars['field_main_image'][0]['filepath']) {
    $vars['main_image_credit'] = $vars['field_main_image_credit'][0]['view'];
    $vars['main_image_title']  = $vars['field_main_image'][0]['data']['title'];
    $vars['main_image_desc'] = $vars['field_main_image'][0]['data']['description'];
    $vars['main_image'] = theme('imagecache', 'body_image',$vars['field_main_image'][0]['filepath'], $vars['main_image_title'], $vars['main_image_title']);  
  }
  
  $vars['related_terms_links'] = openpublish_related_terms_links($vars['node']->taxonomy);
  
}