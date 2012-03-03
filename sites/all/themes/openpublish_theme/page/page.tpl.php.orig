<?php
// $Id: page.tpl.php,v 1.1.2.11 2010/10/20 18:32:12 tirdadc Exp $
 
 /**
  * @file page.tpl.php
  *
  * Main generic page template.
  * @ingroup page
  *
  * Available variables:
  *
  * General utility variables:
  * - $base_path: The base URL path of the Drupal installation. At the very
  *   least, this will always default to /.
  * - $css: An array of CSS files for the current page.
  * - $directory: The directory the theme is located in, e.g. themes/garland or
  *   themes/garland/minelli.
  * - $is_front: TRUE if the current page is the front page. Used to toggle the mission statement.
  * - $logged_in: TRUE if the user is registered and signed in.
  * - $is_admin: TRUE if the user has permission to access administration pages.
  *
  * Page metadata:
  * - $language: (object) The language the site is being displayed in.
  *   $language->language contains its textual representation.
  *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
  * - $head_title: A modified version of the page title, for use in the TITLE tag.
  * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
  *   so on).
  * - $styles: Style tags necessary to import all CSS files for the page.
  * - $scripts: Script tags necessary to load the JavaScript files and settings
  *   for the page.
  * - $body_classes: A set of CSS classes for the BODY tag. This contains flags
  *   indicating the current layout (multiple columns, single column), the current
  *   path, whether the user is logged in, and so on.
  *
  * Site identity:
  * - $front_page: The URL of the front page. Use this instead of $base_path,
  *   when linking to the front page. This includes the language domain or prefix.
  * - $logo: The path to the logo image, as defined in theme configuration.
  * - $site_name: The name of the site, empty when display has been disabled
  *   in theme settings.
  * - $site_slogan: The slogan of the site, empty when display has been disabled
  *   in theme settings.
  * - $mission: The text of the site mission, empty when display has been disabled
  *   in theme settings.
  *
  * Navigation:
  * - $search_box: HTML to display the search box, empty if search has been disabled.
  * - $primary_links (array): An array containing primary navigation links for the
  *   site, if they have been configured.
  * - $secondary_links (array): An array containing secondary navigation links for
  *   the site, if they have been configured.
  *
  * Page content (in order of occurrance in the default page.tpl.php):
  * - $left: The HTML for the left sidebar.
  *
  * - $breadcrumb: The breadcrumb trail for the current page.
  * - $title: The page title, for use in the actual HTML content.
  * - $help: Dynamic help text, mostly for admin pages.
  * - $messages: HTML for status and error messages. Should be displayed prominently.
  * - $tabs: Tabs linking to any sub-pages beneath the current page (e.g., the view
  *   and edit tabs when displaying a node).
  *
  * - $content: The main content of the current Drupal page.
  *
  * - $right: The HTML for the right sidebar.
  *
  * Footer/closing data:
  * - $feed_icons: A string of all feed icons for the current page.
  * - $footer_message: The footer message as defined in the admin settings.
  * - $footer : The footer region.
  * - $closure: Final closing markup from any modules that have altered the page.
  *   This variable should always be output last, after all other dynamic content.
  *
  * @see template_preprocess()
  * @see template_preprocess_page()
  */
 ?>

<?php print $page_header; ?>

<?php if ($left): ?>
  <div id="sidebar-left" class="sidebar">
  	<?php print $left ?>
  </div> <!-- /#sidebar-left -->
<?php endif; ?>

<div id="center" class="clearfix">
  <?php print $breadcrumb; ?>

  <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
  
    <?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
      <?php if ($title && $node->type != 'topichub'): ?>
      	<div id="add-this" class="float-right clearfix">
          <?php print openpublish_addthis_widget($head_title); ?>
      	</div>
        <h1 property="dc:title"><?php print $title; ?></h1>
      <?php endif; ?>
      
      <?php if ($tabs): ?>
      <div id="drupal-control-bar">      
      <?php endif; ?>
        <?php if ($tabs): print '<ul>' . $tabs . '</ul>'; endif; ?>    
        <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
      <?php if ($tabs): ?>        
      </div><!--/ #drupal-control-bar -->
      <?php endif; ?>
      
    
    <?php if ($tabs): print '</div><!--/ #tabs-wrapper -->'; endif; ?>    

  
  <?php if ($show_messages && $messages): print $messages; endif; ?>
  <?php print $help; ?>
  
  <div id="op-over-content">
    <?php print $over_content; ?>    
  </div>
  
  <div id="op-content" typeof="dcmitype:Text">
    <?php print $content ?>
  </div>
  
  <div id="op-under-content">
    <?php print $under_content ?>  
  </div>
  
</div> <!-- /#center -->

<?php if ($right): ?>
  <div id="sidebar-right" class="sidebar">
  	<?php print $right ?>
  </div> <!-- /#sidebar-right -->
<?php endif; ?>
        
<?php print $page_footer;
