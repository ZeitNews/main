<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_default_workflow_nodetypes_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "workflow" && $api == "workflow") {
    return array("version" => 1);
  }
}
