<?php

/**
 *  
 */
class topichubs_plugin_related_topics extends topichub_plugin {

  function options_form(&$form, &$form_state) {
    $hubs = $this->find_all_other_hubs();
    $options = array();
    foreach ($hubs as $hub) {
      $options[$hub->nid] = $hub->title;
    }

    $form['hubs'] = array(
      '#type' => 'select',
      '#title' => t('Other Related Topic Hubs'),
      '#description' => t('Select Topic Hubs that are similar to this one.'),
      '#options' => $options,
      '#size' => 5,
      '#multiple' => TRUE,
      '#default_value' => $this->settings['hubs'] ? $this->settings['hubs'] : array(),
    );
  }  
    
  function execute() {
    if(!empty($this->settings['hubs'])) {
      $hids = array_keys($this->settings['hubs']);
      $sql = "SELECT * FROM {node} WHERE nid IN (" . db_placeholders($hids, 'int') . ") AND status = 1";
      $result = db_query($sql, $hids);
      while($hub = db_fetch_object($result)) {
        $hubs[] = $hub;
      }
    }

    $hub_data = array(
      '#values' => $hubs,
      '#view' => theme(array("topichubs_related_topics__{$this->node->nid}", 'topichubs_related_topics'), $this->node, $hubs),
    );
    return $hub_data;
  } 
  
  /**
   * Find all topic hubs in the database that are published.
   */
  function find_all_other_hubs() {
    $hubs = array();
    $result = db_query("SELECT n.nid, n.title FROM {node} as n WHERE n.type = 'topichub' AND n.status = 1 AND n.nid != %d", $this->node->nid);
    while ($topichub = db_fetch_object($result)) {
      $hubs[] = $topichub;
    }
    return $hubs;
  } 
}
