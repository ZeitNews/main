<?php

/**
 * @file
 * Integration file for blog.module.
 */

/**
 * Implements hook_nodewords_type_id().
 */
function blog_nodewords_type_id(&$result, $arg) {
  if ($arg[0] == 'blog' && is_numeric($arg[1])) {
    $result['type'] = NODEWORDS_TYPE_USER;
    $result['id'] = $arg[1];
  }
}
