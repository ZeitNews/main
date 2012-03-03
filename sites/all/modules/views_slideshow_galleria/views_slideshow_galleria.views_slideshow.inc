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
      'carousel' => views_slideshow_galleria_variable_get('carousel'),
      'carousel_follow' => views_slideshow_galleria_variable_get('carousel_follow'),
      'carousel_speed' => views_slideshow_galleria_variable_get('carousel_speed'),
      'carousel_steps' => views_slideshow_galleria_variable_get('carousel_steps'),
      'clicknext' => views_slideshow_galleria_variable_get('clicknext'),
      'easing' => views_slideshow_galleria_variable_get('easing'),
      'height' => views_slideshow_galleria_variable_get('height'),
      'idle_speed' => views_slideshow_galleria_variable_get('idle_speed'),
      'idle_time' => views_slideshow_galleria_variable_get('idle_time'),
      'image_crop' => views_slideshow_galleria_variable_get('image_crop'),
      'image_margin' => views_slideshow_galleria_variable_get('image_margin'),
      'image_pan' => views_slideshow_galleria_variable_get('image_pan'),
      'image_pan_smoothness' => views_slideshow_galleria_variable_get('image_pan_smoothness'),
      'image_position' => views_slideshow_galleria_variable_get('image_position'),
      'max_scale_ratio' => views_slideshow_galleria_variable_get('max_scale_ratio'),
      'min_scale_ratio' => views_slideshow_galleria_variable_get('min_scale_ratio'),
      'pause_on_interaction' => views_slideshow_galleria_variable_get('pause_on_interaction'),
      'popup_links' => views_slideshow_galleria_variable_get('popup_links'),
      'preload' => views_slideshow_galleria_variable_get('preload'),
      'queue' => views_slideshow_galleria_variable_get('queue'),
      'show' => views_slideshow_galleria_variable_get('show'),
      'show_counter' => views_slideshow_galleria_variable_get('show_counter'),
      'show_imagenav' => views_slideshow_galleria_variable_get('show_imagenav'),
      'show_info' => views_slideshow_galleria_variable_get('show_info'),
      'thumb_crop' => views_slideshow_galleria_variable_get('thumb_crop'),
      'thumb_fit' => views_slideshow_galleria_variable_get('thumb_fit'),
      'thumb_margin' => views_slideshow_galleria_variable_get('thumb_margin'),
      'thumbnails' => views_slideshow_galleria_variable_get('thumbnails'),
      'transition' => views_slideshow_galleria_variable_get('transition'),
      'transition_initial' => views_slideshow_galleria_variable_get('transition_initial'),
      'transition_speed' => views_slideshow_galleria_variable_get('transition_speed'),
      'width' => views_slideshow_galleria_variable_get('width'),
      'advanced' => array(
        'history' => views_slideshow_galleria_variable_get('history'),
        'data_config' => views_slideshow_galleria_variable_get('data_config'),
        'data_selector' => views_slideshow_galleria_variable_get('data_selector'),
        'data_source' => views_slideshow_galleria_variable_get('data_source'),
        'data_type' => views_slideshow_galleria_variable_get('data_type'),
        'debug' => views_slideshow_galleria_variable_get('debug'),
        'extend' => views_slideshow_galleria_variable_get('extend'),
        'keep_source' => views_slideshow_galleria_variable_get('keep_source'),
        'lightbox_fade_speed' => views_slideshow_galleria_variable_get('lightbox_fade_speed'),
        'lightbox_transition_speed' => views_slideshow_galleria_variable_get('lightbox_transition_speed'),
        'overlay_background' => views_slideshow_galleria_variable_get('overlay_background'),
        'overlay_opacity' => views_slideshow_galleria_variable_get('overlay_opacity'),
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
    '#description' => t('Galleria theme to load on display. If you choose the %custom option, you must specify the path to your custom JavaScript theme below.', array('%custom' => t('<custom>'))),
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
    '#description' => t('Leave this blank unless you wish to override the theme used by the plugin. You should specify the name of the custom theme here, and enter its path below. See the !theme_api for how to create your own Galleria JavaScript themes.', array('!theme_api' => l(t('Galleria JavaScript theme API'), 'http://github.com/aino/galleria/blob/master/docs/theme_api.rst', array('attributes' => array('target' => '_blank'))), '%custom' => t('<custom>'))),
    '#default_value' => $view->options['views_slideshow_galleria']['custom_theme_options']['custom_theme'],
  );
  $form['views_slideshow_galleria']['custom_theme_options']['theme_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom theme path'),
    '#description' => t("Leave this blank unless you're overriding the theme. See the !theme_api for how to create your own Galleria JavaScript themes.", array('!theme_api' => l(t('Galleria JavaScript theme API'), 'http://github.com/aino/galleria/blob/master/docs/theme_api.rst', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => $view->options['views_slideshow_galleria']['custom_theme_options']['theme_path'],
  );
  $form['views_slideshow_galleria']['autoplay'] = array(
    '#type' => 'textfield',
    '#title' => t('Autoplay'),
    '#description' => t('The slide show will begin rotating after the specified time in ms. Enter 0 to disable autoplay'),
    '#default_value' => $view->options['views_slideshow_galleria']['autoplay'],
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
  $form['views_slideshow_galleria']['clicknext'] = array(
    '#type' => 'checkbox',
    '#title' => t('Click next'),
    '#description' => t('Click the image to navigate to next item.'),
    '#default_value' => $view->options['views_slideshow_galleria']['clicknext'],
  );
  $form['views_slideshow_galleria']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('This will set a height to the gallery. If you set this to %auto and no CSS height is found, Galleria will automatically add a 16/9 ratio as a fallback.', array('%auto' => 'auto')),
    '#default_value' => $view->options['views_slideshow_galleria']['height'],
  );
  $form['views_slideshow_galleria']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('This will set a width to the gallery. If you set this to %auto and no CSS height is found, Galleria will automatically add a 16/9 ratio as a fallback.', array('%auto' => 'auto')),
    '#default_value' => $view->options['views_slideshow_galleria']['width'],
  );
  $form['views_slideshow_galleria']['idle_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Idle speed'),
    '#description' => t("Controls the animation speed of the idle elements. An example is when the thumbnails and captions hide in the fullscreen theme after a period of inactivity."),
    '#default_value' => $view->options['views_slideshow_galleria']['idle_speed'],
  );
  $form['views_slideshow_galleria']['idle_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Idle time'),
    '#description' => t("You can control the delay before Galleria falls into idle mode using this option."),
    '#default_value' => $view->options['views_slideshow_galleria']['idle_time'],
  );
  $options = array(
    FALSE => t('Disabled'),
    TRUE => t('Enabled'),
    'width' => t('Scale width'),
    'height' => t('Scale height'),
  );
  $form['views_slideshow_galleria']['image_crop'] = array(
    '#type' => 'select',
    '#title' => t('Image scale / crop'),
    '#description' => t('If enabled, all images will be scaled to fill the stage, centered and cropped. Images can also be scaled to fit by width or height. Otherwise, they will scale down so the entire image fits.'),
    '#default_value' => $view->options['views_slideshow_galleria']['image_crop'],
    '#options' => $options,
  );
  $form['views_slideshow_galleria']['image_margin'] = array(
    '#type' => 'textfield',
    '#title' => t('Image margin'),
    '#description' => t('Sets a margin between the image and stage. Specify the number of pixels.'),
    '#default_value' => $view->options['views_slideshow_galleria']['image_margin'],
  );
  $form['views_slideshow_galleria']['image_pan'] = array(
    '#type' => 'checkbox',
    '#title' => t('Image pan'),
    '#description' => t('Galleria comes with a built-in panning effect. The effect is sometimes useful if you have cropped images and want to let the users pan across the stage to see the entire image. Enable image pan to apply a mouse-controlled movement of the image to reveal the cropped parts. Note that when images are scaled by height and the slide transition is used, the image may not stay centered in some browsers when this option is enabled.'),
    '#default_value' => $view->options['views_slideshow_galleria']['image_pan'],
  );
  $form['views_slideshow_galleria']['image_pan_smoothness'] = array(
    '#type' => 'textfield',
    '#title' => t('Image pan smoothness'),
    '#description' => t('This value sets how "smooth" the image pan movement should be when setting image_pan is set to %true. The higher value, the smoother effect but also CPU consuming.', array('%true' => 'true')),
    '#default_value' => $view->options['views_slideshow_galleria']['image_pan_smoothness'],
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
  $form['views_slideshow_galleria']['min_scale_ratio'] = array(
    '#type' => 'textfield',
    '#title' => t('Min scale ratio'),
    '#description' => t("Sets the minimum scale ratio for images. If you don't want Galleria to downscale any images, set this to 1. Leaving it blank will allow any scaling of the images."),
    '#default_value' => $view->options['views_slideshow_galleria']['max_scale_ratio'],
  );
  $form['views_slideshow_galleria']['pause_on_interaction'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pause on interaction'),
    '#description' => t('During playback, Galleria will stop the playback if the user presses thumbnails or any other navigational links. If you dont want this behaviour, set this option to %false.', array('%false' => 'false')),
    '#default_value' => $view->options['views_slideshow_galleria']['pause_on_interaction'],
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
  $form['views_slideshow_galleria']['show_counter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show counter'),
    '#description' => t('Disable if you do not wish to display the counter.'),
    '#default_value' => $view->options['views_slideshow_galleria']['show_counter'],
  );
  $form['views_slideshow_galleria']['show_imagenav'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show image nav'),
    '#description' => t('Disable if you do not wish to display the image navigation (next/prev arrows).'),
    '#default_value' => $view->options['views_slideshow_galleria']['show_imagenav'],
  );
  $form['views_slideshow_galleria']['show_info'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show info'),
    '#description' => t('Disable if you do not wish to display the captions.'),
    '#default_value' => $view->options['views_slideshow_galleria']['show_info'],
  );
  $options = array(
    FALSE => t('Disabled'),
    TRUE => t('Images'),
    'empty' => t('Empty'),
    'numbers' => t('Numbers'),
  );
  $form['views_slideshow_galleria']['thumbnails'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnails'),
    '#description' => t("Sets the creation of thumbnails. If set to %false, then Galleria will not create thumbnails. If you set this to %empty, Galleria will create empty spans with the className %img instead of thumbnails.", array('%empty' => t('Empty'), '%image' => t('img'), '%false' => t('False'))),
    '#default_value' => $view->options['views_slideshow_galleria']['thumbnails'],
    '#options' => $options,
  );
  $options = array(
    FALSE => t('False'),
    TRUE => t('Enabled'),
    'width' => t('Scale width'),
    'height' => t('Scale height'),
  );
  $form['views_slideshow_galleria']['thumb_crop'] = array(
    '#type' => 'select',
    '#title' => t('Thumb scale / crop'),
    '#description' => t('Same as image crop but for thumbnails.'),
    '#default_value' => $view->options['views_slideshow_galleria']['thumb_crop'],
    '#options' => $options,
  );
  $form['views_slideshow_galleria']['thumb_fit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Thumb fit'),
    '#description' => t("If this is enabled, all thumbnail containers will be shrinked to fit the actual thumbnail size. This is useful if you have thumbnails of various sizes and will then float nicely side-by-side.This is only relevant if thumb_crop is set to anything else but 'true'.If you want all thumbnails to fit inside a container with predefined width & height, set this to 'false'."),
    '#default_value' => $view->options['views_slideshow_galleria']['thumb_fit'],
  );
  $form['views_slideshow_galleria']['thumb_margin'] = array(
    '#type' => 'textfield',
    '#title' => t('Image margin'),
    '#description' => t("Same as %image_margin, but for thumbnails.", array('%image_margin' => t('Image margin'))),
    '#default_value' => $view->options['views_slideshow_galleria']['thumb_margin'],
  );
  $options = array(
    'fade' => t('Fade'),
    'flash' => t('Flash'),
    'pulse' => t('Pulse'),
    'slide' => t('Slide'),
    'fadeslide' => t('Fade/Slide'),
  );
  $form['views_slideshow_galleria']['transition'] = array(
    '#type' => 'select',
    '#title' => t('Transition'),
    '#description' => t("The transition that is used when displaying the images.<ul><li>%fade will fade between images.</li><li>%flash will fade into the background color between images.</li><li>%pulse will pulse into the background color between images.</li><li>%slide will slide the images using the Galleria easing depending on image position.</li><li>%fadeslide will fade between images and slide slightly at the same time.</li></ul>", array('%fade' => t('Fade'), '%flash' => t('Flash'), '%pulse' => t('Pulse'), '%slide' => t('Slide'), '%fadeslide' => t('Fade/Slide'))),
    '#default_value' => $view->options['views_slideshow_galleria']['transition'],
    '#options' => $options,
  );
  $form['views_slideshow_galleria']['transition_initial'] = array(
    '#type' => 'select',
    '#title' => t('Transition initial'),
    '#description' => t("Optionally choose a different transition for the first image."),
    '#default_value' => $view->options['views_slideshow_galleria']['transition_initial'],
    '#options' => $options,
  );
  $form['views_slideshow_galleria']['transition_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Transition speed'),
    '#description' => t("The milliseconds used when applying the transition."),
    '#default_value' => $view->options['views_slideshow_galleria']['transition_speed'],
  );
  $form['views_slideshow_galleria']['easing'] = array(
    '#type' => 'textfield',
    '#title' => t('Easing'),
    '#description' => t('You can use this option to control the animation easing on a global level in Galleria. Besides the built-in jQuery easings %linear and %swing, Galleria includes the following easings:<ul><li>%galleria</li><li>%galleriaIn</li><li>%galleriaOut</li></ul>You can use any of these easings or any other easing plugin, f.ex the jQuery Easing Plugin.', array('%linear' => t('linear'), '%swing' => t('swing'), '%galleria' => t('galleria'), '%galleriaIn' => t('galleriaIn'), '%galleriaOut' => t('galleriaOut'))),
    '#default_value' => $view->options['views_slideshow_galleria']['easing'],
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
  $form['views_slideshow_galleria']['advanced']['data_selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Data selector'),
    '#description' => t('The selector Galleria should look for in the HTML source. If you are using other elements than images to store data in the HTML, you can set this option to configure Galleria to look for the right elements.'),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['data_selector'],
  );
  $form['views_slideshow_galleria']['advanced']['data_source'] = array(
    '#type' => 'textfield',
    '#title' => t('Data source'),
    '#description' => t('This is where Galleria finds the data depending on data_type. It defaults to the target selector, which is the same element that was used in the jQuery plugin.'),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['data_source'],
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
    '#description' => t("This function is used to extend the init function of the theme. You will have full access to the Galleria API here. The argument is the cascaded options object, and the scope is always the Galleria gallery instance. Use extend as a method for adding custom modifications such as play/pause without creating a new theme. This example code will open the classic theme in a Galleria lightbox when an image is clicked: <ul><li>function() { this.bind(Galleria.IMAGE, function(e) { $(e.imageTarget).css('cursor','pointer').click(this.proxy(function() { this.openLightbox(); })); }); }</li><li>To toggle fullscreen on click substitute 'toggleFullscreen' in place of 'openLightbox'.</li></ul>"),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['extend'],
  );
  $form['views_slideshow_galleria']['advanced']['keep_source'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep source'),
    '#description' => t('If checked, the source HTML will be left intact, which will also create clickable images of each image inside the source. Useful for building custom thumbnails and still have galleria control the gallery.'),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['keep_source'],
  );
  $form['views_slideshow_galleria']['advanced']['lightbox_fade_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Lightbox fade speed'),
    '#description' => t("When calling ``.showLightbox()`` the lightbox will animate and fade the images and captions. This value controls how fast they should fade in milliseconds."),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['lightbox_fade_speed'],
  );
  $form['views_slideshow_galleria']['advanced']['lightbox_transition_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Lightbox transition speed'),
    '#description' => t("When calling ``.showLightbox()`` the lightbox will animate the white square before displaying the image. This value controls how fast it should animate in milliseconds."),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['lightbox_transition_speed'],
  );
  $form['views_slideshow_galleria']['advanced']['overlay_background'] = array(
    '#type' => 'textfield',
    '#title' => t('Overlay background'),
    '#description' => t("This defines the overlay background color when calling ``showLightbox()``."),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['overlay_background'],
  );
  $form['views_slideshow_galleria']['advanced']['overlay_opacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Overlay opacity'),
    '#description' => t("This sets how much opacity the overlay should have when calling ``showLightbox()``."),
    '#default_value' => $view->options['views_slideshow_galleria']['advanced']['overlay_opacity'],
  );
  $options = array(
    'auto' => t('Auto'),
    FALSE => t('False'),
    TRUE => t('True'),
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
