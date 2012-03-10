<?php

/**
 * @file
 * Admin functions for the Views Slideshow: Galleria module.
 */

/**
 * Configure Views Slideshow: Galleria; menu callback for
 * admin/build/views/views_slideshow_galleria.
 */
function views_slideshow_galleria_settings() {
  // First we attempt to autodiscover the path to the Galleria plugin.
  $path = views_slideshow_galleria_path();

  $form = array();

  $message = t('To use !galleria, you must first !download the plugin package, extract it, and place the entire contents into the folder on your server specified here. (An attempt at autodiscovery will be made if it is within the %sites or %other folders.)', array('%sites' => 'sites/all/libraries', '%other' => 'sites/example.com/libraries', '!galleria' => l(t('Galleria'), 'http://galleria.aino.se/', array('attributes' => array('target' => '_blank'))), '!download' => l(t('download'), 'http://github.com/aino/galleria/archives/master', array('attributes' => array('target' => '_blank')))));
  if (!file_exists($path .'/galleria.js')) {
    drupal_set_message($message, 'error');
  }

  $form[views_slideshow_galleria_variable_name('path')] = array(
    '#type' => 'textfield',
    '#title' => t('Path to the Galleria plugin'),
    '#description' => $message,
    '#default_value' => $path,
  );

  return system_settings_form($form);
}
