<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function op_solr_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-solr-search';
  $context->description = '';
  $context->tag = 'OpenPublish Search';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'search/apachesolr_search/*' => 'search/apachesolr_search/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'apachesolr_search-currentsearch' => array(
          'module' => 'apachesolr_search',
          'delta' => 'currentsearch',
          'region' => 'right',
          'weight' => 0,
        ),
        'apachesolr_search-type' => array(
          'module' => 'apachesolr_search',
          'delta' => 'type',
          'region' => 'right',
          'weight' => 1,
        ),
        'apachesolr_search-field_op_author' => array(
          'module' => 'apachesolr_search',
          'delta' => 'field_op_author',
          'region' => 'right',
          'weight' => 2,
        ),
        'apachesolr_search-im_vid_43' => array(
          'module' => 'apachesolr_search',
          'delta' => 'im_vid_43',
          'region' => 'right',
          'weight' => 3,
        ),
        'apachesolr_search-im_vid_3' => array(
          'module' => 'apachesolr_search',
          'delta' => 'im_vid_3',
          'region' => 'right',
          'weight' => 4,
        ),
        'apachesolr_search-im_vid_22' => array(
          'module' => 'apachesolr_search',
          'delta' => 'im_vid_22',
          'region' => 'right',
          'weight' => 5,
        ),
        'apachesolr_search-im_vid_23' => array(
          'module' => 'apachesolr_search',
          'delta' => 'im_vid_23',
          'region' => 'right',
          'weight' => 6,
        ),
        'apachesolr_search-im_vid_2' => array(
          'module' => 'apachesolr_search',
          'delta' => 'im_vid_2',
          'region' => 'right',
          'weight' => 7,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $export['openpublish-solr-search'] = $context;
  return $export;
}
