$Id: README.txt,v 1.2 2008/03/07 05:46:23 davidwhthomas Exp $
DESCRIPTION:
This module uses JQuery to add captions to images.
The image title attribute is used to create the image

EXAMPLE:
<img src="/files/example.jpg" title="example caption" class="caption" />
This will result in an image with the caption of 'example caption'

Important:
Only images with the class of 'caption' will be included in processing.
Therefore, you need to be able to add the class of 'caption' to your selected images for captioning to work.
If you are using a WYSIWYG editor like FCKEditor or TinyMCE, you should enable the 'styles' select box
and add ".caption{}" to the stylesheet used by your WYSIWYG editor and configured in it's settings page.
Alternatively, you will need to find a way to add the class of caption to your images for captioning.

INSTALL:
1. Copy the image_caption folder to your Drupal modules folder
2. Add the css definition: .caption{} to the stylesheet used by your WYWSIWYG editor,
   or perhaps to your theme style.css file.
3. Enable the Image Caption module in Drupal module administration.
4. After install, you can select the node types to include in image caption processing under
   Site Configuration > Image Caption

Personally, I use the TinyMCE 'advanced image' plugin to select the caption class and set the image title when creating content.
You could also use a similar function in FCKEditor or find a way to add class="caption" to the images that you wish to caption.
