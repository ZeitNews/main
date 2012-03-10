<?php

/**
 * Filter by vocabulary id
 */
class calais_handler_filter_calais_term_vid extends views_handler_filter_in_operator {
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }

    $this->value_options = array();
    $vocabularies = calais_get_vocabularies();
    foreach ($vocabularies as $voc) {
      $this->value_options[$voc->vid] = check_plain($voc->name);
    }
  }
}
