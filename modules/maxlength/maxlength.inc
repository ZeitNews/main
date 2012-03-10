<?php
// $Id: maxlength.inc,v 1.4.4.1.2.2 2011/02/16 13:23:20 aronnovak Exp $
/**
 * @file
 *   Business logic for maxlength
 */

function _maxlength_content_form_alter(&$form, &$form_state, $form_id) {
  $type = $form['type']['#value'];
  // update the title as needed
  if (isset($form['title'])) {
    $form['title']['#after_build'] = array('_maxlength_format_element');
    $form['title']['#max_length_properties'] = array($form['title']['#default_value'], 'title', 'title', $type);
  }

  // Update the body as needed
  if (isset($form['body_field']['body'])) {
    $form['body_field']['body']['#after_build'] = array('_maxlength_format_element');
    $form['body_field']['body']['#max_length_properties'] = array($form['body_field']['body']['#default_value'], 'body', 'body', $type);
  }


  if (module_exists('content')) {
    // Get a list of all the CCK fields for this content type
    $list = array_keys(content_fields(NULL, $type));

    // Update CCK fields as needed
    foreach ($list as $field) {
      if (is_array($form[$field])) {
        foreach (element_children($form[$field]) as $key) {
          if ($form[$field][$key]['#type'] == 'text_textarea' || $form[$field][$key]['#type'] == 'text_textfield') {
            $form[$field][$key]['#after_build'] = array('_maxlength_format_element');
            $form[$field][$key]['#max_length_properties'] = array($form[$field][$key]['#default_value']['value'], $field, str_replace('_', '-', $field) .'-'. $key .'-value', $type);
          }
        }
      }
    }
  }
}

function _maxlength_content_type_form_alter(&$form, &$form_state, $form_id) {
  $type = $form['#node_type']->type;
  $labels = array('-3' => 'title', '-1 ' => 'body');

  foreach ($labels as $weight => $label) {

    // bit of a hack to allow us to position the input fields correctly
    $form['submission'][$label .'_label']['#weight'] = $weight - 1;

    $form['submission']['maxlength_' . $label] = array(
      '#type' => 'fieldset',
      '#weight' => $weight,
      '#title' => t('Limit !type  length', array('!type ' => $label)),
      '#collapsible' => TRUE,
      '#collapsed' => strlen(variable_get($type .'_'. $label, '')) == 0,
    );

    $form['submission']['maxlength_' . $label]['maxlength_' . $label] = array(
      '#type' => 'textfield',
      '#title' => t('!label max length', array('!label' => ucwords($label))),
      '#field_suffix' => t('characters'),
      '#return_value' => 1,
      '#size' => 4,
      '#default_value' => variable_get('maxlength_' . $label .'_'. $type, ''),
      '#description' => t('Maximum number of characters allowed for the !type field of this content type. Leave blank for an unlimited size.', array('!type' => $label)) .'<br/>'.
      '<b>'. t('Please remember, it counts all characters, including HTML, so may not work as expected with rich text editors e.g. FCKeditor / tinyMCE.') .'</b>',
        );
    $form['submission']['maxlength_' . $label]['maxlength_' . $label .'_js'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable remaining characters countdown for the !label', array('!label' => ucwords($label))),
      '#default_value' => variable_get('maxlength_' . $label .'_js_'. $type, '0'),
      '#description' => t('This will enable a Javascript based count down, as well as the client side validation for the !type field of this content type. If no limit set this is ignored.', array('!type' => $label)),
    );
    $form['submission']['maxlength_' . $label]['maxlength_' . $label .'_text'] = array(
      '#type' => 'textarea',
      '#title' => t('!label count down message', array('!label' => ucwords($label))),
      '#default_value' => variable_get('maxlength_' . $label .'_text_'. $type, 'Content limited to !limit characters, remaining: <strong>!remaining</strong>'),
      '#description' => t('The text used in the Javascript message under the !type input, where "!limit", "!remaining" and "!count" are replaced by the appropriate numbers.', array('!type' => $label)),
    );
  }
}

function _maxlength_cck_form_alter(&$form, &$form_state, $form_id) {
  //if form is being loaded, add extra config fields
  if (empty($form['#post'])) {
    $new_fields = array();
    foreach ($form['field'] as $key => $field) {
      $new_fields[$key] = $field;
      if ($key == 'max_length') {
        $new_fields['maxlength_' . $form['field_name']['#value'] .'_js'] = array(
          '#type' => 'checkbox',
          '#title' => t('Enable remaining characters countdown for this field'),
          '#default_value' => variable_get('maxlength_' . $form['field_name']['#value'] .'_js', '0'),
          '#description' => t('This will enable a Javascript based count down, as well as the client side validation for this field. If no limit set this is ignored.'),
        );

        $new_fields['maxlength_' . $form['field_name']['#value'] .'_text'] = array(
          '#type' => 'textarea',
          '#title' => t('Count down message'),
          '#default_value' => variable_get('maxlength_' . $form['field_name']['#value'] .'_text', 'Content limited to !limit characters, remaining: <strong>!remaining</strong>'),
          '#description' => t('The text used in the Javascript message under the input, where "!limit", "!remaining" and "!count" are replaced by the appropriate numbers.'),
        );
      }
    }
    $form['field'] = $new_fields;
  }
  $form['#submit'][] = '_maxlength_cck_form_submit';
}

function _maxlength_cck_form_submit($form, &$form_state) {
  //note, max lenght for the CCK field is stored in this way as for textareas, its not in $element var passed to theme functions.
  variable_set('maxlength_' . $form['field_name']['#value'], $form['#post']['max_length']);
  variable_set('maxlength_' . $form['field_name']['#value'] .'_js', $form['#post']['maxlength_' . $form['field_name']['#value'] .'_js']);
  variable_set('maxlength_' . $form['field_name']['#value'] .'_text', $form['#post']['maxlength_' . $form['field_name']['#value'] .'_text']);
}

function _maxlength_get_values($field = 'body', $type = '') {
  $values = '';
  $values['limit'] = FALSE;

  //CCK
  if (strpos($field, 'field_') === 0) {
    $values['limit'] = variable_get('maxlength_' . $field, FALSE);
    $values['use_js'] = variable_get('maxlength_' . $field .'_js', FALSE);
    $values['text'] = variable_get('maxlength_' . $field .'_text', FALSE);
  } //body and title
  elseif ($type != '') {
    $values['limit'] = variable_get('maxlength_' . $field .'_'. $type, FALSE);
    $values['use_js'] = variable_get('maxlength_' . $field .'_js_'. $type, FALSE);
    $values['text'] = variable_get('maxlength_' . $field .'_text_'. $type, FALSE);
  }

  if ($values['limit']) {
    return $values;
  }
  else {
    return FALSE;
  }
}

