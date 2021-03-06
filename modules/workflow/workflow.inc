<?php

/**
 * @file
 * Worfklow API and CRUD functions.
 */

/**
 * Load function.
 *
 * @param $name
 *   The machine name of the workflow to load.
 * @return $workflow
 *   Object representing the workflow.
 */
function workflow_load($name) {
  $workflows = workflow_load_all();

  return empty($workflows[$name]) ? FALSE : $workflows[$name];
}

/**
 * Get all workflows.
 *
 * @param $reset
 *   Boolean to clear the cached workflows.
 * @return
 *   An array of workflows.
 */
function workflow_load_all($reset = FALSE) {
  static $workflows;

  if (is_null($workflows) || $reset) {
    // See if we have a populated cache first.
    if (!$reset && $cache = cache_get('workflows')) {
      $workflows = $cache->data;
      return $workflows;
    }

    $workflows = array();

    // Load all workflows from the database.
    $result = db_query("SELECT * FROM {workflows} ORDER BY label ASC");
    while ($workflow = db_fetch_object($result)) {
      // Sanitize the label.
      $workflow->label = check_plain(t($workflow->label));
      // Unserialize the options.
      $workflow->options = unserialize($workflow->options);
      // Load up the states.
      $workflow->states = workflow_get_states($workflow->name);
      $workflows[$workflow->name] = $workflow;
    }

    // Load up any workflows from code and save them to the database.
    $default_workflows = module_invoke_all('workflow_default_workflows');
    drupal_alter('workflow_default_workflows', $default_workflows);

    foreach ($default_workflows as $workflow) {
      if (empty($workflows[$workflow->name])) {
        $workflow = workflow_create($workflow);
        $workflows[$workflow->name] = $workflow;
      }
    }

    cache_set('workflows', $workflows);
  }

  return $workflows;
}

/**
 * Get all workflow labels.
 *
 * @return
 *   An array of workflow names.
 */
function workflow_load_all_labels() {
  static $labels;

  if (is_null($labels)) {
    $labels = array();

    foreach (workflow_load_all() as $key => $workflow) {
      $labels[$key] = $workflow->label;
    }
  }

  return $labels;
}

/**
 * Update the transitions for a workflow.
 *
 * @param array $transitions
 *   Transitions, for example:
 *     18 => array(
 *       20 => array(
 *         'author' => 1,
 *         1        => 0,
 *         2        => 1,
 *       )
 *     )
 *   means the transition from state 18 to state 20 can be executed by
 *   the node author or a user in role 2. The $transitions array should
 *   contain ALL transitions for the workflow.
 */
function workflow_update_transitions($transitions = array()) {
  // Empty string is sometimes passed in instead of an array.
  if (!$transitions) {
    return;
  }

  foreach ($transitions as $from => $to_data) {
    foreach ($to_data as $to => $role_data) {
      foreach ($role_data as $role => $can_do) {
        if ($can_do) {
          workflow_transition_add_role($from, $to, $role);
        }
        else {
          workflow_transition_delete_role($from, $to, $role);
        }
      }
    }
  }
  db_query("DELETE FROM {workflow_transitions} WHERE roles = ''");
}

/**
 * Add a role to the list of those allowed for a given transition.
 *
 * Add the transition if necessary.
 *
 * @param $from
 *   The machine name of the originating state.
 * @param $to
 *   The machine name of the target state.
 * @param mixed $role
 *   Int (role ID) or string ('author').
 */
function workflow_transition_add_role($from, $to, $role) {
  $transition = array(
    'state_name' => $from,
    'target_state_name' => $to,
    'roles' => $role,
  );
  $tid = workflow_get_transition_id($from, $to);
  if ($tid) {
    $roles = db_result(db_query("SELECT roles FROM {workflow_transitions} WHERE tid=%d", $tid));
    $roles = explode(',', $roles);
    if (array_search($role, $roles) === FALSE) {
      $roles[] = $role;
      $transition['roles'] = implode(',', $roles);
      $transition['tid'] = $tid;
      drupal_write_record('workflow_transitions', $transition, 'tid');
    }
  }
  else {
    drupal_write_record('workflow_transitions', $transition);
  }
}

/**
 * Remove a role from the list of those allowed for a given transition.
 *
 * @param $from
 *   The machine name of the originating state.
 * @param $to
 *   The machine name of the target state.
 * @param mixed $role
 *   Int (role ID) or string ('author').
 */
function workflow_transition_delete_role($from, $to, $role) {
  $tid = workflow_get_transition_id($from, $to);
  if ($tid) {
    $roles = db_result(db_query("SELECT roles FROM {workflow_transitions} WHERE tid=%d", $tid));
    $roles = explode(',', $roles);
    if (($i = array_search($role, $roles)) !== FALSE) {
      unset($roles[$i]);
      db_query("UPDATE {workflow_transitions} SET roles='%s' WHERE tid=%d", implode(',', $roles), $tid);
    }
  }
}

/**
 * See if a transition is allowed for a given role.
 *
 * @param int $tid
 * @param mixed $role
 *   A single role (int or string 'author') or array of roles.
 * @return
 *   TRUE if the role is allowed to do the transition.
 */
function workflow_transition_allowed($tid, $role = NULL) {
  $allowed = db_result(db_query("SELECT roles FROM {workflow_transitions} WHERE tid = %d", $tid));
  $allowed = explode(',', $allowed);
  if ($role) {
    if (!is_array($role)) {
      $role = array($role);
    }
    return array_intersect($role, $allowed) ==  TRUE;
  }
}

/**
 * Tell caller whether a state is a protected system state, such as the creation state.
 *
 * @param $state
 *   The label of the state to test
 * @return
 *   TRUE if the state is a system state.
 */
function workflow_is_system_state($state) {
  static $states;
  if (!isset($states)) {
    $states = array(t('(creation)') => TRUE);
  }
  return isset($states[$state]);
}

/**
 * Given the machine name of a workflow, return its label.
 *
 * @param string $name
 *   The machine name of the workflow.
 * @return string
 *   The name of the workflow.
 */
function workflow_get_label($name) {
  $label = db_result(db_query("SELECT label FROM {workflows} WHERE name = '%s'", $name));
  return check_plain(t($label));
}

/**
 * Get ID of a workflow for a node type.
 *
 * @param $type
 *   Machine readable node type name, e.g. 'story'.
 * @return string
 *   The machine name of the workflow or FALSE if no workflow is mapped to this type.
 */
function workflow_get_workflow_for_type($type) {
  static $cache;

  if(empty($cache[$type])) {
    $sql = "SELECT workflow_name FROM {workflow_type_map} WHERE type = '%s'";
    $cache[$type] = db_result(db_query($sql, $type));
  }

  return empty($cache[$type]) ? FALSE : $cache[$type];
}

/**
 * Create a workflow and its (creation) state.
 *
 * @param $workflow
 *   An array of values needed to create a workflow.
 * @return
 *   The saved workflow object.
 */
function workflow_create($workflow) {
  $default = array('options' => array('comment_log_node' => 1, 'comment_log_tab' => 1));
  $workflow += $default;

  $workflow = (object) $workflow;

  if (drupal_write_record('workflows', $workflow)) {
    if (empty($workflow->states)) {
      $state = array(
        'name' => _workflow_creation_state($workflow->name),
        'workflow_name' => $workflow->name,
        'label' => t('(creation)'),
        'sysid' => WORKFLOW_CREATION,
        'weight' => WORKFLOW_CREATION_DEFAULT_WEIGHT,
      );
      workflow_state_save($state);
    }
    else {
      // Save each workflow state.
      array_walk($workflow->states, 'workflow_state_save');
    }
    // Workflow creation affects tabs (local tasks), so force menu rebuild.
    menu_rebuild();
  }

  return $workflow;
}

/**
 * Update an existing workflow.
 *
 * @param $workflow
 *   The workflow object to update.
 * @return
 *   The updated workflow object.
 */
function workflow_update($workflow) {
  $workflow = (object) $workflow;
  $workflow->tab_roles = is_array($workflow->tab_roles) ? implode(',', $workflow->tab_roles) : $workflow->tab_roles;
  $workflow = drupal_write_record('workflows', $workflow, 'wid');

  // Workflow name change affects tabs (local tasks), so force menu rebuild.
  menu_rebuild();

  return $workflow;
}

/**
 * Delete a workflow from the database. Deletes all states,
 * transitions and node type mappings, too. Removes workflow state
 * information from nodes participating in this workflow.
 *
 * @param $name
 *   The machine name of the workflow.
 */
function workflow_deletewf($name) {
  $result = db_query("SELECT * FROM {workflow_states} WHERE workflow_name = '%s'", $name);
  while ($state = db_fetch_object($result)) {
    // Delete the state and any associated transitions and actions.
    workflow_state_delete($state->name);
    db_query("DELETE FROM {workflow_node} WHERE state_name = '%s'", $state->name);
  }
  db_query("DELETE FROM {workflow_type_map} WHERE workflow_name = '%s'", $name);
  db_query("DELETE FROM {workflows} WHERE name = '%s'", $name);
  // Notify any interested modules.
  module_invoke_all('workflow', 'workflow delete', $name, NULL, NULL);
  // Workflow deletion affects tabs (local tasks), so force menu rebuild.
  cache_clear_all('*', 'cache_menu', TRUE);
  menu_rebuild();
}

/**
 * Load workflow states for a workflow from the database. If $machine_name is 
 * not passed, all states for all workflows are given. States that have been 
 * deleted are not included.
 *
 * @param $workflow_name
 *   The machine name of the workflow.
 * @param $all
 *   If TRUE, will return all workflows, regardless of status.
 * @return
 *   An array of workflow states.
 */
function workflow_get_states($workflow_name = NULL, $all = FALSE) {
  $states = array();

  if (isset($workflow_name) && $all) {
    $query = "SELECT * FROM {workflow_states} WHERE workflow_name = '%s' ORDER BY weight, label";
    $result = db_query($query, $workflow_name);
  }
  else if (isset($workflow_name)) {
    $query = "SELECT * FROM {workflow_states} WHERE workflow_name = '%s' AND status = 1 ORDER BY weight, label";
    $result = db_query($query, $workflow_name);
  }
  else if ($all) {
    $query = "SELECT * FROM {workflow_states} ORDER BY weight, label";
    $result = db_query($query);
  }
  else {
    $query = "SELECT * FROM {workflow_states} WHERE status = 1 ORDER BY weight, label";
    $result = db_query($query);
  }

  while ($data = db_fetch_object($result)) {
    if (is_null($workflow_name)) {
      $workflow = workflow_load($data->workflow_name);
      $data->label = $workflow->label .': '. $data->label;
    }
    $data->label = check_plain(t($data->label));
    $states[$data->name] = $data;
  }

  return $states;
}

/**
 * Load workflow state names for a workflow from the database. If $workflow_name 
 * is not passed, all states for all workflows are given. States that have been 
 * deleted are not included.
 *
 * @param $workflow_name
 *   The machine name of the workflow.
 * @param $all
 *   If TRUE, will return all workflows, regardless of status.
 * @return
 *   An array of workflow states.
 */
function workflow_get_state_labels($workflow_name = NULL, $all = FALSE) {
  $states = workflow_get_states($workflow_name, $all);

  foreach ($states as $name => $state) {
    $states[$name] = $state->label;
  }

  return $states;
}

/**
 * Given the machine name of a workflow state, return a keyed array representing
 * the state.
 *
 * @param $name
 *   The machine name of the workflow state.
 * @param $active_only
 *   Boolean to indicate to only return active states. Defaults to FALSE.
 * @return
 *   The workflow state object.
 */
function workflow_get_state($name, $active_only = FALSE) {
  $sql = "SELECT * FROM {workflow_states} WHERE name = '%s'";

  if ($active_only) {
    $sql .= " AND status = 1";
  }
  
  $result = db_query($sql, $name);
  // State IDs are unique, so there should be only one row.
  if ($state = db_fetch_object($result)) {
    $state->label = check_plain(t($state->label));
  }

  return $state;
}

/**
 * Given the ID of a state, return its name.
 *
 * @param integer $sid
 *   The ID of the workflow state.
 * @return string
 *   The name of the workflow state.
 */
function workflow_get_state_label($sid) {
  return db_result(db_query('SELECT label FROM {workflow_states} WHERE sid = %d', $sid));
}


/**
 * Add or update a workflow state to the database.
 *
 * @param $edit
 *   An array containing values for the new or updated workflow state.
 * @return
 *   The ID of the new or updated workflow state.
 */
function workflow_state_save($state) {
  if (!isset($state['sid'])) {
    drupal_write_record('workflow_states', $state);
  }
  else {
    drupal_write_record('workflow_states', $state, 'sid');
  }

  return $state;
}

/**
 * Delete a workflow state from the database, including any
 * transitions the state was involved in and any associations
 * with actions that were made to that transition.
 *
 * @param $name
 *   The machine name of the state to delete.
 * @param $new_name
 *   Deleting a state will leave any nodes to which that state is assigned
 *   without a state. If $new_state is given, it will be assigned to those
 *   orphaned nodes.
 */
function workflow_state_delete($name, $new_name = NULL) {
  if ($new_name && $new_state = workflow_get_state($new_name)) {
    // Assign nodes to new state so they are not orphaned.
    // A candidate for the batch API.
    $node = new stdClass();
    $node->workflow_stamp = time();
    $result = db_query("SELECT nid FROM {workflow_node} WHERE state_name = '%s'", $name);
    while ($data = db_fetch_object($result)) {
      $node->nid = $data->nid;
      $node->_workflow = $name;
      _workflow_write_history($node, $new_name, t('Previous state deleted'));
      db_query("UPDATE {workflow_node} SET state_name = '%s' WHERE nid = %d AND state_name = '%s'", $new_name, $data->nid, $name);
    }
  }
  else {
    // Go ahead and orphan nodes.
    db_query("DELETE from {workflow_node} WHERE state_name = '%s'", $name);
  }

  // Delete all associated transitions this state is involved in.
  $result = db_query("SELECT tid FROM {workflow_transitions} WHERE state_name = '%s' OR target_state_name = '%s'", $name, $name);
  while ($data = db_fetch_object($result)) {
    workflow_transition_delete($data->tid);
  }

  // Disable the state.
  db_query("UPDATE {workflow_states} SET status = 0 WHERE name = '%s'", $name);
  // Notify interested modules.
  module_invoke_all('workflow', 'state delete', $name, NULL, NULL);
}

/**
 * Delete a transition (and any associated actions).
 *
 * @param $tid
 *   The ID of the transition.
 */
function workflow_transition_delete($tid) {
  $actions = workflow_get_actions($tid);
  foreach ($actions as $aid => $type) {
    workflow_actions_remove($tid, $aid);
  }
  db_query("DELETE FROM {workflow_transitions} WHERE tid = %d", $tid);
  // Notify interested modules.
  module_invoke_all('workflow', 'transition delete', $tid, NULL, NULL);
}

/**
 * Save mapping of workflow to node type. E.g., "the story node type is using 
 * the Foo workflow."
 *
 * @param $form_state['values']
 */
function workflow_types_save($form_values) {
  db_query("DELETE FROM {workflow_type_map}");
  $node_types = node_get_types();
  foreach ($node_types as $type => $name) {
    db_query("INSERT INTO {workflow_type_map} (type, workflow_name) VALUES ('%s', '%s')", $type, $form_values[$type]['workflow_name']);
    variable_set('workflow_' . $type, array_keys(array_filter(($form_values[$type]['placement']))));
  }
}

/**
 * Validate target state and either execute a transition immediately or schedule
 * a transition to be executed later by cron.
 *
 * @param $node
 * @param $state_name
 *   The machine name of the target state
 */
function workflow_transition($node, $state_name) {
  // Make sure new state is a valid choice.
  if (array_key_exists($state_name, workflow_field_choices($node))) {
    if (!$node->workflow_scheduled) {
      // Clear $node->workflow_comment so we don't process comment more
      // than once in case of subsequent nodeapi updates during one request
      // Modules that hook on workflow should get comment from DB (directly or using Token module)
      // instead of taking it out of $node object.
      $comment = isset($node->workflow_comment) ? $node->workflow_comment : NULL;
      unset($node->workflow_comment);
      // It's an immediate change. Do the transition.
      workflow_execute_transition($node, $state_name, $comment);
    }
    else {
      // Schedule the the time to change the state.
      $comment = $node->workflow_comment;
      $old_state_name = workflow_node_current_state($node);

      if ($node->workflow_scheduled_date['day'] < 10) {
        $node->workflow_scheduled_date['day'] = '0' .
        $node->workflow_scheduled_date['day'];
      }

      if ($node->workflow_scheduled_date['month'] < 10) {
        $node->workflow_scheduled_date['month'] = '0' .
        $node->workflow_scheduled_date['month'];
      }

      if (!$node->workflow_scheduled_hour) {
        $node->workflow_scheduled_hour = '00:00';
      }

      $scheduled = $node->workflow_scheduled_date['year'] . $node->workflow_scheduled_date['month'] . $node->workflow_scheduled_date['day'] . ' ' . $node->workflow_scheduled_hour . 'Z';
      if ($scheduled = strtotime($scheduled)) {
        // Adjust for user and site timezone settings.
        global $user;
        if (variable_get('configurable_timezones', 1) && $user->uid && strlen($user->timezone)) {
          $timezone = $user->timezone;
        }
        else {
          $timezone = variable_get('date_default_timezone', 0);
        }
        $scheduled = $scheduled - $timezone;

        // Clear previous entries and insert.
        db_query("DELETE FROM {workflow_scheduled_transition} WHERE nid = %d", $node->nid);
        db_query("INSERT INTO {workflow_scheduled_transition} (nid, old_state_name, state_name, scheduled, comment) VALUES (%d, '%s', '%s', %d, '%s')", $node->nid, $old_state_name, $state_name, $scheduled, $comment);

        $t_args = array(
          '@node_title' => $node->title,
          '%state_name' => workflow_get_state_label($state_name),
          '!scheduled_date' => format_date($scheduled),
        );
        watchdog('workflow', '@node_title scheduled for state change %state_name on !scheduled_date', $t_args, WATCHDOG_NOTICE, l('view', "node/$node->nid/workflow"));
        drupal_set_message(t('<em>@node_title</em> is scheduled for state change <em>%state_name</em> on <em>!scheduled_date</em> (processed every 15 minutes).', $t_args));
      }
    }
  }
}

/**
 * Get allowable transitions for a given workflow state. Typical use:
 *
 * global $user;
 * $possible = workflow_allowable_transitions($state_name, 'to', $user->roles);
 *
 * If the state name corresponded to the state named "Draft", $possible now
 * contains the states that the current user may move to from the Draft state.
 *
 * @param $state_name
 *   The machine name of the state in question.
 * @param $dir
 *   The direction of the transition: 'to' or 'from' the state denoted by
 *   $state_name. When set to 'to' all the allowable states that may be moved to
 *   are returned; when set to 'from' all the allowable states that may move to
 *   the current state are returned.
 * @param mixed $roles
 *   Array of ints (and possibly the string 'author') representing the user's
 *   roles. If the string 'ALL' is passed (instead of an array) the role
 *   constraint is ignored (this is the default for backwards compatibility).
 *
 * @return
 *   Associative array of states ($state_name => $state_label pairs), excluding
 *   current state.
 */
function workflow_allowable_transitions($state_name, $dir = 'to', $roles = 'ALL') {
  $transitions = array();

  if ($dir == 'to') {
    $field = 'target_state_name';
    $field_where = 'state_name';
  }
  else {
    $field = 'state_name';
    $field_where = 'target_state_name';
  }

  $result = db_query(
    "(SELECT t.tid, t.%s as state_name, s.label AS state_label, s.weight AS state_weight "
    . "FROM {workflow_transitions} t "
    . "INNER JOIN {workflow_states} s "
    . "ON s.name = t.%s "
    . "WHERE t.%s = '%s' AND s.status = 1 "
    . "ORDER BY state_weight) "
    . "UNION "
    . "(SELECT s.sid as tid, s.name as state_name, s.label as state_label, s.weight as state_weight "
    . "FROM {workflow_states} s "
    . "WHERE s.name = '%s' AND s.status = 1) "
    . "ORDER BY state_weight, state_name", $field, $field, $field_where, $state_name, $state_name);
  while ($t = db_fetch_object($result)) {
    if ($roles == 'ALL'  // Superuser.
      || $state_name == $t->state_name // Include current state for same-state transitions.
      || workflow_transition_allowed($t->tid, $roles)) {
      $transitions[$t->state_name] = check_plain(t($t->state_label));
    }
  }

  return $transitions;
}



/**
 * Execute a transition (change state of a node).
 *
 * @param $node
 * @param $state_name
 *   The machine name of the target state.
 * @param $comment
 *   A comment for the node's workflow history.
 * @param $force
 *   If set to TRUE, workflow permissions will be ignored.
 *
 * @return int
 *   ID of new state.
 */
function workflow_execute_transition($node, $state_name, $comment = NULL, $force = FALSE) {
  global $user;
  $old_state = workflow_node_current_state($node);
  if ($old_state == $state_name) {
    // Write comment into history.
    // No comment and no state change means do nothing.
    // We clear comment in workflow_transition() so empty subsequent runs terminate here
    if ($comment && !$node->_workflow_scheduled_comment) {
      $node->workflow_stamp = time();
      db_query("UPDATE {workflow_node} SET stamp = %d WHERE nid = %d", $node->workflow_stamp, $node->nid);
      $result = module_invoke_all('workflow', 'transition pre', $old_state, $state_name, $node);
      _workflow_write_history($node, $state_name, $comment);

      $result = module_invoke_all('workflow', 'transition post', $old_state, $state_name, $node);
      // Rules integration
      if (module_exists('rules')) {
        rules_invoke_event('workflow_comment_added', $node, $old_state, $state_name);
      }
    }
    return;
  }

  $tid = workflow_get_transition_id($old_state, $state_name);
  if (!$tid && !$force) {
      watchdog('workflow', 'Attempt to go to nonexistent transition (from %old to %new)', array('%old' => $old_state, '%new' => $state_name, WATCHDOG_ERROR));
      return;
  }
  // Make sure this transition is valid and allowed for the current user.
  // Check allowability of state change if user is not superuser (might be cron).
  if (($user->uid != 1) && !$force) {
    if (!workflow_transition_allowed($tid, array_merge(array_keys($user->roles), array('author')))) {
      watchdog('workflow', 'User %user not allowed to go from state %old to %new', array('%user' => $user->name, '%old' => $old_state, '%new' => $state_name, WATCHDOG_NOTICE));
      return;
    }
  }
  // Invoke a callback indicating a transition is about to occur. Modules
  // may veto the transition by returning FALSE.
  $result = module_invoke_all('workflow', 'transition pre', $old_state, $state_name, $node);

  // Stop if a module says so.
  if (in_array(FALSE, $result)) {
    watchdog('workflow', 'Transition vetoed by module.');
    return;
  }

  // If the node does not have an existing $node->_workflow property, save
  // the $old_state there so _workflow_write_history() can log it.
  if (!isset($node->_workflow)) {
    $node->_workflow = $old_state;
  }
  // Change the state.
  _workflow_node_to_state($node, $state_name, $comment);
  $node->_workflow = $state_name;

  // Register state change with watchdog.
  $state_label = workflow_get_state_label($state_name);
  $type = node_get_types('name', $node->type);
  watchdog('workflow', 'State of @type %node_title set to %state_name', array('@type' => $type, '%node_title' => $node->title, '%state_name' => $state_label), WATCHDOG_NOTICE, l('view', 'node/' . $node->nid));

  // Notify modules that transition has occurred. Actions should take place
  // in response to this callback, not the previous one.
  module_invoke_all('workflow', 'transition post', $old_state, $state_name, $node);

  // Clear any references in the scheduled listing.
  db_query('DELETE FROM {workflow_scheduled_transition} WHERE nid = %d', $node->nid);

  // Rules integration
  if (module_exists('rules')) {
    rules_invoke_event('workflow_state_changed', $node, $old_state, $state_name);
  }

  return $state_name;
}

/**
 * Get the tid of a transition, if it exists.
 *
 * @param $from
 *   The machine name of the originating state.
 * @param $to
 *   The machine name of the target state.
 * @return int
 *   Tid or FALSE if no such transition exists.
 */
function workflow_get_transition_id($from, $to) {
  return db_result(db_query("SELECT tid FROM {workflow_transitions} WHERE state_name = '%s' AND target_state_name = '%s'", $from, $to));
}

/**
 * Remove an action assignment programmatically.
 *
 * Helpful when deleting a workflow.
 *
 * @see workflow_transition_delete()
 *
 * @param $tid
 *   Transition ID.
 * @param $aid
 *   Action ID.
 */
function workflow_actions_remove($tid, $aid) {
  $ops = array();
  $result = db_query("SELECT op FROM {trigger_assignments} WHERE hook = 'workflow' AND aid = '%s'", $aid);
  while ($data = db_fetch_object($result)) {
    // Transition ID is the last part, e.g., foo-bar-1.
    $transition = array_pop(explode('-', $data->op));
    if ($tid == $transition) {
      $ops[] = $data->op;
    }
  }

  foreach ($ops as $op) {
    db_query("DELETE FROM {trigger_assignments} WHERE hook = 'workflow' AND op = '%s' AND aid = '%s'", $op, $aid);
    $description = db_result(db_query("SELECT description FROM {actions} WHERE aid = '%s'", $aid));
    watchdog('workflow', 'Action %action has been unassigned.',  array('%action' => $description));
  }
}

/**
 * Get the states current user can move to for a given node.
 *
 * @param object $node
 *   The node to check.
 * @return
 *   Array of transitions.
 */
function workflow_field_choices($node) {
  global $user;
  $name = workflow_get_workflow_for_type($node->type);
  if (!$name) {
    // No workflow for this type.
    return array();
  }

  $roles = array_keys($user->roles);
  $current_state = workflow_node_current_state($node);

  // If user is node author or this is a new page, give the authorship role.
  if (($user->uid == $node->uid && $node->uid > 0) || (arg(0) == 'node' && arg(1) == 'add')) {
    $roles += array('author' => 'author');
  }
  if ($user->uid == 1) {
    // Superuser is special.
    $roles = 'ALL';
  }
  $transitions = workflow_allowable_transitions($current_state, 'to', $roles);

  // Include current state if it is not the (creation) state.
  if ($current_state == _workflow_creation_state($name)) {
    unset($transitions[$current_state]);
  }
  return $transitions;
}

/**
 * Get the current state of a given node.
 *
 * @param $node
 *   The node to check.
 * @return
 *   The machine name of the current state.
 */
function workflow_node_current_state($node) {
  $state_name = FALSE;

  // There is no nid when creating a node.
  if (!empty($node->nid)) {
    $state_name = db_result(db_query('SELECT state_name FROM {workflow_node} WHERE nid = %d', $node->nid));
  }

  if (!$state_name && !empty($node->type)) {
    // No current state. Use creation state.
    $name = workflow_get_workflow_for_type($node->type);
    $state_name = _workflow_creation_state($name);
  }
  return $state_name;
}

/**
 * Put a node into a state.
 * No permission checking here; only call this from other functions that know
 * what they're doing.
 *
 * @see workflow_execute_transition()
 *
 * @param object $node
 * @param $state_name
 *   The machine name of the target state.
 */
function _workflow_node_to_state($node, $state_name, $comment = NULL) {
  global $user;
  $node->workflow_stamp = time();
  if (db_result(db_query("SELECT nid FROM {workflow_node} WHERE nid = %d", $node->nid))) {
    db_query("UPDATE {workflow_node} SET state_name = '%s', uid = %d, stamp = %d WHERE nid = %d", $state_name, $user->uid, $node->workflow_stamp, $node->nid);
  }
  else {
    db_query("INSERT INTO {workflow_node} (nid, state_name, uid, stamp) VALUES (%d, '%s', %d, %d)", $node->nid, $state_name, $user->uid, $node->workflow_stamp);
  }
  _workflow_write_history($node, $state_name, $comment);
}

/**
 * Write the node history record to workflow_node_history.
 */
function _workflow_write_history($node, $state_name, $comment) {
  global $user;
  db_query("INSERT INTO {workflow_node_history} (nid, old_state_name, state_name, uid, comment, stamp) VALUES (%d, '%s', '%s', %d, '%s', %d)", $node->nid, $node->_workflow, $state_name, $user->uid, $comment, $node->workflow_stamp);
}

/**
 * Get a list of roles.
 *
 * @return
 *   Array of role names keyed by role ID, including the 'author' role.
 */
function workflow_get_roles() {
  static $roles = NULL;
  if (!$roles) {
    $result = db_query('SELECT * FROM {role} ORDER BY name');
    $roles = array('author' => 'author');
    while ($data = db_fetch_object($result)) {
      $roles[$data->rid] = check_plain($data->name);
    }
  }
  return $roles;
}

/**
 * Helper function to generate a creation state name.
 *
 * @param $name
 *   The machine name of the workflow.
 */
function _workflow_creation_state($name) {
  return $name .'_'. WORKFLOW_CREATION_NAME;
}

