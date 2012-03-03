<?php

/**
 * @file
* Administration interface for nodewords_custom_pages.module.
 */

/**
 * Show the confirmation form for the page meta tags delete operation.
 */
function nodewords_custom_pages_confirm_delete(&$form_state, $page) {
  $form['pid'] = array(
    '#type' => 'value',
    '#value' => $page->pid,
  );

  return confirm_form($form,
    t('Are you sure you want to delete the meta tags for the page %name?', array('%name' => $page->name)),
    'admin/content/nodewords/custom',
    NULL,
    t('Delete')
  );
}

/**
 *
 */
function nodewords_custom_pages_confirm_delete_submit($form, &$form_state) {
  nodewords_delete_tags(
    array('type' => NODEWORDS_TYPE_PAGE, 'id' => $form_state['values']['pid'])
  );

  if (db_affected_rows()) {
    drupal_set_message(t('The configuration options have been saved.'), 'status');
  }

  $form_state['redirect'] = 'admin/content/nodewords/custom';
}

/**
 * Return the list of pages with custom meta tags settings.
 */
function nodewords_custom_pages_overview() {
  $enabled = array();
  $form = array('#tree' => TRUE);
  $pages = array();

  foreach (nodewords_custom_pages_load_all(FALSE) as $pid => $page) {
    $pages[$pid] = '';

    if ($page->enabled) {
      $enabled[] = $pid;
    }

    $form['name'][$pid] = array(
      '#value' => $page->name,
    );

    $form['path'][$pid] = array(
      '#type' => 'value',
      '#value' => $page->path,
    );

    $form['weight'][$pid] = array(
      '#type' => 'weight',
      '#delta' => 10,
      '#default_value' => $page->weight,
    );
  }

  if (!empty($pages)) {
    $form['enabled'] = array(
      '#type' => 'checkboxes',
      '#options' => $pages,
      '#default_value' => $enabled,
      '#checkall' => (TRUE && count($pages) > 1) ? 'nodewords-pages-overview-enabled' : FALSE,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save')
    );
  }

  return $form;
}

function nodewords_custom_pages_overview_submit($form, &$form_state) {
  $row = new stdClass();

  foreach ($form_state['values']['path'] as $pid => $value) {
    $row->pid = $pid;
    $row->path = $form_state['values']['path'][$pid];
    $row->weight = $form_state['values']['weight'][$pid];
    $row->enabled = $form_state['values']['enabled'][$pid] ? 1 : 0;

    drupal_write_record('nodewords_custom', $row, 'pid');
    $done = TRUE;
  }

  if (isset($done)) {
    drupal_set_message(t('The configuration options have been saved.'));
  }
}

/**
 *
 */
function nodewords_custom_pages_edit($form_state, $page = NULL) {
  $form = array();

  if (!isset($page)) {
    $page = (object) array(
      'name' => t('Custom page'),
      'path' => '',
      'weight' => 0,
      'enabled' => 1,
      'tags' => array(),
    );
  }
  else {
    $form['pid'] = array(
      '#type' => 'value',
      '#value' => $page->pid,
    );
  }

  $nodewords_form = nodewords_tags_edit_fields(
    array('type' => NODEWORDS_TYPE_PAGE, 'id' => isset($page->pid) ? $page->pid : 0),
    $page->tags,
    array(
      'fieldset' => FALSE,
      'admin' => TRUE,
    )
  );

  if (empty($nodewords_form)) {
    $form['warning'] = array(
      '#value' => t('You have not yet enabled any <a href="@url">meta tags for administrative settings pages</a>.', array('@url' => url('admin/content/nodewords'))),
      '#prefix' => '<div class="messages warning">',
      '#suffix' => '</div>',
    );
    return $form;
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t("A name to better identify the page in the list of custom pages. The name must contains at least one alpha-numeric character."),
    '#default_value' => $page->name,
    '#maxlength' => 60,
    '#required' => TRUE,
  );

  $form['path'] = array(
    '#type' => 'textarea',
    '#title' => t('Path'),
    '#description' => t("Enter the Drupal paths associated with the page. The character <q>*</q> is a wildcard. Example paths are <em>blog</em> for the blog page, <em>blog/*</em> for every personal blog, and <em>&lt;front></em> for the front page. The list must contain at least one path."),
    '#default_value' => $page->path,
    '#wysiwyg' => FALSE,
    '#required' => TRUE,
  );

  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#description' => t('Pages with lower weight will be considered first. Only the first matching page will be used.'),
    '#delta' => 10,
    '#default_value' => $page->weight,
  );

  $form['enabled'] = array(
    '#type' => 'radios',
    '#options' => array(t('Disabled'), t('Enabled')),
    '#default_value' => $page->enabled,
  );

  $form['nodewords'] = $nodewords_form;
  $form['nodewords']['#tree'] = TRUE;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Validate function for the meta tags edit page.
 */
function nodewords_custom_pages_edit_validate($form, &$form_state) {
  if (trim($form_state['values']['name']) == '') {
    form_set_error('name', t('The name contains only spaces, and other not printable characters.'));
  }

  if (($path = trim($form_state['values']['path'])) != '') {
    $bool = db_result(
      db_query_range("SELECT 1 FROM {nodewords_custom} WHERE path = '%s' AND pid <> %d",
        $path,
        isset($form_state['values']['pid']) ? $form_state['values']['pid'] : 0,
        0, 1
      )
    );

    if ($bool) {
      form_set_error('path', t('The path is already used.'));
    }

    // Meta tags will not be output on administration pages.
    $paths = preg_split('/[\r\n]+/', $path, 0, PREG_SPLIT_NO_EMPTY);
    foreach ($paths as $path) {
      if (drupal_match_path($path, 'admin/*')) {
        if (!form_get_error($form['path'])) {
          form_set_error('path', t('You cannot assign the path %path since meta tags are not output on administration paths.', array('%path' => $path)));
        }
        else {
          drupal_set_message(t('You cannot assign the path %path since meta tags are not output on administration paths.', array('%path' => $path)), 'error');
        }
      }
    }
  }
  else {
    form_set_error('path', t('The path contains only spaces, and other not printable characters.'));
  }
}

/**
 * Submission function for the meta tags edit page.
 */
function nodewords_custom_pages_edit_submit($form, &$form_state) {
  $form_state['values']['path'] = trim($form_state['values']['path']);

  $row = new stdClass();

  if (!empty($form_state['values']['pid'])) {
    $row->pid = $form_state['values']['pid'];
  }

  $row->name = $form_state['values']['name'];
  $row->path = $form_state['values']['path'];
  $row->weight = $form_state['values']['weight'];
  $row->enabled = $form_state['values']['enabled'];

  drupal_write_record('nodewords_custom', $row, !empty($row->pid) ? array('pid') : array());
  nodewords_save_tags($form_state['values']['nodewords']['metatags'], array(
    'type' => NODEWORDS_TYPE_PAGE, 'id' => $row->pid,
  ));

  drupal_set_message(t('The configuration options have been saved.'));

  $form_state['values']['pid'] = $row->pid;
  $form_state['redirect'] = 'admin/content/nodewords/custom';
}

/**
 * Render the list of pages with meta tags.
 */
function theme_nodewords_custom_pages_overview($form) {
  $has_pages = isset($form['name']) && is_array($form['name']);
  $rows = array();

  if ($has_pages) {
    foreach (element_children($form['name']) as $key) {
      $row = array();
      $row[] = drupal_render($form['name'][$key]);

      $form['weight'][$key]['#attributes']['class'] = 'page-weight';

      $row[] = drupal_render($form['weight'][$key]);
      $row[] = drupal_render($form['enabled'][$key]);
      $row[] = l(t('edit'), "admin/content/nodewords/custom/$key/edit");
      $row[] = l(t('delete'), "admin/content/nodewords/custom/$key/delete");

      $rows[] = array(
        'data' => $row,
        'class' => 'draggable',
      );
    }
  }

  if (empty($rows)) {
    $rows[] = array(
      array(
        'data' => t('There are currently no meta tags defined.'),
        'colspan' => '5',
      )
    );
  }

  $header[] = t('Name');
  $header[] = t('Weight');

  $header[] = array(
    'data' => t('Enabled'),
    'class' => (TRUE && count($rows) > 1) ? 'nodewords-pages-overview-enabled' : '',
  );

  $header[] = array(
    'data' => t('Operations'),
    'colspan' => '2',
  );

  drupal_add_tabledrag('nodewords', 'order', 'sibling', 'page-weight');

  return theme('table', $header, $rows, array('id' => 'nodewords')) . drupal_render($form);
}
