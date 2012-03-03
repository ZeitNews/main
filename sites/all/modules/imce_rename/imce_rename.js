//implementation of imce.hookOpSubmit
imce.renameOpSubmit = function(dop) {
  if (imce.fopValidate('rename')) {
    imce.fopLoading('rename', true);
    $.ajax($.extend(imce.fopSettings('rename'), {success: imce.renameResponse}));  
  }
};

//add hook.load
imce.hooks.load.push(function() {
  //set click function for rename tab to toggle crop UI
  imce.ops['rename'].func = imce.renamePrepare;
});

//populate the text box with the current file or dir name
imce.renamePrepare = function(response) {
  var i = 0;
  for (var fid in imce.selected) {
    $('#edit-new-name').val(unescape(imce.selected[fid].id));
    i++;
  }
  if (i == 0) {
    $('#edit-new-name').val(unescape(imce.conf.dir));
  }
  if (i > 1) {
    imce.setMessage(Drupal.t('Only one file can be renamed at a time.'), 'error');
    setTimeout(function() {$('#op-close-link').click();}, 5);
  }
  
  //hack to make renaming of directories possible
  if (imce.selcount == 0) {
    imce.selcount = 1;
    imce.selected['__IS_DIR__'] = '__IS_DIR__';
  }
};

//custom response. keep track of overwritten files.
imce.renameResponse = function(response) {
  imce.processResponse(response);
  imce.vars.cache = false;
  imce.navigate('.'); //should be folder parent and only trigger when a dir is renamed.
  $('#op-close-link').click(); //there is probably a better way to close the dialog than this.
};
