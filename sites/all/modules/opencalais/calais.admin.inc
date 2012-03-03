<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro, Irakli Nadareishvili

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

 */
/**
 * @file
 */

/**
 * Build the administration page for Calais and Content Types
 */
function calais_admin_settings() {
  $form = array();

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
    '#collapsible' => TRUE,
  );

  $form['general']['calais_store_rdf'] = array(
    '#type' => 'checkbox',
    '#title' => t('Store Calais RDF Locally'),
    '#default_value' => variable_get('calais_store_rdf', FALSE),
    '#description' => t('If checked, this will store the RDF data returned from Calais in the local RDF store. This data can be used to get a deeper view into the Calais results as the functionality is more fully developed. It also allows for future semantic applications to query and build upon this linked data, but it vastly increases the database size as there is a large amount of data saved. ENABLE THIS WITH CAUTION.'),
  );
  $form['general']['calais_lookup_loduri'] = array(
    '#type' => 'checkbox',
    '#title' => t('Lookup Linked Open Data URI'),
    '#default_value' => variable_get('calais_lookup_loduri', FALSE),
    '#description' => t('If checked, an additional HTTP request will be made for each disambiguated entity to find the Linked Open Data URIs to DBPedia, Freebase, etc.  It does involve additional requests to external servers.  If you don\'t know what this is, you should leave it disabled.'),
  );

  calais_build_entity_settings($form);
  calais_build_nodetype_settings($form);

  $form = system_settings_form($form);
  $form['#submit'][] = 'calais_admin_settings_submit';
  
  return $form;
}

/**
 * Build the Entity selector. Used for Entity suppression.
 */
function calais_build_entity_settings(&$form, $type = 'global', $name = 'Global', $allow_disable = FALSE) {
  $title = $name;
  $entities = array_keys(calais_get_entity_vocabularies());
  sort($entities);

  $disabled = FALSE;
  if ($allow_disable) {
    $var_name = "calais_use_global_{$type}";
    $disabled = variable_get($var_name, TRUE);

    $entity_options = array(
      TRUE  => t('GLOBAL: use global setting from above'),
      FALSE => t("CUSTOM: pick the categories for this content type"),
    );
    $form[$type][$var_name] = array(
      '#type' => 'radios',
      '#title' => t('Which tag categories (entities) do you want this type tagged with'),
      '#default_value' => $disabled,
      '#description' => t('Use the global settings specified above, or customize the tags applied for this content type.'),
      '#options' => $entity_options,
      '#attributes' => array('class' => "calais-use-global", 'data' => $type),
    );
    $title = t('Customized categories for @name type', array('@name' => $name));
  }

  $entity_attributes = array('class' => "calais-entity-settings-{$type}");
  if ($disabled) {
    $entity_attributes['style'] = 'display:none';
  }
  $form[$type]["calais_entity_settings_{$type}"] = array(
    '#type' => 'fieldset',
    '#title' => $title,
    '#attributes' => $entity_attributes,
    '#collapsible' => TRUE,
    '#collapsed' => !$allow_disable,
  );

  $form[$type]["calais_entity_settings_{$type}"]["calais_applied_entities_{$type}"] = array(
    '#type' => 'checkboxes',
    '#title' => t('Which tag categories (entities) do you wish to use?'),
    '#default_value' => variable_get("calais_applied_entities_{$type}", $entities),
    '#options' => drupal_map_assoc($entities),
    '#description' => t('Choose which vocabularies should be included for term suggestions.'),
  );
}

/**
 * Build the node type settings form for Calais integration.
 */
function calais_build_nodetype_settings(&$form) {
  node_types_rebuild();

  $node_types = node_get_types('types', NULL, TRUE);
  $request_options = array(
    CALAIS_REQUEST_NO             => t('NEVER: not processed by Calais'),
    CALAIS_REQUEST_MANUAL         => t("MANUAL: initiate requests from the 'Calais' tab"),
    CALAIS_REQUEST_AUTO           => t('AUTOMATIC: every time you save content, published or unpublished'),
    CALAIS_REQUEST_AUTO_PUBLISHED => t('AUTOMATIC PUBLISHED: every time you save published content'),
  );
  $process_options = array(
    CALAIS_PROCESS_MANUAL    => t('NEVER: suggest the terms, but let me tag the content'),
    CALAIS_PROCESS_AUTO_ONCE => t('ONCE: tag the content the first time I save'),
    CALAIS_PROCESS_AUTO      => t('ALWAYS: tag the content on every save'),
  );

  foreach ($node_types as $nt) {
    $key = drupal_strtolower($nt->type);
    $name = $nt->name;
    
    $form[$key] = array(
      '#type' => 'fieldset',
      '#title' => $name,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#nodetype' => $key,
      '#theme' => 'calais_nodetype_settings',
    );

    $request = variable_get("calais_node_{$key}_request", CALAIS_REQUEST_NO);
    $form[$key]["calais_node_{$key}_request"] = array(
      '#type' => 'radios',
      '#parents' => array('calais_node_'. $key .'_request'),
      '#title' => t('Send Calais request'),
      '#default_value' => $request,
      '#options' => $request_options,
      '#attributes' => array('class' => "nodetype_toggle", 'data' => $key),
    );

    $processing = variable_get("calais_node_{$key}_process", CALAIS_PROCESS_MANUAL);
    $form[$key]["calais_node_{$key}_process"] = array(
      '#type' => 'radios',
      '#parents' => array('calais_node_'. $key .'_process'),
      '#title' => t('Tag content'),
      '#default_value' => $processing,
      '#options' => $process_options,
    );
    
    _calais_build_semanticproxy_config($form, $nt);
    
    $form[$key]["calais_threshold_{$key}"] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#title' => t('Minimum suggested tag relevancy'),
      '#default_value' => variable_get("calais_threshold_{$key}", 0.0),
      '#description' => t('Determine how relevant a term must be in order for Calais to suggest it for a particular node.  Based on a 0.00-1.00 scale, with 0.00 being least relevant (i.e. many terms appear).'),
    );
    
    calais_build_entity_settings($form, $key, $name, TRUE);
  }
}

/**
 * Configuration for Semantic Proxy integration. This will
 */
function _calais_build_semanticproxy_config(&$form, $node_type) {
  
  $spfields = array('' => "Don't process with SemanticProxy");
  $docfields = array('' => "Don't store document text");

  // If this content type is configured as a feed item
  if(module_exists('feedapi_node')) {
    $feed_types = feedapi_get_types();
    foreach($feed_types as $type => $name) {
      $settings = feedapi_get_settings($type);
      if($settings['processors']['feedapi_node']['content_type'] == $node_type->type) {
        $spfields['calais_feedapi_node'] = t('Feed Item Original URL');
      }
    }
  }

  if(module_exists('content')) {
    $content_type = content_types($node_type->type);
    $type_url_str = $content_type['url_str'];
    $fields = $content_type['fields'];
    if(is_array($fields) && !empty($fields)) {
      foreach($fields as $name => $field) {
        // Fields to submit to SemanticProxy
        if($field['type'] == 'link' || ($field['type'] == 'text' && $field['widget']['type'] == 'text_textfield')) {
          $spfields[$name] = $field['widget']['label'] . ' (' . $field['field_name'] . ')';
        }
        // Fields to store document text
        if($field['type'] == 'text' && $field['widget']['type'] == 'text_textarea') { 
          $docfields[$name] = $field['widget']['label'] . ' (' . $field['field_name'] . ')';
        }
      }
    }
  }
  
  if(count($spfields) == 1)
    return;
    
  $key = drupal_strtolower($node_type->type);  
  $form[$key]['semanticproxy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Semantic Proxy'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form[$key]['semanticproxy']["calais_semanticproxy_field_{$key}"] = array(
    '#type' => 'select',
    '#title' => t('Field that contains the URL to send to SemanticProxy'),
    '#options' => $spfields,
    '#default_value' => variable_get("calais_semanticproxy_field_{$key}", ''),
    '#description' => t('SemanticProxy submits the content of a URL to Calais for processing. You would use this if your content type is a node that has a short blurb/summary with the full content living on another site. This will ask SemanticProxy to get the contents of that URL and submit it to Calais for you. This field must contain a URL.'),
  );  
  $form[$key]['semanticproxy']["calais_semanticproxy_document_{$key}"] = array(
    '#type' => 'select',
    '#title' => t('Field to save document text from above URL'),
    '#options' => $docfields,
    '#default_value' => variable_get("calais_semanticproxy_document_{$key}", ''),
    '#description' => t('SemanticProxy submits the content at the above URL to Calais for processing. This is the field where you would like to save the document content that sent to Calais for processing. You can use this field to submit to to other services such as yahoo Terms, etc. You could use this field for display, but chances are it is not fit for presentation. You can hide this field from display !url', array('!url' => l('here', "admin/content/node-type/{$type_url_str}/display"))),
  );  
}

/**
 * Have to override so that we can manage vocabulary - node_type relationships.
 * This assumes the default submit handler (system_settings_form_submit) was already processed.
 *
 * @param $form_id
 * @param $form_state
 */
function calais_admin_settings_submit($form, &$form_state) {

  // Also, set vocabulary-node relationships
  $node_types = node_get_types('types', NULL, TRUE);
  $all_vocabularies = calais_get_entity_vocabularies();
  foreach ($node_types as $nt) {
    $key = drupal_strtolower($nt->type);
    $request = calais_get_request_type($key);
    foreach ($all_vocabularies as $entity => $vid) {
      // Clean-up
      db_query("DELETE FROM {vocabulary_node_types} WHERE vid='%d' and type='%s'", $vid, $key);
    }
    if ($request != CALAIS_REQUEST_NO) {
      // assign all configured calais vocabs to this node type
      $node_vocabularies = calais_get_entity_vocabularies($key);
      if(!empty($node_vocabularies)) {
        foreach ($node_vocabularies as $entity => $vid) {
          db_query("INSERT INTO {vocabulary_node_types} (vid, type) values('%d','%s') ", $vid, $key);
        }
      }
    }
  }
}

/**
 * Theme function for nodetype settings.
 */
function theme_calais_nodetype_settings($form) {
  drupal_add_js(drupal_get_path("module", "calais") ."/calais.admin.js");
  
  $type = $form['#nodetype'];
  
  $output = '';  
  $output .= drupal_render($form["calais_node_{$type}_request"]);
  
  $extra = $form["calais_node_{$type}_request"]['#value'] == CALAIS_REQUEST_NO ? "style='display:none;'" : "";
  $output .= "<div id='{$type}_toggle' {$extra}>";  
  $output .= drupal_render($form);
  $output .= "</div>";
  
  return $output;
}


/**
 * Build the administration page for submitting nodes of specific Content Types to Calais.
 */
function calais_bulk_process() {

  // Get a system settings form for # of nodes per cron
  $output = drupal_get_form('calais_cron_settings_form');
  
  // Generate a summary of total node counts per content type
  $node_types = array();
  foreach (node_get_types('types', NULL, TRUE) as $type) {
    $node_types[$type->type] = $type->name;
  }

  $header = array(
    t('Type'),
    t('Total Content Count'),
    t('Content in Queue'),
    t('Actions'),
  );
  $config = array();
  $rows = array();
  $result = db_query("SELECT type, COUNT(*) as count FROM {node} GROUP BY type");  
  while ($row = db_fetch_object($result)) {
    $queue_count = db_result(db_query("SELECT COUNT(*) FROM {calais_node_queue} WHERE type = '%s'", $row->type));  
    
    $request = calais_get_request_type($row->type);
    if ($request == CALAIS_REQUEST_NO) {
      $actions = t('Disabled');
    }
    else {
      $actions = $queue_count > 0 
            ? l(t('Clear queue'), "admin/settings/calais/queue/clear/{$row->type}")
            : l(t('Add to queue'), 
                "admin/settings/calais/queue/enqueue/{$row->type}",
                array('attributes' => array('id' => "calais-queue-toggle-{$row->type}", 'class' => 'calais-queue-toggle')));
    }

    $rows[] = array(
      $node_types[$row->type],
      $row->count,
      $queue_count,
      $actions,
    );
    
    // Build the config that poplates the queue form based on type
    $process = calais_get_processing_type($row->type);
    $threshold = calais_get_node_threshold($row->type);
    $config[$row->type] = array('process' => $process, 'threshold' => $threshold);
  }
  
  $queue_summary = array(
    '#type' => 'item',
    '#title' => t('Content Summary'),
    '#value' => theme('table', $header, $rows),
    '#description' => t('Re-tagging content will add it to a queue for bulk processing.'),
  );
  $output .= theme('item', $queue_summary);
  $output .= drupal_get_form('calais_enqueue_form');
  drupal_add_js(array('calais_queue' => $config), 'setting');
  return $output;
}

/**
 * The form that controls how many nodes are sent to Calais on cron runs.
 */
function calais_cron_settings_form() {
  $queue_count = db_result(db_query("SELECT COUNT(*) FROM {calais_node_queue}"));  
  $cron_limit = variable_get('calais_cron_limit', 10);
  if ($cron_limit == 0) {
    $expected = t('There is no processing scheduled');
  }
  else {
    $expected = ceil($queue_count / $cron_limit);
  }
  
  $numbers = drupal_map_assoc(array(0, 5, 10, 25, 50, 100));
  $form['calais_cron_limit'] = array(
    '#type' => 'select',
    '#title' => t('Number of content items processed each cron run'),
    '#default_value' => $cron_limit,
    '#options' => $numbers,
    '#description' => t('The maximum number of content items indexed in each pass of a <a href="@cron">cron maintenance task</a>. If necessary, reduce the number of items to prevent timeouts, memory errors, or throttling while processing.', array('@cron' => url('admin/reports/status')))
  );
  $form['queue'] = array(
    '#type' => 'item',
    '#title' => t('Number of cron executions to fully process this queue'),
    '#value' => $expected,
  );
    
  return system_settings_form($form);
}

/**
 * Add the nodes of a given content type to the queue for Calais processing
 *
 * @param $type 
 *      The node type
 * @param $process_type
 *      The type of Calais processing (i.e. suggest, auto apply, etc.)
 * @param $threshold
 *      The relevenace threshold for filtering tags returned form Calais
 */
function calais_enqueue($type, $process_type = NULL, $threshold = NULL) {
  $count = calais_build_queue($type, $process_type, $threshold);
  drupal_set_message(t('@count @type content items queued for Calais processing', array('@count' => $count, '@type' => $type)), 'status');
  drupal_goto('admin/settings/calais/queue');
}

/**
 * Form used to configure how nodes in the Calais queue are processed.
 */
function calais_enqueue_form($form_state) {
  $form['#theme'] = 'calais_enqueue_form';
  $form['type'] = array(
    '#type' => 'hidden', 
    '#default_value' => '',
  );
  $form['type_label'] = array(
    '#type' => 'item', 
    '#title' => t('Content Type'),
    '#value' => '<div id="calais-queue-type-label"></div>',
    '#description' => t('All content of this type will be added to the queue for tagging.'),
    '#attributes' => array('class' => "xoxoxox"),
  );
  $process_options = array(
    CALAIS_PROCESS_MANUAL => t('Suggest the terms, but let me tag the content'),
    CALAIS_PROCESS_AUTO => t('Automatically tag the content'),
  );  
  $processing = calais_get_processing_type($type);
  if ($processing == CALAIS_PROCESS_AUTO_ONCE) {
    $processing == CALAIS_PROCESS_AUTO;
  }
  $form['process_type'] = array(
    '#type' => 'radios',
    '#title' => t('Tag content'),
    '#default_value' => $processing,
    '#options' => $process_options,
  );  
  $threshold = calais_get_node_threshold($type);  
  $form["threshold"] = array(
    '#type' => 'textfield',
    '#size' => 5,
    '#title' => t('Minimum suggested tag relevancy'),
    '#default_value' => $threshold,
    '#description' => t('Determine how relevant a term must be in order for Calais to suggest it for a particular node.  Based on a 0.00-1.00 scale, with 0.00 being least relevant (i.e. many terms appear).'),
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Queue'), 
  );
  $form['buttons']['close'] = array(
    '#type' => 'button', 
    '#value' => t('Close'), 
  );
  return $form;
}

/**
 * Add the passed content type to the Calais bulk processing queue.
 */
function calais_enqueue_form_submit($form, $form_state) {
  $type = $form_state['values']['type'];
  $process_type = $form_state['values']['process_type'];
  $threshold = $form_state['values']['threshold'];
  if ($threshold == '' || !is_numeric($threshold)) {
    $threshold = NULL;
  }
  calais_enqueue($type, $process_type, $threshold);
}

/**
 * Theme function for the queue process.
 */
function theme_calais_enqueue_form($form) {
  drupal_add_css(drupal_get_path("module", "calais") ."/calais.admin.css");
  drupal_add_js(drupal_get_path("module", "calais") ."/calais.admin.js");
  
  $output = "<div id='calais-queue-form' style='display:none;'>";
  $output .= "<h2>" . t('Bulk process settings') . '</h2>';
  $output .= drupal_render($form);
  $output .= '</div>';
  return $output;
}

/**
 * Confirm form to delete all nodes of a particular type from the bulk Calais queue.
 */
function calais_queue_clear_confirm(&$form_state, $type) {
  $form['type'] = array(
    '#type' => 'value',
    '#value' => $type,
  );

  return confirm_form($form,
    t('Are you sure you want to clear the queue for: %type?', array('%type' => $type)),
    'admin/settings/calais/queue',
    t('This action cannot be undone.'),
    t('Clear'),
    t('Cancel')
  );
}

/**
 * Submit handler for Calais queue delete confirmation.
 */
function calais_queue_clear_confirm_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  db_query("DELETE FROM {calais_node_queue} WHERE nid IN (SELECT nid FROM {node} WHERE type = '%s')", $type);
  
  $form_state['redirect'] = 'admin/settings/calais/queue';
}


