<?php
// $Id: node-op_image.tpl.php,v 1.1.2.4 2010/04/07 16:28:59 inadarei Exp $
/**
 * @file
 * Template for OP Image content type.
 * 
 * Available variables:
 * - $credit: the image credit.
 * - $main_image: The main image.
 * - $body: Body of the OP image node.
 * - $related_terms_links: Related taxonomy links.
 * 
 * @see openpublish_node_op_image_preprocess()
 */
?>
<div class="section-date-author"><?php print t('Image'); ?></div><!-- /.section-date-author -->
<?php if ($main_image): ?>
  <div class="main-image">
    <?php print $main_image; ?>

<?php if ($credit): ?>
  <div class= "main-image-credit image-credit image-desc"><?php print $credit; ?></div>
<?php endif; ?>
  </div><!-- /.main-image -->
<?php endif; ?>



<div class="body-content">
  <?php print $body; ?>
</div><!-- /.body-content -->
<?php print $related_terms_links; ?>