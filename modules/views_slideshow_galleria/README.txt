
============================
 Views Slideshow: Galleria
============================

Integrating Galleria with Views Slideshow.

This module will display a view of images using the Galleria jQuery plugin
available from http://galleria.aino.se/.

Galleria
— A JavaScript gallery for the Fastidious

Galleria is a JavaScript image gallery unlike anything else. It can take a
simple list of images and turn it into a foundation of multiple intelligent
gallery designs, suitable for any project.

==============
 Installation
==============

1. Extract the contents of the project into your modules directory, probably at
   /sites/all/modules/views_slideshow_galleria.
2. Also install Views and Views Slideshow (available from
   http://drupal.org/project/views and http://drupal.org/project/views_slideshow
   respectively).
3. Download the Galleria jQuery plugin from
   http://github.com/aino/galleria/archives/master.
4. Extract the contents of that archive into /sites/all/libraries.
   You may optionally install that to another folder, but will need to then
   specify the new location at /admin/build/views/views_slideshow_galleria.
5. Create a new View with images, using 'Slideshow' for the 'Style', and
   'Galleria' for the 'Slideshow mode' when configuring the style.
