DV.Schema.events.ViewText = {
  next: function(e){
    var nextPage = this.models.document.nextPage();
    this.loadText(nextPage);
    
    this.viewer.history.save('text/p'+(nextPage+1));
  },
  previous: function(e){
    var previousPage = this.models.document.previousPage();
    this.loadText(previousPage);

    this.viewer.history.save('text/p'+(previousPage+1));

  },
  search: function(e){
    e.preventDefault();
    this.viewer.open('ViewSearch');

    return false;
  }
};