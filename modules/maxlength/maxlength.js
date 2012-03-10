/* $Id: maxlength.js,v 1.1.6.6.2.14 2011/02/16 11:09:13 aronnovak Exp $ */

Drupal.maxLength_limit = function (field) {

  // Build maxlength values and settings
  var id = $(field).attr('id');
  // Skip form elements that do not exist. This sometimes occurs with more 
  // complex multi step form building modules like pageroute.
  if (id == undefined) {
    return;
  }
  var limit = Drupal.settings.maxlength[id];
  var maxlength = $('#maxlength-' + id.substr(5));
  maxlength.show_count = false;
  maxlength.span_remaining_count = maxlength.find('span.maxlength-counter-remaining');
  maxlength.find('span.maxlength-count', function() {
    maxlength.show_count = true;
    maxlength.span_count = maxlength.find('span.maxlength-count');
  });

  // calculate the remaining count of chars  
  var length = $(field).val().length;
  var remainingCount = limit - length;  

  // if there is not remaining char, we clear additional content
  if (remainingCount < 0) {
    $(field).val($(field).val().substr(0, limit));    
    remainingCount = 0;
  }  

  // Update the remaing chars text.
  maxlength.span_remaining_count.html(remainingCount.toString());
  // And the current count.
  if (maxlength.show_count) {
    maxlength.span_count.html(length.toString());
  }  
}

Drupal.behaviors.maxlength = function (context) {
  // Get all the settings, and save the limits in the fields.
  var element = {};
  for (var id in Drupal.settings.maxlength) {
  
    element = $("#"+ id);    
    
    if (element.length) {        
      // Update the count at the page load.
      Drupal.maxLength_limit(element);

      // Setup events
      element.load(function() {
        Drupal.maxLength_limit(this);
      });
      element.keyup(function() {
        Drupal.maxLength_limit(this);
      });
      element.change(function() {
        Drupal.maxLength_limit(this);
      });
    }
  }
}

