<?php
// $Id: views-view-row-rss.tpl.php,v 1.1 2008/12/02 22:17:42 merlinofchaos Exp $
/**
 * @file views-view-row-rss.tpl.php
 * Default view template to display a item in an RSS feed.
 *
 * @ingroup views_templates
 */
?>
  <?php //dsm($variables); //dsm(array_keys(get_defined_vars())); ?>
  <item>
    <title><?php print $title; ?></title>
    <link><?php print $link; ?></link>
    <description><![CDATA[
      <?php print $node_teaser_image; ?>
      
      <?php if ($node_deck): ?>
        <h4><?php print $node_deck; ?></h4>
      <?php endif; ?>
      
      <?php if ($node_type): ?>
        <h5>:: <?php print $node_type; ?> ::</h5>
      <?php endif; ?>
      
      <?php if ($event_date): ?>
        <sub><strong>Event Date:</strong> <?php print $event_date; ?></sub>
      <?php endif; ?>
      
      <p><?php print $node_teaser; ?></p>

      <?php //$row->readmore = FALSE; ?>
    ]]></description>
    <?php if ($author_check): ?>
      <?php print $item_elements; ?>
    <?php else: ?>
      <?php print preg_replace('/<dc:creator>.*<\/dc:creator>/', '<dc:creator></dc:creator>', $item_elements); ?>
    <?php endif; ?>
  </item>