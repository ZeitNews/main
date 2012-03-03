<?php

/**
 * @file
 * Integration file for taxonomy.module.
 */

/**
 * Implements hook_nodewords_type_id().
 */
function taxonomy_nodewords_type_id(&$result, $arg) {
  if ($arg[0] == 'taxonomy' && $arg[1] == 'term' && !empty($arg[2])) {
    // Taxonomy paths: taxonomy/term/$tid , taxonomy/term/$tid1+$tid2.
    $ids = preg_split('![+, ]!', $arg[2]);

    if (count($ids)) {
      // Take the first ID that is numeric.
      foreach ($ids as $id) {
        if (is_numeric($id)) {
          $result['type'] = NODEWORDS_TYPE_TERM;
          $result['id'] = $id;
          return;
        }
      }
    }
  }
}
