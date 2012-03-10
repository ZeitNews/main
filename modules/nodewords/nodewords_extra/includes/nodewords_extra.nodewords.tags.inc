<?php

/**
 * @file
 * Nodewords support file.
 */

/**
 * Set the form fields used to implement the options for the meta tag.
 */
function nodewords_extra_dc_contributor_form(&$form, $content, $options) {
  $form['dc.contributor'] = array(
    '#tree' => TRUE,
  );

  $form['dc.contributor']['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Dublin Core contributor'),
    '#description' => t('Enter the name of an entity responsible for making contributions to the resource. Examples of a contributor include a person, an organization, or a service.') . $options['description'],
    '#default_value' => empty($content['value']) ? (!empty($options['default']['dc.contributor']['value']) ? $options['default']['dc.contributor']['value'] : '') : $content['value'],
    '#maxlength' => variable_get('nodewords_max_size', 350),
  );
}

/**
 * Set the meta tag content.
 */
function nodewords_extra_dc_contributor_prepare(&$tags, $content, $options) {
  if (!empty($content['value'])) {
    $tags['dc.contributor'] = nodewords_replace_tokens($content['value'], $options);
  }
}

/**
 * Set the form fields used to implement the options for the meta tag.
 */
function nodewords_extra_dc_creator_form(&$form, $content, $options) {
  $form['dc.creator'] = array(
    '#tree' => TRUE,
  );

  $form['dc.creator']['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Dublin Core creator'),
    '#description' => t('Enter the name of an entity primarily responsible for making the resource. Examples of a creator include a person, an organization, or a service.') . $options['description'],
    '#default_value' => empty($content['value']) ? (!empty($options['default']['dc.creator']['value']) ? $options['default']['dc.creator']['value'] : '') : $content['value'],
    '#maxlength' => variable_get('nodewords_max_size', 350),
  );
}

/**
 * Set the meta tag content.
 */
function nodewords_extra_dc_creator_prepare(&$tags, $content, $options) {
  if (!empty($content['value'])) {
    $tags['dc.creator'] = nodewords_replace_tokens($content['value'], $options);
  }
}

/**
 * Set the form fields used to implement the options for the meta tag.
 */
function nodewords_extra_dc_date_form(&$form, $content, $options) {
  $form['dc.date'] = array(
    '#tree' => TRUE,
  );

  if (isset($content['value']) && is_array($content['value'])) {
    // Support the older date form element value.
    $content['value'] = $content['value']['day'] . ' ' . $content['value']['month'] . ' ' . $content['value']['year'];
  }

  $form['dc.date']['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Dublin Core date'),
    '#description' => t('Enter day, month, and year in this order, separated by a space; a invalid date will not be used. The timezone is UTC.') . $options['description'],
    '#default_value' => isset($content['value']) ? $content['value'] : '',
  );
}

/**
 * Check if the meta tag content is empty.
 */
function nodewords_extra_dc_date_is_empty($content) {
  if (!empty($content['value'])) {
    if (is_array($content['value'])) {
      // Support the older date form element value.
      return FALSE;
    }
    else {
      $parts = preg_split('/\s+/', $content['value'], -1, PREG_SPLIT_NO_EMPTY);
      return count($parts) != 3;
    }
  }
  return TRUE;
}

/**
 * Set the meta tag content.
 */
function nodewords_extra_dc_date_prepare(&$tags, $content, $options) {
  if (!empty($content['value'])) {
    if (is_array($content['value'])) {
      // Support the older date form element value.
      $content['value'] = $content['value']['day'] . ' ' . $content['value']['month'] . ' ' . $content['value']['year'];
    }
    else {
      $content['value'] = nodewords_replace_tokens($content['value'], $options);
    }
    $parts = preg_split('/\s+/', $content['value'], -1, PREG_SPLIT_NO_EMPTY);
    if (count($parts) == 3) {
      list($day, $month, $year) = $parts;
      if ($timestamp = @gmmktime(0, 0, 0, $month, $day, $year)) {
        $tags['dc.date'] = gmdate('Y-m-d\TH:i:s\Z', $timestamp);
      }
    }
  }
}

/**
 * Set the form fields used to implement the options for the meta tag.
 */
function nodewords_extra_dc_description_form(&$form, $content, $options) {
  if (!isset($form['description'])) {
    if (isset($options['content type']) && variable_get('nodewords_use_teaser_' . $options['content type'], FALSE)) {
      $form['dc.description'] = array(
        '#tree' => TRUE,
      );

      $form['dc.description']['value'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#description' => t('Enter a description. Limit your description to about 20 words, with a maximum of %count characters. It should not contain any HTML tags or other formatting.', array('%count' => variable_get('nodewords_max_size', 350))) . $options['description'],
        '#default_value' => empty($content['value']) ? (!empty($options['default']['dc.description']['value']) ? $options['default']['dc.description']['value'] : '') : $content['value'],
        '#cols' => 60,
        '#rows' => 6,
        '#wysiwyg' => FALSE,
      );
    }
  }
}

/**
 * Set the meta tag content.
 */
function nodewords_extra_dc_description_prepare(&$tags, $content, $options) {
  if (empty($tags['description'])) {
    if (!empty($content['value'])) {
      $tags['dc.description'] = nodewords_replace_tokens($content['value'], $options);
    }
  }
  else {
    $tags['dc.description'] = $tags['description'];
  }
}

/**
 * Set the form fields used to implement the options for the meta tag.
 */
function nodewords_extra_dc_publisher_form(&$form, $content, $options) {
  $form['dc.publisher'] = array(
    '#tree' => TRUE,
  );

  $form['dc.publisher']['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Dublin Core publisher'),
    '#description' => t('Enter a name of an entity responsible for making the resource available. Examples of a publisher include a person, an organization, or a service.') . $options['description'],
    '#default_value' => empty($content['value']) ? '' : $content['value'],
    '#maxlength' => variable_get('nodewords_max_size', 350),
  );
}

/**
 * Set the meta tag content.
 */
function nodewords_extra_dc_publisher_prepare(&$tags, $content, $options) {
  if (!empty($content['value'])) {
    $tags['dc.publisher'] = nodewords_replace_tokens($content['value'], $options);
  }
}

/**
 * Set the form fields used to implement the options for the meta tag.
 */
function nodewords_extra_dc_title_form(&$form, $content, $options) {
  $form['dc.title'] = array(
    '#tree' => TRUE,
  );

  $form['dc.title']['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Dublin Core title'),
    '#description' => t('Enter an alternative title. Do not use the value already used for the HTML tag TITLE, or you will probably get warning reports about duplicated titles from the search engines.') . $options['description'],
    '#default_value' => empty($content['value']) ? '' : $content['value'],
    '#maxlength' => variable_get('nodewords_max_size', 350),
  );
}

/**
 * Set the meta tag content.
 */
function nodewords_extra_dc_title_prepare(&$tags, $content, $options) {
  if (!empty($content['value'])) {
    $tags['dc.title'] = nodewords_replace_tokens($content['value'], $options);
  }
}

/**
 * Set the form fields used to implement the options for the meta tag.
 */
function nodewords_extra_location_form(&$form, $content, $options) {
  $form['location'] = array(
    '#tree' => TRUE,
  );

  $form['location']['latitude'] = array(
    '#type' => 'textfield',
    '#title' => t('Latitude'),
    '#description' => t('Enter a value between -180, and +180; any value outside the range will not be used.') . $options['description'],
    '#default_value' => empty($content['latitude']) ? '' : $content['latitude'],
    '#maxlength' => variable_get('nodewords_max_size', 350),
  );

  $form['location']['longitude'] = array(
    '#type' => 'textfield',
    '#title' => t('Longitude'),
    '#description' => t('Enter a value between -180, and +180; any value outside the range will not be used.') . $options['description'],
    '#default_value' => empty($content['longitude']) ? '' : $content['longitude'],
    '#maxlength' => variable_get('nodewords_max_size', 350),
  );
}

/**
 * Check if the meta tag content is empty.
 */
function nodewords_extra_location_is_empty($content) {
  return empty($content['latitude']) && empty($content['longitude']);
}

/**
 * Set the meta tag content.
 */
function nodewords_extra_location_prepare(&$tags, $content, $options) {
  if (!empty($content['latitude']) && !empty($content['longitude'])) {
    $latitude = nodewords_replace_tokens($content['latitude'], $options);
    $longitude = nodewords_replace_tokens($content['longitude'], $options);

    $bool = (
      is_numeric($latitude) &&
      is_numeric($longitude) &&
      $latitude >= -180 && $latitude <= 180 &&
      is_numeric($longitude) &&
      is_numeric($longitude) &&
      $longitude >= -180 && $longitude <= 180
    );
    if ($bool) {
      $tags['location:geo.position'] = $latitude . ';' . $longitude;
      $tags['location:icbm'] = $latitude . ',' . $longitude;
    }
  }
}

/**
 * Set the form fields used to implement the options for the meta tag.
 */
function nodewords_extra_shorturl_form(&$form, $content, $options) {
  $form['shorturl'] = array(
    '#tree' => TRUE,
  );

  $form['shorturl']['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Short URL'),
    '#description' => t('Short URLs are used instead of the original URL because they are shorter, and easier to remember. Short URLs are provided by some web services, such as <a href="@bitly">bit.ly</a>, <a href="@shorturl">ShortURL</a>, and <a href="@tinyurl">TinyURL</a>. Enter the absolute URL.', array('@bitly' => 'http://bit.ly', '@shorturl' => 'http://shorturl.com', '@tinyurl' => 'http://tinyurl.com')) . $options['description'],
    '#default_value' => empty($content['value']) ? '' : $content['value'],
    '#element_validate' => array('nodewords_validate_element'),
    '#maxlength' => variable_get('nodewords_max_size', 350),
  );
}

/**
 * Set the meta tag content.
 */
function nodewords_extra_shorturl_prepare(&$tags, $content, $options) {
  if (!empty($content['value'])) {
    $tags['shorturl'] = check_url(
      nodewords_replace_tokens($content['value'], $options)
    );
  }
}
