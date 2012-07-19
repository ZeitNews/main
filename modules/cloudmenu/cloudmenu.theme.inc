<?php
/**
 * @file cloudmenu.theme.inc
 */

/**
 * Theme function that returns the menu tree items as url parameter for cumulus.swf
 */
function theme_cloudmenu_weighted($items, $settings) {
  $output = '<tags>';
  foreach ($items as $item) {
    $font_size = (12 - (intval($item['depth']) * $settings['flash_font_size_interval'])) + ($settings['flash_font_size'] - $settings['flash_font_size_interval']);
    $output .= l($item['title'], $item['href'], array('absolute' => TRUE, 'attributes' => array('style' => '"font-size: '. $font_size .'px;"'))) ." \n";
  }
  $output .= '</tags>';
  return urlencode($output);
}

/**
 * Theme function that simply returns the menu tree items as links.
 */
function theme_cloudmenu_weighted_alt($items) {
  $output = '';
  foreach($items as $item) {
    $output .= l($item['title'], $item['href'], array('attributes' => $item['options']['attributes']));
  }
  return $output;
}
