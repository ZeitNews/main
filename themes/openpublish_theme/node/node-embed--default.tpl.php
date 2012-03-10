<?php
// $Id: node-embed--default.tpl.php,v 1.1.2.1 2010/09/08 23:34:57 tirdadc Exp $
?>
<div id="embedded-node-<?php print $node->nid; ?>" class="embedded-node 
  <?php if (!$node->status) { print ' node-unpublished'; } ?>">
  <h2><a href="<?php print $node_url; ?>" title="<?php print $title; ?>"><?php print $title; ?></a></h2>

  <div class="content clear-block">
    <?php print $node->body; ?>
  </div>
</div>
