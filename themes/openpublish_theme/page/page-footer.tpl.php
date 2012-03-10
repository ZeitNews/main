<?php
// $Id: page-footer.tpl.php,v 1.1.2.2 2010/07/22 22:01:38 tirdadc Exp $
/**
 * @file page-footer.tpl.php
 * Footer template.
 *
 * For the list of available variables, please see: page.tpl.php
 *
 * @ingroup page
 */
?>

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
</html>
