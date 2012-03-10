<?php
// $Id: both.inc,v 1.2.2.11.2.2 2009/10/01 19:18:36 nancyw Exp $

/**
 * @file
 * @brief Content management filter "both" operations file
 *
 * This file contains all the "both" functions used by the module.
 *
 */

/**
 * Defines the form for mixed content administration filter results.
 *
 * @ingroup forms
 *
 * @return array with forms properties
 */
function cmf_admin_both_form() {
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
      '#prefix' => '<div class="container-inline">', '#suffix' => '</div>'
      );
    $form['options']['operation'] = array(
      '#type' => 'select',
      '#options' => array(
        'publish' => t('Publish'),
        'unpublish' => t('Unpublish'),
        'delete' => t('Delete'),
        ),
      '#default_value' => 'publish'
      );
    $form['options']['submit'] = array('#type' => 'submit', '#value' => t('Update'));
  }

  // Load the objects that we want to display.
  $form['header'] = array(
    '#type'  => 'value',
    '#value' => cmf_build_header(),
    );

  $result = cmf_perform_query($form['header']['#value']);
  // Build a table listing the appropriate objects.
  while ($object = db_fetch_object($result)) {
    if ($object->cid == 0) {
      $objects['n-'. $object->nid] = '';

      if ($_SESSION['cmf_show_nid']) {
        $form['cmf_id']['n-'. $object->nid] = array('#value' => l($object->nid, 'node/'. $object->nid, array('attributes' => array('title' => t('Node !nid', array('!nid' => $object->nid))))));
      }

      $mark = $object->uid == $user->uid ? NULL: ' '. theme('mark', node_mark($object->nid, $object->changed));
      $form['title']['n-'. $object->nid] = array(
        '#value' => l($object->title, 'node/'. $object->nid, array(
          'attributes' => array('title' => check_plain($object->body)),
          'fragment' => 'node-'. $object->nid,
          )
        ) . $mark,
      );

      $form['kind']['n-'. $object->nid] = array('#value' => _cmf_get_img('node', t('node')));

      $form['type']['n-'. $object->nid] = $object->type == 'forum' ? array('#value' => '<p title="'.
        _cmf_get_forum($object->nid) .'">'. check_plain(node_get_types('name', $object)) .'</p>') :
          array('#value' =>  check_plain(node_get_types('name', $object)));

      if (!(arg(0) == 'user' && is_numeric(arg(1)) && arg(1) > 0)) {
        $form['username']['n-'. $object->nid] = array('#value' => theme('cmf_user', $object->uid));
      }

      $status = array();
      $status[] = $object->status ? t('published') : t('not published');
      if ($object->promote) {
        $status[] = t('promoted');
      }
      if ($object->sticky > 0) {  // >0 allows for sticky-encoded weighting.
        $status[] = t('sticky');
      }
      if ($object->moderate) {
        $status[] = t('moderated');
      }
      $form['status']['n-'. $object->nid] = array('#value' => implode(', ', $status));

      $form['created']['n-'. $object->nid] = array('#value' => format_date($object->created, 'small'));

      if ($locale_available) {
        $form['language']['n-'. $object->nid] = array('#value' => $lang_codes[$object->language]);
      }

      if (user_access('filter and manage site content')) {
        $form['operations']['n-'. $object->nid] = array('#value' => l(_cmf_get_img('edit',
          t('edit')) .' '. t('edit'), 'node/'. $object->nid .'/edit', array('query' => $destination, 'html' => TRUE)));
      }
    }
    else{
      $objects['c-'. $object->cid] = '';

      if ($_SESSION['cmf_show_nid']) {
        $form['cmf_id']['c-'. $object->cid] = array('#value' => l($object->nid, 'node/'. $object->nid, array(
          'attributes' => array('title' => t('Node !nid, Comment !cid', array('!nid' => $object->nid, '!cid' => $object->cid))),
          'fragment' => 'comment-'. $object->cid)));
      }

      $form['title']['c-'. $object->cid] = array('#value' => l($object->title, 'node/'. $object->nid,
        array('attributes' => array('title' => check_plain($object->comment)),
        'fragment' => 'comment-'. $object->cid)));

      $form['kind']['c-'. $object->cid] = array('#value' => _cmf_get_img('comment', t('comment')));

      $form['type']['c-'. $object->cid] = $object->type == 'forum' ? array('#value' => '<p title="'.
        _cmf_get_forum($object->nid) .'">'. theme('cmf_type', $object->type) .'</p>') :
          array('#value' =>  theme('cmf_type', $object->type));

      if (!(arg(0) == 'user' && is_numeric(arg(1)) && arg(1) > 0)) {
        $form['username']['c-'. $object->cid] = array('#value' => theme('cmf_user', $object->uid));
      }

      $form['status']['c-'. $object->cid] =  array('#value' =>  ($object->status ? t('not published') : t('published')));

      $form['created']['c-'. $object->cid] = array('#value' => format_date($object->created, 'small'));

      if (user_access('filter and manage site content')) {
        $form['operations']['c-'. $object->cid] = array('#value' => l(_cmf_get_img('edit',
          t('edit')) .' '. t('edit'), 'comment/edit/'. $object->cid, array('query' => $destination, 'html' => TRUE)));
      }
    }
  }

  if (user_access('filter and manage site content')) {
    $form['objects'] = array('#type' => 'checkboxes', '#options' => $objects);
  }
  $form['pager'] = array('#value' => theme('pager', NULL, $_SESSION['cmf_max_rows'], 0));

  return $form;
}

/**
 * Form validation before submit.
 * We can't execute any 'Update options' if no objects were selected.
 *
 * @ingroup forms
 *
 * @param the ID of the passed form
 * @param array with the form properties values
 */
function cmf_admin_both_form_validate($form, &$form_state) {
  $form_state['values']['objects'] = array_diff($form_state['values']['objects'], array(0));
  if (count($form_state['values']['objects']) == 0) {
    form_set_error('', t('No items selected.'));
    drupal_goto('admin/content/filter');
  }
}

/**
 * Handle post-validation form submission.
 * Execute the chosen 'Update option' on the selected objects, such as
 * publishing, unpublishing or deleting.
 *
 * @ingroup forms
 *
 * @param the ID of the passed form
 * @param array with the form properties values
 */
function cmf_admin_both_form_submit($form, &$form_state) {
  // Query building.
  switch ($form_state['values']['operation']) {
    case 'publish':
        $node_query    = 'UPDATE {node} SET status = 1 WHERE nid = %d';
        $comment_query = 'UPDATE {comments} SET status = '. COMMENT_PUBLISHED .' WHERE cid = %d';
      break;
    case 'unpublish':
        $node_query    = 'UPDATE {node} SET status = 0 WHERE nid = %d';
        $comment_query = 'UPDATE {comments} SET status = '. COMMENT_NOT_PUBLISHED .' WHERE cid = %d';
      break;
    case 'delete':
        $node_query    = 'DELETE FROM {node} WHERE nid = %d';
        $comment_query = 'DELETE FROM {comments} WHERE cid = %d';
      break;
  }

  // Perform queries.
  foreach ($form_state['values']['objects'] as $flag) {
    if ($flag) {
      $object = explode('-', $flag);
      $kind   = $object[0];
      $value  = $object[1];

      if ($kind == 'n') {
        db_query($node_query, $value);
      }
      elseif ($kind == 'c') {
        // Perform the update action, then refresh node statistics.
        db_query($comment_query, $value);
        $comment = _comment_load($value);
        _comment_update_node_statistics($comment->nid);
        // Allow modules to respond to the updating of a comment.
        comment_invoke_comment($comment, $form_state['values']['operation']);
      }
    }
  }
  cache_clear_all();
  drupal_set_message(t('The update has been performed.'));

  if (arg(0) == 'user' && is_numeric(arg(1)) && arg(1) > 0) {
    $form_state['redirect'] = 'user/'. arg(1) .'/cmf';
  }
  else {
    $form_state['redirect'] = 'admin/content/filter';
  }
}

/**
 * Theme results table.
 *
 * @ingroup themable
 *
 * @return table with filter results
 */
function theme_cmf_admin_both_form($form) {
  $output = drupal_render($form['options']);

  if (isset($form['title']) && is_array($form['title'])) {
    foreach (element_children($form['title']) as $key) {
      $row = array();
      if (user_access('filter and manage site content')) {
        $row[] = drupal_render($form['objects'][$key]);
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

  $output .= theme('table', $form['header']['#value'], $rows);
  if ($form['pager']['#value']) {
    $output .= drupal_render($form['pager']);
  }

  $output .= drupal_render($form);

  return $output;
}
