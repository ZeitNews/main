<?php

/**
 * @file
 * Integration file for user.module.
 */

/**
 * Implements hook_nodewords_type_id().
 */
function user_nodewords_type_id(&$result, $arg) {
  if ($arg[0] == 'user') {
    if (!isset($arg[1])) {
      $result['type'] = NODEWORDS_TYPE_USER;
      $result['id'] = $GLOBALS['user']->uid;
    }
    elseif (is_numeric($arg[1])) {
      $result['type'] = NODEWORDS_TYPE_USER;
      $result['id'] = $arg[1];
    }
  }
}
