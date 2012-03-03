<?php
// $Id: node.inc,v 1.2.2.13.2.2 2009/10/01 19:18:36 nancyw Exp $

/**
 * @file
 * @brief Content management filter node operations file,
 *
 * This file contains all the node functions used by the module.
 *
 */

/**
 * Defines the form for nodes administration filter results.
 *
 * @ingroup forms
 *
 * @return array with forms properties
 */
function cmf_admin_nodes_form() {
  global $user;
  $destination = drupal_get_destination();
  $lang_codes = array('' => t('Neutral'));
  if (module_exists('locale')) {
    $locale_available = TRUE;
    $lang_codes += locale_language_list('name');
  }
  else {
    $locale_available = FALSE;
  }

  // Build an 'Update options' form.
  if (user_access('filter and manage site content')) {
    $form['options'] = array(
      '#type' => 'fieldset', '#title' => t('Update options'),
      '#prefix' => '<div class="container-inline">', '#suffix' => '</div>',
      );
    $options = array();
    foreach (module_invoke_all('node_operations') as $operation => $array) {
      $options[$operation] = $array['label'];
    }
    $form['options']['operation'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => 'approve',
      );
    $form['options']['submit'] = array('#type' => 'submit', '#value' => t('Update'));
  }

  // Load the nodes that we want to display.
  $form['header'] = array(
    '#type'  => 'value',
    '#value' => cmf_build_header(),
    );

  $result = cmf_perform_query($form['header']['#value']);
  // Build a table listing the appropriate nodes.
  while ($node = db_fetch_object($result)) {
    $nodes[$node->nid] = '';

    if ($_SESSION['cmf_show_nid']) {
      $form['cmf_id'][$node->nid] = array('#value' => l($node->nid, 'node/'. $node->nid, array('attributes' => array('title' => t('Node !nid', array('!nid' => $node->nid))))));
    }

    // Don't mark it if it is the current user.
    $mark = $node->uid == $user->uid ? NULL: ' '. theme('mark', node_mark($node->nid, $node->changed));
    $form['title'][$node->nid] = array(
      '#value' => l($node->title, 'node/'. $node->nid, array(
        'attributes' => array('title' => check_plain($node->body),
        ),
      'fragment' => 'node-'. $node->nid)) . $mark);

    $form['kind'][$node->nid] = array('#value' => _cmf_get_img('node', t('node')));

    $form['type'][$node->nid] = $node->type == 'forum' ? array('#value' => '<p title="'.
      _cmf_get_forum($node->nid) .'">'. check_plain(node_get_types('name', $node)) .'</p>') :
        array('#value' =>  check_plain(node_get_types('name', $node)));

    if (!(arg(0) == 'user' && is_numeric(arg(1)) && arg(1) > 0)) {
      $form['username'][$node->nid] = array('#value' => theme('cmf_user', $node->uid));
    }

    $status = array();
    $status[] = $node->status ? t('published') : t('not published');
    if ($node->promote) {
      $status[] = t('promoted');
    }
    // >0 allows for sticky-encoded weighting.
    if ($node->sticky > 0) {
      $status[] = t('sticky');
    }
    if ($node->moderate) {
      $status[] = t('moderated');
    }
    $form['status'][$node->nid] = array('#value' => implode(', ', $status));

    $form['created'][$node->nid] = array('#value' => format_date($node->created, 'small'));

    if (user_access('filter and manage site content')) {
      $form['operations'][$node->nid] = array('#value' => l(_cmf_get_img('edit', t('edit')) .' '.
        t('edit'), 'node/'. $node->nid .'/edit', array('query' => $destination, 'html' => TRUE)));
    }

    if ($locale_available) {
      $form['language'][$node->nid] = array('#value' => $lang_codes[$node->language]);
    }
  }

  if (user_access('filter and manage site content')) {
    $form['nodes'] = array('#type' => 'checkboxes', '#options' => $nodes);
  }
  $form['pager'] = array('#value' => theme('pager', NULL, $_SESSION['cmf_max_rows'], 0));

  return $form;
}

/**
 * Form validation before submit.
 * We can't execute any 'Update options' if no nodes were selected.
 *
 * @ingroup forms
 *
 * @param the ID of the passed form
 * @param array with the form properties values
 */
function cmf_admin_nodes_form_validate($form, &$form_state) {
  $nodes = array_filter($form_state['values']['nodes']);
  if (count($nodes) == 0) {
    form_set_error('', t('No items selected.'));
  }
}

/**
 * Handle post-validation form submission. \n
 * Execute the chosen 'Update option' on the selected nodes, such as
 * publishing, unpublishing, promotion and stickness status or deleting.
 *
 * @ingroup forms
 *
 * @param the ID of the passed form
 * @param array with the form properties values
 */
function cmf_admin_nodes_form_submit($form, &$form_state) {
  $operations = module_invoke_all('node_operations');
  $operation = $operations[$form_state['values']['operation']];
  // Filter out unchecked nodes.
  $nodes = array_filter($form_state['values']['nodes']);
  if ($function = $operation['callback']) {
    // Add in callback arguments if present.
    if (isset($operation['callback arguments'])) {
      $args = array_merge(array($nodes), $operation['callback arguments']);
    }
    else {
      $args = array($nodes);
    }
    call_user_func_array($function, $args);

    cache_clear_all();
    drupal_set_message(t('The update has been performed.'));

    if (arg(0) == 'user' && is_numeric(arg(1)) && arg(1) > 0) {
      $form_state['redirect'] = 'user/'. arg(1) .'/cmf';
    }
    else {
      $form_state['redirect'] = 'admin/content/filter';
    }
  }
}

/**
 * Theme results table.
 *
 * @ingroup themable
 *
 * @return table with filter results.
 */
function theme_cmf_admin_nodes_form($form) {
  $rows = array();
  $output = drupal_render($form['options']);
  if (isset($form['title']) && is_array($form['title'])) {
    foreach (element_children($form['title']) as $key) {
      $row = array();
      if (user_access('filter and manage site content')) {
        $row[] = drupal_render($form['nodes'][$key]);
      }
      if ($_SESSION['cmf_show_nid']) {
        $row[] = drupal_render($form['cmf_id'][$key]);
      }
      $row[] = drupal_render($form['title'][$key]);
      $row[] = drupal_render($form['kind'][$key]);
      $row[] = drupal_render($form['type'][$key]);
      if (!(arg(0) == 'user' && is_numeric(arg(1)) && arg(1) > 0)) {
        $row[] = drupal_render($form['username'][$key]);
      }
      $row[] = drupal_render($form['status'][$key]);
      $row[] = drupal_render($form['created'][$key]);
      if (isset($form['language'][$key])) {
        $row[] = drupal_render($form['language'][$key]);
      }
      if (user_access('filter and manage site content')) {
        $row[] = drupal_render($form['operations'][$key]);
      }
      $rows[] = $row;
    }
  }
  else {
    $rows[] = array(array('data' => t('Filter returned no results.'), 'colspan' => '7'));
  }

  $output .= theme('table', $form['header']['#value'], $rows, array());
  if ($form['pager']['#value']) {
    $output .= drupal_render($form['pager']);
  }

  $output .= drupal_render($form);

  return $output;
}
