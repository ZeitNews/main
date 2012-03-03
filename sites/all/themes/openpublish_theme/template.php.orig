<?php
// $Id: template.php,v 1.1.2.6 2010/08/16 18:38:48 tirdadc Exp $

function openpublish_theme_theme() {
  return array(
    // The form ID.
    'search_theme_form' => array(
      // Forms always take the form argument.
      'arguments' => array('form' => NULL),
    ),
  );
}

function openpublish_theme_search_theme_form($form) {
  $output = '<div id="search" class="clearfix">';
  unset($form['submit']);
  unset($form['search_theme_form']['#title']);
  $form['submit'] = array(
    '#type' => 'submit',
    '#name' => 'op', 
    '#prefix' => '<div id="top-search-button">',
    '#suffix' => '</div>',
    '#button_type' => 'submit',
    '#value' => t('search'), 
    '#submit' => TRUE,
   
  );
  $output .= drupal_render($form);
  $output .= '</div>';
  return $output;
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return 
 *   a string containing the breadcrumb output.
 */
function openpublish_theme_breadcrumb($breadcrumb) {
  return theme('op_breadcrumb', $breadcrumb);
}


/**
 * Override or insert PHPTemplate variables into the templates.
 */
function openpublish_theme_preprocess_page(&$vars) {
  // Override core Blog module's breadcrumb
  if ($vars['node']->type == 'blog') {
    $breadcrumb = array(
      l(t('Home'), NULL),
      l(t('Blogs'), 'blogs'),
    );
    if ($vars['node']->field_op_author[0]['view']) {
      $breadcrumb[] = $vars['node']->field_op_author[0]['view'];
    }
    $vars['breadcrumb'] = theme('op_breadcrumb', $breadcrumb);
  }
  
  $vars['tabs2'] = menu_secondary_local_tasks();

  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */
function openpublish_theme_menu_local_tasks() {
  return menu_primary_local_tasks();
}

function openpublish_theme_comment_submitted($comment) {
  return t('by <strong>!username</strong> | !datetime',
    array(
      '!username' => theme('username', $comment),
      '!datetime' => format_date($comment->timestamp)
    ));
}

function openpublish_theme_node_submitted($node) {
  return t('by <strong>!username</strong> | !datetime',
    array(
      '!username' => theme('username', $node),
      '!datetime' => format_date($node->created),
    ));
}


/**
 * Adds even and odd classes to <li> tags in ul.menu lists
 */ 
function openpublish_theme_menu_item($link, $has_children, $menu = '', $in_active_trail = FALSE, $extra_class = NULL) {
  static $zebra = FALSE;
  $zebra = !$zebra;
  $class = ($menu ? 'expanded' : ($has_children ? 'collapsed' : 'leaf'));
  if (!empty($extra_class)) {
    $class .= ' '. $extra_class;
  }
  if ($in_active_trail) {
    $class .= ' active-trail';
  }
  if ($zebra) {
    $class .= ' even';
  }
  else {
    $class .= ' odd';
  }
  return '<li class="'. $class .'">'. $link . $menu ."</li>\n";
}
