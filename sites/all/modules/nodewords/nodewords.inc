<?php

/**
 * @file
 * This file contains all PUBLIC and PRIVATE function definitions for
 * nodewords module.
 */

/*****************************************************************************
 * Public functions.
 * 
 * Public functions should behave the same inside the same Drupal core
 * version (eg 5.x, 6.x). They can however change inbetween different
 * core versions.
 *
 * To use this file, just call 'nodewords_include_once()'.
 ****************************************************************************/

/**
 * Get a list of all defined meta tags.
 *
 * @param $reset
 *   Boolean. Reset the internally used cache of this list.
 *
 * @return
 *   Array.
 */
function nodewords_get_tags($reset = FALSE) {
  static $tags = NULL;
  if ($reset || !isset($tags)) {
    nodewords_include_once();
    $tags = _nodewords_db_get_tags();
  }
  return $tags;
}

/*****************************************************************************
 * Private functions.
 *
 * Note that private functions are never intended to be used for other
 * third-party modules. Their purpose is solely internal. If you think
 * something is missing from the public API that you need, let the authors
 * know on http://drupal.org/project/issues/nodewords. You can recognise
 * private functions by the leading '_' character in the function name.
 ****************************************************************************/

/**
 * Remove any content from the value that is not allowed as content.
 *
 * @param $text
 *   String.
 *
 * @return
 *   String.
 */
function _nodewords_check_content($text) {
  // Replace <img> with alt.
  $pattern = '/<img\s[^>]*alt=["\']([^"\']*)["\'][^>]*>/i';
  $replacement = '${1}';
  $text = preg_replace($pattern, $replacement, $text);

  // Strip tags and check_plain.
  $text = strip_tags($text);
  $text = check_plain($text);

  // Replace some needles.
  $needles = array('&nbsp;', "\r", "\n", '&#039;');
  $replaces = array(' ', ' ', ' ', "'");
  $text = str_replace($needles, $replaces, $text);

  // Remove extra whitespace.
  $text = trim($text);
  $text = preg_replace('/\s+/', ' ', $text);

  return $text;
}

/**
 * Limit the length of the value based on nodewords:content-length
 * variable. If this variable is set to 0 then the value is not
 * cut-off.
 *
 * @param $text
 *   String.
 *
 * @return
 *   String.
 */
function _nodewords_check_length($text) {
  $max_size = variable_get('nodewords:content-length', 255);
  if ($max_size > 0 && drupal_strlen($text) > $max_size) {
    $text = truncate_utf8($text, $max_size);
    $length = strrpos($text, ' ');
    if (!is_bool($length)) {
      $text = substr($text, 0, $length);
    }
  }
  return $text;
}

/**
 * List all possible contexts.
 *
 * @return
 *   Array ($context => array('name' => ..., 'description' => ...).
 */
function _nodewords_contexts() {
  $contexts = array(
    'default' => array(
      'name' => t('Global default'),
      'description' => t('The <em>Global default</em> context is used for all pages of the site unless a more specific context is available.'),
    ),
    'default:front' => array(
      'name' => t('Frontpage'),
      'description' => t('The <em>Frontpage</em> context is used for the front page of the site only.'),
    ),
    'default:error' => array(
      'name' => t('Page not found'),
      'description' => t('The <em>Page not found</em> context is used for the pages that are not available for the user or that could not be found.'),
    ),
    'default:node' => array(
      'name' => t('Content'),
      'description' => t('The <em>Content</em> context is used for all content pages (<em>Story</em>, <em>Page</em>, ...) unless a more specific default is set below.'),
    ),
  );

  foreach ((array)node_get_types('names') as $type => $name) {
    $contexts['default:node:'. $type] = array(
      'name' => t('@type content', array('@type' => $name)),
      'description' => t('The %type content context is used for all pages of the %type content type.', array('%type' => $name)),
    );
  }

  return $contexts;
}

/**
 * Create some common meta tags.
 *
 * @return
 *   Nothing.
 */
function _nodewords_create_default_tags() {
  $tags = array();
  $tags['schema.DC'] = array(
    'description' => t('Dublin Core schema'),
    'type' => 'link',
    'defaults' => array(
      'default' => array(
        'value' => 'http://purl.org/dc/elements/1.1/',
      ),
    ),
  );
  $tags['schema.DCTERMS'] = array(
    'description' => t('Dublin Core Terms schema'),
    'type' => 'link',
    'defaults' => array(
      'default' => array(
        'value' => 'http://purl.org/dc/terms/',
      ),
    ),
  );
  $tags['DC.Title'] = array(
    'description' => t('Dublin Core Title'),
    'widget' => 'textfield',
    'widget_options' => array(
      'label' => t('Title'),
    ),
  );
/*
  $tags['DC.Subject'] = array(
    'description' => t('Dublin Core Subject and Keywords'),
  );
*/
  $tags['DC.Description'] = array(
    'description' => t('Dublin Core Description'),
    'widget' => 'textarea',
    'widget_options' => array(
      'label' => t('Description'),
    ),
  );
  $tags['DC.Description.abstract'] = array(
    'description' => t('Dublin Core Abstract'),
    'widget' => 'textfield',
    'widget_options' => array(
      'label' => t('Abstract'),
    ),
  );
/*
  $tags['DC.Type'] = array(
    'description' => t('Dublin Core Resource Type'),
  );
  $tags['DC.Creator'] = array(
    'description' => t('Dublin Core Creator'),
  );
  $tags['DC.Publisher'] = array(
    'description' => t('Dublin Core Publisher'),
  );
  $tags['DC.Rights'] = array(
    'description' => t('Dublin Core Rights Management'),
  );
  $tags['DC.Rights.license'] = array(
    'description' => t('Dublin Core License'),
  );
*/
  $tags['DC.Date'] = array(
    'description' => t('Dublin Core Date'),
    'attributes' => array(
      array(
        'name' => 'scheme',
        'value' => 'DCTERMS.W3CDTF',
      ),
    ),
  );
  $tags['DC.Date.created'] = array(
    'description' => t('Dublin Core Created'),
    'attributes' => array(
      array(
        'name' => 'scheme',
        'value' => 'DCTERMS.W3CDTF',
      ),
    ),
  );
  $tags['DC.Date.modified'] = array(
    'description' => t('Dublin Core Modified'),
    'attributes' => array(
      array(
        'name' => 'scheme',
        'value' => 'DCTERMS.W3CDTF',
      ),
    ),
  );
/*
  $tags['DC.Identifier'] = array(
    'description' => t('Dublin Core Resource Identifier'),
  );
  $tags['DC.Language'] = array(
    'description' => t('Dublin Core Language'),
  );
*/
  $tags['abstract'] = array(
    'description' => t('Abstract'),
    'widget' => 'alias',
    'widget_options' => array(
      'alias' => 'DC.Description.abstract',
    ),
  );
/*
  $tags['copyright'] = array(
    'description' => t('Copyright'),
    'widget' => 'alias',
  );
*/
  $tags['description'] = array(
    'description' => t('Description'),
    'widget' => 'alias',
    'widget_options' => array(
      'alias' => 'DC.Description',
    ),
  );
/*
  $tags['geourl'] = array(
    'description' => t('GeoURL'),
  );
  $tags['keywords'] = array(
    'description' => t('Keywords'),
    'widget' => 'alias',
  );
  $tags['robots'] = array(
    'description' => t('Robots'),
  );
*/

  foreach ($tags as $tag_name => $tag) {
    if (!isset($tag['widget']) || $tag['widget'] != 'alias') {
      $tag['name'] = $tag_name;
      $tags[$tag_name]['tagid'] = _nodewords_db_insert_tag($tag);
    }
  }

  foreach ($tags as $tag_name => $tag) {
    if (isset($tag['widget']) && $tag['widget'] == 'alias') {
      $tag['name'] = $tag_name;
      $tag['widget_options'] = array('alias' => $tags[$tag['widget_options']['alias']]['tagid']);
      $tags[$tag_name]['tagid'] = _nodewords_db_insert_tag($tag);
    }
  }
}

/**
 * Delete an existing tag from the database.
 *
 * @param $tagid
 *   Integer. Unique identifier of a meta tag.
 *
 * @return
 *   Nothing.
 */
function _nodewords_db_delete_tag($tagid) {
  db_query("DELETE FROM {nodewords_tags} WHERE tagid = %d", $tagid);
  db_query("DELETE FROM {nodewords_defaults} WHERE tagid = %d", $tagid);
  db_query("DELETE FROM {nodewords_attributes} WHERE tagid = %d", $tagid);
  module_invoke_all('nodewords_tag', 'delete', $tagid);
  cache_clear_all('nodewords:', NODEWORDS_CACHE_TABLE, TRUE);
}

/**
 * Load the defined attributes for a given meta tag.
 *
 * @param $tagid
 *   Integer. Unique identifier of a meta tag.
 *
 * @return
 *   Array.
 */
function _nodewords_db_get_attributes($tagid) {
  $attributes = array();
  $result = db_query("SELECT * FROM {nodewords_attributes} WHERE tagid = %d ORDER BY weight ASC, attid", $tagid);
  while (($row = db_fetch_object($result))) {
    $attributes[] = $row;
  }
  return $attributes;
}

/**
 * Load the defined defaults for a given meta tag.
 *
 * @param $tagid
 *   Integer. Unique identifier of a meta tag.
 *
 * @return
 *   Array.
 */
function _nodewords_db_get_defaults($tagid) {
  $defaults = array();
  $result = db_query("SELECT * FROM {nodewords_defaults} WHERE tagid = %d ORDER BY context", $tagid);
  while (($row = db_fetch_array($result))) {
    $defaults[$row['context']] = $row;
  }
  return $defaults;
}

/**
 * Load all defined meta tags from the database.
 *
 * @return
 *   Array ($tagid => (object)$tag).
 */
function _nodewords_db_get_tags() {
  $tags = array();
  $result = db_query("SELECT * FROM {nodewords_tags} ORDER BY weight ASC, name ASC");
  while (($row = db_fetch_object($result))) {
    $row->attributes = _nodewords_db_get_attributes($row->tagid);
    $row->defaults = _nodewords_db_get_defaults($row->tagid);
    $row->options = unserialize($row->options);
    $row->widget_options = unserialize($row->widget_options);
    module_invoke_all('nodewords_tag', 'load', $row);
    $tags[$row->tagid] = $row;
  }
  return $tags;
}

/**
 * Inserts a new meta tag in the database.
 *
 * @param $form_values
 *   Array of values.
 *
 * @return
 *   Integer. The tagid of the newly inserted meta tag or NULL on
 *   failure.
 */
function _nodewords_db_insert_tag($form_values) {
  return _nodewords_db_update_tag($form_values, FALSE);
}

/**
 * Update or insert attributes for a given meta tag.
 *
 * @param $tagid
 *   Integer. Unique identifier of a meta tag.
 * 
 * @param $form_values
 *   Array.
 *
 * @return
 *   Nothing.
 */
function _nodewords_db_update_attributes($tagid, $attributes) {
  foreach ($attributes as $attribute) {
    $attribute = (object)$attribute;
    $attribute->tagid = $tagid;
    if (isset($attribute->attid) && !empty($attribute->attid)) {
      if (isset($attribute->delete) && $attribute->delete) {
        db_query("DELETE FROM {nodewords_attributes} WHERE attid = %d", $attribute->attid);
      }
      else {
        drupal_write_record('nodewords_attributes', $attribute, 'attid');
      }
    }
    else if (isset($attribute->name) && !empty($attribute->name) && !(isset($attribute->delete) && $attribute->delete)) {
      drupal_write_record('nodewords_attributes', $attribute);
    }
  }
}

/**
 * Update or insert defaults for a given meta tag.
 *
 * @param $tagid
 *   Integer. Unique identifier of a meta tag.
 *
 * @param $form_values
 *   Array.
 *
 * @return
 *   Nothing.
 */
function _nodewords_db_update_defaults($tagid, $form_values) {
  db_query("DELETE FROM {nodewords_defaults} WHERE tagid = %d", $tagid);
  foreach ((array)$form_values as $context => $object) {
    $object['tagid'] = $tagid;
    $object['context'] = $context;
    drupal_write_record('nodewords_defaults', $object);
  }
  return;
}

/**
 * Updates an existing meta tag in the database.
 *
 * @param $form_values
 *   Array of values.
 *
 * @param $update
 *   Boolean. If TRUE, perform an update. If FALSE, perform an insert.
 *   This parameter is used internally only. Use either:
 *   _nodewords_db_update_tag($form_values) for updates, or
 *   _nodewords_db_insert_tag($form_values) for new inserts.
 *
 * @return
 *   Integer. The tagid of the updated meta tag or NULL on
 *   failure.
 */
function _nodewords_db_update_tag($form_values, $update = TRUE) {
  $object = (object)$form_values;

  if (!isset($object->widget_options)) {
    $object->widget_options = array();
  }

  if (!isset($object->options)) {
    $object->options = array();
  }

  $return = drupal_write_record('nodewords_tags', $object, $update ? 'tagid' : array());

  if (($return == SAVED_NEW && !$update) || ($return == SAVED_UPDATED && $update)) {
    if (isset($object->attributes)) {
      _nodewords_db_update_attributes($object->tagid, $object->attributes);
    }
    if (isset($object->defaults)) {
      _nodewords_db_update_defaults($object->tagid, $object->defaults);
    }
    module_invoke_all('nodewords_tag', $update ? 'update' : 'insert', $object);
    cache_clear_all('nodewords:', NODEWORDS_CACHE_TABLE, TRUE);
    return $object->tagid;
  }
  return NULL;
}

/**
 * Update weight of an existing tag in the database.
 *
 * @param $tagid
 *   Integer.
 *
 * @param $weight
 *   Integer. New tag weight.
 *
 * @return
 *   Nothing.
 */
function _nodewords_db_update_tag_weight($tagid, $weight = 0) {
  db_query("UPDATE {nodewords_tags} SET weight = %d WHERE tagid = %d", $weight, $tagid);
}

/**
 * Update widget and widget options of an existing tag in the database.
 *
 * @param $tagid
 *   Integer.
 *
 * @param $widget
 *   String.
 *
 * @param $widget_options
 *   Array.
 *
 * @return
 *   Nothing.
 */
function _nodewords_db_update_tag_widget($tagid, $widget, $widget_options) {
  db_query("UPDATE {nodewords_tags} SET widget = '%s', widget_options = '%s' WHERE tagid = %d", $widget, serialize($widget_options), $tagid);
}

/**
 * Core function to get and prepare the tags to show for the given
 * context and object.
 *
 * @param $context
 *   String. The context of the object. Eg 'default', 'default:error', ...
 *
 * @param $object
 *   Object. For certain contexts an object is needed. Eg for 'default:node'
 *   a node-object should be passed in $object.
 *
 * @return
 *   Array of tags, ready for output.
 */
function _nodewords_get($context, $object) {
  $output = array();

  $tags = nodewords_get_tags();
  $types = _nodewords_types();

  //TODO: handle aliases

  foreach ($tags as $tagid => $tag) {
    if ($tag->widget != 'alias' && _nodewords_is_viewable($tag, $context)) {
      $template = $types[$tag->type]['template'];

      $attributes = array();
      foreach ((array)$tag->attributes as $attribute) {
        $attributes[$attribute->name] = $attribute->value;
      }

      $values = array(
        'one', 'duplicate', '  ', 'four', 'duplicate',
      );
      //TODO: get the real values
      //TODO: do token replacements

      if (!empty($values)) {
        $values = array_map('_nodewords_check_content', $values);

        if (!isset($tag->options['allow-empty']) || !$tag->options['allow-empty']) {
          $values = array_filter($values);
        }

        if (!isset($tag->options['unique-list']) || $tag->options['unique-list']) {
          $values = array_keys(array_flip($values));
        }

        if (isset($tag->options['combine-values']) && $tag->options['combine-values']) {
          $separator = isset($tag->options['separator']) ? $tag->options['separator'] : ',';
          $values = array(implode($separator, (array)$values));
        }

        $values = array_map('_nodewords_check_length', $values);
      }

      $output[$tagid] = (object) array(
        'name' => $tag->name,
        'template' => $template,
        'values' => $values,
        'attributes' => $attributes,
      );
    }
  }

  return $output;
}

/**
 * Check whether a tag needs to be outputted for given context.
 *
 * @param $tag
 *   Object. The tag to check.
 *
 * @param $context
 *   String. The context.
 *
 * @return
 *   Boolean. TRUE if outputtable, FALSE if not.
 */
function _nodewords_is_viewable($tag, $context) {
  $output = NODEWORDS_INHERIT;
  $contexts = explode(':', $context);

  while ($output == NODEWORDS_INHERIT && !empty($contexts)) {
    $context = implode(':', $contexts);
    if (isset($tag->defaults[$context]['enabled'])) {
      $output = $tag->defaults[$context]['enabled'];
    }
    array_pop($contexts);
  }

  return $output != NODEWORDS_DISABLED;
}

/**
 * List all possible meta tag types.
 *
 * @return
 *   Array ($type => 'name').
 */
function _nodewords_types() {
  return array(
    'meta' => array(
      'title' => t('Meta'),
      'description' => t('<code>&lt;meta name="..." content="..." /&gt;</code>. If unsure, select this option.'),
      'template' => '<meta name="!name" content="!value" !attributes />',
    ),
    'link' => array(
      'title' => t('Link'),
      'description' => t('<code>&lt;link rel="..." href="..." /&gt;</code>.'),
      'template' => '<link rel="!name" href="!value" !attributes />',
    ),
    'http-equiv' => array(
      'title' => t('Http-Equiv'),
      'description' => t('<code>&lt;meta http-equiv="..." content="..." /&gt;</code>.'),
      'template' => '<meta http-equiv="!name" content="!value" !attributes />',
    ),
  );
}

/**
 * List all possible meta tag widgets.
 *
 * @return
 *   Array ($widget => array('title' => ..., 'description' => ...)).
 */
function _nodewords_widgets() {
  $widgets = array();

  $widgets['none'] = array(
    'title' => t('No widget'),
    'description' => t('The user will not be able to edit the meta tag for a specific page. The auto-generated value (based on the context) will be used.'),
  );
  $widgets['alias'] = array(
    'title' => t('Alias'),
    'description' => t('The user will not be able to edit the meta tag for a specific page. The content of this meta tag will be taken from another meta tag instead. This can for example be used to output the same content for <code>DC.Subject</code> and <code>keywords</code> without the user having to input everything twice. Note that in this case the meta tag type (<em>Meta</em> or <em>Link</em>) will be ignored and the type of the meta tag this tag is an alias for will be used.'),
  );
  $widgets['textfield'] = array(
    'title' => t('Text field'),
    'description' => t('A text field to input a short text.'),
  );
  $widgets['textarea'] = array(
    'title' => t('Text area'),
    'description' => t('A text area to input a longer text, typically used for <code>DC.Description</code> or <code>description</code>.'),
  );
/*
  $widgets['select'] = array(
    'title' => t('Select'),
    'description' => t('The user will be presented with a list of possible values for this meta tag. You can specify the options that will be available to the user.'),
  );
*/
  return $widgets;
}

/*****************************************************************************
 * Module widgets.
 ****************************************************************************/

/*****************************************************************************
 * 'Alias' widget.
 ****************************************************************************/


/**
 * Alias widget options.
 *
 * @param $widget_options
 *   Array.
 *
 * @return
 *   Form array.
 */
function _nodewords_widget_options_alias($widget_options) {
  $form = array();
  $options = array();
  foreach ((array)nodewords_get_tags() as $tag) {
    $options[$tag->tagid] = $tag->name;
  }
  $form['alias'] = array(
    '#type' => 'select',
    '#title' => t('Alias'),
    '#options' => $options,
    '#description' => t('Select the meta tag this tag is an alias for.'),
    '#default_value' => $widget_options['alias'],
  );
  return $form;
}

/*****************************************************************************
 * 'Textarea' widget.
 ****************************************************************************/

/**
 * Textarea widget options.
 *
 * @param $widget_options
 *   Array.
 *
 * @return
 *   Form array.
 */
function _nodewords_widget_options_textarea($widget_options) {
  $form = array();
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#description' => t('The label that will be used for this widget.'),
    '#default_value' => $widget_options['label'],
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('The description users see on the edit pages for this widget.'),
    '#default_value' => $widget_options['description'],
  );
  return $form;
}

/**
 * Textarea widget options validate.
 */
function _nodewords_widget_options_textarea_validate($form, &$form_state) {
  $form_values = $form_state['values'];

  if (!isset($form_values['widget_options']['label']) || empty($form_values['widget_options']['label'])) {
    form_set_error('widget_options][label', t('You need to specify a label for this widget.'));
  }
}

/**
 * Textarea widget.
 *
 * @param $value
 *   String. The user inputted value.
 * 
 * @param $widget_options
 *   Array.
 *
 * @return
 *   Form array.
 */
function _nodewords_widget_textarea($value, $widget_options) {
  $form = array(
    '#type' => 'textarea',
    '#title' => $widget_options['label'],
    '#description' => $widget_options['description'],
    '#default_value' => $value,
  );
  return $form;
}

/*****************************************************************************
 * 'Textfield' widget.
 ****************************************************************************/

/**
 * Textfield widget options.
 *
 * @param $widget_options
 *   Array.
 *
 * @return
 *   Form array.
 */
function _nodewords_widget_options_textfield($widget_options) {
  $form = array();
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#description' => t('The label that will be used for this widget.'),
    '#default_value' => $widget_options['label'],
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('The description users see on the edit pages for this widget.'),
    '#default_value' => $widget_options['description'],
  );
  return $form;
}

/**
 * Textfield widget options validate.
 */
function _nodewords_widget_options_textfield_validate($form, &$form_state) {
  $form_values = $form_state['values'];

  if (!isset($form_values['widget_options']['label']) || empty($form_values['widget_options']['label'])) {
    form_set_error('widget_options][label', t('You need to specify a label for this widget.'));
  }
}

/**
 * Textfield widget.
 *
 * @param $value
 *   String. The user inputted value.
 * 
 * @param $widget_options
 *   Array.
 *
 * @return
 *   Form array.
 */
function _nodewords_widget_textfield($value, $widget_options) {
  $form = array(
    '#type' => 'textfield',
    '#title' => $widget_options['label'],
    '#description' => $widget_options['description'],
    '#default_value' => $value,
  );
  return $form;
}
