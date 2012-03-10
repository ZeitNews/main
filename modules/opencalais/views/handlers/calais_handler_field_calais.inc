<?php

/**
 * Field handler to provide simple renderer that allows linking to a calais term.
 */
class calais_handler_field_calais extends views_handler_field {
  /**
   * Constructor to provide additional field to add.
   *
   * This constructer assumes the calais_term table. If using another
   * table, we'll need to be more specific.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['tid'] = 'tid';
    $this->additional_fields['tdid'] = 'tdid';
    $this->additional_fields['vid'] = 'vid';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Provide link to taxonomy option
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link_to'] = array(
      '#title' => t('Link this field to its Calais term page'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to']),
    );
  }

  /**
   * Render whatever the data is as a link to the Calais term.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to']) && !empty($values->{$this->aliases['tid']}) && $data !== NULL && $data !== '') {
      $term = new stdClass();
      $term->tid = $values->{$this->aliases['tdid']};
      $term->vid = $values->{$this->aliases['vid']};

      return isset($term->tid) ? l($data, taxonomy_term_path($term), array('html' => TRUE)) : $data;
    }
    else {
      return $data;
    }
  }

  function render($values) {
    return $this->render_link(check_plain($values->{$this->field_alias}), $values);
  }
}
