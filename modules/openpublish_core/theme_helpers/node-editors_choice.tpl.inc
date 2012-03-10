<?php
// $Id: node-editors_choice.tpl.inc,v 1.1.2.1 2010/10/01 16:31:34 tirdadc Exp $

/**
 * Preprocess variables for node-editors_choice.tpl.php
 */
function openpublish_node_editors_choice_preprocess(&$vars) {

  // If custom HTML is entered, ignore the referenced nodes
  if (trim(strip_tags($vars['node']->content['body']['#value']))) {
    $vars['custom_html'] = trim($vars['node']->content['body']['#value']);
  }
  // Otherwise we will use a view to display the referenced nodes
  else {
    foreach ((array)$vars['node']->field_ec_featured_nodes as $n) {
      $nids[] = $n['nid'];
    }
    
    if ($nids) {
      $vars['featured_nodes'] = views_embed_view('editors_choice', 'block_1', join($nids, '+'));
    }
  }
}