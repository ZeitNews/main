
/**
 *  @file
 *  This will initiate any Galleria browsers we have set up.
 */

(function ($) {
  Drupal.behaviors.viewsSlideshowGalleria = function (context) {
    for (id in Drupal.settings.viewsSlideshowGalleria) {
      $('#' + id + ':not(.viewsSlideshowGalleria-processed)', context).addClass('viewsSlideshowGalleria-processed').each(function () {
        var _settings = Drupal.settings.viewsSlideshowGalleria[$(this).attr('id')];
        
        // Eval settings that are functions
        if (_settings['dataConfig']) {
          var galDataSource = _settings['dataConfig'];
          eval("_settings['dataConfig'] = " + galDataConfig);
        }
        if (_settings['extend']) {
          var galExtend = _settings['extend'];
          eval("_settings['extend'] = " + galExtend);
        }

        // Load Galleria (the theme will be applied inline)
        $(this).galleria(_settings);
      });
    }
  };
})(jQuery);

