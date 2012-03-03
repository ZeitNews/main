Drupal.behaviors.calais_geo = function(context) {

  if($("#edit-calais-geo-term-center").val() != "latlon") {
    $("#edit-calais-geo-center-latitude-wrapper").css('display', 'none');          
    $("#edit-calais-geo-center-longitude-wrapper").css('display', 'none');          
  }

  $("#edit-calais-geo-term-center").change(function() {
    if($(this).val() == "latlon") {
      $("#edit-calais-geo-center-latitude-wrapper").slideDown("slow");          
      $("#edit-calais-geo-center-longitude-wrapper").slideDown("slow");          
    }
    else {
      $("#edit-calais-geo-center-latitude-wrapper").slideUp("slow");          
      $("#edit-calais-geo-center-longitude-wrapper").slideUp("slow");          
    }
  });
}