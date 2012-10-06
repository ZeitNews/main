<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html 
     xmlns="http://www.w3.org/1999/xhtml"      
     xmlns:dc="http://purl.org/dc/terms/" 
     xmlns:dcmitype="http://purl.org/dc/terms/DCMIType/"
     xmlns:ctag="http://commontag.org/ns#"
     xmlns:foaf="http://xmlns.com/foaf/0.1/"      
     xmlns:v="http://rdf.data-vocabulary.org/#"
     xmlns:fb="http://ogp.me/ns/fb#"
     lang="<?php print $language->language; ?>" 
     dir="<?php print $language->dir; ?>"
     version="XHTML+RDFa 1.0" >
<head>
  <title><?php print $head_title ?></title>
  <?php print $op_head; ?>
  <?php // Added <base> for curl page asset downloading (for crawling (varnish)). ?>
  <?php // <base href="<?php print $GLOBALS['base_root'];" /> ?>
  <?php print $styles ?>
  <?php print $scripts ?>
  <!--[if lte IE 7]><?php print openpublish_get_ie_styles(); ?><![endif]-->
  <!--[if IE 8]>
    <link type="text/css" rel="stylesheet" media="all" href="<?php print $base_path . $directory; ?>/css/ie8.css" />
  <![endif]-->
  <!--[if IE 9]>
    <link type="text/css" rel="stylesheet" media="all" href="<?php print $base_path . $directory; ?>/css/ie9.css" />
  <![endif]-->
</head>

<body <?php print openpublish_body_classes($left, $right, $body_classes); ?> >
  <?php if (!empty($admin)) print $admin; ?>
  <div id="outer-wrapper"> 
  <div id="wrapper">    	
  <div id="header">
    <?php print $header; ?>   
    <div class="clear"></div>
  </div> <!-- /#header -->
  
  <?php if (menu_tree('menu-top-menu')): ?>
    <div id="top-menu" class="clearfix">
      <ul id="login-menu">
        <?php if (user_is_logged_in()) : ?>
          <li class="hello"><?php print t('Hello'); ?> <?php print l($GLOBALS['user']->name, 'user') ?>!</li>
          <li><?php print l(t('Log Out'), 'logout'); ?></li>
        <?php else : ?>
          <li class="hello"><?php print t('Hello Visitor!'); ?></li>
          <li><?php print l(t('Log In'), 'user/login', array('query' => drupal_get_destination())) ?> <?php print t('or'); ?> <?php print l(t('Register'),'user/register', array('query' => drupal_get_destination())); ?></li>
        <?php endif; ?>
      </ul>
      <div id="top-menu-region">
        <?php print $top_menu; ?>
        <?php print menu_tree('menu-top-menu'); ?>
      </div>
    </div>
  <?php endif; ?>		

  <div id="logo-area" class="clearfix">	    
    <div id="logo"><a href="<?php print check_url($front_page); ?>" title="<?php print check_plain($site_name); ?>"><img src="<?php print check_url($logo); ?>" alt="<?php print check_plain($site_name); ?>" width="341" height="79" /></a>
    </div><!--/ #logo -->
    <div id="search_box_top" class="clearfix">
      <?php if ($search_box): ?><?php print $search_box; ?><?php endif; ?>
    </div>

  </div><!-- #logo-area -->        

  <div id="nav" class="clearfix">
    <?php if (isset($expanded_primary_links)): ?>
      <?php print theme('openpublish_menu', $expanded_primary_links); ?>
    <?php else: ?> 
      <?php if (isset($primary_links)) : ?>
        <?php print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
      <?php endif; ?>
      <?php if (isset($secondary_links)) : ?>
        <?php print theme('links', $secondary_links, array('class' => 'links secondary-links')) ?>
      <?php endif; ?>
    <?php endif; ?>      
  </div> <!-- /#nav -->
  <div class="clear"></div>	
  <div id="container" class="clearfix">
  <?php //dsm($variables); ?>
  
<!-- #End from page-header.tpl.php -->  

<?php print $page_header; ?>

<?php if ($left): ?>
  <div id="sidebar-left" class="sidebar">
  	<?php print $left ?>
  </div> <!-- /#sidebar-left -->
<?php endif; ?>

<div id="center" class="clearfix">
  <?php if ($show_messages && $messages): print $messages; endif; ?>
  <?php print $help; ?>
  
  <?php print $breadcrumb; ?><?php //print $my_variable; ?>

  <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
  
  <?php //if ($node->links['addtoany']): ?>
    <?php //print '<div id="add-this" class="float-right clearfix"><div class="a2a_kit a2a_default_style"><a class="a2a_button_twitter_tweet"></a><a class="a2a_button_google_plusone"></a><a class="a2a_button_facebook_like"></a></div>' . $node->links['addtoany']['title'] . '</div>'; ?>
  <?php //endif; ?>
  
    <?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
      <?php if ($title && $node->type != 'topichub'): ?>
				<?php if (arg(0) == 'taxonomy'): ?>
					<h1 property="dc:title" class="taxonomy-heading"><?php print $title; ?></h1>
				<?php else : ?>
					<h1 property="dc:title"><?php print $title; ?></h1>
				<?php endif; ?>
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
        
<?php print $page_footer; ?>

<!-- #End from page.tpl.php -->  

      </div> <!-- /#container -->
      <span class="clear"></span>
    </div> <!-- /#wrapper -->
 
        <div class="clear"></div>	
         	
        <div id="footer" class="clearfix clear">
        <div id="footer-links-wrapper">
          <div id="footer-menu-primary"><?php print menu_tree('menu-footer-primary'); ?></div>
					<div id="footer-feed-icon"><a href="<?php print url('rss-full.xml'); ?>" title="<?php print t('Subscribe to the main RSS feed (full text).'); ?>"><span class="socialite-icons-16" style="background-position: 0 0;">&nbsp;</span></a></div>
          <div id="footer-menu-secondary"><?php print menu_tree('menu-footer-secondary'); ?></div>
        </div><!--/footer-links-wrapper-->
          
          <?php print $footer_message . $footer ?>          
        </div> <!-- /#footer -->
 
  </div> <!-- /#outer-wrapper -->
  <!-- /layout -->
  <?php print $closure ?>
</body>

<!-- #End from page-footer.tpl.php -->
</html>  