<?php
/**
 * The settings for for the CloudMenu module.
 */
function cloudmenu_admin_settings() {
  $form = array();
  $form['cloudmenu_blocks'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of blocks'),
    '#default_value' => variable_get('cloudmenu_blocks', 1),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('This is the number of CloudMenu blocks you will be able to configure on !link', array('!link.' => l('your blocks configuration page', 'admin/build/block'))),
  );
  $form['#validate'][] = '_cloudmenu_settings_validate';

  return system_settings_form($form);
}

/**
 * Validation handler for the admin settings form.
 */
function _cloudmenu_settings_validate($form, &$form_state) {
  $blocks = $form_state['values']['cloudmenu_blocks'];
  if ($blocks < 0) {
    form_set_error('cloudmenu_blocks', t("The number of blocks can not be a negative number"));
  }
}
