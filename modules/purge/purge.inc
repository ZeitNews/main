<?php

/**
 * @file
 * Contains the main purging functionality and error handling
 */

/**
 * Purges urls from reverse proxy caches
 *
 * @param $purge_urls
 *   Array of urls to remove from the proxy cache using the http purge method.
 *
 * @return
 *   Array of urls and their http status codes after purging.
 */
function purge_urls($purge_urls) {
  // Get settings
  $proxy_urls = explode(' ', variable_get('purge_proxy_urls', 'http://localhost:80'));
  $purge_requests = array();
  $current_purge_request = 0;

  // Find out the url parts we need from the urls to be purged
  foreach ($purge_urls as $purge_url) {
    $purge_url_parts = parse_url($purge_url);
    // Determine the host
    $purge_url_host = $purge_url_parts['host'];
    // Add portnames to the host if any are set
    if (array_key_exists('port', $purge_url_parts)) {
      $purge_url_host = $purge_url_host . ":" . $purge_url_parts['port'];
    }

    // Process all urls for each proxy
    foreach ($proxy_urls as $proxy_url) {
      // Add url and proxy url to the array for later processing
      $purge_requests[$current_purge_request]['purge_url'] = $purge_url;
      $purge_requests[$current_purge_request]['proxy_url'] = $proxy_url;

      // Select which method to use
      $proxy_url_parts = parse_url($proxy_url);
      if (array_key_exists('query', $proxy_url_parts)) {
        if (strstr($proxy_url_parts['query'], 'purge_method=get')) {
          $method = 'get';
        }
        if (strstr($proxy_url_parts['query'], 'purge_method=ah')) {
          $method = 'ah';
        }

      }
      else {
        $method = 'purge';
      }

      // The default PURGE method. Native to Squid and configurable in Varnish and Nginx
      if ($method == 'purge') {
        // Make it a PURGE request (not GET or POST)
        $purge_requests[$current_purge_request]['request_method'] = 'PURGE';
        // Construct a new url base
        $proxy_url_base = $proxy_url_parts['scheme'] . "://" . $proxy_url_parts['host'];
        if (array_key_exists('port', $proxy_url_parts)) {
          $proxy_url_base = $proxy_url_base . ":" . $proxy_url_parts['port'];
        }
        // Construct a new path retaining the url query string (#1299776 by djboddydrake)
        $purge_path = array_key_exists('query', $purge_url_parts) ? $purge_url_parts['path'] 
          . '?' . $purge_url_parts['query'] : $purge_url_parts['path'];
        $purge_requests[$current_purge_request]['purge_url'] = $proxy_url_base . $purge_path;
        // Set the host header to the sites hostname
        $purge_requests[$current_purge_request]['headers'] = array("Host: " . $purge_url_host);
      }

      // The GET method, native suport on nginx
      elseif ($method == 'get') {
        $purge_requests[$current_purge_request]['request_method'] = 'GET';
        // Construct a new url
        $proxy_url_base = $proxy_url_parts['scheme'] . "://" . $proxy_url_parts['host'];
        if (array_key_exists('port', $proxy_url_parts)) {
          $proxy_url_base = $proxy_url_base . ":" . $proxy_url_parts['port'];
        }
        if (array_key_exists('path', $proxy_url_parts)) {
          $proxy_url_base = $proxy_url_base . $proxy_url_parts['path'];
        }
        $purge_requests[$current_purge_request]['purge_url'] = $proxy_url_base . $purge_url_parts['path'];
        //  Set the host header to the sites hostname
        $purge_requests[$current_purge_request]['headers'] = array("Host: " . $purge_url_host);
      }

      // The AH (Acquia Hosting) option.
      elseif ($method == 'ah') {
        // Make it a PURGE request (not GET or POST)
        $purge_requests[$current_purge_request]['request_method'] = 'PURGE';
        // Just use the url passed by expire
        $purge_requests[$current_purge_request]['purge_url'] = $purge_url;
        //  Set the Acquia purge header to the Acquia Hosting site name
        $purge_requests[$current_purge_request]['headers'] = array('Accept-Encoding: gzip', 'X-Acquia-Purge:' . $_SERVER['AH_SITE_NAME']);
      }
      $current_purge_request++;
    }
  }
  // Issue the requests using curl (for now)
  $purge_request_results = purge_issue_requests_curl($purge_requests);
  return $purge_request_results;
}

/**
 * Issue purge request using curl
 *
 */
function purge_issue_requests_curl($purges) {
  // Initialise a curl_multi object
  $curl_purges = curl_multi_init();
  $current_curl_purge = 0;
  foreach ($purges as $purge) {
    $curl_purge[$current_curl_purge] = curl_init();
    curl_setopt($curl_purge[$current_curl_purge], CURLOPT_CUSTOMREQUEST, $purge['request_method']);
    curl_setopt($curl_purge[$current_curl_purge], CURLOPT_URL, $purge['purge_url']);
    curl_setopt($curl_purge[$current_curl_purge], CURLOPT_HEADER, 1);
    curl_setopt($curl_purge[$current_curl_purge], CURLOPT_HTTPHEADER, $purge['headers']);
    curl_setopt($curl_purge[$current_curl_purge], CURLOPT_RETURNTRANSFER, 0);
    curl_multi_add_handle($curl_purges, $curl_purge[$current_curl_purge]);
    $current_curl_purge++;
  }
  // Execute the purge requests
  ob_start();
  do {
    $mrc = curl_multi_exec($curl_purges, $running);
  } while ($mrc == CURLM_CALL_MULTI_PERFORM);
  ob_end_clean();

  // Result collection. Collects the http code returned for each url purged
  $current_curl_purge = 0;
  foreach ($purges as $purge) {
    $info = curl_getinfo($curl_purge[$current_curl_purge]);
    $purges[$current_curl_purge]['http_code'] = $info['http_code'];
    curl_multi_remove_handle($curl_purges, $curl_purge[$current_curl_purge]);
    $current_curl_purge++;
  }
  curl_multi_close($curl_purges);
  return $purges;
}


/**
 * Logs successful purges and errors to the watchdog.
 *
 * @param $purge_request_results
 *   array of url with their http status code
 */
function purge_logging($purge_request_results) {
  $purge_success = 0;
  $purge_blocking = array();
  $purge_log = array();
  foreach ($purge_request_results as $purge_request_result) {
    switch ($purge_request_result['http_code']) {
      // First check if everything went ok.
      case 200:
        $purge_log[] = $purge_request_result['purge_url'] .' on '. $purge_request_result['proxy_url'] .' Ok';
        $purge_success++;
        break;
      // Notice if the request was not found in the proxy cache
      case 404:
        $purge_log[] = $purge_request_result['purge_url'] .' on '. $purge_request_result['proxy_url'] .' Not Found';
        $purge_success++;
        break;
      // Collect all proxy hosts that are blocking the url requests
      case 405:
        $purge_log[] = $purge_request_result['purge_url'] .' on '. $purge_request_result['proxy_url'] .' Forbidden';
        $purge_blocking[] = parse_url($purge_request_result['url'], PHP_URL_HOST);
        break;
      // Collect all urls and their http error codes
      default:
        $purge_log[] = $purge_request_result['purge_url'] . ' on '
          . $purge_request_result['proxy_url'] . ' ' . $purge_request_result['http_code'];
        break;
    }

  }

  // Watchdog barking
  $purge_errors = count($purge_request_results) - $purge_success;
  // Just a notice when all is ok
  if ($purge_errors == 0) {
    if ($purge_success == 1) {
      watchdog(
        'purge',
        '1 URL has been successfully purged from the reverse proxy caches: !purge_log',
        array('!purge_log' => expire_print_r($purge_log))
      );
    }
    else {
      watchdog(
        'purge',
        '!purge_success_count URLs have been successfully purged from the reverse proxy caches: !purge_log',
        array('!purge_success_count' => $purge_success, '!purge_log' => expire_print_r($purge_log))
      );
    }
  }
  else {
    // Report all urls with errors
    if ($purge_errors == 1) {
      watchdog(
        'purge',
        '1 error has been encountered when purging URLs !purge_log',
        array('!purge_log' => expire_print_r($purge_log)),
        $severity = WATCHDOG_ERROR
      );
    }
    else {
      watchdog(
        'purge',
        '!purge_errors_count errors have been encountered when purging these URLs. !purge_log',
        array('!purge_errors_count' => count($purge_errors), '!purge_log' => expire_print_r($purge_log)),
        $severity = WATCHDOG_ERROR
      );
    }
    // Report on proxy servers that block the purge requests.
    if (!empty($purge_blocking)) {
      foreach ($purge_blocking as $purge_blocking_server) {
        watchdog(
          'purge',
          'The proxy server host %blocking_server is blocking purge requests. Please review the proxy configuration.',
          array('%blocking_server' => $purge_blocking),
          $severity = WATCHDOG_ERROR
        );
      }
    }
  }
}
