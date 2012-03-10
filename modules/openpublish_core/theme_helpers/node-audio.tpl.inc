<?php
// $Id: node-audio.tpl.inc,v 1.1.2.9 2010/10/20 21:04:25 tirdadc Exp $

/**
 * Preprocess variables for node-audio.tpl.php
 */
function openpublish_node_audio_preprocess(&$vars) {
  
  $vars['type'] = ucfirst($vars['type']);
  
  $vars['field_deck_value'] = $vars['field_deck'][0]['value'];
  
  $vars['node_created_timestamp'] = $vars['node']->created;
  $vars['node_created'] = format_date($vars['node']->created, 'medium');
  $vars['node_created_rdfa'] = _openpublish_get_rdfa_date($vars['node']->created, $vars['node_created']);
  
  if ($vars['field_op_author'][0]['view']) {
    $str_author = t('By') . ' ';
    foreach ($vars['field_op_author'] as $author) {
      // check_plain is already run and will happen again with l(), hence the htmlspecialchars_decode
      $str_author .= _openpublish_get_rdfa_author(htmlspecialchars_decode(strip_tags($author['view']), ENT_QUOTES), $author['nid']) . ', ';      
    }
    $vars['authors'] = trim($str_author, ', ');
  }
  
  // Main Image
  if ($vars['field_main_image'][0]['filepath']) {
    $vars['main_image_credit'] = $vars['field_main_image_credit'][0]['view'];
    $main_image_title  = $vars['field_main_image'][0]['data']['title'];
    $main_image_desc = $vars['field_main_image'][0]['data']['description'];
    $vars['main_image'] = theme('imagecache', 'body_image', $vars['field_main_image'][0]['filepath'], $main_image_title, $main_image_title);
  }
  
  // Used for the format_plural
  $vars['plural'] = count($vars['field_op_author']);
  
  $vars['show_authors'] = FALSE;
  if ($vars['field_show_author_info'][0]['value'] && $vars['field_op_author'][0]['view']) {
    $vars['show_authors'] = TRUE;
    
    foreach ($vars['field_op_author'] as $i => $auth) {
      $author = node_load($auth['nid']);
      
      if ($author->field_author_photo[0]['filepath']) {
        $vars['author_profiles'][$i]->photo = l(theme('imagecache', 'author_photo', $author->field_author_photo[0]['filepath'], $author->title, $author->title), 'node/' . $author->nid, array('html' => TRUE));
      }
      
      $vars['author_profiles'][$i]->title = _openpublish_get_rdfa_author($author->title, $author->nid);
      $vars['author_profiles'][$i]->jobtitle = glue_module_expertise($author->taxonomy);
      $vars['author_profiles'][$i]->teaser = $author->teaser;
    }
  }
  
  // DocumentCloud
  if ($vars['node']->field_op_documentcloud_doc && $vars['node']->field_op_documentcloud_doc[0]['url']) {
    $vars['documentcloud_doc'] = $vars['node']->field_op_documentcloud_doc;
  }
  
  $vars['related_terms_links'] = openpublish_related_terms_links($vars['node']->taxonomy);
  $vars['themed_links'] = theme('links', $vars['node']->links);

}
