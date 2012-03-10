<?php

/**
 * Implementation of hook_default_workflow_type_map().
 */
function op_default_workflow_nodetypes_default_workflow_type_map() {
  $export = array();
  $workflow_type_map = new stdClass;
  $workflow_type_map->api_version = 1;
  $workflow_type_map->node_type = 'article';
  $workflow_type_map->workflow_name = 'op_default_workflow';

  $export['article'] = $workflow_type_map;
  $workflow_type_map = new stdClass;
  $workflow_type_map->api_version = 1;
  $workflow_type_map->node_type = 'blog';
  $workflow_type_map->workflow_name = 'op_default_workflow';

  $export['blog'] = $workflow_type_map;
  return $export;
}
