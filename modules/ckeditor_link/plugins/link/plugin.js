// $Id: plugin.js,v 1.7 2010/09/01 11:30:43 anrikun Exp $

/**
 * @file
 * Written by Henri MEDOT <henri.medot[AT]absyx[DOT]fr>
 * http://www.absyx.fr
 *
 * Portions of code:
 * Copyright (c) 2003-2010, CKSource - Frederico Knabben. All rights reserved.
 * For licensing, see LICENSE.html or http://ckeditor.com/license
 */

(function() {

  // Get a CKEDITOR.dialog.contentDefinition object by its ID.
  var getById = function(array, id, recurse) {
    for (var i = 0, item; (item = array[i]); i++) {
      if (item.id == id) return item;
      if (recurse && item[recurse]) {
        var retval = getById(item[recurse], id, recurse);
        if (retval) return retval;
      }
    }
    return null;
  };

  var initAutocomplete = function(input, uri) {
    input.setAttribute('autocomplete', 'OFF');
    new Drupal.jsAC(input, new Drupal.ACDB(uri));
  };

  var extractPath = function(value) {
    value = CKEDITOR.tools.trim(value);
    var match;
    match = /\(([^\(]*?)\)$/i.exec(value);
    if (match && match[1]) {
      value = match[1];
    }
    var basePath = Drupal.settings.basePath;
    if (value.indexOf(basePath) == 0) {
      value = value.substr(basePath.length);
    }
    if (/^node\/\d+$/.test(value)) {
      return value;
    }
    return false;
  };

  CKEDITOR.plugins.add('drupal_path', {

    init: function(editor, pluginPath) {
      CKEDITOR.on('dialogDefinition', function(e) {
        if ((e.editor != editor) || (e.data.name != 'link')) return;

        // Overrides definition.
        var definition = e.data.definition;
        definition.onFocus = CKEDITOR.tools.override(definition.onFocus, function(original) {
          return function() {
            original.call(this);
            if (this.getValueOf('info', 'linkType') == 'drupal') {
              this.getContentElement('info', 'drupal_path').select();
            }
          };
        });

        // Overrides linkType definition.
        var infoTab = definition.getContents('info');
        var content = getById(infoTab.elements, 'linkType');
        content.items.unshift(['Drupal', 'drupal']);
        content['default'] = 'drupal';
        infoTab.elements.push({
          type: 'vbox',
          id: 'drupalOptions',
          children: [{
            type: 'text',
            id: 'drupal_path',
            label: editor.lang.link.title,
            required: true,
            onLoad: function() {
              this.getInputElement().addClass('form-autocomplete');
              initAutocomplete(this.getInputElement().$, Drupal.settings.ckeditor_link.autocomplete_path);
            },
            setup: function(data) {
              this.setValue(data.drupal_path || '');
            },
            validate: function() {
              var dialog = this.getDialog();
              if (dialog.getValueOf('info', 'linkType') != 'drupal') {
                return true;
              }
              var func = CKEDITOR.dialog.validate.notEmpty(editor.lang.link.noUrl);
              if (!func.apply(this)) {
                return false;
              }
              if (!extractPath(this.getValue())) {
                alert(Drupal.settings.ckeditor_link.msg_invalid_path);
                this.focus();
                return false;
              }
              return true;
            }
          }]
        });
        content.onChange = CKEDITOR.tools.override(content.onChange, function(original) {
          return function() {
            original.call(this);
            var dialog = this.getDialog();
            var element = dialog.getContentElement('info', 'drupalOptions').getElement().getParent().getParent();
            if (this.getValue() == 'drupal') {
              element.show();
              if (editor.config.linkShowTargetTab) {
                dialog.showPage('target');
              }
              var uploadTab = dialog.definition.getContents('upload');
              if (uploadTab && !uploadTab.hidden) {
                dialog.hidePage('upload');
              }
            }
            else {
              element.hide();
            }
          };
        });
        content.setup = function(data) {
          if (!data.type || (data.type == 'url') && !data.url) {
            data.type = 'drupal';
          }
          else if (data.url && !data.url.protocol && data.url.url) {
            var path = extractPath(data.url.url);
            if (path) {
              data.type = 'drupal';
              data.drupal_path = path;
              delete data.url;
            }
          }
          this.setValue(data.type);
        };
        content.commit = function(data) {
          data.type = this.getValue();
          if (data.type == 'drupal') {
            data.type = 'url';
            var dialog = this.getDialog();
            dialog.setValueOf('info', 'protocol', '');
            dialog.setValueOf('info', 'url', Drupal.settings.basePath + extractPath(dialog.getValueOf('info', 'drupal_path')));
          }
        };
      });
    }
  });
})();