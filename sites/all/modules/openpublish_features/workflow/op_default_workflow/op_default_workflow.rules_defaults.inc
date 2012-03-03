<?php

/**
* Auto-exported triggered rules definitions for op default workflow
*/
function op_default_workflow_rules_defaults() {

  return array (
    'rules' => 
    array (
      'op_dflt_rule_ready4editing_alert' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_workflow_state_changed',
        '#label' => 'OP Default Workflow: Content Ready for Editing Notification',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'OP Default Workflow',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#type' => 'condition',
            '#settings' => 
            array (
              'from_state' => 
              array (
                'ANY' => 'ANY',
              ),
              'to_state' => 
              array (
                'op_default_workflow_ready_for_editing' => 'op_default_workflow_ready_for_editing',
              ),
              '#argument map' => 
              array (
                'old_state' => 'old_state',
                'new_state' => 'new_state',
              ),
            ),
            '#name' => 'workflow_check_transition',
            '#info' => 
            array (
              'label' => 'Check workflow transition from Any state to OpenPublish Default Workflow: Ready for Editing',
              'arguments' => 
              array (
                'old_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'Old workflow state',
                ),
                'new_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'New workflow state',
                ),
              ),
              'module' => 'Workflow',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          1 => 
          array (
            '#type' => 'action',
            '#settings' => 
            array (
              'recipients' => 
              array (
                4 => 4,
                2 => 0,
                3 => 0,
                5 => 0,
                6 => 0,
              ),
              'from' => '',
              'subject' => 'New Content Item is [node:workflow-current-state-name]',
              'message_html' => '<p>Hello,
  
  <p>[node:workflow-current-state-updating-user-name] has just marked "<a href="[node:node-url]">[node:title]</a>" as: [node:workflow-current-state-name]. 
  
  <p>Please review.',
              'message_plaintext' => '[node:workflow-current-state-updating-user-name] has just marked [node:title] as [node:workflow-current-state-name]. 
  
  The URL of the content item is: [node:node-url]
  
  Please review.',
              'attachments' => '',
              'to' => NULL,
              'cc' => NULL,
              'bcc' => NULL,
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'subject' => 
                  array (
                    0 => 'node',
                  ),
                  'message_html' => 
                  array (
                    0 => 'node',
                  ),
                  'message_plaintext' => 
                  array (
                    0 => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'mimemail_rules_action_mail_to_users_of_role',
            '#info' => 
            array (
              'label' => 'Send an HTML e-mail to all Editors',
              'label callback' => false,
              'module' => 'Mime Mail',
              'eval input' => 
              array (
                0 => 'from',
                1 => 'to',
                2 => 'cc',
                3 => 'bcc',
                4 => 'subject',
                5 => 'message_html',
                6 => 'message_plaintext',
                7 => 'attachments',
              ),
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'op_dflt_rule_publishing_alert' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_workflow_state_changed',
        '#label' => 'OP Default Workflow: Content Staged for Publishing Notification',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'OP Default Workflow',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#type' => 'condition',
            '#settings' => 
            array (
              'from_state' => 
              array (
                'ANY' => 'ANY',
              ),
              'to_state' => 
              array (
                'op_default_workflow_ready_for_publishing' => 'op_default_workflow_ready_for_publishing',
                'op_default_workflow_published' => 'op_default_workflow_published',
              ),
              '#argument map' => 
              array (
                'old_state' => 'old_state',
                'new_state' => 'new_state',
              ),
            ),
            '#name' => 'workflow_check_transition',
            '#info' => 
            array (
              'label' => 'Check workflow transition from Any state to OpenPublish Staged for Publishing',
              'arguments' => 
              array (
                'old_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'Old workflow state',
                ),
                'new_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'New workflow state',
                ),
              ),
              'module' => 'Workflow',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          1 => 
          array (
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => 
            array (
              'from' => '',
              'subject' => 'Your Content Item has been marked as [node:workflow-current-state-name]',
              'message_html' => '<p>Hello,
  
  <p>[node:workflow-current-state-updating-user-name] has just marked "<a href="[node:node-url]">[node:title]</a>" as: [node:workflow-current-state-name]. 
  
  <p>Please review.',
              'message_plaintext' => '[node:workflow-current-state-updating-user-name] has just marked [node:title] as [node:workflow-current-state-name]. 
  
  The URL of the content item is: [node:node-url]
  
  Please review.',
              'attachments' => '',
              '#argument map' => 
              array (
                'user' => 'author',
              ),
              'to' => NULL,
              'cc' => NULL,
              'bcc' => NULL,
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'subject' => 
                  array (
                    0 => 'node',
                  ),
                  'message_html' => 
                  array (
                    0 => 'node',
                  ),
                  'message_plaintext' => 
                  array (
                    0 => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'mimemail_rules_action_mail_to_user',
            '#info' => 
            array (
              'label' => 'Send an HTML mail to Author',
              'label callback' => false,
              'arguments' => 
              array (
                'user' => 
                array (
                  'type' => 'user',
                  'label' => 'Recipient',
                ),
              ),
              'module' => 'Mime Mail',
              'eval input' => 
              array (
                0 => 'from',
                1 => 'to',
                2 => 'cc',
                3 => 'bcc',
                4 => 'subject',
                5 => 'message_html',
                6 => 'message_plaintext',
                7 => 'attachments',
              ),
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'op_dflt_rule_needs_revision_alert' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_workflow_state_changed',
        '#label' => 'OP Default Workflow: Content Needs Revision Notification',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'OP Default Workflow',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#type' => 'condition',
            '#settings' => 
            array (
              'from_state' => 
              array (
                'ANY' => 'ANY',
              ),
              'to_state' => 
              array (
                'op_default_workflow_needs_revision' => 'op_default_workflow_needs_revision',
              ),
              '#argument map' => 
              array (
                'old_state' => 'old_state',
                'new_state' => 'new_state',
              ),
            ),
            '#name' => 'workflow_check_transition',
            '#info' => 
            array (
              'label' => 'Check workflow transition from Any state to OpenPublish Default Workflow: Needs Revision',
              'arguments' => 
              array (
                'old_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'Old workflow state',
                ),
                'new_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'New workflow state',
                ),
              ),
              'module' => 'Workflow',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          1 => 
          array (
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => 
            array (
              'from' => '',
              'subject' => 'Your Content Item has been marked as [node:workflow-current-state-name]',
              'message_html' => '<p>Hello,
  
  <p>[node:workflow-current-state-updating-user-name] has just marked "<a href="[node:node-url]">[node:title]</a>" as: [node:workflow-current-state-name]. 
  
  <p>Please review.',
              'message_plaintext' => '[node:workflow-current-state-updating-user-name] has just marked [node:title] as [node:workflow-current-state-name]. 
  
  The URL of the content item is: [node:node-url]
  
  Please review.',
              'attachments' => '',
              '#argument map' => 
              array (
                'user' => 'author',
              ),
              'to' => NULL,
              'cc' => NULL,
              'bcc' => NULL,
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'subject' => 
                  array (
                    0 => 'node',
                  ),
                  'message_html' => 
                  array (
                    0 => 'node',
                  ),
                  'message_plaintext' => 
                  array (
                    0 => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'mimemail_rules_action_mail_to_user',
            '#info' => 
            array (
              'label' => 'Send an HTML mail to Author',
              'label callback' => false,
              'arguments' => 
              array (
                'user' => 
                array (
                  'type' => 'user',
                  'label' => 'Recipient',
                ),
              ),
              'module' => 'Mime Mail',
              'eval input' => 
              array (
                0 => 'from',
                1 => 'to',
                2 => 'cc',
                3 => 'bcc',
                4 => 'subject',
                5 => 'message_html',
                6 => 'message_plaintext',
                7 => 'attachments',
              ),
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'op_dflt_rule_publish_content' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_workflow_state_changed',
        '#label' => 'OP Default Workflow: Publish Content',
        '#active' => 1,
        '#weight' => '-5',
        '#categories' => 
        array (
          0 => 'OP Default Workflow',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Check workflow transition from Any state to OpenPublish Default Workflow: Published',
              'arguments' => 
              array (
                'old_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'Old workflow state',
                ),
                'new_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'New workflow state',
                ),
              ),
              'module' => 'Workflow',
            ),
            '#name' => 'workflow_check_transition',
            '#settings' => 
            array (
              'from_state' => 
              array (
                'ANY' => 'ANY',
              ),
              'to_state' => 
              array (
                'op_default_workflow_published' => 'op_default_workflow_published',
              ),
              '#argument map' => 
              array (
                'old_state' => 'old_state',
                'new_state' => 'new_state',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#type' => 'action',
            '#settings' => 
            array (
              'auto_save' => 1,
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_core_node_publish_action',
            '#info' => 
            array (
              'label' => 'Publish Updated content',
              'module' => 'Node',
              'arguments' => 
              array (
                'node' => 
                array (
                  'label' => 'Content',
                  'type' => 'node',
                ),
              ),
              'base' => 'rules_core_action_execute',
              'action_name' => 'node_publish_action',
              'configurable' => false,
              'label callback' => 'rules_core_node_label_callback',
              'label_skeleton' => 'Publish @node',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'op_dflt_rule_unpublish_content' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_workflow_state_changed',
        '#label' => 'OP Default Workflow: Unpublish Content',
        '#active' => 1,
        '#weight' => '-10',
        '#categories' => 
        array (
          0 => 'OP Default Workflow',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#negate' => 1,
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Check workflow transition from Any state to OpenPublish Default Workflow: Published',
              'arguments' => 
              array (
                'old_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'Old workflow state',
                ),
                'new_state' => 
                array (
                  'type' => 'workflow_state',
                  'label' => 'New workflow state',
                ),
              ),
              'module' => 'Workflow',
            ),
            '#name' => 'workflow_check_transition',
            '#settings' => 
            array (
              'from_state' => 
              array (
                'ANY' => 'ANY',
              ),
              'to_state' => 
              array (
                'op_default_workflow_published' => 'op_default_workflow_published',
              ),
              '#argument map' => 
              array (
                'old_state' => 'old_state',
                'new_state' => 'new_state',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#type' => 'action',
            '#settings' => 
            array (
              'auto_save' => 1,
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_core_node_unpublish_action',
            '#info' => 
            array (
              'label' => 'Unpublish Updated content',
              'module' => 'Node',
              'arguments' => 
              array (
                'node' => 
                array (
                  'label' => 'Content',
                  'type' => 'node',
                ),
              ),
              'base' => 'rules_core_action_execute',
              'action_name' => 'node_unpublish_action',
              'configurable' => false,
              'label callback' => 'rules_core_node_label_callback',
              'label_skeleton' => 'Unpublish @node',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );

}
