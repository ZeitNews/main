<?php

class views_filters_selective_exposed_form_plugin extends views_plugin_exposed_form_basic {
  function summary_title() {
    return t('Selective Exposed Filters');
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['vfs'] = array('default' => array());
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Go through each filter and add the same options we used to add in hook_form_alter()
    foreach ($this->display->handler->get_handlers('filter') as $label => $filter) {
      if (!$filter->options['exposed']) continue;
      $vfs_options[$label] = views_filters_selective_form_views_ui_config_item_form_alter_do(
        $filter,
        $this->options['vfs'][$label], 
        $this->view, 
        'edit-exposed-form-options-' . (isset($form['#type']) && $form['#type'] == 'fieldset' ? 'views-filters-selective-' : '') . 'vfs-' . str_replace('_', '-', $label) . '-vfs-selective',
        TRUE
      );
    }

    $form['vfs'] = $vfs_options;
  }

  function exposed_form_alter(&$form, &$form_state) {
    parent::exposed_form_alter($form, $form_state);
    views_filters_selective_form_views_exposed_form_alter_do($form, $form_state, $this->options['vfs']);
  }
}

