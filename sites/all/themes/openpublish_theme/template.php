<?php
// $Id: template.php,v 1.1.2.6 2010/08/16 18:38:48 tirdadc Exp $

/**
 * Implementation of hook_theme()
 *
 * Register theme functions here.
 */
  
function openpublish_theme_theme() {
  return array(
    // The form ID.
    'search_theme_form' => array(
      // Forms always take the form argument.
      'arguments' => array('form' => NULL),
      // Uses only theme_search_theme_form instead of template and preprocess.
    ),
    // Originally themed by the generic theme_form (use devel themer to see).
    'user_register' => array(
      'arguments' => array('form' => NULL),
      'template' => 'forms/user-register',
    ),
  );
}

/**
 * Implementation of theme_search_theme_form()
 *
 * The output of the theme function search_theme_form registered above.
 * No template and hence no preprocess function is used.
 */
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
 * Implementation of theme_preprocess_form()
 *
 * The output of the theme function user_register registered above.
 * Adds variables to user-register.tpl.php.
 */
function openpublish_theme_preprocess_user_register(&$vars) {
  $vars['form_items'] = drupal_render($vars['form']);
}

/**
 * Implementation of theme_breadcrumb()
 *
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
 * Implementation of theme_menu_local_tasks(), theme_comment_submitted(),
 * theme_node_submitted()
 *
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
* Implementation of theme_username()
*
* Removes "not verified" from anonymous comments, etc..
*/
function openpublish_theme_username($object) {

  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables.
    if (drupal_strlen($object->name) > 20) {
      $name = drupal_substr($object->name, 0, 15) . '...';
    }
    else {
      $name = $object->name;
    }
  
    if (user_access('access user profiles')) {
      $output = l($name, 'user/' . $object->uid, array('attributes' => array('title' => t('View user profile.'))));
    }
    else {
      $output = check_plain($name);
    }
  }
  else if ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if (!empty($object->homepage)) {
      $output = l($object->name, $object->homepage, array('attributes' => array('rel' => 'nofollow')));
    }
    else {
      $output = check_plain($object->name);
    }
  }
  else {
    $output = check_plain(variable_get('anonymous', t('Anonymous')));
  }
  
  return $output;
}

/**
 * Implementation of theme_menu_item()
 *
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

/**
* Implementation of theme_preprocess_page()
*
* Strict breadcrumb control. Everything's not possible with Custom Breadcrumbs mod.
* And some extra page bits.
*/
function openpublish_theme_preprocess_page(&$vars) {
  $allow_bread = array('article', 'audio', 'video', 'slideshow', 'project', 'event', 'resource');
  if (arg(0) == 'taxonomy') {
    // Removes breadcrumbs from Categories vocab because menu displays hierarchy.
    $term = taxonomy_get_term(arg(2));
    $vid = $term->vid;
    if ($vid == 43) {
      unset($vars['breadcrumb']);
    }
  } elseif ($vars['node']->type == 'blog') {
      // Change blog node breadcrumbs to suit Viewpoints?
      $breadcrumb = array(l(t('Viewpoints'), 'viewpoints'),);
      if ($vars['node']->field_op_author[0]['view']) {
        $breadcrumb[] = l($vars['node']->field_op_author[0]['safe']['title'], 'blog/' . $vars['node']->uid);
      }
      $vars['breadcrumb'] = theme('op_breadcrumb', $breadcrumb);
  } elseif (arg(0) == 'blog' && is_numeric(arg(1))) {
      // Allow breadcrumbs for blog user pages.
      return;
  } elseif (in_array($vars['node']->type, $allow_bread)) {
      // Allow breadcrumbs for node types listed above.
      return;
  } else {
      // Get rid of all other breadcrumbs.
      unset($vars['breadcrumb']);
  }
  
  // Inject secondary tabs in user profile pages.
  $vars['tabs2'] = menu_secondary_local_tasks();
  
  // Change profile wording due to Content Profile.
  if (arg(0) == 'user') {
    $vars['tabs2'] = str_replace('Account</a>', 'Profile (1)</a>', $vars['tabs2']);
    $vars['tabs2'] = str_replace('Profile</a>', 'Profile (2)</a>', $vars['tabs2']);
  }

  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
* Implementation of theme_preprocess_node()
*
* Creates the "Add new comment" link at the bottom of posts, when print $links is not being used.
*/
function openpublish_theme_preprocess_node(&$vars) {
  if($vars['node']->links['comment_add']){
    $vars['add_new_comment'] = '<div class="add-comment">';
    $vars['add_new_comment'] .=  l(
      $vars['node']->links['comment_add']['title'], $vars['node']->links['comment_add']['href'], array(
        'attributes' => array(
          'class' => 'comment-add', 'title' => $vars['node']->links['comment_add']['attributes']['title']
        ),
        'fragment' => 'comment-form'
      )
    );
    $vars['add_new_comment'] .= '</div>';
  }
}

/**
* Implementation of theme_preprocess_views()
*
* Adds additional fields to all feeds that use teasers.
*/
function openpublish_theme_preprocess_views_view_row_rss__feed(&$vars) {
  $node = node_load($vars['row']->nid, NULL, TRUE);
  //$vars['node'] = $node;
  //http://api.drupal.org/api/drupal/modules--node--node.module/function/node_load/6#comment-69
  //$node = menu_get_object('node', 1, 'node/' . $vars['row']->nid);
  
  $vars['node_teaser_image'] = l(theme('imagecache', 'teaser_image_rss', $node->field_thumbnail_image[0]['filepath'], $node->title, $node->title, array('height' => 180, 'width' => 180, 'align' => right, 'hspace' => 10, 'vspace' => 10, 'border' => 0)), $node->path, array('html' => TRUE, 'absolute' => TRUE, 'attributes' => array('target' => '_blank')));
  
  $vars['node_deck'] = $node->field_deck[0]['value'];
  
  $specific_feeds = array('articles', 'projects', 'events', 'resources');
  if (!in_array(arg(0), $specific_feeds)) {
    // NOT a feed where listing type is unnecessary.
    if ($node->type != 'blog') {
      // Not a blog teaser because we do special things with that below.
      $vars['node_type'] = ucfirst($node->type);
    }
    elseif (arg(0) != 'blog' && arg(3) != 'feed') {
      // NOT a viewpoints/jane-doe/feed (blog/7/0/feed) where listing type/author is unnecessary.
      $vars['node_type'] = l($node->name . '&rsquo;s Viewpoint', 'blog/' . $node->uid, array('html' => TRUE, 'absolute' => TRUE, 'attributes' => array('target' => '_blank')));
    }
  }
  
  if ($node->type == 'event') {
    $vars['event_date'] = content_format('field_event_date', $node->field_event_date[0]);
  }
  
  $vars['node_teaser'] = strip_tags($node->teaser) . ' ' . l(t('More') . ' &raquo;', $node->path, array('html' => TRUE, 'absolute' => TRUE, 'attributes' => array('target' => '_blank')));
}

/**
* Implementation of theme_preprocess_views()
*
* Adds additional fields to the full text feed.
*/
function openpublish_theme_preprocess_views_view_row_rss__feed_3(&$vars) {
  $node = node_load($vars['row']->nid, NULL, TRUE);
  //$vars['node'] = $node;
  
  $vars['node_deck'] = $node->field_deck[0]['value'];
  
  if ($node->type != 'blog') {
    // Not a blog teaser because we do special things with that below.
    $vars['node_type'] = ucfirst($node->type);
    
    if ($node->field_op_author[0]['nid']) {
      $str_author = '';
      foreach ($node->field_op_author as $author) {
        $str_author .= module_invoke('content', 'format', 'field_op_author', $author) . ', ';
      }
      global $base_url;
      $vars['authors'] = str_replace('<a href="', '<a target="_blank" href="' . $base_url, trim($str_author, ', '));
    }
  
    $nodes_with_cats = array('article', 'audio', 'video', 'slideshow');
    if (in_array($node->type, $nodes_with_cats) && !empty($node->taxonomy)) {
      $cats = array();
      foreach ($node->taxonomy as $term) {
        if ($term->vid == 43) {
          $cats[] = l($term->name, 'taxonomy/term/' . $term->tid, array('attributes' => array('rel' => 'tag', 'target' => '_blank'), 'absolute' => TRUE));
        }
      }
      usort($cats, "glue_module_term_compare");
      $vars['categories'] = implode(' &raquo; ', $cats);
    }
  }
  else {
    // NOT a viewpoints/jane-doe/feed where listing type/author is unnecessary.
    $vars['node_type'] = l($node->name . '&rsquo;s Viewpoint', 'blog/' . $node->uid, array('html' => TRUE, 'absolute' => TRUE, 'attributes' => array('target' => '_blank')));
  }
  
  if ($node->type == 'event') {
    $vars['event_date'] = content_format('field_event_date', $node->field_event_date[0]);
  }
  
  $find_tags = array('<iframe', '<object');
  $tag_mods = array('<iframe align="left" clear="both" hspace="10" vspace="10" border="0"', '<object align="left" clear="both" hspace="10" vspace="10" border="0"');
  
  switch ($node->type) {
    case 'video':
      if ($node->field_video_embed_code[0]['value']) {
        $vars['video_code'] = str_replace($find_tags, $tag_mods, $node->field_video_embed_code[0]['value']);
      }
    break;
    
    case 'audio':
      if ($node->field_audio_file[0]) {
        $vars['audio_mp3'] = '<p>Download: ' . l($node->field_audio_file[0]['filename'], $node->field_audio_file[0]['filepath'], array('attributes' => array('target' => '_blank'), 'absolute' => TRUE)) . '</p>';
      }
      elseif ($node->field_audio_embed_code[0]['value']) {
        $vars['audio_code'] = str_replace($find_tags, $tag_mods, $node->field_audio_embed_code[0]['value']);
      }
    break;
    
    case 'slideshow':
      $vars['slideshow'] = '<sub>' . l(t('Slideshows can only be viewed on the site.'), $node->path, array('attributes' => array('target' => '_blank'), 'absolute' => TRUE)) . '</sub>';
    break;
  }
  
  // Can't do style for some reason - gets stripped.
  $find_tags_body = array('<img', '<iframe', '<object', '<table', '<a');
  $tag_mods_body = array('<img align="right" hspace="10" vspace="10" border="0"', '<iframe align="right" hspace="10" vspace="10" border="0"', '<object align="right" hspace="10" vspace="10" border="0"', '<table align="right" hspace="10" vspace="10"', '<a target="_blank"');
  
  $vars['node_body'] = str_replace($find_tags_body, $tag_mods_body, $node->body);
  
  if ($node->comment == 2 && $node->comment_count > 0) {
    $vars['add_comment'] = l(t('Add new comment') . ' &raquo', $node->path, array('attributes' => array('target' => '_blank'), 'absolute' => TRUE, 'html' => TRUE, 'fragment' => 'comments'));
  } elseif ($node->comment == 2) {
    $vars['add_comment'] = l(t('Add new comment') . ' &raquo', 'comment/reply/' . $node->nid, array('attributes' => array('target' => '_blank'), 'absolute' => TRUE, 'html' => TRUE, 'fragment' => 'comment-form'));
  }

}

/**
 * Implementation of module_preprocess_semanticviews_view_fields
 *
 * ??
 */
define ('OPENPUBLISH_THEME_MULTIPLE_AUTHORS', '#MUTLIPLE#');

function openpublish_theme_preprocess_semanticviews_view_fields(&$vars) { 
  $view = $vars['view'];
  $view_names = array('articles', 'blogs', 'multimedia');
  
  if (!in_array($view->name, $view_names)) {
    return;
  }
  
  if (!empty($vars['fields']['title_2']) && $vars['fields']['title_2']->content == OPENPUBLISH_THEME_MULTIPLE_AUTHORS) {
    $vars['fields']['title_1']->content .= ', ' . t('et al');
    unset($vars['fields']['title_2']);
  }  
}

/**
 * Implementation of module_preprocess_views_view_field.
 * 
 * Adds RDFa properties to certain field level tags.
 */
function openpublish_theme_preprocess_views_view_field(&$vars) {
  $view = $vars['view'];
  $view_names = array('articles', 'blogs', 'multimedia');
  
  if (!in_array($view->name, $view_names)) {
    return;
  }
  
  switch ($vars['field']->real_field) {
    case 'title':
      // Author node title
      if (strpos($vars['field']->field_alias, 'op_author') !== FALSE) {
        $vars['rdfa_author'] = _openpublish_get_rdfa_author($vars['row']->node_node_data_field_op_author_title, $vars['row']->node_node_data_field_op_author_nid);        
      }
      else {
        // Article node title
        $vars['rdfa_title'] = _openpublish_get_rdfa_title($vars['row']->node_title, $vars['row']->nid);
      }
      break;

    case 'created':
      $vars['rdfa_created'] = _openpublish_get_rdfa_date($vars['row']->node_created, $vars['field']->original_value);
      break;
      
    default:
      $vars['output'] = $vars['field']->advanced_render($vars['row']);
      break;
  } 
}

/**
 * Implementation of template_preprocess_views
 *
 * ??
 */
function openpublish_theme_preprocess_views_view_unformatted(&$vars) {
  $view     = $vars['view'];
  $rows     = $vars['rows'];
  $view_names = array('articles', 'blogs', 'multimedia', 'events', 'projects', 'resources');

  if (!in_array($view->name, $view_names)) {
    return;
  }
  
  $vars['classes'] = array();
  // Set up striping values.
  foreach ($rows as $id => $row) {
    $vars['rdfa_about_links'][$id] = url('node/' . $view->result[$id]->nid);
    
    $row_classes = array();
    $row_classes[] = 'views-row';
    $row_classes[] = 'views-row-' . ($id + 1);
    $row_classes[] = 'views-row-' . ($id % 2 ? 'even' : 'odd');
    if ($id == 0) {
      $row_classes[] = 'views-row-first';
    }
    if ($id == count($rows) -1) {
      $row_classes[] = 'views-row-last';
    }
    // Flatten the classes to a string for each row for the template file.
    $vars['classes'][$id] = implode(' ', $row_classes);
  }
}

/**
 * Implementation of template_preprocess_views
 *
 * ??
 */
function openpublish_theme_preprocess_views_view_field__noderelationships_noderef__name(&$vars) {
  $row = $vars['row'];
  $vars['username_linked'] = l(check_plain($row->users_name), 'user/'. $row->users_uid, array('attributes' => array('title' => t('View user profile.'), 'target' => '_blank')));
}

/**
* Implementation of theme_preprocess_views()
*
* Adds array to view template of Archive page for use in
* views-view-field--multimedia--page-2--created.tpl.php.
*/
function openpublish_theme_preprocess_views_view_field__multimedia__page_2__created(&$vars) {
  $vars['dateless_nodes'] = array('event', 'project', 'resource');
}

/**
* Implementation of theme_preprocess_views()
*
* Adds array to view template of Archive page for use in
* views-view-field--multimedia--page-2--tagorder-1.tpl.php.
*/
function openpublish_theme_preprocess_views_view_field__multimedia__page_2__tagorder_1(&$vars) {
  $vars['tag_only_nodes'] = array('event', 'project', 'resource', 'blog');
}

/**
* Implementation of theme_preprocess_views()
*
* Adds comma separated full location names (province & country).
*/
function openpublish_theme_preprocess_views_view_field__users__page_2__nothing(&$vars) {
  $row = $vars['row'];
  $location_country_name = location_country_name($row->location_country);
  $location_province_name = location_province_name($row->location_country, $row->location_province);
  
  if ($row->location_city || $location_province_name || $location_country_name) {
    $locations = array($row->location_city, $location_province_name, $location_country_name);
    foreach ($locations as $value) {
      if (!empty($value)) {
        $locations_known[] = $value;
      }
    }
    $vars['row']->location = implode(", ", $locations_known);
  } else {
    $vars['row']->location = 'Location Unknown';
  }
}

/**
* Implementation of theme_preprocess()
*
* Tweak user-profile.tpl.php, including Content Profile vars. See CP's README
* for more theming info. content_profile_load is how you load everything.
*/
function openpublish_theme_preprocess_user_profile(&$vars) {
  $vars['cp_vars'] = content_profile_load('profile', $vars['account']->uid);
  
  if ($vars['cp_vars']->vid && $vars['cp_vars']->taxonomy) {
    $weights = array();
    // tagorder.module creates these tables.
    $result = db_query("SELECT tid, weight FROM {tagorder} WHERE vid = %d ORDER BY weight", $vars['cp_vars']->vid);
    while ($data = db_fetch_object($result)) {
      $vars['tagorder_taxonomy'][$data->tid]['tid'] = $data->tid;
      $vars['tagorder_taxonomy'][$data->tid]['name'] = $vars['cp_vars']->taxonomy[$data->tid]->name;
      $vars['tagorder_taxonomy'][$data->tid]['weight'] = $data->weight;
    }
    $fields_of_expertise = array();
    foreach($vars['tagorder_taxonomy'] as $term) {
      // taxonomy_term_path($vars['cp_vars']->taxonomy[$term['tid']])
      $fields_of_expertise[] = l($term['name'], 'users', array('query' => 'tid[]=' . $term['tid'], 'attributes' => array('rel' => 'tag')));
    }
    $vars['fields_of_expertise'] = implode(', ', $fields_of_expertise);
  }
  
  $account = $vars['account'];

  if ($account->location['city'] || $account->location['province_name'] || $account->location['country_name']) {
    $locations_known = array();
    if ($account->location['city']) {
      $locations_known[] = l($account->location['city'], 'users', array('query' => 'city=' . $account->location['city'], 'attributes' => array('rel' => 'tag')));
    }
    if ($account->location['province_name']) {
      // If there is a province, there should be a country (not selectable otherwise).
      // Can't filter by province without country.
      $locations_known[] = l($account->location['province_name'], 'users', array('query' => 'country[]=' . $account->location['country'] . '&province=' . $account->location['province_name'], 'attributes' => array('rel' => 'tag')));
    }
    if ($account->location['country_name']) {
      $locations_known[] = l($account->location['country_name'], 'users', array('query' => 'country[]=' . $account->location['country'], 'attributes' => array('rel' => 'tag')));
    }
    $vars['locations'] = implode(", ", $locations_known);
  }
  
}

/**
* Implementation of theme_preprocess_views()
*
* Adds links to Author node Fields of Expertise terms.
*/
function openpublish_theme_preprocess_views_view_field__author_biography__block_1__tagorder(&$vars) {
  $fields_of_expertise = array();
  foreach ($vars['field']->items as $values) {
    $tids = array_keys($values);
    foreach ($values as $value) {
      $fields_of_expertise[] = l($value, 'authors', array('query' => 'tid[]=' . array_shift($tids), 'attributes' => array('rel' => 'tag')));
    }
  }
  $vars['fields_of_expertise'] = implode(', ', $fields_of_expertise);
}
