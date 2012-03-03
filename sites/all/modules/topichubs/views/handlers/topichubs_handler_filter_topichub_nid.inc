<?php
//$Id: topichubs_handler_filter_topichub_nid.inc,v 1.1.2.1 2009/09/02 12:00:22 inadarei Exp $
/**
 * @file
 */
 
class topichubs_handler_filter_topichub_nid extends views_handler_filter {

  /**
   * Determine if a filter can be exposed.
   */
  function can_expose() { return FALSE; }

  /**
   * Supply an edit form for the Filter.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $hubs = array();
    $result = db_query("SELECT n.nid, n.title FROM {node} n WHERE n.type = 'topichub'");
    while($node = db_fetch_object($result)) {
      $hubs[$node->nid] = $node->title;
    }

    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Topic Hub'),
      '#options' => $hubs,
      '#default_value' => $this->options['value'],
      '#description' => t('Select the Topic Hub filter.  This will use the taxonomy expression built for the Topic Hub and filter the content based on that expression.'),
    ); 
  }

  /**
   * Display the value of the Filter selection in the Views edit screens.
   */
  function admin_summary() {
    $nid = $this->value;
    if(!empty($nid)) {
      $node = node_load($nid);
      return check_plain((string) $this->operator) . ' ' . $node->title;
    }
    return parent::admin_summary();
  }

  /**
   * Modify the query by building the topichub expression as an extension of the current view.
   */
  function query() {
    $nid = $this->value;
    if(!$nid || empty($nid))
      return;

    $node = new stdClass;
    $node->nid = $nid;
    topichub_load($node);
    $conditions = $node->topichub->conditions;

    if(is_array($conditions)) {
      $args = array();
      $wheres = array();
      foreach($conditions as $tids) {
        $where_terms = array();
        foreach($tids as $tid) {
          $alias = $this->add_table('term_node');
          $where_terms[] = "$alias.$this->real_field = %d";
          $args[] = $tid;        
        }
        $wheres[] = '(' . implode(' AND ', $where_terms) . ')';
      }
      
      $where_clause = '(' . implode(' OR ', $wheres) . ')';
      $this->query->add_where(0, $where_clause, $args);
    }    
  }
  
  /**
   * Override default behavior to find the right relationship if needed
   *
   * @param $table
   *    The table we want to join into this query
   * @return
   *    The alias used to join this table
   */
  function add_table($table) {
    $alias = $this->query->add_table($table);
    
    if(!$alias) { // Table was not added, lets find a relationship back to node to use
      $join = views_get_table_join($table, 'node');
      foreach ($this->query->relationships as $relation_alias => $relation) {
        if($relation['table'] == 'node') {
          $alias = $this->query->add_table($table, $relation_alias, $join);
          break;
        }
      }
    }
    
    return $alias;
  }
  
}
 
 