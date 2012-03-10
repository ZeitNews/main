
Drupal.behaviors.moduleFilterDynamicPosition = function() {
  $(window).scroll(function() {
    var top = $('#module-filter-tabs').offset().top;
    var bottom = top + $('#module-filter-tabs').height();
    var windowHeight = $(window).height();
    if (((bottom - windowHeight) > ($(window).scrollTop() - $('#module-filter-submit').height())) && $(window).scrollTop() + windowHeight - $('#module-filter-submit').height() - $('#all-tab').height() > top) {
      if (!$('#module-filter-submit').hasClass('fixed')) {
        $('#module-filter-submit').addClass('fixed');
      }
    }
    else {
      $('#module-filter-submit').removeClass('fixed');
    }
  });
  $(window).trigger('scroll');
  $(window).resize(function() {
    $(window).trigger('scroll');
  });
}
