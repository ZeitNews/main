(function ($) {
// START jQuery

Drupal.vfas = Drupal.vfas || {};

Drupal.behaviors.vfas = function(context) {
  $.each(Drupal.settings.vfas, function(form_id, settings) {
    $('form#'+form_id+':not(.vfas-processed)', context).each(function() {
      // Build the exceptions list.
      var self = this;
      var exceptions;
      if (settings.exceptions) {
        exceptions = ':not('+settings.exceptions+')';
      }    
      else {
        exceptions = '';
      }
      $(self).addClass('vfas-processed');
      // Hide the submit button.
      $('input:submit.form-submit', self).hide();
      // Auto-submit changes to inputs.
      $('div.views-exposed-widget input:checkbox'+exceptions+', div.views-exposed-widget input:radio'+exceptions, self).click(function() {
        $(self).submit();
      });
      $('div.views-exposed-widget select'+exceptions, self).change(function() {
        $(self).submit();
      });
      // Auto-submit keyups after a delay.
      var autoSubmitTimer = 0;
      var autoSubmitDelay = 1000;
      $('div.views-exposed-widget input'+exceptions, self).keyup(function() {
        if (autoSubmitTimer) {
          clearTimeout(autoSubmitTimer);
        }
        autoSubmitTimer = setTimeout(function() {
          $(self).submit();
        }, autoSubmitDelay);
      });

      // Re-focus form field after auto-submit.
      var refocus = $('#edit-views-exposed-form-focused-field', self).val();
      if (refocus) {
        $('#'+refocus, self).focus().val($('#'+refocus, self).val());
      }
      // Store the ID of the currently focused field in our hidden field.
      $('input', self).focus(function() {
        $('#edit-views-exposed-form-focused-field', self).val($(this).attr('id'));
      });
      // Clear value of our hidden field when user deselects the form.
      $('input', self).blur(function() {
        $('#edit-views-exposed-form-focused-field', self).val();
      });
    });
  });
}

// END jQuery
})(jQuery);

