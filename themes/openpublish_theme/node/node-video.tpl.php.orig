<?php
// $Id: node-video.tpl.php,v 1.1.2.3 2010/04/16 01:52:18 inadarei Exp $
/**
 * @file
 * Template for article content type.
 * 
 * Available variables:
 * - $video_file: Video file (shown through embedded player).
 * - $body: Body of the video node.
 * - $related_terms_links: Related taxonomy links.
 * 
 * @see openpublish_node_video_preprocess()
 */
?>
<div class="section-date-author">
  <?php print t('Video'); ?> 
  <?php if ($authors): ?>
     | <?php print t('By'); ?> <?php print $authors; ?>
  <?php endif; ?>
</div><!-- /.section-date-author -->
<div class="body-content">
<?php if ($video_file): ?>
  <?php print $video_file; ?>
<?php endif; ?>

<?php print $node_body; ?>

</div><!-- /.body-content -->
<?php print $related_terms_links; ?>