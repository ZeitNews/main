<?php
// $Id: node-package.tpl.php,v 1.1.2.3 2010/04/12 04:38:02 inadarei Exp $
/**
 * @file
 *  Template for package content type.
 * 
 * Available Variables:
 * - $left_intro: Left column intro.
 * - $left_related_items: Array of left column items.
 *   - $left_related: Left column - Individual item (object).
 *   - $left_related->image: Left column - Individual item's image.
 *   - $left_related->title: Left column - Individual item's title.
 *   - $left_related->teaser: Left column - Individual item's teaser.
 * 
 * - $center_intro: Center column intro.
 * - $center_related_items: Array of center column items.
 *   - $center_related: Center column - Individual item (object).
 *   - $center_related->image: Center column - Individual item's image.
 *   - $center_related->title: Center column - Individual item's title.
 *   - $center_related->teaser: Center column - Individual item's teaser.
 *
 * - $right_intro: Right column intro.
 * - $right_related_items: Array of right column items.
 *   - $right_related: Right column - Individual item (object).
 *   - $right_related->image: Right column - Individual item's image.
 *   - $right_related->title: Right column - Individual item's title.
 *   - $right_related->teaser: Right column - Individual item's teaser.
 * 
 * @see openpublish_node_package_preprocess()
 */
?>
<div class="news-package">
  <div id="news-package-left">
    <?php print $left_intro; ?>
    <?php if ($left_related_items): ?>
      <?php foreach ($left_related_items as $left_related): ?>
        <div class="news-package-left-related">
          <?php if ($left_related->image): ?>
            <?php print $left_related->image; ?>
          <?php endif; ?>
  	      <div class="package-related-article-title"><?php print $left_related->title; ?></div><!-- /.package-related-article-title -->
	        <div class="package-related-article-teaser"><?php print $left_related->teaser; ?></div><!-- /.package-related-article-teaser -->
	      </div><!-- /.news-package-left-related -->
  	  <?php endforeach; ?>
    <?php endif; ?>
  </div><!-- /.news-package-left -->
  
  <div id="news-package-center">
    <?php print $center_intro; ?>
	  <?php if ($center_content): ?>
	    <?php print $center_content; ?>
	  <?php endif; ?>
	<br/>
	<?php if ($center_related_items): ?>
	  <?php foreach($center_related_items as $center_related): ?>
      <div class="news-package-center-related">
  		  <?php if ($center_related->image): ?>
  		    <?php print $center_related->image; ?>
  		  <?php endif; ?>
	      <div class="package-related-article-title"><?php print $center_related->title; ?></div><!-- /.package-related-article-title -->
	      <div class="package-related-article-teaser"><?php print $center_related->teaser; ?></div><!-- /.package-related-article-teaser -->
	    </div><!-- /.news-package-center-related -->
  	<?php endforeach; ?>
  <?php endif; ?>
  </div><!-- /.news-package-center -->
  
  <div id="news-package-right">
    <?php print $right_intro; ?>
    <?php if ($right_related_items): ?>
      <?php foreach($right_related_items as $right_related): ?>
        <div class="news-package-right-related">
          <?php if ($right_related->image): ?>
            <?php print $right_related->image; ?>
          <?php endif; ?>
          <div class="package-related-article-title"><?php print $right_related->title; ?></div><!-- /.package-related-article-title -->
          <div class="package-related-article-teaser"><?php print $right_related->teaser; ?></div><!-- /.package-related-article-teaser -->
        </div><!-- /.news-package-right-related -->
      <?php endforeach; ?>
    <?php endif; ?>
  </div><!-- /.news-package-right -->
  
</div>