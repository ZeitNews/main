<?php

/**
 * @file
 * Available variables:
 * - $descriptions: an array ($title => $description).
 */
?>
<dl class="nodewords-descriptions">
  <?php foreach ($descriptions as $title => $description) : ?>
  <dt><?php print $title; ?></dt>
  <dd><?php print $description; ?></dd>
  <?php endforeach; ?>
</dl>

