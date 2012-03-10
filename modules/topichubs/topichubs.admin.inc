<?php

function topichubs_admin_overview() {
  $header = array(
    t('Title'),
    t('Commands'),
  );
  $rows = array();
  $result = pager_query("SELECT n.nid, n.title FROM {node} n WHERE n.type = 'topichub'", 50, 0);
  while ($topichub = db_fetch_object($result)) {
    $commands = array(
      l(t('Configure'), 'node/'. $topichub->nid .'/topichub'),
      l(t('Delete'), 'node/'. $topichub->nid .'/delete'),
    );
    $rows[] = array(
        l($topichub->title, "node/$topichub->nid"),
        theme('item_list', $commands)
    );
  }
  $output .= theme('table', $header, $rows);
  $output .= theme('pager', 0, 50);
  return $output;
}

/**
 * Listing page for hot topics
 */
function topichubs_hot_topics_page() {
  $header = array(
    t('Term'),
    t('Count'),
    t('Hubs with Term'),
    t('Commands'),
  );
  $rows = array();
   
  $rows = _get_terms_by_node_count(variable_get('hot_topic_ignore', NULL));

  $output .= theme('table', $header, $rows);
  $output .= theme('pager', 0, 50);
  return $output;
}


/**
 * Page to display button to update from Panel 2 to 3
 */
function topichubs_update_page() {
  if (variable_get('topichubs_panel_update_run', 0)) {
    return t('Your Topic Hubs have been updated.');
  }
  else {
    return drupal_get_form('topichubs_update_form');
  }
}

/**
 * This form is just a button to click to start the update process
 */
function topichubs_update_form() {
  $form = array();
  $form['intro'] = array(
    '#value' => '<p>'.t('Clicking the button below will run a database update to update your Topic Hubs from Panels 2 to 3. As with any database update, please backup your database before updating.').'</p>',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Run Update',
  );
  return $form;
}

/**
 *  Handle the update form submission and call the update function
 */
function topichubs_update_form_submit() {
  if (!variable_get('topichubs_panel_update_run', 0)) {
    $success = _update_panel_pane_type();
    if ($success) {
      return t('Your Topic Hubs have been updated.');
    }
    else {
      return t('There was a problem with the update, please check the log for errors.');
    }
  }
  else {
    return t('You have already run the update.');
  }
}

/**
 * Get all taxonomy terms ordered by frequency used.
 *
 * @param $ignore
 *    An array of vocabulary ids to not include in this list.
 * @param $per_page
 *    The number of terms to show on each page
 */
function _get_terms_by_node_count($ignore = NULL, $per_page = 50) {
  $sql = "SELECT td.name, t.tid, COUNT(n.nid) AS count ";
  $sql .= "FROM {term_node} t ";
  $sql .= "INNER JOIN {node} n ON t.vid = n.vid ";
  $sql .= "INNER JOIN {term_data} td ON t.tid = td.tid ";
  $sql .= "WHERE n.status = 1 ";
  if(!empty($ignore))
    $sql .= "AND td.vid NOT IN (" . implode(",",$ignore) . ") ";
    
  $sql .= "GROUP BY t.tid ORDER BY count DESC";
  

  $count_query = "SELECT COUNT(DISTINCT(t.tid)) FROM {term_node} t ";
  if(!empty($ignore)) {
    $count_query .= "JOIN {term_data} td ON td.tid = t.tid "; 
    $count_query .= "WHERE td.vid NOT IN (" . implode(",",$ignore) . ") ";
  }

  $result = pager_query($sql, $per_page, 0, $count_query);
  
  $rows = array();
  while($item = db_fetch_array($result)) {
    $count = _topichub_count_by_tid($item['tid']);
    $item['hub_count'] = $count ? format_plural($count, '1 Hub', '@count Hubs') : '';
    $item['commands'] = _get_topichub_commands($item['tid']);
    unset($item['tid']);
    $rows[] = $item;
  }
  
  return $rows;
}

/**
 * Get the various commands that can be done on the hot topics page.
 */
function _get_topichub_commands($tid) {
  $commands = array();
  $commands[] = l("Create a Topic Hub", "node/add/topichub/topichubs", array('query' => array('tid' => $tid)));  
  return implode(', ', $commands);
}

/**
 * Returns the number of topic hubs that exist already with the provided term id
 * @return int 
 *    The count
 */
function _topichub_count_by_tid($tid) {
  return db_result(db_query("SELECT count(distinct(nid)) FROM {topichub_condition} WHERE tid = %d", $tid));
}

/**
 * Update 'panels_mini' to 'topichub' pane type for exiting topic hubs.
 * This is necessary after a panels update from version 2 to 3.
 * @return bool
 *    success
 */
function _update_panel_pane_type() {
  $success = true;
  $result = db_query("SELECT pp.did FROM {panels_pane} pp INNER JOIN {panels_node} pn ON pn.did = pp.did INNER JOIN {node} n ON n.nid = pn.nid WHERE n.type= 'topichub' AND pp.type = 'panels_mini'");
  
  while($item = db_fetch_array($result)) {
    $updated = db_query("UPDATE {panels_pane} SET type = 'topichubs' WHERE did = %d", $item['did']);
    if (!$updated) {
      $success = false;
    }
  }
  
  if ($success) {
    variable_set('topichubs_panel_update_run', 1);
    watchdog(t('Topic Hubs'), t("Topic Hubs updated from Panels 2 to 3 successfully!"), NULL, WATCHDOG_INFO);
  }
  else {
    drupal_set_message(t('Topic Hubs update failed! Check the log for any errors.'));
    watchdog(t('Topic Hubs'), t("Topic Hubs update from Panels 2 to 3 failed!"), NULL, WATCHDOG_ERROR);
  }
  
  return $success;
}

/**
 * Global settings for Topichubs.
 */
function topichubs_settings(&$form_state) {
  drupal_add_css(drupal_get_path('module', 'topichubs') . "/topichubs-admin.css");
  $form = array();    

  $form['topic_hub_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Settings'),    
  );

  $vocabs = taxonomy_get_vocabularies();
  $options = array();
  foreach($vocabs as $vocab) {
    $options["$vocab->vid"] = $vocab->name;
  }

  $form['topic_hub_settings']['topic_hub_vocab_ignore'] = array(
    '#prefix' => '<div class="topic-hub-settings">',
    '#suffix' => '</div>',
    '#type' => 'select',
    '#title' => t("Disregarded Vocabularies"),
    '#description' => t('Any vocabulary selected will not be listed under the Hot Topics section'),
    '#multiple' => true,
    '#options' => $options,
    '#default_value' => variable_get('hot_topic_ignore', NULL),
  );

  $types = node_get_types();
  $options = array();
  foreach($types as $type => $info) {
    $options[$type] = $info->name;
  }
  
  $form['topic_hub_settings']['topic_hub_plugin_type_default'] = array(
    '#prefix' => '<div class="topic-hub-settings">',
    '#suffix' => '</div>',
    '#type' => 'checkboxes',
    '#title' => 'Global Plugin Type Defaults',
    '#description' => t('If a plugin is allowed to pick which content types it can work with, then the types selected here are used as the default setting.'),
    '#options' => $options,
    '#default_value' => variable_get("topic_hub_plugin_type_default", array_keys($options)),
  );
  
  $parent = 'topic_hub_plugins';
  
  $form[$parent] = array(
    '#type' => 'fieldset',
    '#title' => t("Plugin Settings"),
  );
  
  $plugins = topichubs_discover_plugins();  
  foreach($plugins as $type => $def) {
    $impl = _topichubs_new_handler_class($def);
    if($impl) {
      $impl->init($type, $def, $node, $node->topichub->config[$type]);
      $impl->build_form('settings', $form[$parent], $form_state);
    }    
  }
  
  return system_settings_form($form);
}

