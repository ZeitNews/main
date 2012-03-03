<?php
// $Id: node-blog.tpl.inc,v 1.1.2.7 2010/10/20 21:04:25 tirdadc Exp $

/**
 * Preprocess variables for node-blog.tpl.php
 */
function openpublish_node_blog_preprocess(&$vars) {
  // Post date
  $vars['node_created_timestamp'] = $vars['node']->created;
  $vars['node_created'] = format_date($vars['node']->created, 'medium');
  $vars['node_created_rdfa'] = _openpublish_get_rdfa_date($vars['node']->created, $vars['node_created']);
  
  // Author(s) in string format
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
  
  
  // Author profiles
  if ($vars['field_op_author'][0]['view']) {
    
    foreach ($vars['field_op_author'] as $i => $auth) {
      $author = node_load($auth['nid']);
      
      if ($author->field_author_photo[0]['filepath']) {
        $vars['author_profiles'][$i]->photo = l(theme('imagecache', 'author_photo', $author->field_author_photo[0]['filepath'], $author->title, $author->title), 'node/' . $author->nid, array('html' => TRUE));
      }      
      $vars['author_profiles'][$i]->title = _openpublish_get_rdfa_author($author->title, $author->nid);
      $vars['author_profiles'][$i]->jobtitle = $author->field_op_author_jobtitle[0]['value'];
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