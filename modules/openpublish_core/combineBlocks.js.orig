Drupal.behaviors.combineBlocks = function(c) {
  for (i in Drupal.settings.combineBlocks) {
    blocks = Drupal.settings.combineBlocks[i];
    process = 1;
    for(bi in blocks) {
      if ($(blocks[bi]).size() < 1) {
      process = 0;
      }
    }
    if (process) {
      id = 'combinedblock';
      $(blocks[0]).before("<div id='"+ id +"'><div class = 'combined-header'></div><div class='combined-content'></div></div>");
      start = $(blocks[0]).find('h3');
      cont = $('#' + id);
      for (id in blocks) {
        block = $(blocks[id])
        $(block).find('h3').attr("content", $(block).attr('id'));
        cont.find('.combined-content').append($(block));

      }
      cont.find('h3').each(function () {
        $(".combined-header").append($(this));
        width = (cont.find('.combined-content').width()-4)/2;
        $(this).css("width", width);
        $(this).click(function () {
          $(this).trigger('open');
        });
        $(this).bind('open',function () {
          content = $('#' + $(this).attr("content"));
          content.css("display", "block");
          $(this).addClass('current');
          $(this).siblings().trigger('close');
        });
        $(this).bind('close',function () {
          content = $('#' + $(this).attr("content"));
          content.css("display", "none");
          $(this).removeClass('current');
        });
      });
     start.trigger('open');
   }
  }
}

