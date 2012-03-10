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
  *
  * This tpl exists to fix the problem of "No items were found. Adjust the
  * filters or reopen this window and try again." error when filtering to a
  * node type that doesn't have any comments. Basically can't use the view
  * filter of Node: Comment Count > 0 or get the empty text of "No comments
  * yet." :/
  */
//dsm($row);
?>
<?php if ($row->node_comment_statistics_comment_count > 0): ?>
  <?php print str_replace('href="', 'property="dc:title" href="', $output); ?>
<?php endif; ?>