<?php

/**
 * @file
 * Variable defaults for Views Slideshow: Galleria.
 */

/**
 * Define our constants.
 */

/**
 * This is the variable namespace, automatically prepended to module variables.
 */
define('VIEWS_SLIDESHOW_GALLERIA_NAMESPACE', 'views_slideshow_galleria__');

/**
 * Wrapper for variable_get() for Views Slideshow: Galleria variable registry.
 *
 * @param string $name
 *  The variable name to retrieve. Note that it will be namespaced by
 *  pre-pending VIEWS_SLIDESHOW_GALLERIA_NAMESPACE, as to avoid variable
 *  collisions with other modules.
 * @param unknown $default
 *  An optional default variable to return if the variable hasn't been set
 *  yet. Note that within this module, all variables should already be set
 *  in the views_slideshow_galleria_variable_default() function.
 * @return unknown
 *  Returns the stored variable or its default.
 *
 * @see views_slideshow_galleria_variable_set()
 * @see views_slideshow_galleria_variable_del()
 * @see views_slideshow_galleria_variable_default()
 */
function views_slideshow_galleria_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing is still
  // desired.
  if (!isset($default)) {
    $default = views_slideshow_galleria_variable_default($name);
  }
  // Namespace all variables.
  $variable_name = VIEWS_SLIDESHOW_GALLERIA_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() for Views Slideshow: Galleria variable registry.
 *
 * @param string $name
 *  The variable name to set. Note that it will be namespaced by
 *  pre-pending VIEWS_SLIDESHOW_GALLERIA_NAMESPACE, as to avoid variable
 *  collisions with other modules.
 * @param unknown $value
 *  The value for which to set the variable.
 * @return unknown
 *  Returns the stored variable after setting.
 *
 * @see views_slideshow_galleria_variable_get()
 * @see views_slideshow_galleria_variable_del()
 * @see views_slideshow_galleria_variable_default()
 */
function views_slideshow_galleria_variable_set($name, $value) {
  $variable_name = VIEWS_SLIDESHOW_GALLERIA_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() for Views Slideshow: Galleria variable registry.
 *
 * @param string $name
 *  The variable name to delete. Note that it will be namespaced by
 *  pre-pending VIEWS_SLIDESHOW_GALLERIA_NAMESPACE, as to avoid variable
 *  collisions with other modules.
 *
 * @see views_slideshow_galleria_variable_get()
 * @see views_slideshow_galleria_variable_set()
 * @see views_slideshow_galleria_variable_default()
 */
function views_slideshow_galleria_variable_del($name) {
  $variable_name = VIEWS_SLIDESHOW_GALLERIA_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Views Slideshow: Galleria namespace.
 *
 * @param string $name
 *  Optional variable name to retrieve the default. Note that it has not yet
 *  been pre-pended with the VIEWS_SLIDESHOW_GALLERIA_NAMESPACE namespace at
 *  this time.
 * @return unknown
 *  The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see views_slideshow_galleria_variable_get()
 * @see views_slideshow_galleria_variable_set()
 * @see views_slideshow_galleria_variable_del()
 */
function views_slideshow_galleria_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      'history' => 0,
      'theme' => 'classic',
      'custom_theme' => '',
      'theme_path' => '',
      'autoplay' => 0,
      'autoplay_ms' => 3000,
      'carousel' => TRUE,
      'carousel_speed' => 200,
      'carousel_steps' => 'auto',
      'data_config' => '',
      'data_image_selector' => 'img',
      'data_source' => '',
      'data_type' => 'auto',
      'debug' => 0,
      'extend' => '',
      'height' => 'auto',
      'image_crop' => 0,
      'image_margin' => 0,
      'image_position' => 'center',
      'keep_source' => 0,
      'max_scale_ratio' => '',
      'on_image' => '',
      'popup_links' => 0,
      'preload' => 2,
      'queue' => TRUE,
      'show' => 0,
      'thumb_crop' => TRUE,
      'thumb_margin' => 0,
      'thumb_quality' => TRUE,
      'thumbnails' => TRUE,
      'transition' => 'fade',
      'transition_speed' => 400,
      'avoid_flash_of_content' => TRUE,
    );
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 *
 * @param string $name
 *  The variable name to retrieve the namespaced name.
 * @return string
 *  The fully namespace variable name, prepended with
 *  VIEWS_SLIDESHOW_GALLERIA_NAMESPACE.
 */
function views_slideshow_galleria_variable_name($name) {
  return VIEWS_SLIDESHOW_GALLERIA_NAMESPACE . $name;
}


