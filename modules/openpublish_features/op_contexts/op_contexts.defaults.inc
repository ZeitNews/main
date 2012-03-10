<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _op_contexts_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-general-sitewide';
  $context->description = '';
  $context->tag = 'OpenPublish General';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        '1' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-2' => array(
          'module' => 'block',
          'delta' => 2,
          'region' => 'header',
          'weight' => 0,
        ),
        'block-1' => array(
          'module' => 'block',
          'delta' => 1,
          'region' => 'footer',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-general-sitewide'] = array(
    t('OpenPublish General'),
  );

  $export['openpublish-general-sitewide'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-listing_pages-articles';
  $context->description = '';
  $context->tag = 'OpenPublish Listing Page';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'articles' => 'articles',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 0,
        ),
        'views-most_viewed_by_taxonomy-block' => array(
          'module' => 'views',
          'delta' => 'most_viewed_by_taxonomy-block',
          'region' => 'right',
          'weight' => 1,
        ),
        'views-most_commented_articles-block_1' => array(
          'module' => 'views',
          'delta' => 'most_commented_articles-block_1',
          'region' => 'right',
          'weight' => 2,
        ),
        'block-1' => array(
          'module' => 'block',
          'delta' => 1,
          'region' => 'right',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-listing_pages-articles'] = array(
    t('OpenPublish Listing Page'),
  );

  $export['openpublish-listing_pages-articles'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-listing_pages-blogs';
  $context->description = '';
  $context->tag = 'OpenPublish Listing Page';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'blogs' => 'blogs',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 0,
        ),
        'views-most_viewed_by_node_type-block' => array(
          'module' => 'views',
          'delta' => 'most_viewed_by_node_type-block',
          'region' => 'right',
          'weight' => 1,
        ),
        'views-most_commented_blogs-block_1' => array(
          'module' => 'views',
          'delta' => 'most_commented_blogs-block_1',
          'region' => 'right',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-listing_pages-blogs'] = array(
    t('OpenPublish Listing Page'),
  );

  $export['openpublish-listing_pages-blogs'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-listing_pages-events';
  $context->description = '';
  $context->tag = 'OpenPublish Listing Page';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'events' => 'events',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 0,
        ),
        'views-most_viewed_by_node_type-block' => array(
          'module' => 'views',
          'delta' => 'most_viewed_by_node_type-block',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-listing_pages-events'] = array(
    t('OpenPublish Listing Page'),
  );

  $export['openpublish-listing_pages-events'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-listing_pages-frontpage';
  $context->description = '';
  $context->tag = 'OpenPublish Listing Page';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-articles-block_2' => array(
          'module' => 'views',
          'delta' => 'articles-block_2',
          'region' => 'left',
          'weight' => 0,
        ),
        'views-articles-block_1' => array(
          'module' => 'views',
          'delta' => 'articles-block_1',
          'region' => 'left',
          'weight' => 1,
        ),
        'views-feed_items-block_1' => array(
          'module' => 'views',
          'delta' => 'feed_items-block_1',
          'region' => 'left',
          'weight' => 2,
        ),
        'views-most_viewed_by_node_type-block' => array(
          'module' => 'views',
          'delta' => 'most_viewed_by_node_type-block',
          'region' => 'right',
          'weight' => 0,
        ),
        'views-most_commented_articles-block_1' => array(
          'module' => 'views',
          'delta' => 'most_commented_articles-block_1',
          'region' => 'right',
          'weight' => 1,
        ),
        'block-4' => array(
          'module' => 'block',
          'delta' => 4,
          'region' => 'right',
          'weight' => 2,
        ),
        'openpublish_popular_terms-0' => array(
          'module' => 'openpublish_popular_terms',
          'delta' => 0,
          'region' => 'right',
          'weight' => 3,
        ),
        'block-5' => array(
          'module' => 'block',
          'delta' => 5,
          'region' => 'right',
          'weight' => 4,
        ),
        'openpublish_popular_terms-1' => array(
          'module' => 'openpublish_popular_terms',
          'delta' => 1,
          'region' => 'right',
          'weight' => 5,
        ),
        'views-blogs-block_2' => array(
          'module' => 'views',
          'delta' => 'blogs-block_2',
          'region' => 'over_content',
          'weight' => 0,
        ),
        'views-multimedia-block_1' => array(
          'module' => 'views',
          'delta' => 'multimedia-block_1',
          'region' => 'over_content',
          'weight' => 1,
        ),
        'views-resources-block_1' => array(
          'module' => 'views',
          'delta' => 'resources-block_1',
          'region' => 'over_content',
          'weight' => 2,
        ),
        'views-events-block_1' => array(
          'module' => 'views',
          'delta' => 'events-block_1',
          'region' => 'over_content',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-listing_pages-frontpage'] = array(
    t('OpenPublish Listing Page'),
  );

  $export['openpublish-listing_pages-frontpage'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-listing_pages-multimedia';
  $context->description = '';
  $context->tag = 'OpenPublish Listing Page';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'multimedia' => 'multimedia',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 0,
        ),
        'views-most_viewed_multimedia-block' => array(
          'module' => 'views',
          'delta' => 'most_viewed_multimedia-block',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-listing_pages-multimedia'] = array(
    t('OpenPublish Listing Page'),
  );

  $export['openpublish-listing_pages-multimedia'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-listing_pages-resources';
  $context->description = '';
  $context->tag = 'OpenPublish Listing Page';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'resources' => 'resources',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 0,
        ),
        'views-most_viewed_by_node_type-block' => array(
          'module' => 'views',
          'delta' => 'most_viewed_by_node_type-block',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-listing_pages-resources'] = array(
    t('OpenPublish Listing Page'),
  );

  $export['openpublish-listing_pages-resources'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-multi-content_detail';
  $context->description = '';
  $context->tag = 'OpenPublish Detail Page';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'blog' => 'blog',
        'article' => 'article',
        'event' => 'event',
        'resource' => 'resource',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  $translatables['openpublish-multi-content_detail'] = array(
    t('OpenPublish Detail Page'),
  );

  $export['openpublish-multi-content_detail'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-node_detail-article';
  $context->description = '';
  $context->tag = 'OpenPublish Detail Page';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'article' => 'article',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'morelikethis-taxonomy' => array(
          'module' => 'morelikethis',
          'delta' => 'taxonomy',
          'region' => 'right',
          'weight' => 0,
        ),
        'morelikethis-flickr' => array(
          'module' => 'morelikethis',
          'delta' => 'flickr',
          'region' => 'right',
          'weight' => 1,
        ),
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 2,
        ),
        'morelikethis-googlevideo' => array(
          'module' => 'morelikethis',
          'delta' => 'googlevideo',
          'region' => 'under_content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-node_detail-article'] = array(
    t('OpenPublish Detail Page'),
  );

  $export['openpublish-node_detail-article'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-node_detail-author';
  $context->description = 'Author Page';
  $context->tag = 'OpenPublish Detail Page';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'author' => 'author',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 0,
        ),
        'block-5' => array(
          'module' => 'block',
          'delta' => 5,
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-node_detail-author'] = array(
    t('Author Page'),
    t('OpenPublish Detail Page'),
  );

  $export['openpublish-node_detail-author'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-node_detail-blog';
  $context->description = '';
  $context->tag = 'OpenPublish Detail Page';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'blog' => 'blog',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'morelikethis-taxonomy' => array(
          'module' => 'morelikethis',
          'delta' => 'taxonomy',
          'region' => 'right',
          'weight' => 0,
        ),
        'morelikethis-flickr' => array(
          'module' => 'morelikethis',
          'delta' => 'flickr',
          'region' => 'right',
          'weight' => 1,
        ),
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 2,
        ),
        'morelikethis-googlevideo' => array(
          'module' => 'morelikethis',
          'delta' => 'googlevideo',
          'region' => 'under_content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-node_detail-blog'] = array(
    t('OpenPublish Detail Page'),
  );

  $export['openpublish-node_detail-blog'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-node_detail-event';
  $context->description = '';
  $context->tag = 'OpenPublish Detail Page';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'event' => 'event',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'morelikethis-taxonomy' => array(
          'module' => 'morelikethis',
          'delta' => 'taxonomy',
          'region' => 'right',
          'weight' => 0,
        ),
        'morelikethis-flickr' => array(
          'module' => 'morelikethis',
          'delta' => 'flickr',
          'region' => 'right',
          'weight' => 1,
        ),
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 2,
        ),
        'morelikethis-googlevideo' => array(
          'module' => 'morelikethis',
          'delta' => 'googlevideo',
          'region' => 'under_content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-node_detail-event'] = array(
    t('OpenPublish Detail Page'),
  );

  $export['openpublish-node_detail-event'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'openpublish-node_detail-resource';
  $context->description = '';
  $context->tag = 'OpenPublish Detail Page';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'resource' => 'resource',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'morelikethis-taxonomy' => array(
          'module' => 'morelikethis',
          'delta' => 'taxonomy',
          'region' => 'right',
          'weight' => 0,
        ),
        'morelikethis-flickr' => array(
          'module' => 'morelikethis',
          'delta' => 'flickr',
          'region' => 'right',
          'weight' => 1,
        ),
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'right',
          'weight' => 2,
        ),
        'morelikethis-googlevideo' => array(
          'module' => 'morelikethis',
          'delta' => 'googlevideo',
          'region' => 'under_content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['openpublish-node_detail-resource'] = array(
    t('OpenPublish Detail Page'),
  );

  $export['openpublish-node_detail-resource'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _op_contexts_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
}
