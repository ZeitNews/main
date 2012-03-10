Drupal collapsiblock.module README.txt
==============================================================================

Makes blocks collapsible.


Requirements
------------------------------------------------------------------------------
This module is written for Drupal 5.0 and requires the jstools.module to be
enabled.


Theme Support
------------------------------------------------------------------------------

Collapsiblock needs to know the page element in which  block container, block 
titles (subjects) and block contents are enclosed, something that varies by 
theme.

Collapsiblock tries to support out-of-the-box the majority of theme by using
flexible jQuery selector. But for some themes it might not work.

If Collapsiblock doesn't work, go to the /admin/build/themes/settings.
You can set here your own jQuery selector for the different elements in blocks.

To determine this, look in the theme for the place where blocks are generated.
For PHPTemplate-based themes, look for a block.tpl.php file.

Identify the line in the template or theme file where block titles are
generated and other element, and look for the enclosing elements.

For example, in garland's block.tpl.php, the relevant line for the title is:

  <h2><?php print $block->subject ?></h2>

In this case, the jQuery selector will be 'h2'.
