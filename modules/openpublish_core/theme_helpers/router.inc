<?php
// $Id: router.inc,v 1.1.2.7 2010/11/02 00:13:51 inadarei Exp $


// Include RDFa utility functions
include_once('rdfa.lib.inc');

/**
 * Implementation of hook_preprocess.
 */
function openpublish_core_preprocess(&$vars, $hook) {    
  openpublish_core_suggest_preprocessor($vars, $hook);
}


/**
 * Checks for preprocessor files based on node type and includes them if available.
 */
function openpublish_core_suggest_preprocessor(&$vars, $hook) {

  if ($hook == 'page_header' || $hook == 'page_footer') {
    unset($vars['page_vars']['template_files']);    
    if (is_array($vars['page_vars'])) {
      foreach ($vars['page_vars'] as $var_key => $var_value) {
        $vars[$var_key] = $var_value;
      }
    }
    return;    
  }
  
  
  
  if (!empty($vars['type']) && $hook == 'node') { 
    $inc_file = dirname(__FILE__) . '/node-' . $vars['type'] . '.tpl.inc';
    $func_name = 'openpublish_node_' . $vars['type'] . '_preprocess';
      
    if (file_exists($inc_file)) {
      require_once($inc_file);
      if (function_exists($func_name)) {
        $func_name($vars);
      }
    }
  }
    
}