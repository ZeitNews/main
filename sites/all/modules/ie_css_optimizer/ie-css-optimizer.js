(function ($) {

Drupal.behaviors.ie_css_optimizer = function (context) {
  // This behavior attaches by ID, so is only valid once on a page.
  if ($('#ie-css-optimizer-module.ie-css-optimizer-processed').size()) {
    return;
  }
  $('#ie-css-optimizer-module', context).addClass('ie-css-optimizer-processed');

  // Toggle display of "follow parent" if "follow" has been checked.
  $('input[name=preprocess_css]', context).change( function() {
    if ($('input[name=preprocess_css]:checked').val() == 'module') {
      $('#ie-css-optimizer-module').slideDown('fast');
    }
    else {
      $('#ie-css-optimizer-module').slideUp('fast');
    }
  } );
  if ($('input[name=preprocess_css]:checked').val() != 'module') {
    $('#ie-css-optimizer-module', context).css('display', 'none');
  }

};

})(jQuery);
