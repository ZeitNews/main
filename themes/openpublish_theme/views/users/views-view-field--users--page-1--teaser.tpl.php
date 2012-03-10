<?php
//dsm($row);
?>
<?php if (!empty($row->node_users__node_revisions_teaser)): ?>
  <p property="dc:abstract"><?php print $output . ' ' . l(t('more'), 'user/' . $row->uid); ?> &raquo;</p>
<?php endif; ?>