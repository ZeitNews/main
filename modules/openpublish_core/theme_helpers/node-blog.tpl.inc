<?php
// $Id: node-blog.tpl.inc,v 1.1.2.7 2010/10/20 21:04:25 tirdadc Exp $

/**
 * Preprocess variables for node-blog.tpl.php
 */
function openpublish_node_blog_preprocess(&$vars) {
  
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
  
  // Used for the format_plural
  $vars['plural'] = count($vars['field_op_author']);
  
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
