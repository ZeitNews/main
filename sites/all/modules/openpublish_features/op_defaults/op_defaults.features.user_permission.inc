<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function op_defaults_user_default_permissions() {
  $permissions = array();

  // Exported permission: Use PHP input for field settings (dangerous - grant with care)
  $permissions['Use PHP input for field settings (dangerous - grant with care)'] = array(
    'name' => 'Use PHP input for field settings (dangerous - grant with care)',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: access RDF data
  $permissions['access RDF data'] = array(
    'name' => 'access RDF data',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: access administration pages
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access advuser
  $permissions['access advuser'] = array(
    'name' => 'access advuser',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: access all views
  $permissions['access all views'] = array(
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
  $permissions['access calais'] = array(
    'name' => 'access calais',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access calais rdf
  $permissions['access calais rdf'] = array(
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
  $permissions['access ckeditor'] = array(
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
  $permissions['access comments'] = array(
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
  $permissions['access content'] = array(
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
  $permissions['access devel information'] = array(
    'name' => 'access devel information',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: access openpublish admin pages
  $permissions['access openpublish admin pages'] = array(
    'name' => 'access openpublish admin pages',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access premium content
  $permissions['access premium content'] = array(
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
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access statistics
  $permissions['access statistics'] = array(
    'name' => 'access statistics',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: access user profiles
  $permissions['access user profiles'] = array(
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
  $permissions['add list of open ids'] = array(
    'name' => 'add list of open ids',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer RDF data
  $permissions['administer RDF data'] = array(
    'name' => 'administer RDF data',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer RDF repositories
  $permissions['administer RDF repositories'] = array(
    'name' => 'administer RDF repositories',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer actions
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer advanced pane settings
  $permissions['administer advanced pane settings'] = array(
    'name' => 'administer advanced pane settings',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer advuser
  $permissions['administer advuser'] = array(
    'name' => 'administer advuser',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer blocks
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer calais
  $permissions['administer calais'] = array(
    'name' => 'administer calais',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer calais api
  $permissions['administer calais api'] = array(
    'name' => 'administer calais api',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer calais geo
  $permissions['administer calais geo'] = array(
    'name' => 'administer calais geo',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer ckeditor
  $permissions['administer ckeditor'] = array(
    'name' => 'administer ckeditor',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer comments
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer content types
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer custom content
  $permissions['administer custom content'] = array(
    'name' => 'administer custom content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer custompage
  $permissions['administer custompage'] = array(
    'name' => 'administer custompage',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer features
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer feedapi
  $permissions['administer feedapi'] = array(
    'name' => 'administer feedapi',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer files
  $permissions['administer files'] = array(
    'name' => 'administer files',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer filters
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer flags
  $permissions['administer flags'] = array(
    'name' => 'administer flags',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer flash
  $permissions['administer flash'] = array(
    'name' => 'administer flash',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer imageapi
  $permissions['administer imageapi'] = array(
    'name' => 'administer imageapi',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer imagecache
  $permissions['administer imagecache'] = array(
    'name' => 'administer imagecache',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer imagecrop
  $permissions['administer imagecrop'] = array(
    'name' => 'administer imagecrop',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer imce(execute PHP)
  $permissions['administer imce(execute PHP)'] = array(
    'name' => 'administer imce(execute PHP)',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer languages
  $permissions['administer languages'] = array(
    'name' => 'administer languages',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer login destination
  $permissions['administer login destination'] = array(
    'name' => 'administer login destination',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer menu
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer meta tags
  $permissions['administer meta tags'] = array(
    'name' => 'administer meta tags',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer mollom
  $permissions['administer mollom'] = array(
    'name' => 'administer mollom',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer morelikethis
  $permissions['administer morelikethis'] = array(
    'name' => 'administer morelikethis',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer nodequeue
  $permissions['administer nodequeue'] = array(
    'name' => 'administer nodequeue',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer nodes
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer page manager
  $permissions['administer page manager'] = array(
    'name' => 'administer page manager',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer pane access
  $permissions['administer pane access'] = array(
    'name' => 'administer pane access',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer pane visibility
  $permissions['administer pane visibility'] = array(
    'name' => 'administer pane visibility',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer panel-nodes
  $permissions['administer panel-nodes'] = array(
    'name' => 'administer panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer panels layouts
  $permissions['administer panels layouts'] = array(
    'name' => 'administer panels layouts',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer pathauto
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer permissions
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer scheduler
  $permissions['administer scheduler'] = array(
    'name' => 'administer scheduler',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer search
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer site configuration
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer taxonomy
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer topichubs
  $permissions['administer topichubs'] = array(
    'name' => 'administer topichubs',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer url aliases
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: administer users
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: administer views
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: advanced feedapi options
  $permissions['advanced feedapi options'] = array(
    'name' => 'advanced feedapi options',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: bypass mollom protection
  $permissions['bypass mollom protection'] = array(
    'name' => 'bypass mollom protection',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: change own username
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: clear all drupal cache
  $permissions['clear all drupal cache'] = array(
    'name' => 'clear all drupal cache',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: create article content
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create audio content
  $permissions['create audio content'] = array(
    'name' => 'create audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create author content
  $permissions['create author content'] = array(
    'name' => 'create author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create blog entries
  $permissions['create blog entries'] = array(
    'name' => 'create blog entries',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create event content
  $permissions['create event content'] = array(
    'name' => 'create event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create feed content
  $permissions['create feed content'] = array(
    'name' => 'create feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create feeditem content
  $permissions['create feeditem content'] = array(
    'name' => 'create feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create op_image content
  $permissions['create op_image content'] = array(
    'name' => 'create op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create package content
  $permissions['create package content'] = array(
    'name' => 'create package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create page content
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create panel-nodes
  $permissions['create panel-nodes'] = array(
    'name' => 'create panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: create resource content
  $permissions['create resource content'] = array(
    'name' => 'create resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create slideshow content
  $permissions['create slideshow content'] = array(
    'name' => 'create slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create topichub content
  $permissions['create topichub content'] = array(
    'name' => 'create topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: create url aliases
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: create video content
  $permissions['create video content'] = array(
    'name' => 'create video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: crop any image with toolbox
  $permissions['crop any image with toolbox'] = array(
    'name' => 'crop any image with toolbox',
    'roles' => array(
      '0' => 'editor',
      '1' => 'web editor',
    ),
  );

  // Exported permission: crop images with toolbox
  $permissions['crop images with toolbox'] = array(
    'name' => 'crop images with toolbox',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete any article content
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any audio content
  $permissions['delete any audio content'] = array(
    'name' => 'delete any audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any author content
  $permissions['delete any author content'] = array(
    'name' => 'delete any author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any blog entry
  $permissions['delete any blog entry'] = array(
    'name' => 'delete any blog entry',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any event content
  $permissions['delete any event content'] = array(
    'name' => 'delete any event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any feed content
  $permissions['delete any feed content'] = array(
    'name' => 'delete any feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any feeditem content
  $permissions['delete any feeditem content'] = array(
    'name' => 'delete any feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any op_image content
  $permissions['delete any op_image content'] = array(
    'name' => 'delete any op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any package content
  $permissions['delete any package content'] = array(
    'name' => 'delete any package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any page content
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any panel-nodes
  $permissions['delete any panel-nodes'] = array(
    'name' => 'delete any panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any resource content
  $permissions['delete any resource content'] = array(
    'name' => 'delete any resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any slideshow content
  $permissions['delete any slideshow content'] = array(
    'name' => 'delete any slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any topichub content
  $permissions['delete any topichub content'] = array(
    'name' => 'delete any topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete any video content
  $permissions['delete any video content'] = array(
    'name' => 'delete any video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete own article content
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own audio content
  $permissions['delete own audio content'] = array(
    'name' => 'delete own audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own author content
  $permissions['delete own author content'] = array(
    'name' => 'delete own author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own blog entries
  $permissions['delete own blog entries'] = array(
    'name' => 'delete own blog entries',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own event content
  $permissions['delete own event content'] = array(
    'name' => 'delete own event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own feed content
  $permissions['delete own feed content'] = array(
    'name' => 'delete own feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own feeditem content
  $permissions['delete own feeditem content'] = array(
    'name' => 'delete own feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own op_image content
  $permissions['delete own op_image content'] = array(
    'name' => 'delete own op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own package content
  $permissions['delete own package content'] = array(
    'name' => 'delete own package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own page content
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own panel-nodes
  $permissions['delete own panel-nodes'] = array(
    'name' => 'delete own panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete own resource content
  $permissions['delete own resource content'] = array(
    'name' => 'delete own resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own slideshow content
  $permissions['delete own slideshow content'] = array(
    'name' => 'delete own slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete own topichub content
  $permissions['delete own topichub content'] = array(
    'name' => 'delete own topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: delete own video content
  $permissions['delete own video content'] = array(
    'name' => 'delete own video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: delete revisions
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: display source code
  $permissions['display source code'] = array(
    'name' => 'display source code',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit any article content
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any audio content
  $permissions['edit any audio content'] = array(
    'name' => 'edit any audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any author content
  $permissions['edit any author content'] = array(
    'name' => 'edit any author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any blog entry
  $permissions['edit any blog entry'] = array(
    'name' => 'edit any blog entry',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any event content
  $permissions['edit any event content'] = array(
    'name' => 'edit any event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any feed content
  $permissions['edit any feed content'] = array(
    'name' => 'edit any feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any feeditem content
  $permissions['edit any feeditem content'] = array(
    'name' => 'edit any feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any op_image content
  $permissions['edit any op_image content'] = array(
    'name' => 'edit any op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any package content
  $permissions['edit any package content'] = array(
    'name' => 'edit any package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any page content
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any panel-nodes
  $permissions['edit any panel-nodes'] = array(
    'name' => 'edit any panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any resource content
  $permissions['edit any resource content'] = array(
    'name' => 'edit any resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any slideshow content
  $permissions['edit any slideshow content'] = array(
    'name' => 'edit any slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any topichub content
  $permissions['edit any topichub content'] = array(
    'name' => 'edit any topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit any video content
  $permissions['edit any video content'] = array(
    'name' => 'edit any video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit custompage tiles
  $permissions['edit custompage tiles'] = array(
    'name' => 'edit custompage tiles',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: edit own article content
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own audio content
  $permissions['edit own audio content'] = array(
    'name' => 'edit own audio content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own author content
  $permissions['edit own author content'] = array(
    'name' => 'edit own author content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own blog entries
  $permissions['edit own blog entries'] = array(
    'name' => 'edit own blog entries',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own event content
  $permissions['edit own event content'] = array(
    'name' => 'edit own event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own feed content
  $permissions['edit own feed content'] = array(
    'name' => 'edit own feed content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own feeditem content
  $permissions['edit own feeditem content'] = array(
    'name' => 'edit own feeditem content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own op_image content
  $permissions['edit own op_image content'] = array(
    'name' => 'edit own op_image content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own package content
  $permissions['edit own package content'] = array(
    'name' => 'edit own package content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own page content
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own panel-nodes
  $permissions['edit own panel-nodes'] = array(
    'name' => 'edit own panel-nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: edit own resource content
  $permissions['edit own resource content'] = array(
    'name' => 'edit own resource content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own slideshow content
  $permissions['edit own slideshow content'] = array(
    'name' => 'edit own slideshow content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own topichub content
  $permissions['edit own topichub content'] = array(
    'name' => 'edit own topichub content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: edit own video content
  $permissions['edit own video content'] = array(
    'name' => 'edit own video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: execute php code
  $permissions['execute php code'] = array(
    'name' => 'execute php code',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: export RDF data
  $permissions['export RDF data'] = array(
    'name' => 'export RDF data',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: export enabled modules
  $permissions['export enabled modules'] = array(
    'name' => 'export enabled modules',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: export site settings
  $permissions['export site settings'] = array(
    'name' => 'export site settings',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: filter and manage site content
  $permissions['filter and manage site content'] = array(
    'name' => 'filter and manage site content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: flush imagecache
  $permissions['flush imagecache'] = array(
    'name' => 'flush imagecache',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: import RDF data
  $permissions['import RDF data'] = array(
    'name' => 'import RDF data',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: import enabled modules
  $permissions['import enabled modules'] = array(
    'name' => 'import enabled modules',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: import site settings
  $permissions['import site settings'] = array(
    'name' => 'import site settings',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: manage features
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: manipulate all queues
  $permissions['manipulate all queues'] = array(
    'name' => 'manipulate all queues',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: manipulate queues
  $permissions['manipulate queues'] = array(
    'name' => 'manipulate queues',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: notify of path changes
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: post comments
  $permissions['post comments'] = array(
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
  $permissions['post comments without approval'] = array(
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
  $permissions['receive email advuser'] = array(
    'name' => 'receive email advuser',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: revert revisions
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: schedule (un)publishing of nodes
  $permissions['schedule (un)publishing of nodes'] = array(
    'name' => 'schedule (un)publishing of nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: search content
  $permissions['search content'] = array(
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
  $permissions['select different theme'] = array(
    'name' => 'select different theme',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: send email advuser
  $permissions['send email advuser'] = array(
    'name' => 'send email advuser',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: set api keys
  $permissions['set api keys'] = array(
    'name' => 'set api keys',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: switch users
  $permissions['switch users'] = array(
    'name' => 'switch users',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: translate content
  $permissions['translate content'] = array(
    'name' => 'translate content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: translate interface
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: upload files
  $permissions['upload files'] = array(
    'name' => 'upload files',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: use PHP for block visibility
  $permissions['use PHP for block visibility'] = array(
    'name' => 'use PHP for block visibility',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: use admin toolbar
  $permissions['use admin toolbar'] = array(
    'name' => 'use admin toolbar',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: use advanced search
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: use bulk exporter
  $permissions['use bulk exporter'] = array(
    'name' => 'use bulk exporter',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: use page manager
  $permissions['use page manager'] = array(
    'name' => 'use page manager',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: use panels caching features
  $permissions['use panels caching features'] = array(
    'name' => 'use panels caching features',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: use panels dashboard
  $permissions['use panels dashboard'] = array(
    'name' => 'use panels dashboard',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: use panels in place editing
  $permissions['use panels in place editing'] = array(
    'name' => 'use panels in place editing',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: use views exporter
  $permissions['use views exporter'] = array(
    'name' => 'use views exporter',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view advanced help index
  $permissions['view advanced help index'] = array(
    'name' => 'view advanced help index',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view advanced help popup
  $permissions['view advanced help popup'] = array(
    'name' => 'view advanced help popup',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view advanced help topic
  $permissions['view advanced help topic'] = array(
    'name' => 'view advanced help topic',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view all panes
  $permissions['view all panes'] = array(
    'name' => 'view all panes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: view content workflow state
  $permissions['view content workflow state'] = array(
    'name' => 'view content workflow state',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: view date repeats
  $permissions['view date repeats'] = array(
    'name' => 'view date repeats',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: view documentcloud documents
  $permissions['view documentcloud documents'] = array(
    'name' => 'view documentcloud documents',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'author',
      '4' => 'editor',
      '5' => 'web editor',
    ),
  );

  // Exported permission: view imagecache 400xY
  $permissions['view imagecache 400xY'] = array(
    'name' => 'view imagecache 400xY',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: view imagecache author_photo
  $permissions['view imagecache author_photo'] = array(
    'name' => 'view imagecache author_photo',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: view imagecache featured_image
  $permissions['view imagecache featured_image'] = array(
    'name' => 'view imagecache featured_image',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: view imagecache package_featured
  $permissions['view imagecache package_featured'] = array(
    'name' => 'view imagecache package_featured',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: view imagecache slideshow_image
  $permissions['view imagecache slideshow_image'] = array(
    'name' => 'view imagecache slideshow_image',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: view imagecache spotlight_homepage
  $permissions['view imagecache spotlight_homepage'] = array(
    'name' => 'view imagecache spotlight_homepage',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: view imagecache thumbnail
  $permissions['view imagecache thumbnail'] = array(
    'name' => 'view imagecache thumbnail',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'web editor',
    ),
  );

  // Exported permission: view pane admin links
  $permissions['view pane admin links'] = array(
    'name' => 'view pane admin links',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
      '2' => 'web editor',
    ),
  );

  // Exported permission: view post access counter
  $permissions['view post access counter'] = array(
    'name' => 'view post access counter',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: view revisions
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'author',
      '2' => 'editor',
      '3' => 'web editor',
    ),
  );

  // Exported permission: view uploaded files
  $permissions['view uploaded files'] = array(
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
  $permissions['view user content list'] = array(
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
