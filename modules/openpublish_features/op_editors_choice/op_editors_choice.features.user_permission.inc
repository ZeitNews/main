<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function op_editors_choice_user_default_permissions() {
  $permissions = array();

  // Exported permission: create editors_choice content
  $permissions['create editors_choice content'] = array(
    'name' => 'create editors_choice content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any editors_choice content
  $permissions['delete any editors_choice content'] = array(
    'name' => 'delete any editors_choice content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: delete own editors_choice content
  $permissions['delete own editors_choice content'] = array(
    'name' => 'delete own editors_choice content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any editors_choice content
  $permissions['edit any editors_choice content'] = array(
    'name' => 'edit any editors_choice content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: edit own editors_choice content
  $permissions['edit own editors_choice content'] = array(
    'name' => 'edit own editors_choice content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  return $permissions;
}
