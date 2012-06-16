<?php
// $Id: node-event.tpl.php,v 1.1.2.5 2010/04/14 21:47:06 inadarei Exp $
/**
 * @file
 * Template for event content type.
 * 
 * Available variables:
 * - $main_image: The article's main image.
 * - $main_image_desc: The main image's description.
 * - $main_image_credit: The main image's credit.
 * - $event_date: The event's date(s).
 * - $event_date_raw: The event's date(s) as an unformatted array (equivalent to $field_event_date).
 * - $node_body: Event's body content.
 * - $related_terms_links: Related taxonomy links.
 * 
 * @see openpublish_node_event_preprocess()
 */
?>

<div class="event-date">
  <strong><?php print t('Event Date:'); ?> </strong><?php print $event_date; ?>
</div><!-- /.event-date -->

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