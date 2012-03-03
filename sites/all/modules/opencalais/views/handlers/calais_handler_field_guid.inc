<?php

/**
 * Field handler to provide a renderer for linking to a calais linked data uri.
 *
 * This allows for use the disambiguated guid (if it exists) or the plain entity guid.
 */
class calais_handler_field_guid extends views_handler_field_url {
  /**
   * Constructor to provide additional field to add.
   *
   * This constructer assumes the calais_term table. If using another
   * table, we'll need to be more specific.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['name'] = 'name';
    $this->additional_fields['resolved_name'] = 'resolved_name';
    $this->additional_fields['resolved_guid'] = 'resolved_guid';
  }

  /**
   * Provide configuration defaults.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['use_resolved'] = array('default' => TRUE);
    return $options;
  }

  /**
   * Provide configuration options for the field.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['use_resolved'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use Resolved URI if possible'),
      '#description' => t('Check this box to use the disambiguated Calais Linked Data URI. If a disambiguated URI does not exist, it will call back to the default URI for this entity.'),
      '#default_value' => !empty($this->options['use_resolved']),
      '#weight' => 5,
    );
    $form['display_as_link']['#weight'] = 6;
    $form['link_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to use for link label'),
      '#description' => t('Used when displaying as a link. Enter any text. Other options: Leave blank to use the URI itself as the label. Use [name] to use the Calais Entity Name. Use [resolved_name] to use the Calais Entity Disambiguated Name (if it exists). Use [image] to use a 16x16 Calais logo. Enter HTML in here for your own image tag, etc.'),
      '#default_value' => $this->options['link_text'],
      '#weight' => 7,
    );
  }

  /**
   * Render the URI based on configuration options.
   */
  function render($values) {
    $value = $this->get_guid($values);
    if (!empty($this->options['display_as_link'])) {
      $text = $this->get_link_text($value, $values);
      return l($text, $value, array('html' => TRUE));
    }
    else {
      return $value;
    }
  }

  function get_guid($values) {
    $guid = $values->{$this->field_alias};
    if ($this->options['use_resolved']) {
      $resolved_guid = $values->{$this->aliases['resolved_guid']};
      $guid = $resolved_guid ? $resolved_guid : $guid;
    }
    return check_plain($guid);
  }
  
  function get_link_text($value, $values) {
    $label = $this->options['link_text'];
    switch ($label) {
      case '':
        return $value;
      case '[resolved_name]':
        $resolved_name = $values->{$this->aliases['resolved_name']};
        if (!empty($resolved_name)) // else fall through
          return $resolved_name;
      case '[name]':
        return $values->{$this->aliases['name']};
      case '[image]':
        return theme('image', drupal_get_path('module', 'calais') . '/images/calais-logo.jpg', 'Calais Linked Data URI', 'Calais Linked Data URI');
      default:
        return $label;
    }
  }
}
