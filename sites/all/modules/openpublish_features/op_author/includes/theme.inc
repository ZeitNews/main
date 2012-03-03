<?php
// $Id: theme.inc,v 1.1.2.1 2010/01/15 19:26:44 inadarei Exp $

/**
 * @file
 * OP Author Features Theming
 */


/**
* Implementation of hook_init
*/
function op_author_init() {
  if (_op_author_is_author_page()) {
 
    $module_path = drupal_get_path('module', 'op_author');
        
    //-- Load Author-page-specific CSS
    $css_path = $module_path . '/includes/authorpage.css';
    drupal_add_css($css_path);   
  }

}

/**
* Implementation of hook_registry_alter
*/
function op_author_theme_registry_alter(&$theme_registry) {

  //-- Provide default node template implementations from this module,
  //-- but make sure we give a correspodning tpl in a theme folder a chance 
  //-- to override us.
  $idx = array_search('modules/node', $theme_registry['node']['theme paths']);
  if ($idx !== FALSE) {
    array_splice( $theme_registry['node']['theme paths'], 
                  $idx+1, 0, 
                  drupal_get_path('module', 'op_author') . '/theme');
  }
                
}


/**
* Implementation of hook_preprocess_page
*/
function op_author_preprocess_page(&$vars) {

  if (_op_author_is_author_page()) {  
    //-- Unset title template variable for author pages, to make sure page.tpl.php does not render it.
    unset($vars['title']); 
  }
  
}

/**
* Checks if current page is an author node page
*/
function _op_author_is_author_page() {

  static  $is_author_page;  
  if (isset($is_author_page)) return $is_author_page;
  
  $is_author_page = FALSE;
  
  if (arg(0) == 'node' && is_numeric(arg(1))) { // Node page
    $node_id = arg(1);
    $node = node_load($node_id);
    $is_author_page = ($node->type == 'author');
  }

  return $is_author_page;
  
}