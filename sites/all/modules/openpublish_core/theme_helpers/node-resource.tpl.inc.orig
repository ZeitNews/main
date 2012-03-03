<?php
// $Id: node-resource.tpl.inc,v 1.1.2.1 2010/03/10 18:50:13 inadarei Exp $

/**
 * Preprocess variables for node-resource.tpl.php
 */
function openpublish_node_resource_preprocess(&$vars) {
  // Body value
  $vars['node_body'] = $vars['node']->content['body']['#value'];
  
  // Authors
  if ($vars['field_op_author'][0]['view']) {
    $str_author = t('By') . ' ';
    foreach ($vars['field_op_author'] as $author) {
      $str_author .= $author['view'] . ', ';
    }
    $vars['authors'] = trim($str_author, ', ');
    
  }
  
  if (is_array($vars['field_links']) && !empty($vars['field_links'])) {
    foreach($vars['field_links'] as $link) {
      $vars['resource_links'][] = $link['view'];
    }
  }
  
}