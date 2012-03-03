<?php

/**
 * @file
 * Administration forms.
 */

/**
 * Include the required files.
 */
nodewords_include_once();

/*****************************************************************************
 * Menu callbacks / form builders, submit/validate functions.
 ****************************************************************************/

/**
 * Create a new meta tag.
 */
function nodewords_add(&$form_state) {
  return nodewords_edit($form_state, NULL);
}

/**
 * Show the meta tag delete form.
 */
function nodewords_delete($form_state, $tag) {
  $form = array();

  $form['tagid'] = array('#type' => 'value', '#value' => $tag->tagid);
  $form['name'] = array('#type' => 'value', '#value' => $tag->name);

  return confirm_form($form,
    t('Are you sure you want to delete the %tag_name meta tag?', array('%tag_name' => $tag->name)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/content/nodewords'. $tag->tagid,
    t('This action cannot be undone.'),
    t('Delete meta tag'),
    t('Cancel')
  );
}

/**
 * 'Delete meta tag' submit handler.
 */
function nodewords_delete_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  _nodewords_db_delete_tag($form_values['tagid']);
  drupal_set_message(t('Deleted %tag_name meta tag.', array('%tag_name' => $form_values['name'])));
  $form_state['redirect'] = 'admin/content/nodewords';
}

/**
 * Edit the basics of a meta tag.
 *
 * @param $tag
 *   Object. The meta tag to edit. If NULL a new meta tag will be created.
 */
function nodewords_edit(&$form_state, $tag = NULL) {
  $form = array();

  if (isset($tag->tagid)) {
    drupal_set_title(t('Edit %tag_name meta tag', array('%tag_name' => $tag->name)));
    $form['tagid'] = array('#type' => 'value', '#value' => $tag->tagid);
  }
  else {
    drupal_set_title(t('Create new meta tag'));
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
    '#description' => t('The name of the meta tag.'),
    '#default_value' => $tag->name,
  );

  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('Short description for administrators.'),
    '#default_value' => $tag->description,
  );

  $types = _nodewords_types();
  $titles = array();
  $descriptions = array();
  foreach ($types as $key => $value) {
    $titles[$key] = $value['title'];
    if (isset($value['description'])) {
      $descriptions[$value['title']] = $value['description'];
    }
  }
  $description = t('<p>Select one of the available meta tag types.</p>');
  if (count($descriptions)) {
    $description .= theme('nodewords_descriptions', $descriptions);
  }
  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('Type'),
    '#description' => $description,
    '#default_value' => $tag->type,
    '#options' => $titles,
    '#required' => TRUE,
  );

  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content construction'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );
  $form['options']['use-all'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use all inheritted values'),
    '#description' => t('The normal way of handling different context defaults is that the more specific context default overrides the broader one. For some meta tags (such as <code>keywords</code>) it is more useful to use all defaults from all broader contexts. Checking this option will use the user-inputted value and all context default values as values for this meta tag. If unsure, unselect this option.'),
    '#default_value' => (isset($tag->options['use-all']) ? $tag->options['use-all'] : FALSE),
  );
  $form['options']['allow-empty'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow empty value'),
    '#description' => t('If a meta tag value is empty, normally there is no use of outputting the meta tag. Check this option if you want to output an empty-valued meta tag.'),
    '#default_value' => (isset($tag->options['allow-empty']) ? $tag->options['allow-empty'] : FALSE),
  );
  $form['options']['unique-list'] = array(
    '#type' => 'checkbox',
    '#title' => t('Suppress duplicate values'),
    '#description' => t('Normally there is no use of outputting the same value of a meta tag multiple times. For meta tags as <code>keywords</code> or <code>DC.Subject</code> this is even discouraged as it may lower your SEO ranking. Checking this option will remove duplicate values for this meta tag. If unsure, select this option.'),
    '#default_value' => (isset($tag->options['unique-list']) ? $tag->options['unique-list'] : TRUE),
  );
  $form['options']['combine-values'] = array(
    '#type' => 'checkbox',
    '#title' => t('Combine multiple values'),
    '#description' => t('If a meta tag has multiple values, either by checking the option above or when the widget supports multiple values, one meta tag is outputted for each value. For some meta tags (such as <code>keywords</code>) it is more usefull to combine all those values into one single value. Checking this option will combine all inputted or automatic values into a single one separated by the separator below. If unsure, unselect this option.'),
    '#default_value' => (isset($tag->options['combine-values']) ? $tag->options['combine-values'] : FALSE),
  );
  $form['options']['separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Separator'),
    '#description' => t('For the <em>Combine multiple values</em> option above we need a separator. If unsure, input <em>, (comma)</em>.'),
    '#size' => 6,
    '#default_value' => (isset($tag->options['separator']) ? $tag->options['separator'] : ','),
  );

  $form['buttons'] = array(
    '#weight' => 50,
    'save' => array(
      '#type' => 'submit',
      '#value' => (isset($tag->tagid) ? t('Save meta tag') : t('Create new meta tag')),
      '#submit' => array('nodewords_edit_submit_save'),
      '#weight' => 0,
    ),
  );
  if (isset($tag->tagid)) {
    $form['buttons']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete meta tag'),
      '#submit' => array('nodewords_edit_submit_delete'),
      '#weight' => 5,
    );
  }

  return $form;
}

/**
 * 'Save meta tag' submit handler.
 */
function nodewords_edit_submit_save($form, &$form_state) {
  $form_values = $form_state['values'];
  if (isset($form_values['tagid']) && is_numeric($form_values['tagid'])) {
    $tagid = _nodewords_db_update_tag($form_values);
    drupal_set_message(t('Updated %tag_name meta tag.', array('%tag_name' => $form_values['name'])));
  }
  else {
    $tagid = _nodewords_db_insert_tag($form_values);
    drupal_set_message(t('Created new %tag_name meta tag.', array('%tag_name' => $form_values['name'])));
  }
  $form_state['redirect'] = 'admin/content/nodewords/'. $tagid;
  $form_state['tagid'] = $tagid;
}

/**
 * 'Delete meta tag' submit handler.
 */
function nodewords_edit_submit_delete($form, &$form_state) {
  $form_values = $form_state['values'];
  $destination = '';
  if (isset($_REQUEST['destination'])) {
    $destination = drupal_get_destination();
    unset($_REQUEST['destination']);
  }
  $form_state['redirect'] = array('admin/content/nodewords/'. $form_values['tagid'] .'/delete', $destination);
}

/**
 * Edit the attributes of a meta tag.
 *
 * @param $tag
 *   Object. The meta tag to edit. If NULL a new meta tag will be created.
 */
function nodewords_edit_attributes(&$form_state, $tag) {
  drupal_set_title(t('Edit %tag_name meta tag attributes', array('%tag_name' => $tag->name)));

  if ($tag->widget == 'alias') {
    drupal_set_message(t('You can not set attributes for a meta tag which is an alias.'), 'error');
    return array();
  }

  $form = array();
  $form['tagid'] = array('#type' => 'value', '#value' => $tag->tagid);
  $form['name'] = array('#type' => 'value', '#value' => $tag->name);

  if ($form_state['rebuild']) {
    $attributes = $form_state['values']['attributes'];
  }
  else {
    $attributes = $tag->attributes;
  }

  $form['attributes'] = array(
    '#tree' => TRUE,
  );
  foreach ((array)$attributes as $i => $value) {
    $value = (object)$value;
    $form['attributes'][] = array(
      'attid' => array('#type' => 'value', '#value' => $value->attid),
      'delete' => array('#type' => 'checkbox', '#default_value' => (isset($value->delete) ? $value->delete : FALSE)),
      'name' => array('#type' => 'textfield', '#default_value' => $value->name, '#size' => 16),
      'value' => array('#type' => 'textfield', '#default_value' => $value->value, '#size' => 32),
      'weight' => array('#type' => 'weight', '#default_value' => $value->weight),
    );
  }

  $form['buttons'] = array(
    '#weight' => 50,
    'save' => array(
      '#type' => 'submit',
      '#value' => t('Save attributes'),
      '#validate' => array('nodewords_edit_attributes_validate_save'),
      '#submit' => array('nodewords_edit_attributes_submit_save'),
      '#weight' => 5,
    ),
    'add' => array(
      '#type' => 'submit',
      '#value' => t('Add new attribute'),
      '#submit' => array('nodewords_edit_attributes_submit_add'),
      '#weight' => 5,
    ),
  );

  return $form;
}

/**
 * 'Add new attribute' submit handler.
 */
function nodewords_edit_attributes_submit_add($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $form_state['values']['attributes'][] = array(
    'attid' => '',
    'delete' => FALSE,
    'name' => '',
    'value' => '',
    'weight' => 0,
  );
}

/**
 * 'Save attributes' validate handler.
 */
function nodewords_edit_attributes_validate_save($form, &$form_state) {
  $form_values = $form_state['values'];
  //TODO: check if values of attributes can be empty in W3C standards - prolly yes
  foreach ((array)$form_values['attributes'] as $attribute) {
    if (empty($attribute['name']) && !($attribute['delete'] || empty($attribute['value']))) {
      form_set_error('', t('The name of an attribute can not be empty.'));
    }
  }
}

/**
 * 'Save attributes' submit handler.
 */
function nodewords_edit_attributes_submit_save($form, &$form_state) {
  $form_values = $form_state['values'];
  _nodewords_db_update_attributes($form_values['tagid'], $form_values['attributes']);
  drupal_set_message(t('Updated %tag_name meta tag attributes.', array('%tag_name' => $form_values['name'])));
}

/**
 * Form callback: edit defaults.
 */
function nodewords_edit_defaults(&$form_state, $tag) {
  drupal_set_title(t('Edit %tag_name meta tag defaults', array('%tag_name' => $tag->name)));

  $form = array();

  $form['tagid'] = array('#type' => 'value', '#value' => $tag->tagid);
  $form['name'] = array('#type' => 'value', '#value' => $tag->name);
  $form['defaults'] = array('#tree' => TRUE);

  $options = array(
    NODEWORDS_INHERIT => t('Inherit'),
    NODEWORDS_ENABLED => t('Yes'),
    NODEWORDS_DISABLED => t('No'),
  );

  foreach ((array)_nodewords_contexts() as $context => $info) {
    $form['defaults'][$context] = array(
      '#title' => $info['name'],
      '#description' => $info['description'],
      '#tree' => TRUE,
    );
    $form['defaults'][$context]['context'] = array(
      '#type' => 'value',
      '#value' => $context,
    );
    $form['defaults'][$context]['enabled'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => (isset($tag->defaults[$context]['enabled']) ? $tag->defaults[$context]['enabled'] : NODEWORDS_INHERIT),
    );
    $editable = (isset($tag->defaults[$context]['editable']) ? $tag->defaults[$context]['editable'] : NODEWORDS_INHERIT);
    if (($tag->widget == 'alias' || $tag->widget == 'none') && $editable == NODEWORDS_ENABLED) {
      $editable = NODEWORDS_DISABLED;
    }
    $form['defaults'][$context]['editable'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $editable,
      '#disabled' => ($tag->widget == 'alias' || $tag->widget == 'none'),
    );
    $form['defaults'][$context]['value'] = array(
      '#type' => 'textfield',
      '#default_value' => (isset($tag->defaults[$context]['value']) ? $tag->defaults[$context]['value'] : ''),
      '#disabled' => ($tag->widget == 'alias'),
    );
  }

  $form['buttons'] = array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save defaults'),
      '#submit' => array('nodewords_edit_defaults_submit_save'),
      '#weight' => 0,
    ),
    '#weight' => 50,
  );

  return $form;
}

/**
 * 'Save defaults' submit handler.
 */
function nodewords_edit_defaults_submit_save($form, &$form_state) {
  $form_values = $form_state['values'];
  _nodewords_db_update_defaults($form_values['tagid'], $form_values['defaults']);
  drupal_set_message(t('Updated %tag_name meta tag defaults.', array('%tag_name' => $form_values['name'])));
}

/**
 * Edit widget.
 */
function nodewords_edit_widget(&$form_state, $tag) {
  drupal_set_title(t('Edit %tag_name meta tag widget', array('%tag_name' => $tag->name)));

  if (isset($form_state['rebuild']) && $form_state['rebuild']) {
    $widget_options = $form_state['values']['widget_options'];
    $widget = $form_state['values']['widget'];
  }
  else {
    $widget_options = $tag->widget_options;
    $widget = $tag->widget;
  }

  $form = array();

  $form['tagid'] = array('#type' => 'value', '#value' => $tag->tagid);
  $form['name'] = array('#type' => 'value', '#value' => $tag->name);
  $form['old-widget'] = array('#type' => 'value', '#value' => $widget);

  $widgets = _nodewords_widgets();
  $titles = array();
  $descriptions = array();
  foreach ($widgets as $key => $value) {
    $titles[$key] = $value['title'];
    if (isset($value['description'])) {
      $descriptions[$value['title']] = $value['description'];
    }
  }
  $description = t('<p>Select the widget to use to edit this meta tag.</p>');
  if (count($descriptions)) {
    $description .= theme('nodewords_descriptions', $descriptions);
  }
  $form['widget'] = array(
    '#type' => 'radios',
    '#title' => t('Widget type'),
    '#description' => $description,
    '#options' => $titles,
    '#default_value' => $widget,
    '#required' => TRUE,
  );

  $form['widget_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Widget options'),
    '#tree' => TRUE,
    '#description' => t('Here you can customize the widget. The available options depend on the selected widget.'),
  );

  $function = '_nodewords_widget_options_'. $widget;
  if (function_exists($function)) {
    $form_options = $function($widget_options);
    $form['widget_options'] = array_merge($form['widget_options'], $form_options);
  }

  if (count(element_children($form['widget_options'])) == 0) {
    $form['widget_options'][] = array(
      '#value' => t('There are no options available for this widget.'),
    );
  }

  $form['buttons'] = array(
    '#weight' => 50,
    'save' => array(
      '#type' => 'submit',
      '#value' => t('Save widget'),
      '#validate' => array('nodewords_edit_widget_validate_save'),
      '#submit' => array('nodewords_edit_widget_submit_save'),
    ),
  );

  return $form;
}

/**
 * 'Save widget' validate handler.
 */
function nodewords_edit_widget_validate_save($form, &$form_state) {
  $form_values = $form_state['values'];

  if ($form_values['old-widget'] == $form_values['widget']) {
    $function = '_nodewords_widget_options_'. $form_values['widget'] .'_validate';
    if (function_exists($function)) {
      $function($form, $form_state);
    }
  }
}

/**
 * 'Save widget' submit handler.
 */
function nodewords_edit_widget_submit_save($form, &$form_state) {
  $form_values = $form_state['values'];

  if ($form_values['old-widget'] != $form_values['widget']) {
    $form_state['rebuild'] = TRUE;
    drupal_set_message(t('You have changed the widget to use, please fill in the widget options.'));
  }
  else {
    _nodewords_db_update_tag_widget($form_values['tagid'], $form_values['widget'], $form_values['widget_options']);
    drupal_set_message(t('Updated %tag_name meta tag widget.', array('%tag_name' => $form_values['name'])));
  }
}

/**
 * list the available meta tags.
 */
function nodewords_list() {
  $tags = nodewords_get_tags();

  $form = array(
    'tags' => array('#tree' => TRUE),
  );

  $types = _nodewords_types();
  $widgets = _nodewords_widgets();
  $destination = drupal_get_destination();

  foreach ($tags as $tagid => $tag) {
    $form['tags'][$tagid] = array(
      'tagid' => array('#type' => 'value', '#value' => $tagid), 
      'name' => array('#value' => check_plain($tag->name)),
      'type' => array('#value' => $tag->widget != 'alias' ? check_plain($types[$tag->type]['title']) : t('Ignored')),
      'widget' => array('#value' => check_plain($widgets[$tag->widget]['title'])),
      'description' => array('#value' => check_plain($tag->description)),
      'weight' => array('#type' => 'weight', '#default_value' => $tag->weight),
      'edit' => array('#value' => l(t('edit'), 'admin/content/nodewords/'. $tagid)),
      'delete' => array('#value' => l(t('delete'), 'admin/content/nodewords/'. $tagid .'/delete', array('query' => $destination))),
    );
  }

  $form['buttons'] = array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save meta tags'),
      '#disabled' => (count($tags) == 0),
      '#submit' => array('nodewords_list_submit_save'),
      '#weight' => 0,
    ),
    '#weight' => 50,
  );

  return $form;
}

/**
 * 'Save meta tags' submit handler.
 */
function nodewords_list_submit_save($form, &$form_state) {
  $form_values = $form_state['values'];
  foreach ($form_values['tags'] as $tagid => $tag) {
    if (isset($tag['weight'])) {
      _nodewords_db_update_tag_weight($tagid, (int)$tag['weight']);
    }
  }
  drupal_set_message(t('The meta tag settings have been updated.'));
}

/**
 * General settings form.
 */
function nodewords_settings($form_state) {
  $form = array();

  $form['nodewords:content-length'] = array(
    '#type' => 'textfield',
    '#title' => t('Content length'),
    '#description' => t('The maximum number of characters the content of a meta tag can contain. Set to 0 to allow any length. If unsure, set it to 255 (a common cut-off length search engines use).'),
    '#default_value' => variable_get('nodewords:content-length', 255),
    '#size' => 6,
  );

  $form['nodewords:repeat-on-pager'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat meta tags for lists'),
    '#description' => t('Some search engines punish sites that use the same meta tags on different pages. Check this option if you want to repeat the same meta tags on pages that use the pager (such as the default front page). If unchecked, Drupal will only display the meta tags on the first page and not for subsequent pages. If unsure, unselect this option.'),
    '#default_value' => variable_get('nodewords:repeat-on-pager', FALSE),
  );

  $form['nodewords:use-front-page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use front page meta tags'),
    '#description' => t('Check this option if you want to use the meta tags for the front page even if the default front page specified is a view, panel or node - in this case, the meta tags specified for the view, panel or node will be ignored. If you want to use the meta tags of the view, panel or node instead, uncheck this option. If unsure, select this option and specify the meta tags you want on the meta tags for the front page.'),
    '#default_value' => variable_get('nodewords:use-front-page', TRUE),
  );

  return system_settings_form($form);
}

/*****************************************************************************
 * Theme functions.
 ****************************************************************************/

/**
 * Process variables for nodewords-edit-attributes.tpl.php.
 */
function template_preprocess_nodewords_edit_attributes(&$variables) {
  $variables['attributes'] = array();
  $form = $variables['form'];

  foreach (element_children($form['attributes']) as $child) {
    $attribute = &$form['attributes'][$child];

    if (isset($attribute['attid'])) {
      $attribute['weight']['#attributes']['class'] = 'nodewords-weight';

      $variables['attributes'][] = (object)array(
        'delete_check' => drupal_render($attribute['delete']),
        'name' => drupal_render($attribute['name']),
        'value' => drupal_render($attribute['value']),
        'weight_select' => drupal_render($attribute['weight']),
      );
    }
  }

  $variables['form_submit'] = drupal_render($form);
}

/**
 * Process variables for nodewords-edit-defaults.tpl.php.
 */
function template_preprocess_nodewords_edit_defaults(&$variables) {
  $variables['defaults'] = array();
  $form = $variables['form'];

  foreach (element_children($form['defaults']) as $child) {
    $default = &$form['defaults'][$child];

    $variables['defaults'][$child] = (object)array(
      'context_title' => $default['#title'],
      'context_description' => $default['#description'],
      'enabled_select' => drupal_render($default['enabled']),
      'editable_select' => drupal_render($default['editable']),
      'value' => drupal_render($default['value']),
    );
  }

  $variables['form_submit'] = drupal_render($form);
}

/**
 * Process variables for nodewords-list.tpl.php.
 */
function template_preprocess_nodewords_list(&$variables) {
  $variables['tags'] = array();

  foreach (element_children($variables['form']['tags']) as $tagid) {
    $tag = &$variables['form']['tags'][$tagid];

    $variables['form']['tags'][$tagid]['weight']['#attributes']['class'] = 'nodewords-weight';

    $variables['tags'][$tagid] = (object)array(
      'name' => drupal_render($tag['name']),
      'type' => drupal_render($tag['type']),
      'widget' => drupal_render($tag['widget']),
      'description' => drupal_render($tag['description']),
      'weight_select' => drupal_render($tag['weight']),
      'edit_link' => drupal_render($tag['edit']),
      'delete_link' => drupal_render($tag['delete']),
    );
  }

  $variables['form_submit'] = drupal_render($variables['form']);
}
