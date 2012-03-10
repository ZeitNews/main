<?php

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _op_defaults_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_imagecache_default_presets().
 */
function _op_defaults_imagecache_default_presets() {
  $items = array(
    '400xY' => array(
      'presetname' => '400xY',
      'actions' => array(
        '0' => array(
          'weight' => '-1',
          'module' => 'imagecrop',
          'action' => 'imagecrop_javascript',
          'data' => array(
            'width' => '400',
            'height' => '200',
            'xoffset' => 'center',
            'yoffset' => 'center',
            'resizable' => 1,
            'aspect' => FALSE,
            'disable_if_no_data' => 1,
          ),
        ),
        '1' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '400',
            'height' => '',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'featured_image' => array(
      'presetname' => 'featured_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '200',
            'height' => '',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'package_featured' => array(
      'presetname' => 'package_featured',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '425',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'spotlight_homepage' => array(
      'presetname' => 'spotlight_homepage',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '345',
            'height' => '',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'thumbnail' => array(
      'presetname' => 'thumbnail',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '100',
            'height' => '',
            'upscale' => 1,
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _op_defaults_user_default_permissions() {
  $permissions = array();

  // Exported permission: Use PHP input for field settings (dangerous - grant with care)
  $permissions[] = array(
    'name' => 'Use PHP input for field settings (dangerous - grant with care)',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: access RDF data
  $permissions[] = array(
    'name' => 'access RDF data',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: access administration pages
  $permissions[] = array(
    'name' => 'access administration pages',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access advuser
  $permissions[] = array(
    'name' => 'access advuser',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: access all views
  $permissions[] = array(
    'name' => 'access all views',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'author',
      '4' => 'editor',
      '5' => 'web editor',
    ),
  );

  // Exported permission: access calais
  $permissions[] = array(
    'name' => 'access calais',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access calais rdf
  $permissions[] = array(
    'name' => 'access calais rdf',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'author',
      '4' => 'editor',
      '5' => 'web editor',
    ),
  );

  // Exported permission: access ckeditor
  $permissions[] = array(
    'name' => 'access ckeditor',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'author',
      '3' => 'editor',
      '4' => 'web editor',
    ),
  );

  // Exported permission: access comments
  $permissions[] = array(
    'name' => 'access comments',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'author',
      '4' => 'editor',
      '5' => 'web editor',
    ),
  );

  // Exported permission: access content
  $permissions[] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'author',
      '4' => 'editor',
      '5' => 'web editor',
    ),
  );

  // Exported permission: access devel information
  $permissions[] = array(
    'name' => 'access devel information',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: access openpublish admin pages
  $permissions[] = array(
    'name' => 'access openpublish admin pages',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access premium content
  $permissions[] = array(
    'name' => 'access premium content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'author',
      '3' => 'editor',
      '4' => 'web editor',
    ),
  );

  // Exported permission: access site reports
  $permissions[] = array(
    'name' => 'access site reports',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access statistics
  $permissions[] = array(
    'name' => 'access statistics',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access user profiles
  $permissions[] = array(
    'name' => 'access user profiles',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'author',
      '4' => 'editor',
      '5' => 'web editor',
    ),
  );

  // Exported permission: add list of open ids
  $permissions[] = array(
    'name' => 'add list of open ids',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer RDF data
  $permissions[] = array(
    'name' => 'administer RDF data',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer RDF repositories
  $permissions[] = array(
    'name' => 'administer RDF repositories',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer actions
  $permissions[] = array(
    'name' => 'administer actions',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer advanced pane settings
  $permissions[] = array(
    'name' => 'administer advanced pane settings',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer advuser
  $permissions[] = array(
    'name' => 'administer advuser',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer blocks
  $permissions[] = array(
    'name' => 'administer blocks',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer calais
  $permissions[] = array(
    'name' => 'administer calais',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer calais api
  $permissions[] = array(
    'name' => 'administer calais api',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer calais geo
  $permissions[] = array(
    'name' => 'administer calais geo',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer ckeditor
  $permissions[] = array(
    'name' => 'administer ckeditor',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer comments
  $permissions[] = array(
    'name' => 'administer comments',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: administer content types
  $permissions[] = array(
    'name' => 'administer content types',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer custompage
  $permissions[] = array(
    'name' => 'administer custompage',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer features
  $permissions[] = array(
    'name' => 'administer features',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer feedapi
  $permissions[] = array(
    'name' => 'administer feedapi',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer files
  $permissions[] = array(
    'name' => 'administer files',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer filters
  $permissions[] = array(
    'name' => 'administer filters',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer flags
  $permissions[] = array(
    'name' => 'administer flags',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer flash
  $permissions[] = array(
    'name' => 'administer flash',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer imageapi
  $permissions[] = array(
    'name' => 'administer imageapi',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer imagecache
  $permissions[] = array(
    'name' => 'administer imagecache',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer imagecrop
  $permissions[] = array(
    'name' => 'administer imagecrop',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer languages
  $permissions[] = array(
    'name' => 'administer languages',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer login destination
  $permissions[] = array(
    'name' => 'administer login destination',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer menu
  $permissions[] = array(
    'name' => 'administer menu',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer meta tags
  $permissions[] = array(
    'name' => 'administer meta tags',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer mollom
  $permissions[] = array(
    'name' => 'administer mollom',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer morelikethis
  $permissions[] = array(
    'name' => 'administer morelikethis',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer nodequeue
  $permissions[] = array(
    'name' => 'administer nodequeue',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer nodes
  $permissions[] = array(
    'name' => 'administer nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer page manager
  $permissions[] = array(
    'name' => 'administer page manager',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer pane access
  $permissions[] = array(
    'name' => 'administer pane access',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer pane visibility
  $permissions[] = array(
    'name' => 'administer pane visibility',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer panel-nodes
  $permissions[] = array(
    'name' => 'administer panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer pathauto
  $permissions[] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer permissions
  $permissions[] = array(
    'name' => 'administer permissions',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer scheduler
  $permissions[] = array(
    'name' => 'administer scheduler',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer search
  $permissions[] = array(
    'name' => 'administer search',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer site configuration
  $permissions[] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer taxonomy
  $permissions[] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer topichubs
  $permissions[] = array(
    'name' => 'administer topichubs',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer url aliases
  $permissions[] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer users
  $permissions[] = array(
    'name' => 'administer users',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer views
  $permissions[] = array(
    'name' => 'administer views',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: advanced feedapi options
  $permissions[] = array(
    'name' => 'advanced feedapi options',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: bypass mollom protection
  $permissions[] = array(
    'name' => 'bypass mollom protection',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: change own username
  $permissions[] = array(
    'name' => 'change own username',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: clear all drupal cache
  $permissions[] = array(
    'name' => 'clear all drupal cache',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: create article content
  $permissions[] = array(
    'name' => 'create article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create audio content
  $permissions[] = array(
    'name' => 'create audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create author content
  $permissions[] = array(
    'name' => 'create author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create blog entries
  $permissions[] = array(
    'name' => 'create blog entries',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create event content
  $permissions[] = array(
    'name' => 'create event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create feed content
  $permissions[] = array(
    'name' => 'create feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create feeditem content
  $permissions[] = array(
    'name' => 'create feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create op_image content
  $permissions[] = array(
    'name' => 'create op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create package content
  $permissions[] = array(
    'name' => 'create package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create page content
  $permissions[] = array(
    'name' => 'create page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create panel-nodes
  $permissions[] = array(
    'name' => 'create panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: create resource content
  $permissions[] = array(
    'name' => 'create resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create slideshow content
  $permissions[] = array(
    'name' => 'create slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create topichub content
  $permissions[] = array(
    'name' => 'create topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: create url aliases
  $permissions[] = array(
    'name' => 'create url aliases',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: create video content
  $permissions[] = array(
    'name' => 'create video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: crop images with toolbox
  $permissions[] = array(
    'name' => 'crop images with toolbox',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete any article content
  $permissions[] = array(
    'name' => 'delete any article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any audio content
  $permissions[] = array(
    'name' => 'delete any audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any author content
  $permissions[] = array(
    'name' => 'delete any author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any blog entry
  $permissions[] = array(
    'name' => 'delete any blog entry',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any event content
  $permissions[] = array(
    'name' => 'delete any event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any feed content
  $permissions[] = array(
    'name' => 'delete any feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any feeditem content
  $permissions[] = array(
    'name' => 'delete any feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any op_image content
  $permissions[] = array(
    'name' => 'delete any op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any package content
  $permissions[] = array(
    'name' => 'delete any package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any page content
  $permissions[] = array(
    'name' => 'delete any page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any resource content
  $permissions[] = array(
    'name' => 'delete any resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any slideshow content
  $permissions[] = array(
    'name' => 'delete any slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any topichub content
  $permissions[] = array(
    'name' => 'delete any topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any video content
  $permissions[] = array(
    'name' => 'delete any video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete own article content
  $permissions[] = array(
    'name' => 'delete own article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own audio content
  $permissions[] = array(
    'name' => 'delete own audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own author content
  $permissions[] = array(
    'name' => 'delete own author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own blog entries
  $permissions[] = array(
    'name' => 'delete own blog entries',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own event content
  $permissions[] = array(
    'name' => 'delete own event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own feed content
  $permissions[] = array(
    'name' => 'delete own feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own feeditem content
  $permissions[] = array(
    'name' => 'delete own feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own op_image content
  $permissions[] = array(
    'name' => 'delete own op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own package content
  $permissions[] = array(
    'name' => 'delete own package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own page content
  $permissions[] = array(
    'name' => 'delete own page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own resource content
  $permissions[] = array(
    'name' => 'delete own resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own slideshow content
  $permissions[] = array(
    'name' => 'delete own slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own topichub content
  $permissions[] = array(
    'name' => 'delete own topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own video content
  $permissions[] = array(
    'name' => 'delete own video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete revisions
  $permissions[] = array(
    'name' => 'delete revisions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: display source code
  $permissions[] = array(
    'name' => 'display source code',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit any article content
  $permissions[] = array(
    'name' => 'edit any article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any audio content
  $permissions[] = array(
    'name' => 'edit any audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any author content
  $permissions[] = array(
    'name' => 'edit any author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any blog entry
  $permissions[] = array(
    'name' => 'edit any blog entry',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any event content
  $permissions[] = array(
    'name' => 'edit any event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any feed content
  $permissions[] = array(
    'name' => 'edit any feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any feeditem content
  $permissions[] = array(
    'name' => 'edit any feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any op_image content
  $permissions[] = array(
    'name' => 'edit any op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any package content
  $permissions[] = array(
    'name' => 'edit any package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any page content
  $permissions[] = array(
    'name' => 'edit any page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any panel-nodes
  $permissions[] = array(
    'name' => 'edit any panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any resource content
  $permissions[] = array(
    'name' => 'edit any resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any slideshow content
  $permissions[] = array(
    'name' => 'edit any slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any topichub content
  $permissions[] = array(
    'name' => 'edit any topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any video content
  $permissions[] = array(
    'name' => 'edit any video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit canonical URL meta tag
  $permissions[] = array(
    'name' => 'edit canonical URL meta tag',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit custompage tiles
  $permissions[] = array(
    'name' => 'edit custompage tiles',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit meta tag ABSTRACT
  $permissions[] = array(
    'name' => 'edit meta tag ABSTRACT',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit meta tag COPYRIGHT
  $permissions[] = array(
    'name' => 'edit meta tag COPYRIGHT',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit meta tag DESCRIPTION
  $permissions[] = array(
    'name' => 'edit meta tag DESCRIPTION',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit meta tag KEYWORDS
  $permissions[] = array(
    'name' => 'edit meta tag KEYWORDS',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit meta tag REVISIT-AFTER
  $permissions[] = array(
    'name' => 'edit meta tag REVISIT-AFTER',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit meta tag ROBOTS
  $permissions[] = array(
    'name' => 'edit meta tag ROBOTS',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit own article content
  $permissions[] = array(
    'name' => 'edit own article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own audio content
  $permissions[] = array(
    'name' => 'edit own audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own author content
  $permissions[] = array(
    'name' => 'edit own author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own blog entries
  $permissions[] = array(
    'name' => 'edit own blog entries',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own event content
  $permissions[] = array(
    'name' => 'edit own event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own feed content
  $permissions[] = array(
    'name' => 'edit own feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own feeditem content
  $permissions[] = array(
    'name' => 'edit own feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own op_image content
  $permissions[] = array(
    'name' => 'edit own op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own package content
  $permissions[] = array(
    'name' => 'edit own package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own page content
  $permissions[] = array(
    'name' => 'edit own page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own panel-nodes
  $permissions[] = array(
    'name' => 'edit own panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit own resource content
  $permissions[] = array(
    'name' => 'edit own resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own slideshow content
  $permissions[] = array(
    'name' => 'edit own slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own topichub content
  $permissions[] = array(
    'name' => 'edit own topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own video content
  $permissions[] = array(
    'name' => 'edit own video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: execute php code
  $permissions[] = array(
    'name' => 'execute php code',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: export RDF data
  $permissions[] = array(
    'name' => 'export RDF data',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: export enabled modules
  $permissions[] = array(
    'name' => 'export enabled modules',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: export site settings
  $permissions[] = array(
    'name' => 'export site settings',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: filter and manage site content
  $permissions[] = array(
    'name' => 'filter and manage site content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: flush imagecache
  $permissions[] = array(
    'name' => 'flush imagecache',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: import RDF data
  $permissions[] = array(
    'name' => 'import RDF data',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: import enabled modules
  $permissions[] = array(
    'name' => 'import enabled modules',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: import site settings
  $permissions[] = array(
    'name' => 'import site settings',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: manage features
  $permissions[] = array(
    'name' => 'manage features',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: manipulate all queues
  $permissions[] = array(
    'name' => 'manipulate all queues',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: manipulate queues
  $permissions[] = array(
    'name' => 'manipulate queues',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: notify of path changes
  $permissions[] = array(
    'name' => 'notify of path changes',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: post comments
  $permissions[] = array(
    'name' => 'post comments',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'author',
      '3' => 'editor',
      '4' => 'web editor',
    ),
  );

  // Exported permission: post comments without approval
  $permissions[] = array(
    'name' => 'post comments without approval',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'author',
      '3' => 'editor',
      '4' => 'web editor',
    ),
  );

  // Exported permission: receive email advuser
  $permissions[] = array(
    'name' => 'receive email advuser',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: revert revisions
  $permissions[] = array(
    'name' => 'revert revisions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: schedule (un)publishing of nodes
  $permissions[] = array(
    'name' => 'schedule (un)publishing of nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: search content
  $permissions[] = array(
    'name' => 'search content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'author',
      '4' => 'editor',
      '5' => 'web editor',
    ),
  );

  // Exported permission: select different theme
  $permissions[] = array(
    'name' => 'select different theme',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: send email advuser
  $permissions[] = array(
    'name' => 'send email advuser',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: set api keys
  $permissions[] = array(
    'name' => 'set api keys',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: switch users
  $permissions[] = array(
    'name' => 'switch users',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: translate content
  $permissions[] = array(
    'name' => 'translate content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: translate interface
  $permissions[] = array(
    'name' => 'translate interface',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: upload files
  $permissions[] = array(
    'name' => 'upload files',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: use PHP for block visibility
  $permissions[] = array(
    'name' => 'use PHP for block visibility',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: use admin toolbar
  $permissions[] = array(
    'name' => 'use admin toolbar',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: use advanced search
  $permissions[] = array(
    'name' => 'use advanced search',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: use bulk exporter
  $permissions[] = array(
    'name' => 'use bulk exporter',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: use local files as feeds
  $permissions[] = array(
    'name' => 'use local files as feeds',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: use page manager
  $permissions[] = array(
    'name' => 'use page manager',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: use panels caching features
  $permissions[] = array(
    'name' => 'use panels caching features',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: use panels dashboard
  $permissions[] = array(
    'name' => 'use panels dashboard',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: use views exporter
  $permissions[] = array(
    'name' => 'use views exporter',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view advanced help index
  $permissions[] = array(
    'name' => 'view advanced help index',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view advanced help popup
  $permissions[] = array(
    'name' => 'view advanced help popup',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view advanced help topic
  $permissions[] = array(
    'name' => 'view advanced help topic',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view all panes
  $permissions[] = array(
    'name' => 'view all panes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: view date repeats
  $permissions[] = array(
    'name' => 'view date repeats',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view imagecache 400xY
  $permissions[] = array(
    'name' => 'view imagecache 400xY',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view imagecache author_photo
  $permissions[] = array(
    'name' => 'view imagecache author_photo',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view imagecache featured_image
  $permissions[] = array(
    'name' => 'view imagecache featured_image',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view imagecache package_featured
  $permissions[] = array(
    'name' => 'view imagecache package_featured',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view imagecache slideshow_image
  $permissions[] = array(
    'name' => 'view imagecache slideshow_image',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view imagecache spotlight_homepage
  $permissions[] = array(
    'name' => 'view imagecache spotlight_homepage',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view imagecache thumbnail
  $permissions[] = array(
    'name' => 'view imagecache thumbnail',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view pane admin links
  $permissions[] = array(
    'name' => 'view pane admin links',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: view post access counter
  $permissions[] = array(
    'name' => 'view post access counter',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: view revisions
  $permissions[] = array(
    'name' => 'view revisions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: view uploaded files
  $permissions[] = array(
    'name' => 'view uploaded files',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'author',
      '4' => 'editor',
      '5' => 'web editor',
    ),
  );

  // Exported permission: view user content list
  $permissions[] = array(
    'name' => 'view user content list',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  return $permissions;
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _op_defaults_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'filter_default_format';
  $strongarm->value = '1';

  $export['filter_default_format'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_article_pattern';
  $strongarm->value = 'article/[title-raw]';

  $export['pathauto_node_article_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_audio_pattern';
  $strongarm->value = 'audio/[title-raw]';

  $export['pathauto_node_audio_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_author_pattern';
  $strongarm->value = 'author/[title-raw]';

  $export['pathauto_node_author_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_blog_pattern';
  $strongarm->value = 'blog/[title-raw]';

  $export['pathauto_node_blog_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_event_pattern';
  $strongarm->value = 'event/[title-raw]';

  $export['pathauto_node_event_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_feeditem_pattern';
  $strongarm->value = 'feed-item/[title-raw]';

  $export['pathauto_node_feeditem_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_op_image_pattern';
  $strongarm->value = 'image/[title-raw]';

  $export['pathauto_node_op_image_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_package_pattern';
  $strongarm->value = 'package/[title-raw]';

  $export['pathauto_node_package_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_pattern';
  $strongarm->value = 'content/[title-raw]';

  $export['pathauto_node_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_resource_pattern';
  $strongarm->value = 'resource/[title-raw]';

  $export['pathauto_node_resource_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_slideshow_pattern';
  $strongarm->value = 'slideshow/[title-raw]';

  $export['pathauto_node_slideshow_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_topichub_pattern';
  $strongarm->value = 'topic-hub/[title-raw]';

  $export['pathauto_node_topichub_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_twitter_item_pattern';
  $strongarm->value = 'twitter-item/[title-raw]';

  $export['pathauto_node_twitter_item_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_video_pattern';
  $strongarm->value = 'video/[title-raw]';

  $export['pathauto_node_video_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'preprocess_css';
  $strongarm->value = 'theme';

  $export['preprocess_css'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'preprocess_css_module';
  $strongarm->value = '';

  $export['preprocess_css_module'] = $strongarm;
  return $export;
}
