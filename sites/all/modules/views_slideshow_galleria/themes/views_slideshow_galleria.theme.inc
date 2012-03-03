<?php

/**
 *  @file
 *  Theme & preprocess functions for the Views Slideshow: Galleria module.
 */

/**
 *  We'll grab only the first image from each row.
 */
function template_preprocess_views_slideshow_galleria(&$vars) {
  // Initialize our $images array.
  $vars['images'] = array();

  $vars['original_rows'] = $vars['rows'];

  // Strip all images from the $rows created by the original view query.
  foreach ($vars['rows'] as $id => $item) {
    preg_match('@(<\s*img\s+[^>]*>)@i', $item, $matches);
    if ($image = $matches[1]) {
      // If our image is in an anchor tag, use its URL.
      preg_match('@<\s*a\s+href\s*=\s*"\s*([^"]+)\s*"[^>]*>[^<]*'. preg_quote($image) .'[^<]*<\s*/a\s*>@i', $item, $urls);
      if (!($url = $urls[1])) {
        // Otherwise link to the original image.
        preg_match('@src\s*=\s*"([^"]+)"@i', $image, $urls);
        if (!($url = $urls[1])) {
          // If we get this far, there are probably more serious problems.
          // But for now, we'll go to the front page instead.
          $url = url('<front>');
        }
      }

      // Ensure the link for the original image is preserved.
      // $url has already been url'ized.
      $vars['rows'][$id] = '<a href="'. $url .'">'. $image .'</a>';

      // Add the image to our image array to display.
      $vars['images'][$id] = $image;
    }
  }

  $options = $vars['options']['views_slideshow_galleria'];

  _views_slideshow_galleria_add_js($options, 'views-slideshow-galleria-images-'. $vars['id']);

  $vars['class'] = array(
    'views-slideshow-galleria-images',
    'galleria',
  );

  // Avoid flash of content.
  if ($options['advanced']['avoid_flash_of_content']) {
    $vars['class'][] = 'hidden';
  }

  $vars['classes'] = implode(' ', $vars['class']);
  drupal_add_css(drupal_get_path('module', 'views_slideshow_galleria') .'/themes/css/views_slideshow_galleria.css');
}

function _views_slideshow_galleria_add_js($options, $id) {

  // Find the path to our plugin.
  $path = views_slideshow_galleria_path();

  // Add the required JS and CSS.
  drupal_add_js($path .'/galleria.js');

  $drupal_path = drupal_get_path('module', 'views_slideshow_galleria') . '/themes';
  drupal_add_js($drupal_path .'/js/views_slideshow_galleria.js');

  if ($options['advanced']['history']) {
    drupal_add_js($path .'/plugins/galleria.history.js');
  }

  // Set $theme_url to the path to the JS theme file for the galleria.
  if ($options['custom_theme_options']['custom_theme'] && $options['custom_theme_options']['theme_path']) {
    $theme_url = $options['custom_theme_options']['theme_path'];
  }
  elseif ($options['theme'] && !$options['custom_theme_options']['theme_path']) {
    $theme_url = $path ."/themes/{$options['theme']}/galleria.{$options['theme']}.js";
  }
  elseif ($options['custom_theme_options']['theme_path']) {
    // We'll allow a custom theme path to override the default.
    $theme_url = $options['custom_theme_options']['theme_path'];
  }
  else {
    // No theme specified; we assume they're using a Drupal theme for styling.
    $theme_url = FALSE;
  }

  // Output our Galleria loadTheme function inline.
  drupal_add_js(' Galleria.loadTheme("'. $theme_url .'");', 'inline');

  $settings = array(
    'autoplay' => (integer)$options['autoplay'],
    'carousel' => $options['carousel'] ? TRUE : FALSE,
    'carouselFollow' => $options['carousel_follow'] ? TRUE : FALSE,
    'carouselSpeed' => (integer)$options['carousel_speed'],
    'carouselSteps' => ($options['carousel_steps'] == 'auto') ? 'auto' : (integer)$options['carousel_steps'],
    'clicknext' => $options['clicknext'] ? TRUE : FALSE,
    'debug' => $options['advanced']['debug'] ? TRUE : FALSE,
    'height' => ($options['height'] == 'auto') ? 'auto' : (integer)$options['height'],
    'width' => ($options['width'] == 'auto') ? 'auto' : (integer)$options['width'],
    'idleSpeed' => (integer)$options['idle_speed'],
    'idleTime' => (integer)$options['idle_time'],
    'imageMargin' => (integer)$options['image_margin'],
    'imagePan' => $options['image_pan'] ? TRUE : FALSE,
    'imagePanSmoothness' => (integer)$options['image_pan_smoothness'],
    'imagePosition' => check_plain($options['image_position']),
    'keepSource' => $options['advanced']['keep_source'] ? TRUE : FALSE,
    'lightboxFadeSpeed' => (integer)$options['advanced']['lightbox_fade_speed'],
    'lightboxTransitionSpeed' => (integer)$options['advanced']['lightbox_transition_speed'],
    'minScaleRatio' => (integer)$options['min_scale_ratio'],
    'maxScaleRatio' => (integer)$options['max_scale_ratio'],
    'overlayBackground' => check_plain($options['advanced']['overlay_background']),
    'overlayOpacity' => (float)$options['advanced']['overlay_opacity'],
    'pauseOnInteraction' => $options['pause_on_interaction'] ? TRUE : FALSE,
    'popupLinks' => $options['popup_links'] ? TRUE : FALSE,
    'preload' => ($options['preload'] == 'auto') ? 'auto' : (integer)$options['preload'],
    'queue' => $options['queue'] ? TRUE : FALSE,
    'show' => (integer)$options['show'],
    'showCounter' => $options['show_counter'] ? TRUE : FALSE,
    'showImagenav' => $options['show_imagenav'] ? TRUE : FALSE,
    'showInfo' => $options['show_info'] ? TRUE : FALSE,
    'thumbFit' => $options['thumb_fit'] ? TRUE : FALSE,
    'thumbMargin' => (integer)$options['thumb_margin'],
    'thumbQuality' => ($options['thumb_quality'] == 'auto') ? 'auto' : (boolean)$options['thumb_quality'],
    'transition' => $options['transition'],
    'transitionInitial' => $options['transition_initial'],
    'transitionSpeed' => (integer)$options['transition_speed'],
  );

  // Image crop is true, false or by height or width.
  if ($options['image_crop'] == 'width') {
    $settings['imageCrop'] = 'width';
  }
  elseif ($options['image_crop'] == 'height') {
    $settings['imageCrop'] = 'height';
  }
  else {$settings['imageCrop'] = $options['image_crop'] ? TRUE : FALSE;}

  // Thumbnails is empty, numbers or boolean.
  if ($options['thumbnails'] == 'empty') {
    $settings['thumbnails'] = 'empty';
  }
  elseif ($options['thumbnails'] == 'numbers') {
    $settings['thumbnails'] = 'numbers';
  }
  else {$settings['thumbnails'] = $options['thumbnails'] ? TRUE : FALSE;}

  // Thumb crop is true, false or by height or width.
  if ($options['thumb_crop'] == 'width') {
    $settings['thumbCrop'] = 'width';
  }
  elseif ($options['thumb_crop'] == 'height') {
    $settings['thumbCrop'] = 'height';
  }
  else {$settings['thumbCrop'] = $options['thumb_crop'] ? TRUE : FALSE;}

  // These settings can break the Galleria if they are passed empty.
  if ($options['advanced']['data_selector']) {
    $settings['dataSelector'] = check_plain($options['advanced']['data_selector']);
  }
  if ($options['advanced']['data_source']) {
    $settings['dataSource'] = check_plain($options['advanced']['data_source']);
  }
  if ($options['advanced']['data_config']) {
    $settings['dataConfig'] = $options['advanced']['data_config'];
  }
  if ($options['advanced']['extend']) {
    $settings['extend'] = $options['advanced']['extend'];
  }
   
  // Output the settings array.
  drupal_add_js(array('viewsSlideshowGalleria' => array($id => $settings)), 'setting');

}
