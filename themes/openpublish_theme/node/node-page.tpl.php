<?php
/**
 * @file
 * Template for page content type.
 * 
 * Available variables:
 * - $node_body: Resource's body content.
 * - $authors:: List of authors.
 * - $resource_links: Array of resource links.
 *   - $link: each resource link contained in $resource_links.
 * - $related_terms_links: Related taxonomy links.
 * 
 * @see openpublish_node_page_preprocess()
 */
//dsm($variables);
?>
<div class="body-content">
  <?php if ($main_image): ?>
    <div class="main-image">
      <?php print $main_image; ?>
      <div class="main-image-desc image-desc">
        <?php print $main_image_desc; ?> <span class="main-image-credit image-credit"><?php print $main_image_credit; ?></span>
      </div>
    </div><!-- /.main-image -->
  <?php endif; ?>
  
  <?php print $body; ?>
</div><!-- /.body-content -->