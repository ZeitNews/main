<?php

/**
 * @file
 * Provide user interface for changing workflow state.
 */

/**
 * Menu callback. Display workflow summary of a node.
 */
function workflow_tab_page($node = NULL) {
  drupal_set_title(check_plain($node->title));
  $workflow_name = workflow_get_workflow_for_type($node->type);
  $states_per_page = variable_get('workflow_states_per_page', 20);

  $states = workflow_get_states($workflow_name, TRUE);
  $all_states = workflow_get_states(NULL, TRUE);
  $current_state_name = workflow_node_current_state($node);
  $current_state = $states[$current_state_name];

  $output = '<p>'. t('Current state: !state', array('!state' => theme('workflow_current_state', $current_state->label))) . "</p>\n";
  $output .= drupal_get_form('workflow_tab_form', $node, $workflow_name, $states, $current_state);

  $rows = array();
  $result = pager_query("SELECT h.*, u.name "
    ."FROM {workflow_node_history} h "
    ."LEFT JOIN {users} u ON h.uid = u.uid "
    ."WHERE nid = %d ORDER BY hid DESC", $states_per_page, 0, NULL, $node->nid);
  while ($history = db_fetch_object($result)) {
    $state = isset($states[$history->state_name]) ? $states[$history->state_name] : $all_states[$history->state_name];

    if ($history->state_name == $current_state_name && $state->status && !isset($current_themed)) {
      // Theme the current state differently so it stands out.
      $state_label = theme('workflow_current_state', $state->label);
      // Make a note that we have themed the current state; other times in the
      // history of this node where the node was in this state do not need to be
      // specially themed.
      $current_themed = TRUE;
    }
    elseif (!$states[$history->state_name]->status) {
      // The state has been deleted, but we include it in the history.
      $state_label = theme('workflow_deleted_state', $state->label);
      $footer_needed = TRUE;
    }
    else {
      // Regular state.
      $state_label = $state->label;
    }

    $old_state = isset($states[$history->old_state_name]) ? $states[$history->old_state_name] : $all_states[$history->old_state_name];

    if ($old_state->status) {
      $old_state_label = $old_state->label;
    }
    else {
      $old_state_label = theme('workflow_deleted_state', $disabled_states[$history->old_state_name]);
      $footer_needed = TRUE;
    }
    $rows[] = theme('workflow_history_table_row', $history, $old_state_label, $state_label);
  }
  $output .= theme('workflow_history_table', $rows, !empty($footer_needed));
  $output .= theme('pager', $states_per_page);
  return $output;
}

/*
 * Theme one workflow history table row.
 *
 * $old_state_name and $state_name must be run through check_plain(t()) prior
 * to calling this theme function.
 */
function theme_workflow_history_table_row($history, $old_state_name, $state_name) {
  return array(
    format_date($history->stamp),
    $old_state_name,
    $state_name,
    theme('username', $history),
    filter_xss($history->comment, array('a', 'em', 'strong')),
  );
}

/*
 * Theme entire workflow history table.
 */
function theme_workflow_history_table($rows, $footer) {
  $output = theme('table', array(t('Date'), t('Old State'), t('New State'), t('By'), t('Comment')), $rows, array('class' => 'workflow_history'), t('Workflow History'));
  if ($footer) {
    $output .= t('*State is no longer available.');
  }
  return $output;
}

/**
 * Theme the current state in the workflow history table.
 */
function theme_workflow_current_state($label) {
  return '<strong>'. $label .'</strong>';
}

/**
 * Theme a deleted state in the workflow history table.
 */
function theme_workflow_deleted_state($label) {
  return $label .'*';
}

/**
 * Form builder. Allow workflow state change and scheduling from workflow tab.
 *
 * @param $node
 *   Node for which workflow information will be displayed.
 * @param $workflow_name
 *   The machine name of the workflow to display.
 * @param $states
 *   Array of states for the workflow.
 * @param $current_state
 *   The state object of the current workflow state.
 * @return
 *   Form definition array.
 */
function workflow_tab_form($form_state, $node, $workflow_name, $states, $current_state) {
  $form['#tab'] = TRUE;
  $choices = workflow_field_choices($node);

  $min = ($current_state->name == _workflow_creation_state($name)) ? 1 : 2;
  // Only build form if user has possible target state(s).
  if (count($choices) >= $min) {
    $workflow = workflow_load($workflow_name);
    $form['#wf'] = $workflow;
    // See if scheduling information is present.
    if ($node->_workflow_scheduled_timestamp && $node->_workflow_scheduled_state_name) {
      // The default value should be the scheduled state.
      $default_value = $node->_workflow_scheduled_state_name;
      $timestamp = $node->_workflow_scheduled_timestamp;
      $comment = $node->_workflow_scheduled_comment;
    }

    if (empty($default_value)) {
      $choices_filtered = $choices;
      unset($choices_filtered[$current_state->name]);
      $default_value = array_shift(array_keys($choices_filtered));
    }

    // Include the same form elements here that are included on a
    // regular node editing page. $form is modified by reference.
    workflow_node_form($form, $form_state, t('Change %s state', array('%s' => $workflow->label)), $workflow_name, $default_value, $choices, $timestamp, $comment);

    $form['node'] = array(
      '#type' => 'value',
      '#value' => $node,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit')
    );
  }
  return $form;
}

/**
 * Submit handler for the form on the workflow tab.
 *
 * @see workflow_tab_form
 */
function workflow_tab_form_submit($form, &$form_state) {
  // The entire node object was stashed in the form.
  $node = $form_state['values']['node'];
  $node->workflow = $form_state['values']['workflow'];
  $node->workflow_comment = $form_state['values']['workflow_comment'];
  $node->workflow_scheduled = $form_state['values']['workflow_scheduled'];
  $node->workflow_scheduled_date = $form_state['values']['workflow_scheduled_date'];
  $node->workflow_scheduled_hour = $form_state['values']['workflow_scheduled_hour'];

  // Call node_save() to make sure any handlers that use the
  // new workflow values will see them.
  node_save($node);

  $form_state['redirect'] = 'node/' . $node->nid;
}