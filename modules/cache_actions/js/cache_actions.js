Drupal.behaviors.cache_actions = function(context) {
  var variants = Drupal.settings.variants;
  // Get the initial default values
  default_vals = $("#edit-settings-panes").val();
  // Clear out all the panes.
  $("#edit-settings-panes").html('');
  appendPanes(variants[$("#edit-settings-panel").val()]);
  default_vals = [];
  /**
   * Append the panes in the object to the settings pane.
   */
  function appendPanes(panes) {
    if(panes != undefined) {
      $.each(panes, function(k, v){
          option = $("<option></option>").attr('value', k).html(v);
          if(default_vals != undefined) {
            // Make sure that the default values are still selected.
            if (jQuery.inArray(k, default_vals) != -1) {
              option.attr('selected', 'selected');
            }
          }
          $("#edit-settings-panes").append(option);
      });
    }
  }
  
  $("#edit-settings-panel").change(function() {
      val = $(this).val();
      //default_vals = $('#edit-settings-panes').val();
      // Clear out the panes in the select
      $("#edit-settings-panes").html('');
      // Then append the panes attached to this variant.
      appendPanes(variants[val]);
  });
}

