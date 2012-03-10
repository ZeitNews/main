jQuery("document").ready(function(){
  var id = Drupal.settings.document_cloud.id;
  var height = Drupal.settings.document_cloud.height;
  var width = Drupal.settings.document_cloud.width;
  
  if(!height){
    var height = '100%';
    if(document.getElementById('viewer').parentNode.clientHeight < 200){
      height = '600px';
    }     
  }  
  if(!width){
    var width = '100%';
    document.getElementById('viewer').style.width = width;
  }
  
  DV.load("http://www.documentcloud.org/documents/"+id+".js", {
    sidebar: false,
    container: "#viewer",
    height : height,
    width : width
  });
});
        