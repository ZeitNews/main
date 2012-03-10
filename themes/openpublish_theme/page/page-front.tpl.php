<?php
// $Id: page-front.tpl.php,v 1.1.2.7 2010/06/21 00:49:06 inadarei Exp $
/**
 * @file page-front.tpl.php
 *
 * For the list of available variables, please see: page.tpl.php
 *
 * Homepage template.
 * @ingroup page
 */
?>
<?php print $page_header; ?>

<?php if ($show_messages && $messages): ?>
  <div class="messages">
    <?php print $messages; ?>
  </div>
<?php endif; ?>

<?php $showhelp = variable_get('openpublish_show_help', TRUE); ?>
<?php if ($showhelp && user_access('administer nodes')): ?>
  <div class="messages status">
    <ul>
      <li><?php print t('Not sure what to do next? See:'); ?> <?php print l(t('Getting Started'), "http://openpublishapp.com/doc/openpublish-user-documentation", array('attributes' => array('target' => '_blank'))); ?> (<?php print l(t('hide this'), "admin/settings/openpublish/clear-help"); ?>)</li>
    </ul>
  </div>
<?php endif; ?>

<div id="sidebar-left">
  <?php print $left; ?>
</div>
<div id="op-content">
  <?php print $over_content; ?>
</div>
<div id="sidebar-right" class="sidebar"><!-- #sidebar-right -->
  <?php print $right; ?>
</div>

<?php print $page_footer; ?>
