<?php


/**
 * @file.
 * Nodewords hooks.
 */

/**
 * Reports the API is supported by the modules implementing meta tags.
 *
 * @return
 * An array containing the following indexes:
 *
 *   - path - the path where the files for the integration with Nodewords are
 *     placed.
 *   - version - the API version used by the module; basing on this value
 *     Nodewords will take the necessary steps to assure to keep the module
 *     compatible with Nodewords, The minimum API currently supported by the
 *     module is contained in the constant NODEWORDS_MINIMUM_API_VERSION, and
 *     the current API version is contained in the constant
 *     NODEWORDS_API_VERSION.
*/
function hook_nodewords_api() {
  return array('version' => '1.14', 'path' => '');
}

/**
 * Alters the default meta tags values.
 *
 * @param &$values
 *  The array of default meta tags values.
 * @param $parameters
 *  An array of parameters. The currently defined are:
 *   * type - the type of object for the page to which the meta
 *     tags are associated.
 *   * id - The ID for the object associated with the page.
 *   * phase - when it's 'pre_load', the hook is called before the meta tags
 *     loaded from the database.
 */
function hook_nodewords_default_values_alter(&$values, $parameters) {
  if (!empty($values['abstract']) && $parameters['type'] == NODEWORDS_TYPE_USER) {
    $values['abstract'] = t('User profile');
  }
}

/**
 * Notifies modules when meta tags are deleted.
 *
 * @param $options.
 *   An array of options that allows to identify the meta tags being deleted.
 */
function hook_nodewords_delete_tags($options) {
  if ($options['type'] == NODEWORDS_TYPE_PAGE) {
    db_query("DELETE FROM {nodewords_custom} WHERE pid = '%s'", $options['id']);
  }
}

/**
 * Changes the permission a user has on the meta tags being edited.
 *
 * @param &$permission
 *   TRUE, if the user can edit the current meta tag.
 * @param $object
 *   An array describing the object to which the meta tag are associated.
 * @param $tag_name
 *   The name of the meta tag.
 * @param $tag_info
 *   An array describing the meta tag.
 */
function hook_nodewords_tags_permission_alter(&$permission, $object, $tag_name, $tag_info) {
  global $user;
  if (user_access('administer meta tags')) {
    $permission = TRUE;
    return;
  }

  if ($object['type'] == 'node' && ($node = node_load($options['id']))) {
    if ($user->uid == $node->uid && user_access("edit one's own node meta tags")) {
      $permission = TRUE;
      return;
    }

    if (user_access('edit any node meta tags')) {
      $permission = TRUE;
    }
    else {
      $permission = FALSE;
    }
  }
  elseif ($object['type'] == 'user' && ($account = user_load($object['id']))) {
    if ($user->uid == $account->uid && user_access("edit one's own user profile meta tags")) {
      $permission = TRUE;
      return;
    }

    if (user_access('edit any user profile meta tags')) {
      $permission = TRUE;
    }
    else {
      $permission = FALSE;
    }
  }
}

/**
 * Declares the meta tags implemented by the module.
 *
 *
 * @return
 *   An array containing the following values:
 *
 *  - attributes - the tag attributes used when outputting the tag on HTML HEAD.
 *  - callback - the string used to built the name of the functions called for
 *    any meta tags operations.
 *  - context - the contexts in which the meta tags are allowed (and denied).
 *  - label - the label used as title in the fieldset for the form field
 *    shown in the form to edit the meta tags values.
 *  - templates - the templates used when the meta tag is output.
 *  - weight - the weight used to order the meta tags before to output them;
 *    the lighter meta tag will be output first.
 *
 */
function hook_nodewords_tags_info() {
  $tags = array(
    'dc.title' => array(
      'callback' => 'nodewords_extra_dc_title',
      'context' => array(
        'denied' => array(
          NODEWORDS_TYPE_DEFAULT,
        ),
      ),
      'label' => t('Dublin Core title'),
      'templates' => array(
        'head' => array(
          'dc.title' => NODEWORDS_META,
        ),
      ),
    ),
    'location' => array(
      'callback' => 'nodewords_extra_location',
      'label' => t('Location'),
      'templates' => array(
        'head' => array(
          'geo.position' => NODEWORDS_META,
          'icbm' => NODEWORDS_META,
        )
      ),
    ),
  );

  return $tags;
}

/**
 * Alters the meta tags description passed by other modules.
 *
 * @param &$tags_info
 *   The array containing the information about the implemented meta tags.
 *
 * @see hook_nodewords_tags_info().
 */
function hook_nodewords_tags_info_alter(&$tags_info) {
  if (isset($tags_info['abstract'])) {
    $tags_info['abstract']['label'] = t('New label for abstract');
  }
}

/**
 * Alters the meta tags content.
 *
 * @param &$tags
 *  The array of meta tags values.
 * @param $parameters
 *  An array of parameters. The currently defined are:
 *   * type - the type of object for the page to which the meta
 *     tags are associated.
 *   * ids - the array of IDs for the object associated with the page.
 *   * output - where the meta tags are being output; the parameter value can
 *     'head' or 'update index'.
 */
function hook_nodewords_tags_alter(&$tags, $parameters) {
  if (empty($output['abstract']) && $parameters['type'] == NODEWORDS_TYPE_PAGE) {
    $output['abstract'] = t('Node content');
  }
}

/**
 * Alters the meta tags output.
 * The hook is called when the meta tags are already rendered.
 *
 * @param &$output
 *  The string to alter.
 * @param $parameters
 *  An array of parameters. The currently defined are:
 *   * type - the type of object for the page to which the meta
 *     tags are associated.
 *   * id - the ID for the object associated with the page.
 *   * output - where the meta tags are being output; the parameter value can
 *     'head' or 'update index'.
 */
function hook_nodewords_tags_output_alter(&$output, $parameters) {
  $bool = (
    variable_get('nodewords_add_dc_schema', FALSE) &&
    isset($parameters['output']) &&
    $parameters['output'] == 'head'
  );
  if ($bool) {
    $output = (
      '<link rel="schema.dc" href="http://purl.org/dc/elements/1.1/" />' . "\n" .
      $output
    );
  }
}

/**
 * Determinates the type of the object associated with the viewed page.
 *
 * @param &$result
 *   the array used to write the result.
 * @param $arg
 *   the array as obtained from arg().
 */
function hook_nodewords_type_id(&$result, $arg) {
  if ($arg[0] == 'user') {
    // User page paths: user/$uid.
    if (isset($arg[1]) && is_numeric($arg[1])) {
      $result['type'] = NODEWORDS_TYPE_USER;
      $result['id'] = $arg[1];
    }
  }
}
