<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">

  <h1><?php print $title; ?></h1>

  <div class="content">
    <?php print $content; ?>
  </div>
</div>
