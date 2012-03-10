<?php

// render callback
// editor render callback
// add callback
// edit callback
// title callback

/**
 * Implementation of hook_panels_content_types()
 */
function topichubs_panels_panels_content_types() {

  $items['panels_mini'] = array(
    'title' => t('Topichubs Panels'),
    'content_types' => 'topichubs_panels_content_types',
    'render callback' => 'topichubs_panels_content',
    'add callback' => 'topichubs_panels_add_mini_panel',
    'edit callback' => 'topichubs_panels_edit_mini_panel',
    'title callback' => 'topichubs_panels_title_mini_panel',
  );
  return $items;
  
}

/**
 * Return each available mini panel available as a subtype.
 */
function topichubs_panels_content_types() {

$plugins = topichubs_discover_plugins();
$topichub_panes = array();
foreach ($plugins as $type => $def) {
  $impl = _topichubs_new_handler_class($def);
  if($impl) {
    $pane = new StdClass();
    $pane->category = t('Topic Hubs');
    $pane->title = $def['title'];
    $pane->description = $def['description']; 
    $topichub_panes[] = $pane; 
//    $impl->init($type, $def, $node, $node->topichub->config[$type]);
//    $node->topichub->data[$type] = $impl->execute();
  }
}

  $types = array();
  
  foreach ($topichub_panes as $pane) {

    $types[$pane->title] = array(
      'title' => filter_xss_admin($pane->title),
      // For now mini panels will just use the contrib block icon.
      'icon' => 'icon_contrib_block.png',
      'path' => panels_get_path("content_types/block"),
      'description' => filter_xss_admin($pane->description),
      'category' => array(!empty($mini->category) ? filter_xss_admin($mini->category) : t('Topic Hubs'), -8),
    );
  }
  return $types;
}

/**
 * Statically store all used IDs to ensure all mini panels get a unique id.
 */
function topichubs_panels_get_id($name) {
  static $id_cache = array();

  $id = 'topichubs-pane-' . $name;
  if (!empty($id_cache[$name])) {
    $id .= "-" . $id_cache[$name]++;
  }
  else {
    $id_cache[$name] = 1;
  }

  return $id;
}

/**
 * Render a topichubs pane called from a panels display.
 */
function topichubs_panels_content($subtype, $conf, $panel_args, &$contexts) {

  panels_load_include('plugins');
  
  $implementation_identified = FALSE;
  $impl_def = topichubs_lookup_plugin_by_name($conf['name']);
  if (empty($impl_def)) {
    $content = '';
  }
  else {
    $implementation_identified = TRUE;
  }
  
  if ($implementation_identified) {
    $impl = _topichubs_new_handler_class($impl_def->def);
    if($impl && arg(0) =='node' && is_numeric(arg(1))) {
      $node = node_load(arg(1));
      $impl->init($impl_def->type, $def, $node, $node->topichub->config[$impl_def->type]);
      $data = $impl->execute();
      $content = $data['#view'];
    } 
    else {
      $content = '';
    }
  }
  else {
    $content = '';
  }

//  echo "<pre>".print_r ( $node->nid,true)."</pre>";   
//  echo "<pre>".print_r ( $impl_def,true)."</pre>";
//  echo "<pre>".print_r ( $impl,true)."</pre>";  
//  echo "<pre>".print_r ( $content,true)."</pre>";    
//  exit();

  $block = new stdClass();
  $block->module  = 'topichubs_panels';
  $block->delta   = $conf['name'];
  $block->subject = filter_xss_admin($conf['name']);

  $block->content = $content;

  
  return $block;
}

/**
 * Form to add a mini panel to a panel.
 */
function topichubs_panels_add_mini_panel($id, $parents, $conf = array()) {
  $conf['name'] = $id;
  return topichubs_panels_edit_mini_panel($id, $parents, $conf);
}

/**
 * Returns an edit form for the mini panel.
 *
 * There isn't much here as most of this is set up at mini panel creation time.
 */
function topichubs_panels_edit_mini_panel($id, $parents, $conf) {
  $form['name'] = array(
    '#type' => 'value',
    '#value' => $conf['name'],
  );

  return $form;
}

function topichubs_panels_title_mini_panel($subtype, $conf) {

  return $conf['name'];
  
}

// ---------------------------------------------------------------------------
// Database functions.

/**
 * A list of the fields used in the panel_mini table.
 */
function topichubs_panels_fields() {
  return array(
    'name' => "'%s'",
    'category' => "'%s'",
    'title' => "'%s'",
    'contexts' => "'%s'",
    'requiredcontexts' => "'%s'",
    'relationships' => "'%s'",
  );
}


/**
 * Sanitize a mini panel, to guarantee certain data is as we believe it will be.
 */
function topichubs_panels_sanitize($mini) {
  foreach (array('contexts', 'relationships', 'requiredcontexts') as $id) {
    if (!isset($mini->$id) || !is_array($mini->$id)) {
      $mini->$id = array();
    }
  }

  return $mini;
}

/**
 * Fetch all mini panels in the system.
 *
 * This function does not cache.
 */
function topichubs_panels_load_all($page_size = 0) {
  static $results = array();

  if (array_key_exists($page_size, $results)) {
    return $results[$page_size];
  }

  $panels = $dids = array();
  $query = "SELECT * FROM {panels_mini}";
  if ($page_size) {
    $result = pager_query($query, $page_size);
  }
  else {
    $result = db_query($query);
  }

  while ($mini = db_fetch_object($result)) {
    $mini->contexts = (!empty($mini->contexts)) ? unserialize($mini->contexts) : array();
    $mini->requiredcontexts = (!empty($mini->requiredcontexts)) ? unserialize($mini->requiredcontexts) : array();
    $mini->relationships = (!empty($mini->relationships)) ? unserialize($mini->relationships) : array();
    $mini->category = (!empty($mini->category)) ? $mini->category : 'Mini panels';

    $mini->type = t('Local');
    $panels[$mini->name] = topichubs_panels_sanitize($mini);
  }

  $status = variable_get('panel_mini_defaults', array());
  foreach (topichubs_panels_default_panels() as $mini) {
    // Determine if default panel is enabled or disabled.
    if (isset($status[$mini->name])) {
      $mini->disabled = $status[$mini->name];
    }

    if (!empty($panels[$mini->name])) {
      $panels[$mini->name]->type = t('Overridden');
    }
    else {
      $mini->type = t('Default');
      $panels[$mini->name] = $mini;
    }
  }
  $results[$page_size] = $panels;

  return $results[$page_size];
}

/**
 * Load a mini panel.
 */
function topichubs_panels_load($pid) {
  static $cache = array();

  if (array_key_exists($pid, $cache)) {
    return $cache[$pid];
  }

  $where = is_numeric($pid) ? 'pid = %d' : "name = '%s'";
  $panel_mini = db_fetch_object(db_query("SELECT * FROM {panels_mini} WHERE $where", $pid));

  if (!$panel_mini) {
    $defaults = topichubs_panels_default_panels();
    if (isset($defaults[$pid])) {
      $panel_mini = $defaults[$pid];
      $status = variable_get('panel_mini_defaults', array());
      // Determine if default panel is enabled or disabled.
      if (isset($status[$panel_mini->name])) {
        $panel_mini->disabled = $status[$panel_mini->name];
      }
      $cache[$pid] = $panel_mini;
      return $panel_mini;
    }
    return;
  }

  $panel_mini->contexts = (!empty($panel_mini->contexts)) ? unserialize($panel_mini->contexts) : array();
  $panel_mini->requiredcontexts = (!empty($panel_mini->requiredcontexts)) ? unserialize($panel_mini->requiredcontexts) : array();
  $panel_mini->relationships = (!empty($panel_mini->relationships)) ? unserialize($panel_mini->relationships) : array();

  $cache[$pid] = topichubs_panels_sanitize($panel_mini);
  $cache[$pid]->display = panels_load_display($cache[$pid]->did);

  return $cache[$pid];
}

/**
 * Save a mini panel.
 */
function topichubs_panels_save(&$panel_mini) {
  $fields = $types = $values = $pairs = array();
  // Save the display if one was given to us.
  if (!empty($panel_mini->display)) {
    $display = panels_save_display($panel_mini->display);
  }

  // Ensure empty values get translated correctly.
  // Also make sure we don't mess up the original.
  $mini_clone = drupal_clone(topichubs_panels_sanitize($panel_mini));

  // If pid is set to our "magic value", this is an insert, otherwise an update.
  $insert = $mini_clone->pid && $mini_clone->pid == 'new';

  // Build arrays of fields and types (resp. pairs of both) and of values.
  foreach (topichubs_panels_fields() as $field => $type) {
    // Skip empty values.
    if (isset($mini_clone->$field)) {
      if ($insert) {
        $fields[] = $field;
        $types[] = $type;
      }
      else {
        $pairs[] = "$field = $type";
      }
      // Build the $values array, serializing some fields.
      $serialize = in_array($field, array('contexts', 'requiredcontexts', 'relationships'));
      $values[] = $serialize ? serialize($mini_clone->$field) : $mini_clone->$field;
    }
  }

  if ($insert) {
    // Build the query adding the new primary key and the did.
    $sql = 'INSERT INTO {panels_mini} (' . implode(', ', $fields) . ', did) VALUES (' . implode(', ', $types) . ', %d)';
    $values[] = $display->did;
    db_query($sql, $values);

    // Determine the new primary key.
    $mini_clone->pid = db_last_insert_id('panels_mini', 'pid');
  }
  else {
    // Build the query filtering by the primary key.
    $sql = 'UPDATE {panels_mini} SET ' . implode(', ', $pairs) . ' WHERE pid = %d';
    $values[] = $mini_clone->pid;
    db_query($sql, $values);
  }

  return $mini_clone->pid;
}

/**
 * Delete a mini panel.
 */
function topichubs_panels_delete($panel_mini) {
  db_query("DELETE FROM {panels_mini} WHERE pid = %d", $panel_mini->pid);
  db_query("DELETE FROM {blocks} WHERE module = 'panels_mini' AND delta = %d", $panel_mini->pid);
  return panels_delete_display($panel_mini->did);
}

/**
 * Export a mini panel into PHP code for use in import.
 *
 * The code returned from can be used directly in topichubs_panels_save().
 */
function topichubs_panels_export($panel_mini, $prefix = '') {
  $output = '';
  $fields = topichubs_panels_fields();
  $output .= $prefix . '$mini = new stdClass()' . ";\n";
  $output .= $prefix . '$mini->pid = \'new\'' . ";\n";
  foreach ($fields as $field => $sub) {
    $output .= $prefix . '  $mini->' . $field . ' = ' . panels_var_export($panel_mini->$field, '  ') . ";\n";
  }
  // Export the primary display
  $display = !empty($panel_mini->display) ? $panel_mini->display : panels_load_display($panel_mini->did);
  $output .= panels_export_display($display, $prefix);
  $output .= $prefix . '$mini->display = $display' . ";\n";

  return $output;
}

/**
 * Get all 'default' mini panels.
 */
function topichubs_panels_default_panels() {
  $panels = module_invoke_all('default_panel_minis');
  if (!is_array($panels)) {
    $panels = array();
  }

  return $panels;
}

/**
 * Remove the block version of mini panels from being available content types.
 */
function topichubs_panels_panels_block_info($module, $delta, &$info) {
  $info = NULL;
}

/**
 * Implementation of hook_panels_exportables().
 */
function topichubs_panels_panels_exportables($op = 'list', $panels = NULL, $name = 'foo') {
  static $all_panels = NULL;
  if ($op == 'list') {
    if (empty($all_panels)) {
      $all_panels = topichubs_panels_load_all();
    }

    foreach ($all_panels as $name => $panel) {
      $return[$name] = check_plain($name) . ' (' . check_plain($panel->title) . ')';
    }
    return $return;
  }

  if ($op == 'export') {
    $code = "/**\n";
    $code .= " * Implementation of hook_default_panel_minis()\n";
    $code .= " */\n";
    $code .= "function " . $name . "_default_panel_minis() {\n";
    foreach ($panels as $panel => $truth) {
      $code .= topichubs_panels_export($all_panels[$panel], '  ');
      $code .= '  $minis[\'' . check_plain($panel) . '\'] = $mini;' . "\n\n\n";
    }
    $code .= "  return \$minis;\n";
    $code .= "}\n";
    return $code;
  }
}


/**
 * Menu callback to check to see if a mini panel is valid as part
 * of a path, and if it is, return the mini.
 */
function topichubs_panels_admin_load($name) {
  $mini = topichubs_panels_load($name);
  if ($mini && empty($mini->disabled)) {
    return $mini;
  }
}
