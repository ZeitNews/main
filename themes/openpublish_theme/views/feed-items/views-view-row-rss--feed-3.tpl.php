<?php
// $Id: views-view-row-rss.tpl.php,v 1.1 2008/12/02 22:17:42 merlinofchaos Exp $
/**
 * @file views-view-row-rss.tpl.php
 * Default view template to display a item in an RSS feed.
 *
 * @ingroup views_templates
 */
?>
<?php //print $out; //dsm(array_keys(get_defined_vars())); //dsm($row); ?>
<item>
  <title><?php print $title; ?></title>
  <link><?php print $link; ?></link>
  <description><![CDATA[
    <?php if ($node_deck): ?>
      <h4><?php print $node_deck; ?></h4>
    <?php endif; ?>
    
    <h5>:: <?php print $node_type; ?> <?php print $authors ? 'by ' . $authors : ''; ?> <?php print $categories ? 'in ' . $categories : ''; ?> ::</h5>
  
    <?php if ($event_date): ?>
      <sub><strong>Event Date:</strong> <?php print $event_date; ?></sub>
    <?php endif; ?>
    
    <?php if ($video_code): ?>
      <div><?php print $video_code; ?></div>
      <sub>Embedded media is only viewable in RSS if your reader supports it.</sub>
    <?php endif; ?>
    
    <?php if ($audio_mp3): ?>
      <sub><?php print $audio_mp3; ?></sub>
    <?php endif; ?>
    
    <?php if ($audio_code): ?>
      <div><?php print $audio_code; ?></div>
      <sub>Embedded media is only viewable in RSS if your reader supports it.</sub>
    <?php endif; ?>
    
    <?php if ($slideshow): ?>
      <div><?php print $slideshow; ?></div>
    <?php endif; ?>
    
    <?php print $node_body; ?>
    
    <?php if ($add_comment): ?>
      <sub><?php print $add_comment; ?></sub>
    <?php endif; ?>
    
    <br /><br /><br />
  ]]></description>
  <?php if ($authors): ?>
    <?php print $item_elements; ?>
  <?php else: ?>
    <?php print preg_replace('/<dc:creator>.*<\/dc:creator>/', '<dc:creator></dc:creator>', $item_elements); ?>
  <?php endif; ?>
</item>