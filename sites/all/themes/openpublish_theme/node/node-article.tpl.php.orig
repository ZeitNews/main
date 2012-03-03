<?php
// $Id: node-article.tpl.php,v 1.1.2.10 2010/10/26 21:17:19 jec006 Exp $
/**
 * @file
 * Template for article content type.
 * 
 * Available variables:
 * - $type: Content type (article).
 * - $field_deck: Used to determine visibility of $field_deck_value.
 * - $field_deck_value: The article's deck text.
 * - $authors: List of authors.
 * - $node_created: The article's post date.
 * - $node_created_timestamp: The article's post date in timestamp format.
 * - $body: Actual body content of the article.
 * - $main_image: The article's main image.
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
 * @see openpublish_node_article_preprocess()
 */
?>
<?php if ($field_deck): ?>
	<div class="deck"><?php print $field_deck_value; ?></div><!-- /.deck -->
<?php endif; ?>
<div class="section-date-author"><?php print t($type); ?> | 
  
  <?php print $node_created_rdfa; ?>

  <?php if ($authors): ?>
    | <?php print $authors; ?>
  <?php endif; ?>
   	
</div><!-- /.section-date-author -->
<div class="body-content">
<?php
  
  if ($main_image): ?>
    <div class="main-image">
      <?php print $main_image; ?>
        <div class="main-image-desc image-desc">
          <?php print $main_image_desc; ?> <span class="main-image-credit image-credit"><?php print $main_image_credit; ?></span>
        </div><!-- /.main-image-desc -->
    </div><!-- /.main-image -->
  <?php endif; ?>
  
  <div property="dc:description"><?php print $body; ?></div>
  
  <?php if ($documentcloud_doc): ?>
    <h2><?php print t("Source Documents ");?></h2>
    <?php foreach ($documentcloud_doc as $doc) : ?>
      <?php print $doc['view']; ?>
    <?php endforeach; ?>
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
          <div class="user-bio"><?php print $author->teaser; ?></div>
        </div>
  	  <?php endforeach; ?>
    </div><!-- /.user-profile -->
	<div class="clear"><br/></div>
  <?php endif; ?>
  
</div>
<?php if ($calais_geo_map): ?>
<div class="google-map">
	 <?php print $calais_geo_map; ?>
</div><!-- /.google-map -->
<?php endif; ?>

<?php print $related_terms_links; ?>
<?php print $themed_links; ?>