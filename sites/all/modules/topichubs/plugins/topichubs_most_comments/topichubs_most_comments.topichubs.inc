<?php

/**
 * List content by comment count
 */
class topichubs_plugin_most_comments extends topichub_views_plugin {

  function get_view_name() {
    return 'topichub_most_comments';
  }
  
  function options_form(&$form, &$form_state) {
    $this->add_types_field($form, $form_state);
    $this->add_count_field($form, $form_state);
  }  
    
  function execute() {
    $types = $this->get_types_setting();
    $this->add_content_type_filter($types);
    
    $count = $this->get_setting('count', 10);
    $this->set_items_per_page($count);

    return $this->execute_view();
  }
}