<?php
/**
 * @file
 * Sample template for topterms item.
 * Available variables:
 * $item->tid
 * $item->name
 * $item->total // node statistics score
 * 
 **/
?>
<div><?php echo l($item->name, 'taxonomy/term/'. $item->tid, array('html'=>true)); ?></div>


