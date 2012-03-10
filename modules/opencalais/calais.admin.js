Drupal.behaviors.calais_admin = function(context) {

  $("input.nodetype_toggle").change(function(){
    var type = $(this).attr('data');
    var selector = "#" + type + "_toggle";
    if ($(this).val() == "0") {
      $(selector).hide(500);
    }
    else {
      $(selector).show(500);
    }
  });

  $("input.calais-use-global").change(function(){
    var type = $(this).attr('data');
    var selector = ".calais-entity-settings-" + type;
    $(selector).toggle(500);
  });
  
}

Drupal.behaviors.calais_enqueue = function(context) {

  // Hide the queue form on close
  $("#calais-queue-form #edit-close", context).click(function() {
    $("#calais-queue-form").hide(500);
  });
  
  // Display the queue form filled with the data from the proper content type
  $("a.calais-queue-toggle", context).click(function(){
    var type = $(this).attr('id').split('calais-queue-toggle-')[1];
    if ($("#calais-queue-form").is(':visible') && $("#edit-type").val() == type) {
      $("#calais-queue-form").hide(500)
    }
    else {
      var config = Drupal.settings.calais_queue;
      $("#edit-type").val(type);
      $('#calais-queue-type-label').html(type);
      $("#edit-process-type-" + config[type].process).attr('checked', true);
      $("#edit-threshold").val(config[type].threshold);
      $("#calais-queue-form").show(500);
    }
    return false;
  });
  
}