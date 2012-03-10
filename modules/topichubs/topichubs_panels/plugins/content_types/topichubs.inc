<?php

/**
 * Implementation of hook_ctools_content_types()
 */
function topichubs_panels_topichubs_ctools_content_types() {
  $items = array(
    'title' => t('Topichubs Panels'),
  );
  return $items;
  
}
/**
 * Implementation of hook_PLUGINNAME_content_type_content_types()
 */
function topichubs_panels_topichubs_content_type_content_types($plugins) {
  $plugins = topichubs_discover_plugins();
  $topichub_panes = array();
  foreach ($plugins as $type => $def) {
    $impl = _topichubs_new_handler_class($def);
    if($impl) {
      $pane = new StdClass();
      $pane->category = t('Topic Hubs');
      $pane->title = $def['title'];
      $pane->description = $def['description']; 
      $topichub_panes[] = $pane; 
    }
  }

  $types = array();
  
  foreach ($topichub_panes as $pane) {

    $types[$pane->title] = array(
      'title' => filter_xss_admin($pane->title),
      // For now mini panels will just use the contrib block icon.
      'icon' => 'icon_contrib_block.png',
      'path' => panels_get_path("content_types/block"),
      'description' => filter_xss_admin($pane->description),
      'category' => array(!empty($mini->category) ? filter_xss_admin($mini->category) : t('Topic Hubs'), -8),
    );
  }
  return $types;
}
/**
 * Implementation of hook_PLUGINNAME_content_type_render()
 */
function topichubs_panels_topichubs_content_type_render($subtype, $conf,$panel_args, &$contexts) {
  panels_load_include('plugins');
  
  $implementation_identified = FALSE;
  $impl_def = topichubs_lookup_plugin_by_name($subtype);
  if (empty($impl_def)) {
    $content = '';
  }
  else {
    $implementation_identified = TRUE;
  }
  
  if ($implementation_identified) {
    $impl = _topichubs_new_handler_class($impl_def->def);
    if($impl && arg(0) =='node' && is_numeric(arg(1))) {
      $node = node_load(arg(1));
      $impl->init($impl_def->type, $def, $node, $node->topichub->config[$impl_def->type]);
      $data = $impl->execute();
      $content = $data['#view'];
    } 
    else {
      $content = '';
    }
  }
  else {
    $content = '';
  }

  $block = new stdClass();
  $block->module  = 'topichubs_panels';
  $block->delta   = $conf['name'];
  $block->title = filter_xss_admin($conf['name']);

  $block->content = $content;
  
  return $block;
}
/**
 * Implementation of hook_PLUGINNAME_content_type_edit_form()
 */
function topichubs_panels_topichubs_content_type_edit_form(&$form,$form_state) {
}
/**
 * Implementation of hook_PLUGINNAME_content_type_admin_title()
 */
function topichubs_panels_topichubs_content_type_admin_title($subtype, $conf) {
  return $subtype;
}
