<?php
// $Id: node-audio.tpl.php,v 1.1.2.10 2010/10/26 21:17:19 jec006 Exp $
/**
 * @file
 * Template for audio content type.
 * 
 * Available variables:
 * - $type: Content type (audio).
 * - $field_deck: Used to determine visibility of $field_deck_value.
 * - $field_deck_value: The audio's deck text.
 * - $authors: List of authors.
 * - $node_created: The audio's post date.
 * - $node_created_timestamp: The audio's post date in timestamp format.
 * - $body: Actual body content of the audio.
 * - $main_image: The audio's main image.
 * - $main_image_desc: The main image's description.
 * - $main_image_credit: The main image's credit.
 * - $show_authors: Determines whether the "About the Authors" block is shown or not.
 * - $author_profiles: an array of author profiles to display. Each $author in $author_profiles contains:
 *   - $author->title: Author's name.
 *   - $author->jobtitle: Author's job title.
 *   - $author->teaser: Author's teaser text. 
 *   - $author->photo: Author's photo thumbnail. 
 * - $calais_geo_map: Calais geomapping data.
 * - $related_terms_links: Related taxonomy links.
 * - $themed_links: Themed links.
 * 
 * @see openpublish_node_audio_preprocess()
 */
?>
<?php if ($field_deck_value): ?>
	<?php print '<h2 class="deck">' . $field_deck_value . '</h2><!-- /.deck -->'; ?>
<?php endif; ?>
<div class="section-date-author">
	<?php print l(t($type), 'multimedia', array('query' => 'type[]=audio')); ?> | 
  <?php print $node_created_rdfa; ?>
  <?php if ($authors): ?>
    | <?php print $authors; ?>
  <?php endif; ?>
</div><!-- /.section-date-author -->

<div class="body-content">
  
<div property="dc:description"><?php print $body; ?></div>

<?php print $related_terms_links; ?>

<?php if ($calais_geo_map): ?>
<div class="google-map">
	 <?php print $calais_geo_map; ?>
</div><!-- /.google-map -->
<?php endif; ?>

<?php if ($show_authors): ?>
	<div class="user-profile">
		<h3><?php print format_plural($plural, 'About the Author', 'About the Authors'); ?></h3>    	
		<?php foreach ($author_profiles as $author): ?>    	   
			<?php if ($author->photo): ?>
				<?php print $author->photo; ?>
			<?php endif; ?>
	 
			<div class="clearfix">
				<div class="user-name"><?php print $author->title; ?></div>
				<div class="user-job-title"><?php print $author->jobtitle; ?></div>
				<div class="user-bio"><p><?php print strip_tags($author->teaser); ?> <?php print l(t('Read full bio'), 'node/' . $node->field_op_author[0]['nid']); ?>.</p></div>
			</div>
		<?php endforeach; ?>
	</div><!-- /.user-profile -->
	
<div class="clear"><br/></div>
<?php endif; ?>

</div><!-- /.body-content -->

<?php if ($links && $comment_count == 0 && arg(0) != 'comment'): ?>
  <div class="links">
      <?php print $add_new_comment; ?>
  </div>
<?php endif; ?>