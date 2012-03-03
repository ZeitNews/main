<?php
// $Id: node-editors_choice.tpl.php,v 1.1.2.1 2010/10/01 16:23:02 tirdadc Exp $
/**
 * @file
 * Template for Editor's Choice content type.
 * 
 * Available variables:
 * - $type: Content type (article).
 * - $custom_html: content of the custom HTML (body) field
 * - $featured_nodes: the views-driven output displayed when featured nodes are picked.
 *   See views-view-fields--editors-choice.tpl.php for fields-level theming.
 * 
 * @see openpublish_node_editors_choice_preprocess()
 */
?>

<?php if ($custom_html): ?>
  <?php print $custom_html; ?>
<?php elseif ($featured_nodes): ?>
  <?php print $featured_nodes; ?>
<?php endif; ?>