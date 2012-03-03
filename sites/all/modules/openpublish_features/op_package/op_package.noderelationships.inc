<?php

/**
 * Implementation of hook_noderelationships_default_settings().
 */
function op_package_noderelationships_default_settings() {
  $export = array();
  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'package';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_center_related';
  $noderelationships_default_setting->settings = array(
    'search_and_reference_view' => 'noderelationships_noderef:page_grid',
    'create_and_reference' => 'field_center_related',
  );
  $noderelationships_default_setting->export_key = 'package__noderef____field_center_related';
  $export['package__noderef____field_center_related'] = $noderelationships_default_setting;

  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'package';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_left_related';
  $noderelationships_default_setting->settings = array(
    'search_and_reference_view' => 'noderelationships_noderef:page_grid',
    'create_and_reference' => 'field_left_related',
  );
  $noderelationships_default_setting->export_key = 'package__noderef____field_left_related';
  $export['package__noderef____field_left_related'] = $noderelationships_default_setting;

  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'package';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_right_related';
  $noderelationships_default_setting->settings = array(
    'search_and_reference_view' => 'noderelationships_noderef:page_grid',
    'create_and_reference' => 'field_right_related',
  );
  $noderelationships_default_setting->export_key = 'package__noderef____field_right_related';
  $export['package__noderef____field_right_related'] = $noderelationships_default_setting;

  return $export;
}
