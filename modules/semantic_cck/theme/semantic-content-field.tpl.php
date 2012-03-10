<?php
/**
 * @file semantic-content-field.tpl.php
 * Theme implementation to display the value of a semantic field. Modified from the default 
 * CCK field template file (content-field.tpl.php).
 *
 * Available variables:
 * - $node: The node object.
 * - $field: The field array.
 * - $items: An array of values for each item in the field array.
 * - $teaser: Whether this is displayed as a teaser.
 * - $page: Whether this is displayed as a page.
 * - $field_name: The field name.
 * - $field_type: The field type.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $label: The item label.
 * - $label_display: Position of label display, inline, above, or hidden.
 * - $field_empty: Whether the field has any valid value.
 *
 * Semantic HTML variables:
 * - $field_element: The HTML element to surround the entire field with.
 * - $field_prefix: Character(s) to output before the field.
 * - $field_suffix: Character(s) to output after the field.
 * - $label_element: The HTML element to surround the label text with.
 * - $label_suffix: A character or string displayed directly after the label, eg. a colon.
 * - $items_element: The HTML element to surround all of the field items with.
 * - $item_element: The HTML element to surround each field item with.
 *
 * Each $item in $items contains:
 * - 'view' - the themed view for that item
 *
 * @see template_preprocess_content_field()
 * @see semantic_cck_preprocess_content_field()
 */ 
if (!$field_empty) {
  print $field_prefix;
  if ($field_element) { 
    print "<" . $field_element . drupal_attributes($field_attributes) . ">";
  }
  if ($label_display == 'above') {
    print "<" . $label_element . drupal_attributes($label_attributes[0]) .">" . t($label) . $label_suffix . "</" . $label_element . ">";
  }
  if ($items_element) {
    print "<" . $items_element . drupal_attributes($items_attributes) . ">";
  }
  foreach ($items as $delta => $item) {
    if (!$item['empty']) {
      if ($item_element) {
        print "<" . $item_element . drupal_attributes($item_attributes[$delta]) . ">";
      }
      if ($label_display == 'inline') {
        print "<" . $label_element . drupal_attributes($label_attributes[$delta]) . ">" . t($label) . $label_suffix . "</" . $label_element . ">";
      }
      print $item_prefix . $item['view'] . $item_suffix;
      if ($item_element) {
        print "</" . $item_element . ">";
      }
      if ($delta < (count($items) - 1)) {
        print $item_separator;
      }
    }
  }
  if ($items_element) {
    print "</" . $items_element . ">";
  }
  if ($field_element) {
    print "</" . $field_element . ">";
  }
  print $field_suffix;
} 