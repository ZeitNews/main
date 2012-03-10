Drupal.behaviors.openpublish_menu = function(c) {
  if ($.browser.msie && $.browser.version=="6.0") {
    addOver = function(id) {
      var sfEls = document.getElementById(id).getElementsByTagName("li");
      for (var i=0; i<sfEls.length; i++) {
        sfEls[i].onmouseover=function() {
          this.className+=" over";
        }
        sfEls[i].onmouseout=function() {
          this.className=this.className.replace(new RegExp(" over\\b"), "");
        }
      }
    }
    addOver("nav");
  }
}