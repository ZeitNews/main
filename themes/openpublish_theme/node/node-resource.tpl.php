<?php
// $Id: node-resource.tpl.php,v 1.1.2.4 2011/01/27 22:04:16 inadarei Exp $
/**
 * @file
 * Template for resource content type.
 * 
 * Available variables:
 * - $node_body: Resource's body content.
 * - $authors:: List of authors.
 * - $resource_links: Array of resource links.
 *   - $link: each resource link contained in $resource_links.
 * - $related_terms_links: Related taxonomy links.
 * 
 * @see openpublish_node_resource_preprocess()
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
  <?php print $related_terms_links; ?>
</div><!-- /.body-content -->

<?php if ($links && $comment_count == 0 && arg(0) != 'comment'): ?>
  <div class="links">
      <?php print $add_new_comment; ?>
  </div>
<?php endif; ?>