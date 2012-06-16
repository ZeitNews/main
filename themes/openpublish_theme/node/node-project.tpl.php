<?php
/**
 * @file
 * Template for project content type.
 * 
 * Available variables:
 * - $node_body: Resource's body content.
 * - $authors:: List of authors.
 * - $resource_links: Array of resource links.
 *   - $link: each resource link contained in $resource_links.
 * - $related_terms_links: Related taxonomy links.
 * 
 * @see openpublish_node_project_preprocess()
 */
//dsm($variables);
?>
<?php if ($node->links['addtoany']): ?>
  <?php print 
  '<div id="add-this" class="float-left clearfix">'
  . $node->links['addtoany']['title'] .
  '<a id="comment-button" href="/comment/reply/'. $node->nid .'#comment-form" title="Add new comment.">Comment</a><span id="comment-arrow"></span><a id="comment-count" href="#comments" title="Read comments.">'. $node->comment_count .'</a>
  <div class="a2a_kit a2a_default_style">
    <a class="a2a_button_twitter_tweet"></a>
    <a class="a2a_button_google_plusone"></a>
    <a class="a2a_button_facebook_like"></a>
  </div>
  </div>';
  ?>
<?php endif; ?>

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