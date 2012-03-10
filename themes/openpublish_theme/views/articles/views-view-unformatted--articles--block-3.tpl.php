<?php if (!empty($title)): ?>
  <h2><?php print $title; ?></h2>
<?php endif; ?>

<?php foreach ($rows as $id => $row): ?>
  <div class="<?php print $classes[$id]; ?>">
    <?php print $row; ?>
  </div>
<?php endforeach; ?>
<div class="views-separator"></div>
