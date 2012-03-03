<?php
//$Id: $
/**
 * Handler to filter for users that are not in a queue.
 */
class userqueue_handler_filter_in_queue extends views_handler_filter_boolean_operator {
  function query() {
    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], "$this->table_alias.uid " . ($this->value ? '<> 0' : 'IS NULL'));
  }
}
