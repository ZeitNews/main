<?php
// $Id: node-audio.tpl.php,v 1.1.2.5 2010/04/16 01:52:18 inadarei Exp $
/**
 * @file
 * Template for audio content type.
 * 
 * Available variables:
 * - $body: Actual body content of the article.
 * - $audio_file: Embedded audio file player.
 * - $related_terms_links: Related taxonomy links.
 * 
 * @see openpublish_node_audio_preprocess()
 */
?>
<div class="section-date-author">
  <?php print t('Audio'); ?>
  <?php if ($authors): ?>
     | <?php print t('By'); ?> <?php print $authors; ?>
  <?php endif; ?>  
</div><!-- /.section-date-author -->
<div class="body-content">	

  <div class="clearfix">
  <?php  
    print $body; 
  ?>
  </div>
  <?php if ($audio_file): ?>
    <?php print $audio_file; ?>
  <?php endif; ?>
</div><!-- /.body-content -->

<?php print $related_terms_links; ?>