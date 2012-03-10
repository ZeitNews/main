
Drupal.behaviors.openpublish_core = function(context) { 

  // Hide the edit form on the preview screen and show a Back button
  if ($("div.preview") && $("div.preview").length > 0) {
  
    var is_in_modify = $("#edit-state-is-modify").val();   
        
    if (is_in_modify != 'yes') {
      $('#node-form div.standard').css('display', 'none');
      $('#node-form div.admin').css('display', 'none');
      $('#edit-state-is-modify').val("yes");
    }
    else {
      $('#edit-state-is-modify').val("");
      $('div.preview div.node').css('display', 'none');
    }
        
  }
  
  return;

}
