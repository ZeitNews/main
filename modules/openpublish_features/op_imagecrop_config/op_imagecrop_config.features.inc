<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function op_imagecrop_config_ctools_plugin_api() {
  module_load_include('inc', 'op_imagecrop_config', 'op_imagecrop_config.defaults');
  $args = func_get_args();
  return call_user_func_array('_op_imagecrop_config_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function op_imagecrop_config_strongarm() {
  module_load_include('inc', 'op_imagecrop_config', 'op_imagecrop_config.defaults');
  $args = func_get_args();
  return call_user_func_array('_op_imagecrop_config_strongarm', $args);
}
