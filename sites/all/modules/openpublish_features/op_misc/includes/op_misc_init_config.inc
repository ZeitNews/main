<?php

/**
* Pre-populate topics vocabulary
*/
function _op_misc_prepopulate_topics_vocabulary($vid) {
  if ($vid && is_numeric($vid)) {
    $topics = array('Business', 'Health', 'Politics', 'Technology');
    $sub_terms = array(
      'Business' => array('Finance', 'Markets', 'Personal Finance', 'Management'),
      'Healthcare' => array('Medicine', 'Fitness', 'Nutrition'),
      'Technology' => array('Internet', 'Gadgets', 'Biotech', 'Social Media', 'Gaming'),
      'Politics' => array('Local', 'National', 'International'),
    );
    $weight = 0;
    foreach ($topics as $topic) {
      $weight++;
      $form_values = array(
        'vid' => $vid,
        'name' => $topic,
        'weight' => $weight,
      );
      taxonomy_save_term($form_values);
      
      // Get the parent tid
      $parent_tid = $form_values['tid'];
      
      // Child terms
      $child_weight = 0;
      foreach ($sub_terms[$topic] as $child_term) {
        $child_weight++;
        $form_values = array(
          'vid' => $vid,
          'name' => $child_term,
          'parent' => $parent_tid,
          'weight' => $child_weight,
        );
        taxonomy_save_term($form_values); 
      }
    } 
  } 
}
