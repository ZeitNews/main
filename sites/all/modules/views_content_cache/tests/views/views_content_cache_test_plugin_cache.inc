<?php

/**
 * Simple testing plugin for Views content cache cache plugin.
 */
class views_content_cache_test_plugin_cache extends views_content_cache_plugin_cache {

  function post_render(&$output) {

    // If the results came from the cache, indicate
    if (!empty($this->view->build_info['cached_results'])) {
      $output .= '[served results from views_content_cache]';
    }

  }

  /**
   * Retrieve data from the cache.
   *
   * A plugin should override this to provide specialized caching behavior.
   */
  function cache_get($type) {
    $cutoff = $this->cache_expire($type);
    switch ($type) {
      case 'query':
        // Not supported currently, but this is certainly where we'd put it.
        return FALSE;
      case 'results':
        // Values to set: $view->result, $view->total_rows, $view->execute_time,
        // $view->pager['current_page'].
        if ($cache = cache_get($this->get_results_key(), $this->table)) {
          if (!$cutoff || $cache->created > $cutoff) {
            $this->view->result = $cache->data['result'];
            $this->view->total_rows = $cache->data['total_rows'];
            $this->view->pager = $cache->data['pager'];
            $this->view->execute_time = 0;
            $this->view->build_info['cached_results'] = TRUE;
            return TRUE;
          }
        }
        return FALSE;
      case 'output':
        if ($cache = cache_get($this->get_output_key(), $this->table)) {
          if (!$cutoff || $cache->created > $cutoff) {
            $this->storage = $cache->data;
            $this->view->display_handler->output = $cache->data['output'] . '[Served output from views_content_cache]' . "$type: Maximum age: " . format_interval($cache->created - $cutoff);
            $this->restore_headers();
            return TRUE;
          }
          elseif (!empty($cutoff)) {
            print_r('Results to old: ' . format_interval($cache->created - $cutoff));
          }
        }
        return FALSE;
    }
  }
}
