
/**
 *  @file
 *  This will initiate any Galleria browsers we have set up.
 */

(function ($) {
  Drupal.behaviors.viewsSlideshowGalleria = function (context) {
    for (id in Drupal.settings.viewsSlideshowGalleria) {
      $('#' + id + ':not(.viewsSlideshowGalleria-processed)', context).addClass('viewsSlideshowGalleria-processed').each(function () {
        var settings = Drupal.settings.viewsSlideshowGalleria[$(this).attr('id')];

        if (settings['themeURL']) {
//           Galleria.loadTheme(settings['themeURL']);
        }

        // I get an error if I just use $(this)... @WTF?
        if (settings['theme']) {
          $('#' + $(this).attr('id')).galleria(settings['theme'], settings);
        }
        else {
          $('#' + $(this).attr('id')).galleria(settings);
        }
      });
    }
  };
})(jQuery);
