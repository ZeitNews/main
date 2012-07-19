/**
 * @file: cloudmenu.js
 *
 * Contains cloudmenu specific function, which runs on page-load.
 */
Drupal.behaviors.cloudmenu = function(context) {
  var blocks = Drupal.settings.cloudmenu;
  for (var i = 0; i < blocks.length; i++) {
    // Vex the browser cache by adding a random number.
    var rnumber = Math.floor(Math.random()*9999999);
    // Param with value 9 indicates required version of flash player - see http://blog.deconcept.com/swfobject/
    var widget_so = new SWFObject(blocks[i].path_to_flash + '?r='+ rnumber, 'cumulusflash', blocks[i].width, blocks[i].height, 9, blocks[i].background);
    if (blocks[i].flash_transparency) {
      widget_so.addParam('wmode', 'transparent');
    }
    widget_so.addParam('allowScriptAccess', 'always');
    widget_so.addVariable('tcolor', blocks[i].color);
    widget_so.addVariable('tcolor2', blocks[i].color2);
    widget_so.addVariable('hicolor', blocks[i].hicolor);
    widget_so.addVariable('tspeed', blocks[i].speed);
    widget_so.addVariable('distr', blocks[i].distribute);
    widget_so.addVariable('mode', 'tags');
    widget_so.addVariable('tagcloud', blocks[i].tags_formatted_flash);
    widget_so.write('cloudmenu-'+ blocks[i].delta);
  }
}
