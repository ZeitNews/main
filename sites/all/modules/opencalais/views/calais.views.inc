<?php
/**
 * @file calais.views.inc
 */

/**
 * Implementation of hook_views_data()
 */
function calais_views_data() {
  $data = array();

  // Core Calais Term
  $data['calais_term']['table']['group']  = t('Calais');
  $data['calais_term']['table']['base'] = array(
    'field' => 'tid',
    'title' => t('Calais Term'),
    'help' => t('Calais terms are attached to nodes.'),
  );


  $data['calais_term']['table']['join'] = array(
    'node' => array(
      'left_table' => 'calais_term_node',
      'left_field' => 'tid',
      'field' => 'tid',
    ),
    'node_revision' => array(
      'left_table' => 'calais_term_node',
      'left_field' => 'tid',
      'field' => 'tid',
    ),
    'term_data' => array(
      'left_field' => 'tid',
      'field' => 'tdid',
    ),
  );

  $data['calais_term']['tid'] = array(
    'title' => t('Term ID'),
    'help' => t('The Calais term ID'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['calais_term']['vid'] = array(
    'title' => t('Entity Type'),
    'help' => t('The Calais Entity Class that corresponds to a Taxonomy Vocabulary'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'argument' => array(
      'handler' => 'calais_handler_argument_calais_term_vid',
    ),
    'filter' => array(
      'handler' => 'calais_handler_filter_calais_term_vid',
    ),    
  );

  $data['calais_term']['name'] = array(
    'title' => t('Entity Name'),
    'help' => t('Calais Entity'),
    'field' => array(
      'handler' => 'calais_handler_field_calais',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['calais_term']['guid'] = array(
    'title' => t('Linked Data URI'),
    'help' => t('Calais Linked Data URI'),
    'field' => array(
      'handler' => 'calais_handler_field_guid',
    ),
  );
  
  $data['calais_term']['resolved_name'] = array(
    'title' => t('Resolved Name'),
    'help' => t('The disambiguated Calais Entity name'),
    'field' => array(
      'handler' => 'calais_handler_field_calais',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['calais_term']['resolved_type'] = array(
    'title' => t('Resolved Type'),
    'help' => t('The type of disambiguated Calais data (e.g geo, company, product)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  // Relevance
  $data['calais_term_node']['table']['group']  = t('Calais');
  $data['calais_term_node']['table']['join'] = array(
    // links to calais_term directly via tid.
    'calais_term' => array(
      'left_field' => 'tid',
      'field' => 'tid',
    ),
    // links to node directly via vid
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  // relevance score
  $data['calais_term_node']['relevance'] = array(
    'title' => t('Relevance Score'), // The item it appears as on the UI,
    'field' => array(
      'help' => t('The relevance score provided by Calais. Value from 0-1 with 1 being the most relevant.'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
      //'skip base' => array('calais_term'),
    ),
    'filter' => array(
      'handler' => 'calais_handler_filter_float',
      'help' => t('Filter based on the relevance score provided by Calais. Value from 0.000 - 1.000 with 1 being the most relevant.'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );  
  $data['calais_term_node']['nid'] = array(
    'title' => t('Node ID'),
    'help' => t('A Node ID to limit the results'),
    'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'title' => t('Node ID'),
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  
  // Calais resovled geo data
  $data['calais_term_data_geo']['table']['group']  = t('Calais Geo Data');
  $data['calais_term_data_geo']['table']['join'] = array(
    'calais_term' => array(
      // links to calais_term directly via tid.
      'left_field' => 'tid',
      'field' => 'tid',
    ),
    'term_data' => array(
      'left_table' => 'calais_term',
      'left_field' => 'tid',
      'field' => 'tid',
    ),
    // links to node via tid and calai_term_node nid
    'node' => array(
      'left_table' => 'calais_term_node',
      'left_field' => 'tid',
      'field' => 'tid',
    ),   
  );  
  
  $data['calais_term_data_geo']['latitude'] = array(
    'title' => t('Latitude'),
    'help' => t('The latitude geo coordinate of the Calais Entity'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
     'handler' => 'views_handler_filter_float',
    ),
  );
  $data['calais_term_data_geo']['longitude'] = array(
    'title' => t('Longitude'),
    'help' => t('The longitude geo coordinate of the Calais Entity'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
     'handler' => 'views_handler_filter_float',
    ),
  );  
  $data['calais_term_data_geo']['shortname'] = array(
    'title' => t('Short Name'),
    'help' => t('Core name of a resolved geography'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['calais_term_data_geo']['containedbystate'] = array(
    'title' => t('Contained By State'),
    'help' => t('Province/State name that contains a resolved geograpy (city)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['calais_term_data_geo']['containedbycountry'] = array(
    'title' => t('Contained By State'),
    'help' => t('Country name that contains a resolved geography (city or province/state)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  // Calais resovled company data
  $data['calais_term_data_company']['table']['group']  = t('Calais Company Data');
  $data['calais_term_data_company']['table']['join'] = array(
    'calais_term' => array(
      // links to calais_term directly via tid.
      'left_field' => 'tid',
      'field' => 'tid',
    ),
    'term_data' => array(
      'left_table' => 'calais_term',
      'left_field' => 'tid',
      'field' => 'tid',
    ),
  );    
  $data['calais_term_data_company']['ticker'] = array(
    'title' => t('Ticker'),
    'help' => t('Stock Symbol'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  $data['calais_term_data_company']['score'] = array(
    'title' => t('Company Score'),
    'help' => t('Confidence score (range: 0 lowest - 1 highest)'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );

  // Calais resovled product data
  $data['calais_term_data_product']['table']['group']  = t('Calais Product Data');
  $data['calais_term_data_product']['table']['join'] = array(
    'calais_term' => array(
      // links to calais_term directly via tid.
      'left_field' => 'tid',
      'field' => 'tid',
    ),
    'term_data' => array(
      'left_table' => 'calais_term',
      'left_field' => 'tid',
      'field' => 'tid',
    ),
  );    
  $data['calais_term_data_product']['score'] = array(
    'title' => t('Product Score'),
    'help' => t('Confidence score (range: 0 lowest - 1 highest)'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function calais_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'calais') . '/views/handlers',
    ),
    'handlers' => array(
      // fields
      'calais_handler_field_calais' => array(
        'parent' => 'views_handler_field',
      ),
      'calais_handler_field_guid' => array(
        'parent' => 'views_handler_field_url',
      ),
      // filters
      'calais_handler_filter_calais_term_vid' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'calais_handler_filter_float' => array(
        'parent' => 'views_handler_filter_numeric',
      ),
      // arguments
      'calais_handler_argument_calais_term_vid' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
    ),
  );
}
