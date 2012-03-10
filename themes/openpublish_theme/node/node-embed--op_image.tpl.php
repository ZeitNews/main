<?php
// $Id: node-embed--op_image.tpl.php,v 1.1.2.1 2010/09/08 23:34:57 tirdadc Exp $
?>

<div id="embedded-node-<?php print $node->nid; ?>" class="embedded-node 
  <?php if (!$node->status) { print ' node-unpublished'; } ?>">
  <div class="content clear-block">
    <?php if ($main_image): ?>
      <div class="main-image">
        <?php print $main_image; ?>

        <?php if ($credit): ?>
          <div class= "main-image-credit image-credit image-desc"><?php print $credit; ?></div>
        <?php endif; ?>
  
      </div><!-- /.main-image -->
    <?php endif; ?>
  </div>
</div>