<?php
//$Id$
/**
 * Specialized relationship handler to add userqueues.
 */
class userqueue_handler_relationship_userqueue extends views_handler_relationship {
  function options(&$options) {
    parent::options($options);

    $options['limit'] = FALSE;
    $options['uqids'] = array();
  }

  /**
   * Default options form that provides the label widget that all fields
   * should have.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);


    $form['limit'] = array(
      '#type' => 'checkbox',
      '#title' => t('Limit to one or more queues (recommended)'),
      '#default_value'=> $this->options['limit'],
    );

    $options = array();
    $queues = userqueue_load_queues();
    foreach ($queues as $queue) {
      $options[$queue->uqid] = $queue->title;
    }
    $form['uqids'] = array(
      '#prefix' => '<div><div id="edit-options-uqids">',
      '#suffix' => '</div></div>',
      '#type' => 'checkboxes',
      '#title' => t('Queues'),
      '#options' => $options,
      '#default_value' => $this->options['uqids'],
      '#process' => array('expand_checkboxes', 'views_process_dependency'),
      '#dependency' => array('edit-options-limit' => array(TRUE)),
    );
  }

  /**
   * Called to implement a relationship in a query.
   */
  function query() {
    // Figure out what base table this relationship brings to the party.
    $join = new views_join();
    $join->definition = array(
      'table' => 'userqueue_user',
      'field' => 'uid',
      'left_table' => 'users',
      'left_field' => 'uid',
    );

    if (!empty($this->options['required'])) {
      $join->definition['type'] = 'INNER';
    }

    if (!empty($this->options['limit'])) {
      $join->definition['extra'] = array(array(
        'field' => 'uqid',
        'value' => array_filter($this->options['uqids']),
        'numeric' => TRUE,
      ));
    }

    $join->construct();

    $alias = $join->definition['table'] . '_' . $join->definition['left_table'];

    $this->alias = $this->query->add_relationship($alias, $join, 'userqueue_user', $this->relationship);
  }
}
