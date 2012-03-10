<?php

/**
 * @file nodewords-list.tpl.php
 * Default theme implementation to configure meta tags (admin/content/nodewords).
 *
 * Available variables:
 * - $tags: An array of meta tags.
 * - $form_submit: Form submit button.
 *
 * Each $data in $tags contains:
 * - $data->name: Meta tag name (text).
 * - $data->type: Meta tag type (text).
 * - $data->widget: Meta tag widget (text).
 * - $data->description: Meta tag description (text).
 * - $data->weight_select: Drop-down menu for setting weights.
 * - $data->edit_link: Meta tag edit link.
 * - $data->delete_link: Meta tag delete link.
 *
 * @see template_preprocess_nodewords_list() theme_nodewords_list()
 */
?>
<?php
  drupal_add_js('misc/tableheader.js');
  drupal_add_tabledrag('nodewords-list-table', 'order', 'sibling', 'nodewords-weight');
?>

<table id="nodewords-list-table" class="sticky-enabled">
  <thead>
    <tr>
      <th><?php print t('Name'); ?></th>
      <th><?php print t('Type'); ?></th>
      <th><?php print t('Widget'); ?></th>
      <th><?php print t('Description'); ?></th>
      <th><?php print t('Weight'); ?></th>
      <th colspan="2"><?php print t('Operations'); ?></th>
    </tr>
  </thead>
  <tbody>
    <?php $row = 0; ?>
    <?php foreach ($tags as $data): ?>
    <tr class="draggable <?php print $row % 2 == 0 ? 'odd' : 'even'; ?>">
      <td><?php print $data->name; ?></td>
      <td><?php print $data->type; ?></td>
      <td><?php print $data->widget; ?></td>
      <td><?php print $data->description; ?></td>
      <td><?php print $data->weight_select; ?></td>
      <td><?php print $data->edit_link; ?></td>
      <td><?php print $data->delete_link; ?></td>
    </tr>
    <?php $row++; ?>
    <?php endforeach; ?>
    <?php if (count($tags) == 0) : ?>
    <tr class="odd">
      <td colspan="7"><?php print t('No meta tags available.'); ?></td>
    </tr>
    <?php endif; ?>
  </tbody>
</table>

<?php print $form_submit; ?>
