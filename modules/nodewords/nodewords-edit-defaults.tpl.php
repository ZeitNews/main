<?php

/**
 * @file nodewords-edit-defaults.tpl.php
 * Default theme implementation to edit the defaults of a meta tag
 * (admin/content/nodewords/%/defaults).
 *
 * Available variables:
 * - $defaults: An array of meta tag attributes.
 * - $form_submit: Form submit button.
 *
 * Each $data in $defaults contains:
 * - $data->context_title: String (title of context).
 * - $data->context_description: String (description of that context).
 * - $data->enabled_select: Select for enabling/disabling the tag (select).
 * - $data->editable_select: Select for enabling/disabling editability (select).
 * - $data->value: Default value (textfield).
 */
?>
<?php
  drupal_add_js('misc/tableheader.js');
?>

<table id="nodewords-edit-defaults-table" class="sticky-enabled">
  <thead>
    <tr>
      <th><?php print t('Context'); ?></th>
      <th><?php print t('Output in HEAD?'); ?></th>
      <th><?php print t('Editable?'); ?></th>
      <th><?php print t('Default value'); ?></th>
    </tr>
  </thead>
  <tbody>
    <?php $row = 0; ?>
    <?php foreach ($defaults as $data): ?>
    <tr class="<?php print $row % 2 == 0 ? 'odd' : 'even'; ?>">
      <th rowspan="2"><?php print $data->context_title; ?></th>
      <td><?php print $data->enabled_select; ?></td>
      <td><?php print $data->editable_select; ?></td>
      <td><?php print $data->value; ?></td>
    </tr>
    <tr class="<?php print $row % 2 == 0 ? 'odd' : 'even'; ?>">
      <td colspan="3"><?php print $data->context_description; ?></td>
    </tr>
    <?php $row++; ?>
    <?php endforeach; ?>
  </tbody>
</table>

<?php print $form_submit; ?>
