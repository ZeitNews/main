_.extend(DV.Schema.events, {
  handleNavigation: function(e){
    var el          = this.viewer.$(e.target);
    var parentEl    = el.parent();

    if(el.hasClass('DV-trigger') || parentEl.hasClass('DV-trigger')){

      if(el.hasClass('DV-expander')){
        return parentEl.parent().toggleClass('DV-expanded');

      }else if(parentEl.hasClass('DV-first')){
        // its a header, take it to the page
        parentEl.parent().addClass('DV-expanded');
        var cid           = parseInt(parentEl.parent()[0].id.replace('DV-chapter-',''), 10);
        var chapterIndex  = parseInt(this.models.chapters.getChapterPosition(cid),10);
        var pageNumber    = parseInt(chapterIndex,10)+1;

        if(this.viewer.state === 'ViewText'){
          this.loadText(chapterIndex);
          this.viewer.history.save('text/p'+pageNumber);
        }else if(this.viewer.state === 'ViewDocument'){
          this.helpers.jump(chapterIndex);
          this.viewer.history.save('document/p'+pageNumber);
        }else{
          return false;
        }

      }else if(parentEl[0].tagName.toUpperCase() === 'DIV'){
        var aid         = parentEl[0].id.replace('DV-annotationMarker-','');
        var annotation  = this.models.annotations.getAnnotation(aid);
        var pageNumber  = parseInt(annotation.index,10)+1;

        if(this.viewer.state === 'ViewText'){
          this.loadText(annotation.index);

          this.viewer.history.save('text/p'+pageNumber);
        }else{
          this.viewer.pageSet.showAnnotation(annotation);
        }

      }else{
        return false;
      }
    }
  }
});