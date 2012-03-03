<?php foreach($items as $item): ?>
  <div class="author">
    <?php if(isset($item->picture)): ?>
      <div class="picture" style="float:left;"><?php print theme('image', $item->picture); ?></div>
    <?php endif; ?>
    <!--<div class="name"><?php print l($item->name, "user/$item->uid"); ?></div>-->
    <div class="name"><?php print theme('username', $item); ?></div>
    <div style="clear:both;"></div>
  </div>
<?php endforeach; ?>
