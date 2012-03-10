<div class="view view-articles view-id-articles clearfix subscription-only">
  <div class="views-field-title">              
    <?php print $fields['title']->content; ?> 
    <?php if (!empty($fields['tags']->content)): ?>
      <span class="subject-topic">(<?php print $fields['tags']->content;?>)</span>
    <?php endif; ?>
  </div><!--/views-field-title--> 
  
  <div class="blurb">
    <?php print $fields['teaser']->content; ?>

    <?php if (!empty($fields['authors']->content)): ?>
    <div class="views-field-value byline">
       <?php print $fields['authors']->content; ?>
    </div><!--/views field value-->
    <?php endif; ?>

  </div><!--/ blurb -->
  
  <div class="clearfix">  
    <?php if ($fields['comment_count']->raw): ?>
      <div class="comments">
        <?php print l($fields['comment_count']->content . ' ' . t('Comments'), 'node/' . $fields['nid']->raw); ?>           
      </div><!--/comments-->
    <?php endif; ?>
    
    <?php if (!empty($fields['premium']->raw)) : ?>
      <div class=".subscribe-only-tag"><?php print $fields['premium']->content; ?></div>
    <?php endif; ?>
  </div><!--/clearfix-->
</div><!--/view articles-->

<div class="views-separator"/></div>
