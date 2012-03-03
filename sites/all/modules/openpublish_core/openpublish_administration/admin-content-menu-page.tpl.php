<h4><?php print t("Content"); ?></h4>

<?php 
  $menu_link = module_exists('cmf') ? menu_get_item("admin/content/filter") : menu_get_item("admin/content/node/overview");
?>
<?php if ($menu_link['access']): ?>
  <dl>
    <dt><?php print l(t('Content List'), $menu_link['path']); ?></dt>
    <dd><?php print t('Manage site content. Quick view allows the ability to view, update, and remove content in a simple list format.') ?></dd>
  </dl>
<?php endif; ?>

<?php if (module_exists('admin')) : ?>
  <dl>
    <dt><?php print l(t('Create Content'), 'node/add'); ?></dt>
    <dd><?php print t('Add new content to your OpenPublish site.') ?></dd>
  </dl>
<?php else: ?>
  <?php
  if (module_exists('content')) {
    $content_types = content_types();
    $output = '';
    foreach($content_types as $content_type) {
      $menu_link = menu_get_item("node/add/".$content_type['url_str']);
      if ($menu_link['access']) {
        $output .= '<dt>' . l($content_type['name'], $menu_link['path']) . '</dt>';
        if ($content_type['description']) {
          $output .= '<dd>' . $content_type['description'] . '</dd>';
        }
      }
    }
    if ($output) {
      print '<strong>' . t('Create Content') . '</strong><dl>';
      print $output;
      print '</dl>';
    }
  }
  ?>
<?php endif; ?>


<?php 
  // Taxonomy
  $menu_link = menu_get_item('admin/content/taxonomy/list');
  $menu_link2 = menu_get_item('admin/content/taxonomy/add/vocabulary');
?>
<?php if ($menu_link['access'] || $menu_link2['access']): ?>
  <h4><?php print t('Taxonomy'); ?></h4>
  <dl>
  <?php if ($menu_link['access']): ?>
    <dt><?php print l(t('Taxonomy List'), $menu_link['path']); ?></dt>
    <dd><?php print t('Manage tagging, categorization, and classification of your content') ?></dd>
  <?php endif; ?>
  <?php if ($menu_link2['access']): ?>
    <dt><?php print l(t('Add Vocabulary'), $menu_link2['path']); ?>:</dt>
    <dd><?php print t('Add a new Vocabulary to your taxonomy structure and set preferences') ?></dd>
  <?php endif; ?>
  </dl>
<?php endif; ?>

<?php
  // Comments
  $menu_link = menu_get_item('admin/content/comment');
  $menu_link2 = menu_get_item('admin/content/comment/approval');
?>
<?php if ($menu_link['access'] || $menu_link2['access']): ?>
  <h4><?php print t('Comments'); ?></h4>
  <dl>
  <?php if ($menu_link['access']): ?>
    <dt><?php print l(t('Comments List'), $menu_link['path']); ?></dt>
    <dd><?php print t('View, update and remove site comments') ?></dd>
  <?php endif; ?>
  <?php if ($menu_link2['access']): ?>
    <dt><?php print l(t('Approval Queue'), $menu_link2['path']); ?>:</dt>
    <dd><?php print t('View and update comments waiting for moderator approval') ?></dd>
  <?php endif; ?>
  </dl>
<?php endif; ?>

<?php 
  // RSS Listing
  $menu_link = menu_get_item('admin/content/feed');
?>
<?php if ($menu_link['access']): ?>
  <h4><?php print t('Feeds'); ?></h4>
  <dl>
    <dt><?php print l(t('Feeds List'), $menu_link['path']); ?></dt>
    <dd><?php print t('View, update and remove feeds the site consumes') ?></dd>
  <dl>
<?php endif; ?>
