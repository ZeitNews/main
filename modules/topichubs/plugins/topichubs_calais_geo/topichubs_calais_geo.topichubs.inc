<?php
/**
 * @file topichubs_calais_geo.topichubs.inc
 */
 
/**
 * Requires Calais Geo Module 
 */
class topichubs_plugin_calais_geo extends topichub_sql_plugin {

  function options_form(&$form, &$form_state) {
    
    $geo_vocabs = variable_get('calais_geo_vocabularies', array());
    $all_vocabs = calais_get_entity_vocabularies();
    foreach($geo_vocabs as $vid) {
      $vocab_options[$vid] = array_search($vid, $all_vocabs);
    }
    
    $this->add_types_field($form, $form_state);
    $form['vocab'] = array(
      '#type' => 'select',
      '#title' => t('Vocabulary to Map'),
      '#description' => t('Choose a vocabulary whose terms should be used to plot/represent each node 
shown in the Locations Mentioned map.'),
      '#options' => $vocab_options,
      '#default_value' => $this->settings['vocab'] ? $this->settings['vocab'] : array(),
    );
    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Map width'),
      '#default_value' => $this->settings['width'],
      '#size' => 10,
      '#maxlength' => 10,
      '#description' => t('The default width of a Google map, as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>. Leave blank to use the defaults.'),
    );   
    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Map height'),
      '#default_value' => $this->settings['height'],
      '#size' => 10,
      '#maxlength' => 10,
      '#description' => t('The default height of the map, expressed as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>. Leave blank to use the defaults.'),
    );
  }  
    
  function execute() {
    $items = $this->get_nodes_by_term();

    $markers = array();
    if($items && count($items) > 0) {
      foreach ($items as $tid => $item) {
        $term = calais_get_term(NULL, $tid);

        $nodes = array();
        foreach ($item['#nodes'] as $node) {
          $nodes[] = l($node->title, "node/$node->nid");
        }

        $marker = array(
          'text' => theme('topichubs_calais_geo_marker', $term, $nodes),
          'latitude' => floatval($term->extra['latitude']),
          'longitude' => floatval($term->extra['longitude']),
        );
        $markers[] = $marker;
      }
    }

    $content = $this->build_map($markers);
    $hub_data = array(
      '#values' => $result,
      '#view' => $content,
    );
    return $hub_data;
  }

  /**
   * Run the query to find relevant nodes, grouped by the terms of the selected vocabulary.
   */
  function get_nodes_by_term() {
    $vid = $this->get_setting('vocab', 0);
    $args = array($vid);

    $node_alias = 'n';
    $term_joins = $this->get_term_where($node_alias);    
    $args = array_merge($args, $term_joins['args']);

    $type_where = $this->get_content_type_where($this->get_types_setting(), $node_alias);    
    $args = array_merge($args, $type_where['args']);
    
    $sql .= "SELECT DISTINCT(n.nid), n.title, ct.tid";
    $sql .= " FROM {node} {$node_alias}";
    $sql .= implode(' ', $term_joins['joins']);
    $sql .= " JOIN {term_node} tn2 ON {$node_alias}.nid = tn2.nid ";
    $sql .= " JOIN {calais_term} ct ON ct.tdid = tn2.tid AND ct.vid = %d";
    $sql .= " WHERE {$node_alias}.status = 1 AND ct.resolved_type = 'geo'";
    $sql .= " AND " . $term_joins['where'];
    $sql .= " AND " . $type_where['where'];
    //$sql .= " AND n.created >= %d AND n.created <= %d";
    $sql .= " ORDER BY {$node_alias}.created DESC";
    $results = db_query($sql, $args);
    
    while($node = db_fetch_object($results)) {
      $items[$node->tid]['#nodes'][] = $node;
    }
    return $items;
  }
  
  /**
   * Build the gmap array.
   */
  function build_map($markers) {
    $settings = array(
      'markers' => $markers,
      'behavior' => array('autozoom' => TRUE),
    );

    list($lat, $lon) = calais_geo_calc_map_center($markers);
    $settings['latitude'] = $lat;
    $settings['longitude'] = $lon;
    if(!empty($this->settings['width'])) {
      $settings['width'] = $this->settings['width'];
    }
    if(!empty($this->settings['height'])) {
      $settings['height'] = $this->settings['height'];
    }
        
    $map_data = array(
      '#settings' => $settings,
    );
    return theme('gmap', $map_data);    
  }  
}
