<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function op_default_workflow_user_default_permissions() {
  $permissions = array();

  // Exported permission: access workflow summary views
  $permissions['access workflow summary views'] = array(
    'name' => 'access workflow summary views',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer workflow
  $permissions['administer workflow'] = array(
    'name' => 'administer workflow',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: schedule workflow transitions
  $permissions['schedule workflow transitions'] = array(
    'name' => 'schedule workflow transitions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  return $permissions;
}
