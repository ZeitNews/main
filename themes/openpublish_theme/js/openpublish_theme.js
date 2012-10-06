/**
 * Implementation of Drupal behavior.
 */
Drupal.behaviors.openpublish = function(context) {
  
// Focus cursor into username field for login.
$('#user-register #edit-name, #user-login #edit-name, #user-pass #edit-name').focus();

// Fade out distracting social media icons slightly.
// http://cssbeauty.com/skillshare/discussion/1593/#Item_5
$('#add-this').fadeTo('100', 0.6);
$('#add-this').hover(function(){
  $(this).fadeTo('400', 1.0);
},function(){
  $(this).fadeTo('400', 0.6);
});

// Set proper margins on images based on float direction.
// Iterate over all images in #op-content div (body and comments).
$('#op-content img').each(function() {
  
  // If it's likely a user editable image (has style attribute).
  if ($(this).attr('style')) {
    // Get the float from the style attribute or also unfortunately the stylesheet.
    var img_float = $(this).css('float');
    
    // Change CSS based on which float and if it has a caption.
    // Only downfall here is if you wanted to add custom margins via WYSIWYG, have to use !important.
    // Also if a system img uses a style attribute its margins are going to get clobbered.
    if (img_float == 'left') {
      // If it has an image caption.
      if ($(this).parent().hasClass('image-caption-container')) {
        $(this).parent().css({
          'margin': '10px 25px 23px 0px',
          'clear': 'left'
          });
      } else {
        $(this).css({
          'margin': '10px 25px 23px 0px',
          'clear': 'left'
          });
      }
    }
  
    if (img_float == 'right') {
      if ($(this).parent().hasClass('image-caption-container')) {
        $(this).parent().css({
          'margin': '10px 0px 23px 25px',
          'clear': 'right'
        });
      } else {
        $(this).css({
          'margin': '10px 0px 23px 25px',
          'clear': 'right'
        });
      }
    }
  }
});

// Creates :parents filter. Filter any level parent. http://stackoverflow.com/a/965962/1055558
jQuery.expr[':'].parents = function(a,i,m){
  return jQuery(a).parents(m[3]).length < 1;
};

// Set fancybox class and rel attributes for images linked to images in .body-content, including main-image.
// Also combat image theft.
$('.body-content img').filter(':parents(.views-slideshow-galleria, .fieldgroup)').each(function() {
  if (/zeitnews/i.test($(this).attr('src'))) {
    // Does the img element have an <a> parent?
    if ($(this).closest('a').length > 0) {
      // Does the <a> parent link to an image? If so, add the fancybox class and rel.
      $(this).closest('a')
        .filter(function(){
          return /(jpe?g|png|gif)$/i.test($(this).attr('href'));
        })
        .addClass('fancybox').attr('rel', 'gallery')
      ;
      // Does the image have a .fancybox class (is it an image link)?
      if ($(this).closest('a').hasClass('fancybox')) {
        if ($(this).hasClass('caption')) {
          // Get title (explicit caption, if exists)
          var title = $(this).attr('title');
          // and assign to alt for fancybox use.
          $(this).attr('alt', title);
        }
        // Set informative hover title for fancybox images.
        $(this).attr('title', 'Click to enlarge.');
      }
    }
  } else {
    $(this).attr('src', '/sites/all/themes/openpublish_theme/images/hijack.jpg')
  }
});

$('a.fancybox').each(function() {
  var $a = $(this);
  // Move the link to surround the img directly on inserted images for caption expander to function.
  // Cannot include in the function below - kills Fancybox - WTF?!
  $a.children('.image-caption-container, .image-caption-container-full-width').unwrap().find('img').wrap($a);
});

/* Fancybox, Version 1.3.4 (2010/11/11) http://fancybox.net. Version 2 requires jQuery 1.6 which I can't do.
 * Alternate way of calling fancybox() so I can use $(this) and use each anchor's decendent image's alt text.
 * http://stackoverflow.com/questions/11139067/access-this-inside-fancybox-options
*/
$('a.fancybox').each(function() {
  var $a = $(this);

  // For title and pager for Fancybox titleFormat setting.
  function formatTitle(title, currentArray, currentIndex, currentOpts) {
    if (title && title.length) {
      return '<div id="fancybox-title-over"><span style="display:block;line-height:1.4em;font-weight:bold;">' + title + '</span>' + (currentArray.length > 1 ? '<span style="display:block;padding-top:5px;">Image ' + (currentIndex + 1) + ' of ' + currentArray.length + '</span>' : '') + '</div>';
    }
    return (currentArray.length > 1 ? '<div id="fancybox-title-over">Image ' + (currentIndex + 1) + ' of ' + currentArray.length + '</div>' : '');
  }
  
  // Actual use of the fancybox() method.
  $a.fancybox({
    'onStart' : function() {
      // Use the image's alt instead of the default anchor's title.
      this.title = $a.find('img').attr('alt');
    },
    'titlePosition' : 'over',
    'titleFormat'		: formatTitle,
    'cyclic'  : true,
    'padding' : 5,
    'margin'  : 15,
    'onComplete'  : function() {
      $('#fancybox-content, #fancybox-left, #fancybox-right, #fancybox-title').hover(function() {
        $('#fancybox-title').show();
      }, function() {
        $('#fancybox-title').hide();
      });
    }
  });
});

// jQuery Expander Plugin - http://plugins.learningjquery.com/expander/
$('div.body-content span.main-image-credit, div.body-content span.caption').expander({
  slicePoint:       205,
  expandPrefix:     '... ',
  expandText:       'more »',
  beforeExpand: function() {
    $(this).find('span.details').css({'display' : 'inline'});
  },
  userCollapsePrefix: ' ',
  userCollapseText: '« less'
});

// Make sure floated .media_embed has div parent with overflow:hidden property for fieldset crowding.
// Going with 25px bottom margin on .media_embed because this stops floating.
//$('.body-content .media_embed').wrap('<div style="overflow:hidden"/>');

// One carriage return in plain text editors makes a break, resulting in commenters making bad spacing.
$('.comment .content p br').replaceWith('<span class="break"></span>');

// Only way I could fix spacing on topic hub slider when no image caption is present.
if (!$('.term-page-slideshow-credit').length) {
  $('div.views_slideshow_main').css({'margin-bottom' : '23px'});
}

// Highlight active exposed filters.
// Title
if (!!$('input#edit-title').attr('value')) {
  $('label[for="edit-title"]').css({'color' : '#46607B', 'font-style' : 'italic'});
}
// Date
if (!!$('.views-widget-filter-date_filter input').attr('value')) {
  $('.views-widget-filter-date_filter').children('label').css({'color' : '#46607B', 'font-style' : 'italic'});
}
// Type
if ($('.views-widget-filter-type .bef-checkboxes').find('input[checked]').length) {
  $('label[for="edit-type"]').css({'color' : '#46607B', 'font-style' : 'italic'});
  $('.views-widget-filter-type legend a:link, .views-widget-filter-type legend a:visited').css({'color' : '#46607B', 'font-style' : 'italic'});
}
// Taxonomy 1
if ($('.views-widget-filter-tid .bef-tree').find('input[checked]').length) {
  $('.views-widget-filter-tid legend a:link, .views-widget-filter-tid legend a:visited').css({'color' : '#46607B', 'font-style' : 'italic'});
}
// Taxonomy 2
if ($('.views-widget-filter-tid_1 .bef-tree').find('input[checked]').length) {
  $('.views-widget-filter-tid_1 legend a:link, .views-widget-filter-tid_1 legend a:visited').css({'color' : '#46607B', 'font-style' : 'italic'});
}
// Author
if ($('.views-widget-filter-field_op_author_nid .bef-tree').find('input[checked]').length) {
  $('.views-widget-filter-field_op_author_nid legend a:link, .views-widget-filter-field_op_author_nid legend a:visited').css({'color' : '#46607B', 'font-style' : 'italic'});
}
// Map
if (!$('.views-widget-filter-country .bef-checkboxes').find('input[checked]').length) {
  $('input#edit-province').attr('disabled', 'disabled');
} else {
  $('label[for="edit-country"]').css({'color' : '#46607B', 'font-style' : 'italic'});
}
// A nice way to check against both false and undefined is to use the double not trick.
// This is done instead of using .length because if .attr('value') is empty it returns undefined & breaks.
if (!!$('input#edit-province').attr('value')) {
  $('label[for="edit-province"]').css({'color' : '#46607B', 'font-style' : 'italic'});
}
if (!!$('input#edit-city').attr('value')) {
  $('label[for="edit-city"]').css({'color' : '#46607B', 'font-style' : 'italic'});
}

// Not needed with 2 below.
// Replace p parents of media with div
//$('#op-content p').find('iframe, object, script').each(function() {
//  $(this).unwrap().wrap('<div></div>');
//});

// Remove empty p tags.
$('#op-content p')
  .filter(function() {
    return $.trim($(this).text()) === ''
  })
  .remove()

// Hide media not inserted properly.
$('#op-content iframe, #op-content object, #op-content script').filter(':parents(.media_embed, .video-embed-code, .audio-embed-code, .flowplayer)').hide();

// Highlight footnotes with scroll effect.
$("sup > a").click(function(event) {
  var href = $(this).attr("href").substring(1);
  $(".ref-highlight").removeClass("ref-highlight");
  $('[name='+href+']').addClass("ref-highlight");
  $("html, body").animate({"scrollTop": $('[name='+href+']').offset().top}, 1000);
});

// Remove link styling from a anchors that don't link anywhere.
$('.body-content a:not([href])').addClass('link-to-nowhere');

// END
};