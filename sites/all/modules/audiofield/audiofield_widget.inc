<?php
// $Id: audiofield_widget.inc,v 1.3 2010/11/23 19:45:37 tamerzg Exp $

/**
 * @file
 * audiofield widget hooks and callbacks.
 */

/**
 * Implementation of CCK's hook_widget_settings($op = 'form').
 */
function audiofield_widget_settings_form($widget) {
  $form = module_invoke('filefield', 'widget_settings', 'form', $widget);

  $form['file_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Permitted upload file extensions'),
    '#default_value' => is_string($widget['file_extensions']) ? $widget['file_extensions'] :'mp3',
    '#size' => 64,
    '#description' => t('Extensions a user can upload to this field. Separate extensions with a space and do not include the leading dot. Leaving this blank will allow users to upload a file with any extension.'),
    '#weight' => 1,
  );

  return $form;
}

/**
 * Implementation of CCK's hook_widget_settings($op = 'save').
 */
function audiofield_widget_settings_save($widget) {
  $filefield_settings = module_invoke('filefield', 'widget_settings', 'save', $widget);
    
  return $filefield_settings;
}

/**
 * Element #value_callback function.
 */
function audiofield_widget_value($element, $edit = FALSE) {
  $field = filefield_widget_value($element, $edit);
  
  return $field;
}

/**
 * FormAPI theme function. Theme the output of an image field.
 */
function theme_audiofield_widget($element) {
  
  $z=theme('form_element', $element, $element['#children']);
  
  return $z;
}