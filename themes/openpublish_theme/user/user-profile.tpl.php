<?php
//dsm($variables);
//dsm($account);
//dsm($cp_vars);
//dsm($cp_vars->taxonomy);
//dsm($tagorder_taxonomy);
?>
<div class="user-profile">
  <?php if ($account->picture): ?>
    <?php print theme('imagecache', 'user_image_large', $account->picture, $alt, $title, $attributes); ?>
  <?php endif; ?>
  
  <?php if ($fields_of_expertise): ?>
    <div class="user-job-title">
      <h3><?php print $fields_of_expertise; ?></h3>
    </div>
  <?php endif;?>
  
  <?php if ($locations): ?>
    <div class="user-locale">
      <h4><?php print $locations ?></h4>
    </div>
  <?php endif; ?>
  
  <?php if ($cp_vars): ?>
    <?php print $cp_vars->body; ?>
  <?php endif; ?>
</div>
