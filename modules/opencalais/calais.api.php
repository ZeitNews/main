<?php

/**
 * @file
 * Documentation of hooks.
 */

/**
 * Invoked after data has been returned from Calais but before it is processed.
 */
function hook_calais_preprocess(&$node, &$keywords) {
}

/**
 * Invoked after data has been returned from Calais and after it has been processed.
 */
function hook_calais_postprocess(&$node, &$keywords) {
}

/**
 * Invoked before a Node body is sent to Calais.
 */
function hook_calais_body_alter(&$body, $loaded_node) {
}

/**
* Alter a URL before Semantic Proxy processes it.
*
* @param $url 
*    The URL to alter.
 */
function hook_semanticproxy_url_alter(&$url) {
  // SemanticProxy obeys robots.txt and as such will not follow redirects, etc. For example,
  // RSS feeds for Google News Search will send you through Google News to redirect to the real source.
  // SemanticProxy will give a <em>Content Permissions Validator Exception</em> and not follow the 
  // link b/c Google's robots.txt disallows following /news.  We try to strip those out.
  $host = parse_url($url, PHP_URL_HOST);

  // Google's robot.txt disallows the follow by bots, so lets extract the real source
  if ($host == 'news.google.com') {
    $querystring = parse_url($url, PHP_URL_QUERY);

    // Split on &, but not if the & is in an html entity. This is a better impl of parse_str().
    $args = preg_split('|&(?!.[a-z0-9]{1,6}+;)|ims', $querystring);
    if(!is_array($args)) {
      return;
    }

    // Process query string args, find the 'url' arg and return the value if it's a valid URL
    foreach($args as $arg) {
      list($key, $val) = explode('=', $arg, 2);
      if ($key == 'url') {
        $val = urldecode($val);
        if(valid_url($val, TRUE)) {
          $url = $val;
          return;
        }
      }
    }
  }
}
