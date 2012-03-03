<?php
  if(empty($items))
    return;
    
  $links = array();
  foreach($items as $item){
    $links[] = l($item->title, "node/$item->nid");
  }
  print theme('item_list', $links);
