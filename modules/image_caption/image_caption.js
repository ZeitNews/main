/*$Id: image_caption.js,v 1.2.2.3 2010/02/03 07:50:25 davidwhthomas Exp $*/
$(document).ready(function(){
  $("img.caption").each(function(i) {
    var imgwidth = $(this).width();
    var imgheight = $(this).height();
    var captiontext = $(this).attr('title');
    var style = $(this).attr('style');
    var alignment = $(this).attr('align');
    //Clear image styles to prevent conflicts with parent div
    $(this).attr({align:""});
    $(this).attr({style:""});
    $(this).wrap("<span class=\"image-caption-container\" style=\"display:block;" + style + "; float: " + alignment + "\"></span>");
    $(this).parent().addClass('image-caption-container-' + alignment);
    if(imgwidth != 'undefined' && imgwidth != 0){
      $(this).parent().width(imgwidth);
    }
    $(this).parent().append("<span style=\"display:block;\" class=\"image-caption\">" + captiontext + "</span>");
  });
});