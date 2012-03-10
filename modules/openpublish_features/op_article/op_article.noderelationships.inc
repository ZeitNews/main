<?php

/**
 * Implementation of hook_noderelationships_default_settings().
 */
function op_article_noderelationships_default_settings() {
  $export = array();
  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'article';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_op_author';
  $noderelationships_default_setting->settings = array(
    'search_and_reference_view' => 'noderelationships_noderef:page_grid',
    'create_and_reference' => 'field_op_author',
  );
  $noderelationships_default_setting->export_key = 'article__noderef____field_op_author';
  $export['article__noderef____field_op_author'] = $noderelationships_default_setting;

  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'article';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_op_related_mmedia';
  $noderelationships_default_setting->settings = array(
    'search_and_reference_view' => 'noderelationships_noderef:page_grid',
    'create_and_reference' => 'field_op_related_mmedia',
  );
  $noderelationships_default_setting->export_key = 'article__noderef____field_op_related_mmedia';
  $export['article__noderef____field_op_related_mmedia'] = $noderelationships_default_setting;

  $noderelationships_default_setting = new stdClass;
  $noderelationships_default_setting->disabled = FALSE; /* Edit this to true to make a default noderelationships_default_setting disabled initially */
  $noderelationships_default_setting->api_version = 1;
  $noderelationships_default_setting->type_name = 'article';
  $noderelationships_default_setting->relation_type = 'noderef';
  $noderelationships_default_setting->related_type = '';
  $noderelationships_default_setting->field_name = 'field_related_content';
  $noderelationships_default_setting->settings = array(
    'search_and_reference_view' => 'noderelationships_noderef:page_grid',
    'create_and_reference' => 'field_related_content',
  );
  $noderelationships_default_setting->export_key = 'article__noderef____field_related_content';
  $export['article__noderef____field_related_content'] = $noderelationships_default_setting;

  return $export;
}
