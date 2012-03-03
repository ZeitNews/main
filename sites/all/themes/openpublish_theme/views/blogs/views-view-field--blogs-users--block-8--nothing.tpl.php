<?php
// $Id: views-view-field.tpl.php,v 1.1 2008/05/16 22:22:32 merlinofchaos Exp $
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */
  //dsm($row);
  //dsm($view->field['tagorder']);
?>
<div id="viewpoint-user-info">
<?php if ($row->users_picture && $row->node_node_data_field_op_author_nid): ?>
  <?php print l(theme('imagecache', 'author_photo_viewpoint', $row->users_picture, $row->users_name . "'s photo", 'View ' . $row->users_name . "'s biography.", $attributes), 'node/' . $row->node_node_data_field_op_author_nid, array('html' => TRUE)); ?>
<?php elseif ($row->users_picture): ?>
  <?php print theme('imagecache', 'author_photo_viewpoint', $row->users_picture, $row->users_name . "'s photo", 'View ' . $row->users_name . "'s biography.", $attributes); ?>
<?php endif; ?>
<?php if ($row->users_name && $view->field['tagorder']->last_render): ?>
  <h1 class="taxonomy-heading" property="dc:title"><?php print truncate_utf8(ucwords($row->users_name) . ' <span class="job-t">~ ' . $view->field['tagorder']->last_render . '</span>', 113, FALSE, FALSE); ?></h1>
<?php elseif ($row->users_name): ?>
  <h1 class="taxonomy-heading" property="dc:title"><?php print ucwords($row->users_name); ?></h1>
<?php endif; ?>
</div>