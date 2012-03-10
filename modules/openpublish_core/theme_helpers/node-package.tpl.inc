<?php
// $Id: node-package.tpl.inc,v 1.1.2.1 2010/03/10 18:49:21 inadarei Exp $

/**
 * Preprocess variables for node-package.tpl.php
 */
function openpublish_node_package_preprocess(&$vars) {
  
  // Left column intro
  $vars['left_intro'] = $vars['field_left_intro'][0]['view'];

  $vars['left_related_items'] = _build_items_list($vars['field_left_related']);
  
  // Center column intro
  $vars['center_intro'] = $vars['field_center_intro'][0]['view'];

  if ($vars['field_embedded_video'][0]['view']) {
    $vars['center_content'] = $vars['field_embedded_video'][0]['view'];
  }
  else if ($vars['field_embedded_audio'][0]['view']) {
    $vars['center_content'] = $vars['field_embedded_audio'][0]['view'];
  }
  else if ($vars['field_center_main_image'][0]['filepath']) {
    $vars['center_content'] = theme('imagecache', 'spotlight_homepage', $vars['field_center_main_image'][0]['filepath'], $vars['field_center_main_image'][0]['data']['description'], $vars['field_center_main_image'][0]['data']['description']);
  }
  
  $vars['center_related_items'] = _build_items_list($vars['field_center_related']);

  // Right column intro
  $vars['right_intro'] = $vars['field_right_intro'][0]['view'];
  
  $vars['right_related_items'] = _build_items_list($vars['field_right_related']);
}

/**
 * Returns an array of simplified objects displayed within
 * each column's node reference field.
 */
function _build_items_list($field) {
  if (is_array($field) && !empty($field)) {
    $list = array();
    foreach ($field as $left_related) {
      $related_node = node_load($left_related['nid']);

      // Simplified version of the node object
      $related_obj = new stdClass();

      if ($related_node->field_main_image[0]['filepath']) {
        $related_obj->image = theme('imagecache', 'thumbnail', $related_node->field_main_image[0]['filepath'], $related_node->field_main_image[0]['data']['description'], $related_node->field_main_image[0]['data']['description']);
      }
      $related_obj->title = l($related_node->title, 'node/'.$related_node->nid);
      
      // Teaser
      if (empty($related_node->field_teaser[0]['value'])) {
        $related_obj->teaser = $related_node->teaser;
      }
      else {
        $related_obj->teaser = $related_node->field_teaser[0]['value'];
      }

      $list[] = $related_obj;
    }
    return $list;
  }
  return NULL;
}