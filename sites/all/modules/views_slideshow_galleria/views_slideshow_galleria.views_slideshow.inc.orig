<?php

/**
 *  @file
 *  The default options available with Views Slideshow: Galleria.
 */

/**
 *  Implements hook_views_slideshow_modes().
 */
function views_slideshow_galleria_views_slideshow_modes() {
  // Expose the mode for Galleria slide shows.
  $options = array(
    'views_slideshow_galleria' => t('Galleria'),
  );
  return $options;
}

/**
 *  Implements hook_views_slideshow_option_definition().
 */
function views_slideshow_galleria_views_slideshow_option_definition() {
  // Set our default options.
  $options['views_slideshow_galleria'] = array(
    'default' => array(
      'theme' => views_slideshow_galleria_variable_get('theme'),
      'custom_theme_options' => array(
        'custom_theme' => views_slideshow_galleria_variable_get('custom_theme'),
        'theme_path' => views_slideshow_galleria_variable_get('theme_path'),
      ),
      'autoplay' => views_slideshow_galleria_variable_get('autoplay'),
      'autoplay_ms' => views_slideshow_galleria_variable_get('autoplay_ms'),
      'carousel' => views_slideshow_galleria_variable_get('carousel'),
      'carousel_follow' => views_slideshow_galleria_variable_get('carousel_follow'),
      'carousel_speed' => views_slideshow_galleria_variable_get('carousel_speed'),
      'carousel_steps' => views_slideshow_galleria_variable_get('carousel_steps'),
      'height' => views_slideshow_galleria_variable_get('height'),
      'image_crop' => views_slideshow_galleria_variable_get('image_crop'),
      'image_margin' => views_slideshow_galleria_variable_get('image_margin'),
      'image_position' => views_slideshow_galleria_variable_get('image_position'),
      'max_scale_ratio' => views_slideshow_galleria_variable_get('max_scale_ratio'),
      'popup_links' => views_slideshow_galleria_variable_get('popup_links'),
      'preload' => views_slideshow_galleria_variable_get('preload'),
      'queue' => views_slideshow_galleria_variable_get('queue'),
      'show' => views_slideshow_galleria_variable_get('show'),
      'thumb_crop' => views_slideshow_galleria_variable_get('thumb_crop'),
      'thumb_margin' => views_slideshow_galleria_variable_get('thumb_margin'),
      'thumbnails' => views_slideshow_galleria_variable_get('thumbnails'),
      'transition' => views_slideshow_galleria_variable_get('transition'),
      'transition_speed' => views_slideshow_galleria_variable_get('transition_speed'),
      'advanced' => array(
        'history' => views_slideshow_galleria_variable_get('history'),
        'data_config' => views_slideshow_galleria_variable_get('data_config'),
        'data_image_selector' => views_slideshow_galleria_variable_get('data_image_selector'),
        'data_source' => views_slideshow_galleria_variable_get('data_source'),
        'data_type' => views_slideshow_galleria_variable_get('data_type'),
        'debug' => views_slideshow_galleria_variable_get('debug'),
        'extend' => views_slideshow_galleria_variable_get('extend'),
        'keep_source' => views_slideshow_galleria_variable_get('keep_source'),
        'on_image' => views_slideshow_galleria_variable_get('on_image'),
        'thumb_quality' => views_slideshow_galleria_variable_get('thumb_quality'),
        'avoid_flash_of_content' => views_slideshow_galleria_variable_get('avoid_flash_of_content'),
      ),
    ),
  );
  return $options;
}

/**
 *  Implements hook_views_slideshow_options_form().
 */
function views_slideshow_galleria_views_slideshow_options_form(&$form, &$form_state, &$view) {
  // Create the form elements for our Galleria view options.
  $form['views_slideshow_galleria'] = array(
    '#type' => 'fieldset',
    '#title' => t('Galleria options'),
    '#description' => t("These options affect the slide show when it's in the !galleria mode. Please see !documentation for more information.", array('!galleria' => l(t('Galleria'), 'http://galleria.aino.se/', array('attributes' => array('target' => 'blank'))), '!documentation' => l(t('documentation'), 'http://github.com/aino/galleria/tree/master/docs/', array('attributes' => array('target' => '_blank'))))),
    '#collapsible' => TRUE,
    '#collapsed' => !($view->options['mode'] == 'views_slideshow_galleria'),
  );
  $options = array(
    0 => t('&lt;Custom&gt; (specify options below)'),
    'classic' => t('Classic'),
    'dots' => t('Dots'),
    'fullscreen' => t('Fullscreen'),
    'lightbox' => t('Lightbox'),
  );
  $form['views_slideshow_galleria']['theme'] = array(
    '#type' => 'radios',
    '#title' => t('Theme'),
    '#description' => t('Galleria theme to load on display. If you choose the %custom option, you must specify the path to your custom JavaScript theme below.', array('%custom' => t('<Custom>'))),
    '#default_value' => $view->options['views_slideshow_galleria']['theme'],
    '#options' => $options,
  );
  $form['views_slideshow_galleria']['custom_theme_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom theme options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['views_slideshow_galleria']['custom_theme_options']['custom_theme'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom theme'),
    '#description' => t('Leave this blank unless you wish to override the theme used by the plugin. You should specify the name of the custom theme here, and enter its path below. See the !theme_api for how to create your own Galleria JavaScript themes.', array('!theme_api' => l(t('Galleria JavaScript theme API'), 'http://github.com/aino/galleria/blob/master/docs/theme_api.rst', array('attributes' => array('target' => '_blank'))), '%custom' => t('<Custom>'))),
    '#default_value' => $view->options['views_slideshow_galleria']['custom_theme_options']['custom_theme'],
  );
  $form['views_slideshow_galleria']['custom_theme_options']['theme_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom theme path'),
    '#description' => t("Leave this blank unless you're overriding the theme. See the !theme_api for how to create your own Galleria JavaScript themes.", array('!theme_api' => l(t('Galleria JavaScript theme API'), 'http://github.com/aino/galleria/blob/master/docs/theme_api.rst', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => $view->options['views_slideshow_galleria']['custom_theme_options']['theme_path'],
  );
  $form['views_slideshow_galleria']['autoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Autoplay'),
    '#description' => t('If checked, then the slide show will begin rotating after the specified time below.'),
    '#default_value' => $view->options['views_slideshow_galleria']['autoplay'],
  );
  $form['views_slideshow_galleria']['autoplay_ms'] = array(
    '#type' => 'textfield',
    '#title' => t('Autoplay time'),
    '#description' => t('If the slide show is set to autoplay above, then begin after this many miliseconds.'),
    '#default_value' => $view->options['views_slideshow_galleria']['autoplay_ms'],
  );
  $form['views_slideshow_galleria']['carousel'] = array(
    '#type' => 'checkbox',
    '#title' => t('Carousel'),
    '#description' => t('If checked, this will activate the carousel when needed. Otherwise it will not appear at all.'),
    '#default_value' => $view->options['views_slideshow_galleria']['carousel'],
  );
  $form['views_slideshow_galleria']['carousel_follow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Carousel follow'),
    '#description' => t('If checked, the carousel will follow the active image.'),
    '#default_value' => $view->options['views_slideshow_galleria']['carousel_follow'],
  );
  $form['views_slideshow_galleria']['carousel_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Carousel speed'),
    '#description' => t('The slide speed of the carousel in milliseconds.'),
    '#default_value' => $view->options['views_slideshow_galleria']['carousel_speed'],
  );
  $form['views_slideshow_galleria']['carousel_steps'] = array(
    '#type' => 'textfield',
    '#title' => t('Carousel steps'),
    '#description' => t('The number of "steps" the carousel will slide when navigating between available thumbnails. Specifying %auto will move the carousel as many steps as there are visible thumbnails.', array('%auto' => 'auto')),
    '#default_value' => $view->options['views_slideshow_galleria']['carousel_steps'],
  );
  $form['views_slideshow_galleria']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('This will set a height to the gallery. If you set this to %auto and no CSS height is found, Galleria will automatically add a 16/9 ratio as a fallback.', array('%auto' => 'auto')),
    '#default_value' => $view->options['views_slideshow_galleria']['height'],
  );
  $form['views_slideshow_galleria']['image_crop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Image crop'),
    '#description' => t('If checked, all images will be scaled to fill the stage, centered and cropped. Otherwise, they will scale down so the entire image fits.'),
    '#default_value' => $view->options['views_slideshow_galleria']['image_crop'],
  );
  $form['views_slideshow_galleria']['image_margin'] = array(
    '#type' => 'textfield',
    '#title' => t('Image margin'),
    '#description' => t('Sets a margin between the image and stage. Specify the number of pixels.'),
    '#default_value' => $view->options['views_slideshow_galleria']['image_margin'],
  );
  $form['views_slideshow_galleria']['image_position'] = array(
    '#type' => 'textfield',
    '#title' => t('Image position'),
    '#description' => t("Positions the main image. Works like the CSS background-position property; i.e., 'top right' or '20% 100%'. You can use keywords, percents or pixels. The first value is the horizontal position and the second is the vertical. Read more at !read_more.", array('!read_more' => l('http://www.w3.org/TR/REC-CSS1/#background-position', 'http://www.w3.org/TR/REC-CSS1/#background-position', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => $view->options['views_slideshow_galleria']['image_position'],
  );
  $form['views_slideshow_galleria']['max_scale_ratio'] = array(
    '#type' => 'textfield',
    '#title' => t('Max scale ratio'),
    '#description' => t("Sets the maximum scale ratio for images. If you don't want Galleria to upscale any images, set this to 1. Leaving it blank will allow any scaling of the images."),
    '#default_value' => $view->options['views_slideshow_galleria']['max_scale_ratio'],
  );
  $form['views_slideshow_galleria']['popup_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Popup links'),
    '#description' => t('Checking this box will open any image links in a new window.'),
    '#default_value' => $view->options['views_slideshow_galleria']['popup_links'],
  );
  $form['views_slideshow_galleria']['preload'] = array(
    '#type' => 'textfield',
    '#title' => t('Preload'),
    '#description' => t("Defines how many images Galleria should preload in advance. Please note that this only applies when you are using separate thumbnail files. Galleria always cache all preloaded images. <ul><li>%2 preloads the next 2 images in line.</li><li>%all forces Galleria to start preloading all images. This may slow down client.</li><li>%0 will not preload any images</li></ul>", array('%2' => '2', '%all' => 'all', '%0' => '0')),
    '#default_value' => $view->options['views_slideshow_galleria']['preload'],
  );
  $form['views_slideshow_galleria']['queue'] = array(
    '#type' => 'checkbox',
    '#title' => t('Queue'),
    '#description' => t("Galleria queues all activation clicks (next/prev & thumbnails). You can see this effect when, for example, clicking %next many times. If you don't want Galleria to queue, then uncheck the box.", array('%next' => t('next'))),
    '#default_value' => $view->options['views_slideshow_galleria']['queue'],
  );
  $form['views_slideshow_galleria']['show'] = array(
    '#type' => 'textfield',
    '#title' => t('Show'),
    '#description' => t("This defines what image index to show at first. If you have left the %history box checked, then a permalink will override this number.", array('%history' => t('History permalinks'))),
    '#default_value' => $view->options['views_slideshow_galleria']['show'],
  );
  $form['views_slideshow_galleria']['thumb_crop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Thumb crop'),
    '#description' => t("Same as %image_crop, but for thumbnails.", array('%image_crop' => t('Image crop'))),
    '#default_value' => $view->options['views_slideshow_galleria']['thumb_crop'],
  );
  $form['views_slideshow_galleria']['thumb_margin'] = array(
    '#type' => 'textfield',
    '#title' => t('Image margin'),
    '#description' => t("Same as %image_margin, but for thumbnails.", array('%image_margin' => t('Image margin'))),
    '#default_value' => $view->options['views_slideshow_galleria']['thumb_margin'],
  );
  $options = array(
    'empty' => t('Empty'),
    0 => t('False'),
    1 => t('True'),
  );
  $form['views_slideshow_galleria']['thumbnails'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnails'),
    '#description' => t("Sets the creation of thumbnails. If set to %false, then Galleria will not create thumbnails. If you set this to %empty, Galleria will create empty spans with the className %img instead of thumbnails.", array('%empty' => t('Empty'), '%image' => t('img'), '%false' => t('False'))),
    '#default_value' => $view->options['views_slideshow_galleria']['thumbnails'],
    '#options' => $options,
  );
  $options = array(
    'fade' => t('Fade'),
    'flash' => t('Flash'),
    'slide' => t('Slide'),
    'fadeslide' => t('Fade/Slide'),
  );
  $form['views_slideshow_galleria']['transition'] = array(
    '#type' => 'select',
    '#title' => t('Transition'),
    '#description' => t("The transition that is used when displaying the images.<ul><li>%fade will fade between images.</li><li>%flash will fade into the background color between images.</li><li>%slide will slide the images using the Galleria easing depending on image position.</li><li>%fadeslide will fade between images and slide slightly at the same time.</li></ul>", array('%fade' => t('Fade'), '%flash' => t('Flash'), '%slide' => t('Slide'), '%fadeslide' => t('Fade/Slide'))),
    '#default_value' => $view->options['views_slideshow_galleria']['transition'],
    '#options' => $options,
  );
  $form['views_slideshow_galleria']['transition_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Transition speed'),
    '#description' => t("The milliseconds used when applying the transition."),
    '#default_value' => $view->options['views_slideshow_galleria']['transition_speed'],
  );

  $form['views_slideshow_galleria']['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#description' => t('WARNING: Some of these settings will pass raw JavaScript to the browser, so should be used with care. See the !docs for more information on their usage.', array('!docs' => l(t('documentation'), 'http://github.com/aino/galleria/blob/master/docs/options.rst', array('attributes' => array('target' => '_blank'))))),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['views_slideshow_galleria']['advanced']['history'] = array(
    '#type' => 'checkbox',
    '#title' => t('History permalinks'),
    '#description' => t('Add permalinks to all images in the gallery.'),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['history'],
  );
  $form['views_slideshow_galleria']['advanced']['data_config'] = array(
    '#type' => 'textarea',
    '#title' => t('Data config'),
    '#description' => t('This javascript function configures how the data should be extracted from the source. It should return an object that will blend in with the default extractions. WARNING: Raw JavaScript will be passed here.'),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['data_config'],
  );
  $form['views_slideshow_galleria']['advanced']['data_image_selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Data image selector'),
    '#description' => t('The selector Galleria should look for in the HTML source. Defaults to %img and there is rarely any reason to change this.', array('%img' => views_slideshow_galleria_variable_get('data_image_selector'))),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['data_image_selector'],
  );
  $form['views_slideshow_galleria']['advanced']['data_source'] = array(
    '#type' => 'textfield',
    '#title' => t('Data source'),
    '#description' => t('This is where Galleria finds the data depending on data_type. It defaults to the target selector, which is the same element that was used in the jQuery plugin.'),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['data_source'],
  );
  $options = array(
    'auto' => t('Auto'),
    'json' => t('JSON'),
    'html' => t('HTML'),
  );
  $form['views_slideshow_galleria']['advanced']['data_type'] = array(
    '#type' => 'select',
    '#title' => t('Data type'),
    '#description' => t("The dataType Galleria will use to extract data. There is rarely any reason to change this from auto, but you might encounter a situation where you'd like to force a certain data type."),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['data_type'],
    '#options' => $options,
  );
  $form['views_slideshow_galleria']['advanced']['debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug'),
    '#description' => t('If checked, the slide show will throw errors when something is not right.'),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['debug'],
  );
  $form['views_slideshow_galleria']['advanced']['extend'] = array(
    '#type' => 'textarea',
    '#title' => t('Extend'),
    '#description' => t("This function is used to extend the init function of the theme. Use this to quickly add minor customizations to the theme. The first argument is the options object, and the scope is always the Galleria gallery, just like the theme's init() function. WARNING: Raw JavaScript will be passed here."),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['extend'],
  );
  $form['views_slideshow_galleria']['advanced']['keep_source'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep source'),
    '#description' => t('If checked, the source HTML will be left intact, which will also create clickable images of each image inside the source. Useful for building custom thumbnails and still have galleria control the gallery.'),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['keep_source'],
  );
  $form['views_slideshow_galleria']['advanced']['on_image'] = array(
    '#type' => 'textarea',
    '#title' => t('on_image(image, thumbnail)'),
    '#description' => t("Helper event function that triggers when an image is loaded and about to enter the stage. This function simplifies the process of adding extra functionality when showing an image without using the extend method och manipulating the theme. %image is the main image and %thumbnail is the active thumbnail. WARNING: Raw JavaScript will be passed here.", array('%image' => 'image', '%thumbnail' => 'thumbnail')),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['on_image'],
  );
  $options = array(
    'auto' => t('Auto'),
    0 => t('False'),
    1 => t('True'),
  );
  $form['views_slideshow_galleria']['advanced']['thumb_quality'] = array(
    '#type' => 'select',
    '#title' => t('Thumb quality'),
    '#description' => t("Defines if and how IE should use bicubic image rendering for thumbnails.<ul><li>%auto uses high quality if image scaling is moderate.</li><li>%false will not use high quality (better performance).</li><li>%true will force high quality renedring (can slow down performance)</li></ul>", array('%auto' => t('Auto'), '%false' => t('False'), '%true' => t('True'))),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['thumb_quality'],
    '#options' => $options,
  );
  $form['views_slideshow_galleria']['advanced']['avoid_flash_of_content'] = array(
    '#type' => 'checkbox',
    '#title' => t('Avoid flash of content'),
    '#description' => t('If checked, then the images of the Galleria slide show will be hidden by JavaScript in the page header, so that there is no flash of content on the page load.'),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['avoid_flash_of_content'],
  );
}
