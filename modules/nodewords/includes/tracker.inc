<?php

/**
 * @file
 * Integration file for tracker.module.
 */

/**
 * Implements hook_nodewords_type_id().
 */
function tracker_nodewords_type_id(&$result, $arg) {
  if ($arg[0] == 'tracker') {
    $result['type'] = NDOEWORDS_TYPE_USER;
    $result['id'] = is_numeric($arg[1]) ? $arg[1] : $GLOBALS['user']->uid;
  }
}
