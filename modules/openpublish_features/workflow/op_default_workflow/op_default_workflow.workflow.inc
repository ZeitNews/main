<?php

/**
 * Implementation of hook_default_workflows().
 */
function op_default_workflow_default_workflows() {
  $export = array();
  $workflow = new workflow;
  $workflow->api_version = 1;
  $workflow->name = 'op_default_workflow';
  $workflow->label = 'OpenPublish Default Workflow';
  $workflow->tab_roles = 'author,3,4,6,0,0,0';
  $workflow->options = array(
    'comment_log_node' => 1,
    'comment_log_tab' => 1,
  );
  $workflow->states = array();

  $workflow_state = new workflow_state;
  $workflow_state->name = 'op_default_workflow_creation';
  $workflow_state->workflow_name = 'op_default_workflow';
  $workflow_state->label = '(creation)';
  $workflow_state->weight = -50;
  $workflow_state->sysid = TRUE;
  $workflow_state->status = TRUE;
  $workflow->states['op_default_workflow_creation'] = $workflow_state;

  $workflow_state = new workflow_state;
  $workflow_state->name = 'op_default_workflow_needs_revision';
  $workflow_state->workflow_name = 'op_default_workflow';
  $workflow_state->label = 'Needs Revision';
  $workflow_state->weight = -10;
  $workflow_state->sysid = FALSE;
  $workflow_state->status = TRUE;
  $workflow->states['op_default_workflow_needs_revision'] = $workflow_state;

  $workflow_state = new workflow_state;
  $workflow_state->name = 'op_default_workflow_ready_for_editing';
  $workflow_state->workflow_name = 'op_default_workflow';
  $workflow_state->label = 'Ready for Editing';
  $workflow_state->weight = -9;
  $workflow_state->sysid = FALSE;
  $workflow_state->status = TRUE;
  $workflow->states['op_default_workflow_ready_for_editing'] = $workflow_state;

  $workflow_state = new workflow_state;
  $workflow_state->name = 'op_default_workflow_ready_for_publishing';
  $workflow_state->workflow_name = 'op_default_workflow';
  $workflow_state->label = 'Ready for Publishing';
  $workflow_state->weight = -8;
  $workflow_state->sysid = FALSE;
  $workflow_state->status = TRUE;
  $workflow->states['op_default_workflow_ready_for_publishing'] = $workflow_state;

  $workflow_state = new workflow_state;
  $workflow_state->name = 'op_default_workflow_published';
  $workflow_state->workflow_name = 'op_default_workflow';
  $workflow_state->label = 'Published';
  $workflow_state->weight = -7;
  $workflow_state->sysid = FALSE;
  $workflow_state->status = TRUE;
  $workflow->states['op_default_workflow_published'] = $workflow_state;

  $workflow->transitions = array();

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_creation';
  $workflow_transition->target_state_name = 'op_default_workflow_needs_revision';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[0] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_creation';
  $workflow_transition->target_state_name = 'op_default_workflow_ready_for_editing';
  $workflow_transition->roles = array(
    0 => 'author',
    1 => '3',
    2 => '4',
    3 => '6',
  );
  $workflow->transitions[1] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_creation';
  $workflow_transition->target_state_name = 'op_default_workflow_ready_for_publishing';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[2] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_creation';
  $workflow_transition->target_state_name = 'op_default_workflow_published';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[3] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_needs_revision';
  $workflow_transition->target_state_name = 'op_default_workflow_ready_for_editing';
  $workflow_transition->roles = array(
    0 => 'author',
    1 => '3',
    2 => '4',
    3 => '6',
  );
  $workflow->transitions[4] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_needs_revision';
  $workflow_transition->target_state_name = 'op_default_workflow_ready_for_publishing';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[5] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_needs_revision';
  $workflow_transition->target_state_name = 'op_default_workflow_published';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[6] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_ready_for_editing';
  $workflow_transition->target_state_name = 'op_default_workflow_needs_revision';
  $workflow_transition->roles = array(
    0 => 'author',
    1 => '3',
    2 => '4',
    3 => '6',
  );
  $workflow->transitions[7] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_ready_for_editing';
  $workflow_transition->target_state_name = 'op_default_workflow_ready_for_publishing';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[8] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_ready_for_editing';
  $workflow_transition->target_state_name = 'op_default_workflow_published';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[9] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_ready_for_publishing';
  $workflow_transition->target_state_name = 'op_default_workflow_needs_revision';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[10] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_ready_for_publishing';
  $workflow_transition->target_state_name = 'op_default_workflow_ready_for_editing';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[11] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_ready_for_publishing';
  $workflow_transition->target_state_name = 'op_default_workflow_published';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[12] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_published';
  $workflow_transition->target_state_name = 'op_default_workflow_needs_revision';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[13] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_published';
  $workflow_transition->target_state_name = 'op_default_workflow_ready_for_editing';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[14] = $workflow_transition;

  $workflow_transition = new workflow_transition;
  $workflow_transition->state_name = 'op_default_workflow_published';
  $workflow_transition->target_state_name = 'op_default_workflow_ready_for_publishing';
  $workflow_transition->roles = array(
    0 => '3',
    1 => '4',
    2 => '6',
  );
  $workflow->transitions[15] = $workflow_transition;

  $workflow->roles = array(
    0 => 'author',
    1 => '3',
    2 => '4',
    3 => '6',
    4 => '0',
    5 => '0',
    6 => '0',
  );

  $export['op_default_workflow'] = $workflow;
  return $export;
}
