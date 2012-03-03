<?php
/**
 * @file
 * Default template.
 **/
?>
<?php
if($items) {
	$list_items = array();
	foreach($items as $item){
	  $list_items[] = theme('topterms_block_item', $item);
	}
	echo theme('item_list', $list_items);
}  
?>