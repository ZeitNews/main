<?php

/**
 * @file nodewords-edit-attributes.tpl.php
 * Default theme implementation to list attributes of a meta tag (admin/content/nodewords/%/attributes).
 *
 * Available variables:
 * - $attributes: An array of meta tag attributes.
 * - $form_submit: Form submit button.
 *
 * Each $data in $attributes contains:
 * - $data->delete_check: Checkbox for deletion (checkbox).
 * - $data->name: Meta tag name (textfield).
 * - $data->value: Meta tag type (textfield).
 * - $data->weight_select: Drop-down menu for setting weights.
 */
?>
<?php
  drupal_add_js('misc/tableheader.js');
  drupal_add_tabledrag('nodewords-edit-attributes-table', 'order', 'sibling', 'nodewords-weight');
?>

<table id="nodewords-edit-attributes-table" class="sticky-enabled">
  <thead>
    <tr>
      <th><?php print t('Delete'); ?></th>
      <th><?php print t('Name'); ?></th>
      <th><?php print t('Value'); ?></th>
      <th><?php print t('Weight'); ?></th>
    </tr>
  </thead>
  <tbody>
    <?php $row = 0; ?>
    <?php foreach ($attributes as $data): ?>
    <tr class="draggable <?php print $row % 2 == 0 ? 'odd' : 'even'; ?>">
      <td><?php print $data->delete_check; ?></td>
      <td><?php print $data->name; ?></td>
      <td><?php print $data->value; ?></td>
      <td><?php print $data->weight_select; ?></td>
    </tr>
    <?php $row++; ?>
    <?php endforeach; ?>
    <?php if (count($attributes) == 0) : ?>
    <tr class="odd">
      <td colspan="4"><?php print t('No meta tag attributes available.'); ?></td>
    </tr>
    <?php endif; ?>
  </tbody>
</table>

<?php print $form_submit; ?>
