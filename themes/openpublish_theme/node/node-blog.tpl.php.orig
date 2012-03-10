<?php
// $Id: node-blog.tpl.php,v 1.1.2.9 2010/10/26 21:17:19 jec006 Exp $
/**
 * @file
 * Template for blog content type.
 * 
 * Available variables:
 * - $authors: List of authors.
 * - $node_created: The blog post's date.
 * - $node_created_timestamp: The blog post's date in timestamp format.
 * - $body: Actual body content of the blog post.
 * - $authors: Array of author objects. Each $author in $authors contains:
 *   - $author->title: Author's name.
 *   - $author->jobtitle: Author's job title.
 *   - $author->teaser: Author's teaser text. 
 *   - $author->photo: Author's photo thumbnail. 
 * - $calais_geo_map: Calais geomapping data.
 * - $related_terms_links: Related taxonomy links.
 * - $themed_links: Themed links.
 * 
 * @see openpublish_node_blog_preprocess()
 */
?>
<div class="section-date-author"><?php print t($type); ?> | <?php print $node_created_rdfa; ?>
  <?php if ($authors): ?>
    | <?php print $authors; ?>
  <?php endif; ?>
</div><!-- /.section-date-author -->
<div class="body-content">
  <div property="dc:description"><?php print $body; ?></div>
   
  <?php if ($documentcloud_doc): ?>
    <h2><?php print t("Source Documents");?></h2>
    <?php foreach ($documentcloud_doc as $doc) : ?>
      <?php print $doc['view']; ?>
    <?php endforeach; ?>
  <?php endif; ?>
  
  <?php if ($author_profiles): ?>
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
    
</div><!-- /.body-content -->

<?php if ($calais_geo_map): ?>
<div class="google-map">
	 <?php print $calais_geo_map; ?>
</div><!-- /.google-map -->
<?php endif; ?>

<?php print $related_terms_links; ?>
<?php print $themed_links; ?>