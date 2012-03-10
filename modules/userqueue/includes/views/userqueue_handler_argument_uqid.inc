<?php
/**
 * Argument handler for subqueues.
 *
 * Subqueues have titles that are determined by doing substitution from
 * the subqueue_title on the queue using the title on the subqueue, which
 * takes a little extra work to do here.
 */
class userqueue_handler_argument_uqid extends views_handler_argument_numeric {
  function title_query() {
    foreach ($this->value as &$uqid) {
      $queue = userqueue_load($this->value[0]);
      $uqid = $queue ? $queue->title : $this->value;
    }
    return $this->value;
  }
}
