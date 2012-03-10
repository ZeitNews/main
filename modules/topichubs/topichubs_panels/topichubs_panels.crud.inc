<?php

function topichubs_panels_add() {
  $output = '';

  panels_load_include('plugins');
  // If no layout selected, present a list of choices.
  foreach (panels_get_layouts() as $id => $layout) {
    $output .= panels_print_layout_link($id, $layout, 'node/add/topichub/' . $id);
  }
  return $output;
}

/**
 * Implementation of hook_topichubs_render_form().
 */
function topichubs_panels_topichubs_render_form(&$node, &$form) {
  $form['panels_node']['#tree'] = TRUE;
  if (!$node->nid) {
    // Grab our selected layout from the $node, If it doesn't exist, try arg(3)
    // and if that doesn't work present them with a list to pick from.
    $panel_layout = isset($node->panel_layout) ? $node->panel_layout : arg(3);
    if (empty($panel_layout)) {
      return drupal_goto('node/add/topichub_panel/choose-layout');
    }

    panels_load_include('plugins');
    $layout = panels_get_layout($panel_layout);
    
    if (empty($layout)) {
      return drupal_not_found();
    }
    $form['panels_node']['layout'] = array(
      '#type' => 'value',
      '#value' => $panel_layout,
    );
  }

  $type = node_get_types('type', $node);

  $css_id = '';
  if (!empty($node->panels_node['css_id'])) {
    $css_id = $node->panels_node['css_id'];
  }

  $form['panels_node']['css_id'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS ID'),
    '#size' => 30,
    '#description' => t('An ID that can be used by CSS to style the panel.'),
    '#default_value' => $css_id,
  );
  
}

/**
 * Implementation of hook_topichubs_render_validate().
 */
function topichubs_panels_topichubs_render_validate($node) {
  if (!$node->nid && empty($node->panels_node['layout'])) {
    form_set_error('', t('Please select a layout.'));
  }
}

/**
 * Implementation of hook_topichubs_render_load().
 *
 * Panels does not use revisions for nodes because that would open us up
 * to have completely separate displays, and we'd have to copy them,
 * and that's going to be a LOT of data.
 */
function topichubs_panels_topichubs_render_load(&$node) {
  // We shortcut this because only in some really drastic corruption circumstance will this
  // not work.
  $node->panels_node = db_fetch_array(db_query("SELECT * FROM {panels_node} WHERE nid = %d", $node->nid));
}

/**
 * Implementation of hook_topichubs_render_insert().
 *
 * Add Default Panes to the node
 */
function topichubs_panels_topichubs_render_insert(&$node) {
  panels_node_insert($node);
  $display = panels_load_display($node->panels_node['did']);
  foreach(_topichubs_panels_topichubs_render_insert_get_default_panes($display->layout) as $key => $pane) {
    $display->content[$key] = $pane;
    $display->panels[$pane->panel][] = $key;
  }
  panels_save_display($display);
  drupal_goto('node/'.$node->nid.'/topichub');
}

/**
 * creates array of default panes dependent on layout
 * @param $layout:
 *   a string with the name of a panels layout
 * @return 
 *   an array of pane objects based on a call to panels_new_pane()
 */
function _topichubs_panels_topichubs_render_insert_get_default_panes($layout) {
  
  // find default panes desc function based on layout.
  $panes_desc_function = "topichubs_panels_default_panes_desc_$layout";
  if(function_exists($panes_desc_function)) {
    $panes_desc = $panes_desc_function();
  }
  // if there is no function then get the desc for the topicbubs layout
  // and distribute the panes to the different panels of the layout.
  else {
   $panes_desc = topichubs_panels_default_panes_desc_topichubs();
   $layout_info = panels_get_layout($layout);
   $panels = array_keys($layout_info['panels']);
   $i =0;
   foreach($panes_desc as $key => $pane_desc) {
     $panes_desc[$key]['panel'] = $panels[$i];
     $i ++;
     $i = $i >= sizeof($panels)? 0 : $i;
   }
  }
  //build the pane objects
  foreach($panes_desc as $key => $pane_desc) {
    $pane = panels_new_pane($pane_desc['type'],$pane_desc['sub_type']);
    $pane->panel = $pane_desc['panel'];
    $pane->configuration = $pane_desc['configuration'];
    $pane->configuration['name'] = $pane_desc['name'];
    $panes["new-$key"] = $pane; 
  }
  return $panes;
}
/**
 * Creates an array describing a set default panes for the 
 * _topicbuis_panels_topichubs_render_insert_get_default_panes function
 * @return
 *   an array of pane desc for use in the
 *   _topicbuis_panels_topichubs_render_insert_get_default_panes function
 */
function topichubs_panels_default_panes_desc_topichubs() {
  
  if( function_exists('panels_context_create') )  {
    return array(
      array(
        'type'     =>'custom',
        'sub_type' =>'custom', 
        'name'     =>'Overview',
        'configuration' => array(
          'title' =>'Overview',
          'body'  => 'You can edit this description of a Topic Hub to detail any information you find most relevant.',
        ),
        'panel'=>'left'
      ),
      array(
        'type'     =>'panels_mini',
        'sub_type' =>'Most Recent', 
        'name'     =>'Most Recent',
        'configuration' => array(),
        'panel'=>'left',
      ),
      array(
        'type'     =>'panels_mini',
        'sub_type' =>'Most Viewed', 
        'name'     =>'Most Viewed',
        'configuration' => array(),
        'panel'=>'middle',
      ),
      array(
        'type'     =>'panels_mini',
        'sub_type' =>'Related Tpoics', 
        'name'     =>'Related Topics',
        'configuration' => array(),
        'panel'=>'middle',
      ),
      array(
        'type'     =>'panels_mini',
        'sub_type' =>'Recent Comments', 
        'name'     =>'Recent Comments',
        'configuration' => array(),
        'panel'=>'right',
      ),
      array(
        'type'     =>'panels_mini',
        'sub_type' =>'Most Comments', 
        'name'     =>'Most Comments',
        'configuration' => array(),
        'panel'=>'right',
      ),
      array(
        'type'     =>'panels_mini',
        'sub_type' =>'Top Contributors', 
        'name'     =>'Top Contributors',
        'configuration' => array(),
        'panel'=>'right',
      ),
      array(
        'type'     =>'panels_mini',
        'sub_type' =>'Locations', 
        'name'     =>'Locations',
        'configuration' => array(),
        'panel'=>'top',
      ),

    );
  }
  else {
  return array(
      array(
        'type'     =>'custom',
        'sub_type' =>'custom', 
        'name'     =>'Overview',
        'configuration' => array(
          'title' =>'Overview',
          'body'  => 'You can edit this description of a Topic Hub to detail any information you find most relevant.',
        ),
        'panel'=>'left'
      ),
      array(
        'type'     =>'topichubs',
        'sub_type' =>'Most Recent', 
        'name'     =>'Most Recent',
        'configuration' => array(),
        'panel'=>'left',
      ),
      array(
        'type'     =>'topichubs',
        'sub_type' =>'Most Viewed', 
        'name'     =>'Most Viewed',
        'configuration' => array(),
        'panel'=>'middle',
      ),
      array(
        'type'     =>'topichubs',
        'sub_type' =>'Related Tpoics', 
        'name'     =>'Related Topics',
        'configuration' => array(),
        'panel'=>'middle',
      ),
      array(
        'type'     =>'topichubs',
        'sub_type' =>'Recent Comments', 
        'name'     =>'Recent Comments',
        'configuration' => array(),
        'panel'=>'right',
      ),
      array(
        'type'     =>'topichubs',
        'sub_type' =>'Most Comments', 
        'name'     =>'Most Comments',
        'configuration' => array(),
        'panel'=>'right',
      ),
      array(
        'type'     =>'topichubs',
        'sub_type' =>'Top Contributors', 
        'name'     =>'Top Contributors',
        'configuration' => array(),
        'panel'=>'right',
      ),
      array(
        'type'     =>'topichubs',
        'sub_type' =>'Locations', 
        'name'     =>'Locations',
        'configuration' => array(),
        'panel'=>'top',
      ),

    );
 
  }

}

/**
 * Implementation of hook_topichubs_render_delete().
 */
function topichubs_panels_topichubs_render_delete($nid) {
  panels_node_delete($node);
}

/**
 * Implementation of hook_topichubs_render_update().
 */
function topichubs_panels_topichubs_render_update($node) {
  panels_node_update($node);
}

/**
 * Implementation of hook_topichubs_render_view().
 */
function topichubs_panels_topichubs_render_view(&$node, $teaser = FALSE, $page = FALSE) {
  panels_load_include('plugins');
  if ($teaser) {
    // Do the standard view for teaser.
    $node = node_prepare($node, $teaser);
  }
  else {
    $display = panels_load_display($node->panels_node['did']);
    $display->css_id = $node->panels_node['css_id'];
    // TODO: Find a way to make sure this can't node_view.
    // check to see of panels_context_create (panels 2) exists
    // else use panels_node_get_context (panels 3 this might also 
    // work with panels 2)
    if( function_exists('panels_context_create') )  {
      $display->context = array('panel-node' => panels_context_create('node', $node));
    }
    else {
      $display->context = panels_node_get_context($node);
    }

    $node->content['body'] = array(
      '#value' => panels_render_display($display),
      '#weight' => 0,
    );
  }

  return $node;
}
