<?php

function op_author_layout_author_page_layout_panels_layouts() {
  $items['author_page_layout'] = array(
    'title' => t('Author Page Layout'),
    'icon' => 'author_page_layout.png',
    'theme' => 'op_author_layout_author_page_layout',
    'css' => 'author_page_layout.css',
    'panels' => array(
      'author_brief' => t('Author Brief'),
      'left_column' => t('Left Column'), 
      'right_column' => t('Right Column'),
    ),
  );
  return $items;
}