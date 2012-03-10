<?php
/**
 * @file calais_handler_filter_float.inc
 */
 
/**
 * This is just to get this handler exposed until http://drupal.org/node/372192 is fixed.
 */
class calais_handler_filter_float extends views_handler_filter_numeric {
  
  function op_between($field) {
    if ($this->operator == 'between') {
      $this->query->add_where($this->options['group'], "$field >= %f", $this->value['min']);
      $this->query->add_where($this->options['group'], "$field <= %f", $this->value['max']);
    }
    else {
      $this->query->add_where($this->options['group'], "$field <= %f OR $field >= %f", $this->value['min'], $this->value['max']);
    }
  }

  function op_simple($field) {
    $this->query->add_where($this->options['group'], "$field $this->operator %f", $this->value['value']);
  }
}