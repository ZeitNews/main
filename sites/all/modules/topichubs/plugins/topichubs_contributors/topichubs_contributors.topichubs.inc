<?php

/**
 *  
 */
class topichubs_plugin_contributors extends topichub_sql_plugin {

  function settings_form(&$form, &$form_state) {
    $options = array();
    $result = db_query("SELECT uid, name from {users}");
    while($item = db_fetch_object($result)) {
      $options[$item->uid] = $item->name;
    }

    $form['topichubs_contrib_ignore'] = array(
      '#type' => 'select',
      '#title' => t('Ignore the following'),
      '#options' => $options,
      '#multiple' => true,
      '#default_value' => variable_get('topichubs_contrib_ignore', 1),
      '#description' => t('Selected Users will not appear as contributors'),
    );
  }

  function options_form(&$form, &$form_state) {
    $this->add_types_field($form, $form_state);
    $form['author_count'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of Authors to return'),
      '#description' => t('Set the maximum number of Top Contributors to be displayed on the Topic Hub\'s 
page.'),
      '#size' => 4,
      '#maxlength' => 4,
      '#default_value' => $this->settings['author_count'] ? $this->settings['author_count'] : 5,
    );
  }  
    
  function execute() {
    $authors = $this->get_authors();
    $hub_data = array(
      '#values' => $authors,
      '#view' => theme(array("topichubs_contributors__{$this->node->nid}", 'topichubs_contributors'), $this->node, $authors),
    );
    return $hub_data;
  }
  
  /**
   * Find the <em>x</em> most published authors for this topic hub.
   */
  function get_authors() {
    $ignore = variable_get('topichubs_contrib_ignore', array());
        
    $node_alias = 'n';
    $term_joins = $this->get_term_where($node_alias);    
    $args = $term_joins['args'];

    $type_where = $this->get_content_type_where($this->get_types_setting(), $node_alias);    
    $args = array_merge($args, $type_where['args']);
    
    $sql .= "SELECT u.uid, u.name, u.picture, count(*) as node_count";
    $sql .= " FROM {users} u";
    $sql .= " JOIN {node} n ON n.uid = u.uid";
    $sql .= implode(' ', $term_joins['joins']);
    $sql .= " WHERE u.status = 1 AND n.status = 1";
    $sql .= " AND " . $term_joins['where'];
    $sql .= " AND " . $type_where['where'];
    if(!empty($ignore)) {
      $sql .= " AND u.uid NOT IN (" . db_placeholders($ignore, 'int') . ")";
      $args = array_merge($args, array_values($ignore));
    }
    $sql .= " GROUP BY u.uid";
    $sql .= " ORDER BY node_count DESC";

    $count = (int)$this->get_setting('author_count', 5);
    if($count > 0) {
      $result = db_query_range($sql, $args, 0, $count);
    }
    else {
      $result = db_query($sql, $args);
    }
    
    $results = array();
    while ($contributor = db_fetch_object($result)) {
      if(empty($contributor->picture)) {
        $contributor->picture = variable_get('user_picture_default', '');
      }
      $results[] = $contributor;
    }
    return $results;
  }
}
