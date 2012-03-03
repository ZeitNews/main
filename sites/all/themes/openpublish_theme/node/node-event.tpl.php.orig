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
<div class="body-content">

<div class="event-date">
  <strong><?php print t('Event Dates:'); ?> </strong><?php print $event_date; ?>
</div><!-- /.event-date -->

<?php if ($main_image): ?>
    <div class="main-image">
      <?php print $main_image; ?>
      <div class="main-image-desc image-desc">
        <?php print $main_image_desc; ?> <span class="main-image-credit image-credit"><?php print $main_image_credit; ?></span>
      </div>
    </div><!-- /.main-image -->
<?php endif; ?>

<?php print $node_body; ?>
</div>
<?php print $related_terms_links; ?>