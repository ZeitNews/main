DV.model.Chapters = function(viewer) {
  this.viewer = viewer;
  this.loadChapters();
};

DV.model.Chapters.prototype = {

  // Load (or reload) the chapter model from the schema's defined sections.
  loadChapters : function() {
    var chapters = this.chapters = this.viewer.schema.data.chapters = [];
    _.each(this.viewer.schema.data.sections, function(sec) {
      sec.id    = sec.id || _.uniqueId();
      var range = sec.pages.split('-');
      var start = parseInt(range[0], 10);
      var end   = parseInt(range[0], 10);
      for (var i=range[0]-1; i<range[1]; i++) chapters[i] = sec.id;
    });
  },

  getChapterId: function(_index){
    return this.chapters[_index];
  },

  getChapterPosition: function(chapterId){
    for(var i = 0,len=this.chapters.length; i < len; i++){
      if(this.chapters[i] === chapterId){
        return i;
      }
    }
  }
};
