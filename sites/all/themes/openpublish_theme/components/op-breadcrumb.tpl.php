<?php if (!empty($breadcrumb)): ?>

  <?php
  // uncomment the next line to enable current page in the breadcrumb trail
  // $breadcrumb[] = drupal_get_title(); 
  ?>

  <div class="breadcrumb"><?php print implode(' » ', $breadcrumb); ?></div>
   
<?php endif; ?>