<?php 
$title_used = false;
$result_arr = $view->result; 
$current = 1;
foreach($result_arr as $id => $result) {
  if ($result->nid == $row->nid) { 
    $current = ($id +1);
    break;
  }
}

foreach ($fields as $id => $field) {
  $out = '';
  switch ($field->class) {
    case 'title':
      if (!$title_used) {
        $out .= '<h3>'.$field->content.' <span class="number">('.($current).' of '.count($result_arr).')</span></h3>';
      }
      break;
    case 'body':
      $out .= $field->content;
      break;
    case 'field-main-image-fid':
      $out .= $field->content;
      $img_data =unserialize($row->node_data_field_main_image_field_main_image_data);
        if ($img_data['description']) {
          $out .= ' <div class="credit">'.$img_data['description'].'</div>';
      }
      break;
  }
  print $out;
}
?>
