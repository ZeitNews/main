<?php if (!empty($taxonomy)): ?>
  <div class="related-terms">
    <strong><?php print t('Related Terms:'); ?></strong>
      <?php foreach($taxonomy as $term): ?>
        <?php if (is_object($term) && !empty($term->name)): ?>
      	  <div class="related-term"><?php print l($term->name,'topics/'.$term->name); ?></div>
    	  <?php endif; ?>
      <?php endforeach; ?>
  </div><!--/ .related-terms-->    
<?php endif; ?>