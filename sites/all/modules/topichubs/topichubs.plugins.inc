<?php
// $Id: topichubs.plugins.inc,v 1.1.2.1 2009/09/02 12:00:20 inadarei Exp $
/**
 * @file
 *
 * Provides the basic plugin definition used by plugins.
 */

/**
 * Find all topichub plugins defined in all modules. A plugin is defined
 * by 'plugin_name' => array(options)
 *
 * Plugin name should be unique across all plugins. Otherwise the last one 
 * will win and override the previous.
 *
 * Options for plugin arrays are:
 *    - title: Required. The title/name of the plugin
 *    - description: Optional. A description that may be used somewhere.
 *    - handler: Required. The class that extends topichub_plugin.
 *    - path: Optional. The path to the file containing the handler class. 
 *            Defaults to plugins/<em>plugin_name</em>
 *    - file: Options. The filename for the plugin handler. 
 *            Defaults to <em>handlername</em>.inc
 */
function topichubs_discover_plugins() {
  static $cache;
  
  // Get plugins from all modules.
  foreach (module_implements('topichubs_plugins') as $module) {
    $function = $module . '_topichubs_plugins';
    $result = $function();
    if (!is_array($result)) {
      continue;
    }

    $module_dir = drupal_get_path('module', $module);
    foreach ($result as $plugin => $def) {
      $def['module'] = $module;
      
      if (!isset($def['file'])) {
        $def['file'] = $def['module'] . '.topichubs.inc';
      }
      if (!isset($def['theme path'])) {
        $def['theme path'] = $module_dir;
      }
      // merge the new data in
      $cache[$plugin] = $def;
    }
  }
  return $cache;  
}

/**
* Look up plugin implementation class by plugin name (human readable one).
**/
function topichubs_lookup_plugin_by_name($name) {
  static $plugins_map;
  
  if (!empty($plugins_map)) {
    if (!empty($plugins_map[$name])) {
      return $plugins_map[$name];
    } else {
      return NULL;
    }
  }
  
  $plugins = topichubs_discover_plugins();
  $p_map = array();
  if (is_array($plugins)) {
    foreach ($plugins as $key => $plugin) {
      $impl = new StdClass();
      $impl->type = $key;
      $impl->def = $plugin;
      
      $p_map[$plugin['title']] = $impl;
    }
    $plugins_map = $p_map;
    if (!empty($p_map[$name])) {
      return $p_map[$name];
    } else {
      return NULL;
    }    
  } else {
    return NULL;
  }
}

/**
 * Instantiate an instance of the handler class for the provided plugin definition.
 *
 * @param $definition
 *      A plugin definition as specified in hook_topichubs_plugins
 *
 * @see hook_topichubs_plugins
 * @see topichubs_topichubs_plugins
 */
function _topichubs_new_handler_class($definition) {
  $module_dir = drupal_get_path('module', $definition['module']);
  $filename = $module_dir;
  if(isset($definition['path'])) {
    $filename .= '/' . $definition['path'];
  }
  $filename .= '/' . $definition['file'];
  
  if (file_exists($filename)) {
    require_once $filename;
    if(class_exists($definition['handler'])) {
      return new $definition['handler'];
    }
  }
  
  return NULL;
}

/**
 * Base class to provide a common interface for all plugins.
 */
class topichub_plugin {
  
  var $type;
  var $conf;
  var $node;
  var $topichub;
  var $settings;

  /**
   * Initialize the plugin with the topichub node and any settings previously saved.
   */
  function init($type, $conf, &$node, $settings) {
    $this->type = $type;
    $this->conf = $conf;
    $this->node = $node;
    $this->topichub = $node->topichub;
    $this->settings = $settings;
  }

  /**
   * Provide a form for configuring default settings.
   */
  function settings_form(&$form, &$form_state) { }

  /**
   * Validate the default settings.
   */
  function settings_validate($form, &$form_state) { }
  
  /**
   * Provide a form for setting per topichub options.
   */
  function options_form(&$form, &$form_state) { }

  /**
   * Validate the options_form.
   */
  function options_validate($form, &$form_state) { }

  /**
   * Execute the plugin.
   *
   * @return
   *   The results of this topichub plugin.
   */
  function execute() { return array(); }

  /**
   * Set a form error, make sure the right path is set so the proper field is highlighted.
   */
  function form_error($key, $msg) {
    form_set_error("topichub][config][$this->type][$key]", $msg);
  }
  
  /**
   * Get a value form the plugin settings
   *
   * @param $key
   *    The setting key
   * @param $default
   *    The value to use if the setting
   */
  function get_setting($key, $default, $allow_empty = FALSE) {
    if($allow_empty) {
      return $this->settings && isset($this->settings[$key]) ? $this->settings[$key] : $default;
    }
    
    return $this->settings && !empty($this->settings[$key]) ? $this->settings[$key] : $default;
  }
  
  function get_global_default_types() {
    return variable_get('topic_hub_plugin_type_default' , array());
  }  
  
  /**
   * Get the content type settings.
   */
  function get_types_setting() {
    $types = $this->get_setting('types', array());
    return array_filter(array_values($types));
  }
  
  /**
   * Build a plugin form.
   *
   * @param $form_type
   *    The type of plugin form to build (corresponds to a plugin function like options_form, etc)
   * @param $form
   *    The form to add to
   * @param $form_state
   *    The current form state
   */
  function build_form($form_type, &$form, &$form_state) {
    $form_method = "{$form_type}_form";
    if(method_exists($this, $form_method)) {
      $plugin_form = array();
      $this->$form_method($plugin_form, $form_state);
      if(!empty($plugin_form)) {
        $form[$this->type] = array(
          '#type' => 'markup',
          '#title' => t($this->conf['title']),
        );
    	  $form[$this->type] = array_merge($form[$this->type], $plugin_form);
      }
    }
  }
  
  /**
   * Add a field to specify desired node types.
   */
  function add_types_field(&$form, &$form_state) {
    $types = node_get_types();
    foreach ($types as $type => $info) {
      $options[$type] = $info->name;
    }
    
    $form['types'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Node Types to Include'),
      '#description' => t('Choose which node types are eligible for inclusion in the Locations Mentioned map.'),
      '#options' => $options,
      '#default_value' => $this->settings['types'] ? $this->settings['types'] : $this->get_global_default_types(),
    );
  }  

  /**
   * Add a field to specify a node count.
   */
  function add_count_field(&$form, &$form_state) {
    $form['count'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of nodes to return'),
      '#description' => t('Select the maximum number of nodes to be displayed.'),
      '#size' => 4,
      '#maxlength' => 4,
      '#default_value' => $this->settings['count'] ? $this->settings['count'] : 10,
    );
  }    
}

/**
 * Base class for plugins that use Views.
 */
class topichub_views_plugin extends topichub_plugin {
  
  var $view;
  
  function init($type, $conf, &$node, $settings) {
    parent::init($type, $conf, $node, $settings);
    $view_name = $this->get_view_name();
    $this->view = views_get_view($view_name);
  }
  
  /**
   * Get the name of the view this plugin uses.
   *
   * @return 
   *    The view name for this plugin
   */
  function get_view_name() {}
 
  /**
   * Add Content Type filter to the View
   *
   * @param $types
   *    The content types
   * @param $display
   *    The view display on which to add the filter
   */
  function add_content_type_filter($types, $display = 'block_1') {
    if(!empty($types)) {
      $this->view->add_item($display, 'filter', 'node', 'type', array('value' => $types, 'relationship' => 'nid'));
    }
  }

  /**
   * Add per page item count to the view.
   *
   * @param $count
   *    The number of items to display
   * @param $display
   *    The view display on which to add the count
   */
  function set_items_per_page($count, $display = 'block_1') {
    $this->view->set_display($display);
    $view_display = $this->view->display[$display];
    $view_display->handler->set_option('items_per_page', $count);
  }
  
  /**
   * Add Topic Hub Expression filter to the View
   *
   * @param $display
   *    The view display on which to add the filter
   */
  function add_topichub_filter($display = 'block_1') {
    if($this->node->topichub->conditions) {
      $this->view->add_item($display, 'filter', 'topichub', 'nid', array('value' => $this->node->nid));
    }
  } 
  
  /**
   * Run the view.
   *
   * @param $display
   *    The view display to run
   * @return
   *    An array containing the raw results and the formatted results
   */
  function execute_view($display = 'block_1') {
    $content = $this->view->preview($display, array($this->node->nid));
    $hub_data = array(
      '#values' => $view->result,
      '#view' => $content,
    );
    return $hub_data;
  }  
}

/**
 * Base class for plugins that create their own SQL.
 * Provide some convenience functions where possible for common operations.
 */
class topichub_sql_plugin extends topichub_plugin {
  
  /**
   * Add Content Type filter to the View
   *
   * @param $types
   *    The content types
   * @param $display
   *    The view display on which to add the filter
   */
  function get_term_where($node_alias = 'n') {
    $joins = array();
    $wheres = array();
    $args = array();
    
    foreach($this->topichub->conditions as $tids) {
      $where_terms = array();
      foreach($tids as $tid) {
        $alias = 'term_node' . count($joins);
        $joins[] = " JOIN {term_node} $alias ON {$node_alias}.nid = $alias.nid";
        $where_terms[] = "$alias.tid = %d";
        $args[] = $tid;        
      }
      $wheres[] = '(' . implode(' AND ', $where_terms) . ')';      
    }
    $where_clause = '(' . implode(' OR ', $wheres) . ')';
    
    return array(
      'joins' => $joins, 
      'where' => $where_clause, 
      'args' => $args,
    );
  }
  
  /**
   * Add Content Type filter to the query
   *
   * @param $types
   *    The content types
   * @param $node_alias
   *    The the alias used for the node table
   */
  function get_content_type_where($types, $node_alias = 'n') {
    $where = '1=1';
    $args = $types;
    
    if(!empty($types)) {
      $where = " {$node_alias}.type IN (" . db_placeholders($types, 'varchar') . ")";
    }
    
    return array(
      'where' => $where, 
      'args' => $args,
    );
  }
  
  
}
