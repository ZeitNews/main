<?php

$view = new view;
$view->name = 'most_commented_articles';
$view->description = 'Content with the most comments.';
$view->tag = '';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('fields', array(
  'title' => array(
    'label' => '',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'none',
  ),
));
$handler->override_option('sorts', array(
  'comment_count' => array(
    'order' => 'DESC',
    'id' => 'comment_count',
    'table' => 'node_comment_statistics',
    'field' => 'comment_count',
    'relationship' => 'none',
  ),
  'title' => array(
    'order' => 'ASC',
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'none',
  ),
));
$handler->override_option('arguments', array(
  'name' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => 'Most Commented in %1',
    'default_argument_type' => 'php',
    'default_argument' => '',
    'validate_type' => 'none',
    'validate_fail' => 'not found',
    'glossary' => 0,
    'limit' => '0',
    'case' => 'none',
    'path_case' => 'none',
    'transform_dash' => 0,
    'add_table' => 0,
    'require_value' => 0,
    'id' => 'name',
    'table' => 'term_data',
    'field' => 'name',
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => 'all',
    'default_argument_php' => '$arg0 = arg(0);
    $arg1 = arg(1);
    if ($arg0 == \'articles\' && $arg1)  { 
        return  $arg1;
    }
    else return \'all\';',
    'validate_argument_node_type' => array(
      'blog' => 0,
      'article' => 0,
      'audio' => 0,
      'event' => 0,
      'feed' => 0,
      'feeditem' => 0,
      'op_image' => 0,
      'package' => 0,
      'page' => 0,
      'resource' => 0,
      'story' => 0,
      'twitter_item' => 0,
      'video' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(
      '42' => 0,
      '43' => 0,
      '44' => 0,
      '41' => 0,
      '45' => 0,
      '46' => 0,
      '47' => 0,
      '48' => 0,
      '49' => 0,
      '50' => 0,
      '51' => 0,
      '52' => 0,
      '53' => 0,
      '54' => 0,
      '55' => 0,
      '56' => 0,
      '57' => 0,
      '58' => 0,
      '59' => 0,
      '60' => 0,
      '61' => 0,
      '62' => 0,
      '63' => 0,
      '64' => 0,
      '65' => 0,
      '66' => 0,
      '67' => 0,
      '68' => 0,
      '69' => 0,
      '70' => 0,
      '71' => 0,
      '72' => 0,
      '73' => 0,
      '74' => 0,
      '75' => 0,
      '76' => 0,
      '77' => 0,
      '78' => 0,
      '79' => 0,
      '80' => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_node_flag_name' => '*relationship*',
    'validate_argument_node_flag_test' => 'flaggable',
    'validate_argument_node_flag_id_type' => 'id',
    'validate_argument_user_flag_name' => '*relationship*',
    'validate_argument_user_flag_test' => 'flaggable',
    'validate_argument_user_flag_id_type' => 'id',
    'validate_argument_php' => '',
    'override' => array(
      'button' => 'Override',
    ),
  ),
));
$handler->override_option('filters', array(
  'status' => array(
    'operator' => '=',
    'value' => 1,
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'status',
    'table' => 'node',
    'field' => 'status',
    'relationship' => 'none',
  ),
  'type' => array(
    'operator' => 'in',
    'value' => array(
      'article' => 'article',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('title', 'Most Commented');
$handler->override_option('items_per_page', 5);
$handler->override_option('use_more', 0);
$handler->override_option('distinct', 1);
$handler->override_option('style_plugin', 'list');
$handler->override_option('style_options', array(
  'grouping' => '',
  'type' => 'ul',
));
$handler = $view->new_display('block', 'Block', 'block_1');
$handler->override_option('block_description', 'Most Commented Articles');
$handler->override_option('block_caching', -1);
