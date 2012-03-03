<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

 */
/**
 * @file
 */

/**
 * Settings form to configure which Calais vocabularies are presented for mapping
 */
function calais_geo_settings_form() {
  $node_options = array();
  foreach(node_get_types() as $key => $type) {
    $node_options[$key] = $type->name;
  }

  $form['calais_geo_nodes_enabled'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Which types should allow calais geo terms to be added to a map'),
    '#default_value' => variable_get('calais_geo_nodes_enabled', array_keys($node_options)),
    '#options' => $node_options,
    '#description' => t('Check the node types that will display the Calais geo node fieldset.'),
  );

  $entities = calais_get_entity_vocabularies();

  $form['calais_geo_vocabularies'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Which Calais Vocabularies do you want available for geomapping?'),
    '#default_value' => variable_get('calais_geo_vocabularies', $entities),
    '#options' => array_flip($entities),
    '#description' => t("Choose which vocabulary's terms can be used to represent markers in a map display (this is a node-specific selection available in the Locations field group on the node's edit page."),
  );
  
  return system_settings_form($form);
}
