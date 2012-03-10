<?php

// $Id: openpublish_core_init_config.inc,v 1.1.2.11 2010/10/28 03:33:33 tirdadc Exp $

/**
* @File helper file for .install that contains various initial configuration settings. 
* Extracting this from .install allows the ability to avoid overpopulating .install with
* large amount of code.
*/

function openpublish_core_init_config_roles() {

    //-- make sure .module is included and we have access to openpublish_core_get_rid_by_name()
    require_once(dirname(__FILE__) . '/openpublish_core.module');  
    
    // Load the permissions export
    include_once dirname(__FILE__) . "/includes/openpublish.perms.inc";
  
    //reformat for use with openpublish_core_add_permissions
    $role_perms = openpublish_core_reverse_perm_array($openpublish_perms);
    // Import the permissions for each role
    foreach ($role_perms as $role => $perms) {
      $rid = openpublish_core_get_rid_by_name($role);
      openpublish_core_add_permissions($rid, $perms);
    }
    
    db_query('INSERT INTO {users_roles} (uid, rid) VALUES (%d, %d)', 1, $admin_rid);
}


/**
* configure CKEditor
*/
function openpublish_core_init_config_ckeditor() {

  //-- make sure .module is included and we have access to openpublish_core_get_rid_by_name()
  require_once(dirname(__FILE__) . '/openpublish_core.module');  

  // Setup some reasonable CKEditor defaults
  $ckprofiles = ckeditor_profile_load();

  // Configure global visibilities
  $globalkey = 'CKEditor Global Profile';
  $ckglobal = $ckprofiles[$globalkey];
  $ckglobal->settings['old_name'] = $globalkey;
  $ckglobal->settings['name'] = $globalkey;
  $ckglobal->settings['excl'] = $ckglobal->settings['excl'] . "admin/*\n";  
  $ckglobal->settings['excl'] = $ckglobal->settings['excl'] . "user/*/openid*\n"; 
  $ckglobal->settings['excl'] = $ckglobal->settings['excl'] . "*@comment/reply/*.edit-comment\n";  
  $ckglobal->settings['excl'] = $ckglobal->settings['excl'] . "*@comment/edit/*.edit-comment\n";  
      
  db_query("UPDATE {ckeditor_settings} SET settings = '%s' WHERE name='%s'", serialize($ckglobal->settings) , $globalkey);

  module_load_include('inc', 'ckeditor', '/includes/ckeditor.admin');
  ckeditor_rebuild_selectors($globalkey);

  // Add role permissions to the built in profiles
  foreach (array('Default', 'Advanced') as $profile_name) {
    //-- Set permissions
    foreach (array('administrator', 'editor', 'web editor', 'author') as $role) {
      $rid = openpublish_core_get_rid_by_name($role);
      $rid_exists = db_result(db_query("SELECT rid FROM {ckeditor_role} WHERE name='%s' AND rid='%s'", $profile_name, $rid));
      if(empty($rid_exists)) {
        db_query("INSERT INTO {ckeditor_role} (name, rid) VALUES ('%s', %d)", $profile_name, $rid);      
      }
    }
    
    //-- Set editor-specific CSS file to editor.css
    $settings = $ckprofiles[$profile_name]->settings;    
    $settings['css_mode'] = 'self';
    $settings['css_path'] = '%hsites/all/themes/openpublish_theme/css/editor.css';
    db_query("UPDATE {ckeditor_settings} SET settings = '%s' WHERE name='%s'", serialize($settings) , $profile_name);

  }

}