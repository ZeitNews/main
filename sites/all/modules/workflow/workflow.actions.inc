<?php

/**
 * @file
 * Actions related functions.
 */

/**
 * Get the actions associated with a given transition.
 *
 * @see _trigger_get_hook_aids()
 *
 * @param int $tid
 *   ID of transition.
 * @return array
 *   Array of action ids in the same format as _trigger_get_hook_aids().
 */
function workflow_get_actions($tid) {
  $aids = array();
  if (!module_exists('trigger')) {
    watchdog('workflow', 'Unable to get actions associated with a transition because the trigger module is not enabled.', array(), WATCHDOG_WARNING);
    return $aids;
  }

  $result = db_query("SELECT op FROM {trigger_assignments} WHERE hook = 'workflow'");
  while ($data = db_fetch_object($result)) {
    // Transition ID is the last part, e.g., foo-bar-1.
    $transition = array_pop(explode('-', $data->op));
    if ($tid == $transition) {
      $results = db_query("SELECT aa.aid, a.type FROM {trigger_assignments} aa LEFT JOIN {actions} a ON aa.aid = a.aid WHERE aa.hook = '%s' AND aa.op = '%s' ORDER BY weight", 'workflow', $data->op);
      while ($action = db_fetch_object($results)) {
        $aids[$action->aid]['type'] = $action->type;
      }
    }
  }

  return $aids;
}

/**
 * Implementation of hook_action_info().
 */
function workflow_action_info() {
  return array(
    'workflow_select_next_state_action' => array(
      'type' => 'node',
      'description' => t('Change workflow state of post to next state'),
      'configurable' => FALSE,
      'hooks' => array(
        'nodeapi' => array('presave'),
        'comment' => array('insert', 'update'),
        'workflow' => array('any'),
      ),
    ),
    'workflow_select_given_state_action' => array(
      'type' => 'node',
      'description' => t('Change workflow state of post to new state'),
      'configurable' => TRUE,
      'hooks' => array(
        'nodeapi' => array('presave'),
        'comment' => array('insert', 'update'),
        'workflow' => array('any'),
      ),
    ),
  );
}

/**
 * Implementation of a Drupal action. Move a node to the next state in the
 * workfow.
 */
function workflow_select_next_state_action($node, $context) {
  // If this action is being fired because it's attached to a workflow '
  // transition then the node's new state (now its current state) should be in 
  // $node->workflow because that is where the value from the workflow form 
  // field is stored; otherwise the current state is placed in $node->_workflow 
  // by our nodeapi load.
  if (!isset($node->workflow) && !isset($node->_workflow)) {
    watchdog('workflow', 'Unable to get current workflow state of node %nid.', array('%nid' => $node->nid));
    return;
  }
  $current_state = isset($node->workflow) ? $node->workflow : $node->_workflow;

  // Get the node's new state.
  $choices = workflow_field_choices($node);
  foreach ($choices as $state_name => $label) {
    if (isset($flag)) {
      $new_state = $state_name;
      $new_state_label = $label;
      break;
    }
    if ($state_name == $current_state) {
      $flag = TRUE;
    }
  }

  // Fire the transition.
  workflow_execute_transition($node, $new_state);
}

/**
 * Implementation of a Drupal action. Move a node to a specified state.
 */
function workflow_select_given_state_action($node, $context) {
  $t_args = array(
    '%title' => check_plain($node->title),
    '%state' => check_plain($context['label']),
  );
  $comment = t($context['workflow_comment'], $t_args);
  workflow_execute_transition($node, $context['target_state_name'], $comment, $context['force']);
}

/**
 * Configuration form for "Change workflow state of post to new state" action.
 *
 * @see workflow_select_given_state_action()
 */
function workflow_select_given_state_action_form($context) {
  $result = db_query("SELECT w.label AS workflow_label, ws.name AS state_name, ws.label AS state_label "
    . "FROM {workflow_states} ws "
    . "LEFT JOIN {workflows} w ON ws.workflow_name = w.name "
    . "WHERE ws.sysid = 0 AND ws.status = 1 "
    . "ORDER BY ws.workflow_name, ws.weight");
  $previous_workflow = '';
  $options = array();
  while ($data = db_fetch_object($result)) {
    $workflow_label = check_plain(t($data->workflow_label));
    $options[$workflow_label][$data->state_name] = check_plain(t($data->state_label));;
  }
  $form['target_state_name'] = array(
    '#type' => 'select',
    '#title' => t('Target state'),
    '#description' => t('Please select that state that should be assigned when this action runs.'),
    '#default_value' => isset($context['target_state']) ? $context['target_state'] : '',
    '#options' => $options,
  );
  $form['force'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force transition'),
    '#description' => t('If this box is checked, the new state will be assigned even if workflow permissions disallow it.'),
    '#default_value' => isset($context['force']) ? $context['force'] : '',
  );
  $form['workflow_comment'] = array(
    '#type' => 'textfield',
    '#title' => t('Message'),
    '#description' => t('This message will be written into the workflow history log when the action runs. You may include the following variables: %state, %title'),
    '#default_value' => isset($context['workflow_history']) ? $context['workflow_history'] : t('Action set %title to %state.'),
  );
  return $form;
}

/**
 * Submit handler for "Change workflow state of post to new state" action
 * configuration form.
 *
 * @see workflow_select_given_state_action_form()
 */
function workflow_select_given_state_action_submit($form_id, $form_state) {
  $label = workflow_get_state_label($form_state['values']['target_state_name']);
  return array(
    'target_state_name' => $form_state['values']['target_state_name'],
    'label' => $label,
    'force' => $form_state['values']['force'],
    'workflow_comment' => $form_state['values']['workflow_comment'],
  );
}