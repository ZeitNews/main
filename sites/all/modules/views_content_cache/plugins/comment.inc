<?php

class views_content_cache_key_comment extends views_content_cache_key {
  function options_form($value) {
    return array(
      '#title' => t('Comments'),
      '#description' => t('Checks for new or updated comments'),
      '#type' => 'checkboxes',
      '#options' => array(
        'changed' => t('New or updated comments'),
      ),
      '#default_value' => $value,
    );
  }

  function content_key($object, $object_type) {
    if ($object_type === 'comment') {
      return 'changed';
    }
  }
}
