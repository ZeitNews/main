<?php

/**
 * @file
 * Integration file for node.module.
 */

/**
 * Implements hook_nodewords_type_id().
 */
function node_nodewords_type_id(&$result, $arg) {
  if ($arg[0] == 'node' && is_numeric($arg[1])) {
    $result['type'] = NODEWORDS_TYPE_NODE;
    $result['id'] = $arg[1];
  }
}
