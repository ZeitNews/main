<?php

/**
 * @file
 * Template for slideshow content type.
 * 
 * Available variables:
 * - $field_op_slideshow_images: nodereferences to op_images; uses view image_gallery_images to display.
 * - $related_terms_links: Related taxonomy links.
 * 
 * @see openpublish_node_slideshow_preprocess()
 */
?>
<div class="section-date-author"><?php print t('Slideshow'); ?> 
<?php if ($authors): ?>
   | <?php print t('By'); ?> <?php print $authors; ?>
<?php endif; ?>
</div><!-- /.section-date-author -->

<div id="image-gallery-slideshow">
<?php
  if (is_array($field_op_slideshow_images) && $field_op_slideshow_images[0]['view']) {
  
    $images_nids = array();
    foreach($field_op_slideshow_images as $image) {
      $images_nids[] = $image['nid'];  
    }
     
     print views_embed_view('image_gallery_images', 'block_1', implode(',', $images_nids));     
  }
?>
</div>
  
<?php print $related_terms_links; ?>


