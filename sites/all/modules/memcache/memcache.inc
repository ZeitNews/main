<?php
// $Id: memcache.inc,v 1.15.2.8.2.28 2010/12/28 11:11:27 robertDouglass Exp $

/** Implementation of cache.inc with memcache logic included **/

require_once 'dmemcache.inc';
require_once variable_get('memcache_extra_include', 'database.inc');

/**
 * Defines the period after which wildcard clears are not considered valid.
 */
define('MEMCACHE_WILDCARD_INVALIDATE', 86400 * 28);

/**
 * Return data from the persistent cache.
 * 
 * Data may be stored as either plain text or as serialized data.
 * cache_get() will automatically return unserialized objects and arrays.
 *
 * @param $cid
 *   The cache ID of the data to retrieve.
 * @param $table
 *   The table $table to store the data in. Valid core values are 'cache_filter',
 *   'cache_menu', 'cache_page', or 'cache' for the default cache.
 */
function cache_get($cid, $table = 'cache') {
  // Handle excluded bins first.
  $bins = variable_get('memcache_bins', array());
  if (!is_null($table) && isset($bins[$table]) && $bins[$table] == 'database') {
    return _cache_get($cid, $table);
  }

  // Determine when the current table was last flushed.
  $cache_flush = variable_get("cache_flush_$table", 0);
  // Retrieve the item from the cache.
  $cache = dmemcache_get($cid, $table);

  if (!is_object($cache)) {
    return FALSE;
  }

  $wildcard_flushes = variable_get('memcache_wildcard_flushes', array());
  $wildcard_invalidate = variable_get('memcache_wildcard_invalidate', MEMCACHE_WILDCARD_INVALIDATE);

  // Only validate against wildcard flushes if this table has seen a recent
  // wildcard flush, as there is overhead in checking for wildcard flushes.
  if (!empty($wildcard_flushes[$table]) &&
      max($wildcard_flushes[$table]) >= ($_SERVER['REQUEST_TIME'] - $wildcard_invalidate)) {
    // Previously cached content won't have ->flushes defined.  We could
    // force flush, but instead leave this up to the site admin.
    $flushes = isset($cache->flushes) ? (int)$cache->flushes : 0;
    if ($flushes < memcache_wildcard_flushes($cid, $table)) {
      return FALSE;
    }
  }

  $cache_tables = isset($_SESSION['cache_flush']) ? $_SESSION['cache_flush'] : NULL;
  $cache_lifetime = variable_get('cache_lifetime', 0);
  if (is_array($cache_tables) && !empty($cache_tables) && $cache_lifetime) {
    // Expire the $_SESSION['cache_flush'] variable array if it is older than
    // the minimum cache lifetime, since after that the $cache_flush variable
    // will take over.
    if (max($cache_tables) < ($_SERVER['REQUEST_TIME'] - $cache_lifetime)) {
      unset($_SESSION['cache_flush']);
      $cache_tables = NULL;
    }
  }

  // Items cached before the cache was last flushed are no longer valid.
  if ($cache_lifetime && $cache->created && $cache_flush &&
      ($cache->created < $cache_flush) &&
      (($_SERVER['REQUEST_TIME'] - $cache->created >= $cache_lifetime)) ||
      (is_array($cache_tables) && isset($cache_tables[$table]) &&
      $cache_tables[$table] >= $cache->created)) {
    // Cache item expired, return FALSE.
    return FALSE;
  }
  return $cache;
}

/**
 * Store data in memcache.
 *
 * @param $cid
 *   The cache ID of the data to store.
 * @param $data
 *   The data to store in the cache. Complex data types will be automatically
 *   serialized before insertion. Strings will be stored as plain text and 
 *   not serialized.
 * @param $table
 *   The table $table to store the data in. Valid core values are 'cache_filter',
 *   'cache_menu', 'cache_page', or 'cache'.
 * @param $expire
 *   One of the following values:
 *   - CACHE_PERMANENT: Indicates that the item should never be removed unless
 *     explicitly told to using cache_clear_all() with a cache ID.
 *   - CACHE_TEMPORARY: Indicates that the item should be removed at the next
 *     general cache wipe.
 *   - A Unix timestamp: Indicates that the item should be kept at least until
 *     the given time, after which it behaves like CACHE_TEMPORARY.
 * @param $headers
 *   A string containing HTTP header information for cached pages.
 */
function cache_set($cid, $data, $table = 'cache', $expire = CACHE_PERMANENT, $headers = NULL) {
  // Handle database fallback first.
  $bins = variable_get('memcache_bins', array());
  if (!is_null($table) && isset($bins[$table]) && $bins[$table] == 'database') {
    return _cache_set($cid, $data, $table, $expire, $headers);
  }
  
  $created = $_SERVER['REQUEST_TIME'];

  // Create new cache object.
  $cache = new stdClass;
  $cache->cid = $cid;
  $cache->data = is_object($data) ? memcache_clone($data) : $data;
  $cache->created = $created;
  $cache->headers = $headers;
  // Record the previous number of wildcard flushes affecting our cid.
  $cache->flushes = memcache_wildcard_flushes($cid, $table);
  if ($expire == CACHE_TEMPORARY) {
    // Convert CACHE_TEMPORARY (-1) into something that will live in memcache
    // until the next flush.
    $cache->expire = $_SERVER['REQUEST_TIME'] + 2591999;
  }
  // Expire time is in seconds if less than 30 days, otherwise is a timestamp.
  else if ($expire != CACHE_PERMANENT && $expire < 2592000) {
    // Expire is expressed in seconds, convert to the proper future timestamp
    // as expected in dmemcache_get().
    $cache->expire = $_SERVER['REQUEST_TIME'] + $expire;
  }
  else {
    $cache->expire = $expire;
  }

  // We manually track the expire time in $cache->expire.  When the object
  // expires, we only allow one request to rebuild it to avoid cache stampedes.
  // Other requests for the expired object while it is still being rebuilt get
  // the expired object.
  dmemcache_set($cid, $cache, 0, $table);
}

/**
 *
 * Expire data from the cache. If called without arguments, expirable
 * entries will be cleared from the cache_page and cache_block tables.
 *
 * Memcache logic is simpler than the core cache because memcache doesn't have
 * a minimum cache lifetime consideration (it handles it internally), and 
 * doesn't support wildcards.  Wildcard flushes result in the entire table
 * being flushed.
 *
 * @param $cid
 *   If set, the cache ID to delete. Otherwise, all cache entries that can
 *   expire are deleted.
 *
 * @param $table
 *   If set, the table $table to delete from. Mandatory
 *   argument if $cid is set.
 *
 * @param $wildcard
 *   If set to TRUE, the $cid is treated as a substring
 *   to match rather than a complete ID. The match is a right hand
 *   match. If '*' is given as $cid, the table $table will be emptied.
 */
function cache_clear_all($cid = NULL, $table = NULL, $wildcard = FALSE) {
  // Handle database fallback first.
  $bins = variable_get('memcache_bins', array());
  if (!is_null($table) && isset($bins[$table]) && $bins[$table] == 'database') {
    return _cache_clear_all($cid, $table, $wildcard);
  }
  
  // Default behavior for when cache_clear_all() is called without parameters
  // is to clear all of the expirable entries in the block and page caches.
  if (!isset($cid) && !isset($table)) {
    cache_clear_all('*', 'cache_block', TRUE);
    cache_clear_all('*', 'cache_page', TRUE);
    return;
  }
  if (empty($cid) || $wildcard === TRUE) {
    // system_cron() flushes all cache bins returned by hook_flush_caches()
    // with cache_clear_all(NULL, $bin); This is for garbage collection with
    // the database cache, but serves no purpose with memcache. So return
    // early here.
    if (!isset($cid)) {
      return;
    }
    elseif ($cid == '*') {
      $cid = '';
    }
    if (variable_get('cache_lifetime', 0) && empty($cid)) {
      // Update the timestamp of the last global flushing of this table.  When
      // retrieving data from this table, we will compare the cache creation
      // time minus the cache_flush time to the cache_lifetime to determine
      // whether or not the cached item is still valid.
      variable_set("cache_flush_$table", $_SERVER['REQUEST_TIME']);

      // We store the time in the current user's session which is saved into
      // the sessions table by sess_write().  We then simulate that the cache
      // was flushed for this user by not returning cached data to this user
      // that was cached before the timestamp.
      if (is_array($_SESSION['cache_flush'])) {
        $cache_tables = $_SESSION['cache_flush'];
      }
      else {
        $cache_tables = array();
      }
      $cache_tables[$table] = $_SERVER['REQUEST_TIME'];
      $_SESSION['cache_flush'] = $cache_tables;
    }
    else {
      // Register a wildcard flush for current cid
      memcache_wildcards($cid, $table, TRUE);
    }
  }
  else {
    dmemcache_delete($cid, $table);
  }
}

/**
 * Sum of all matching wildcards.  Checking any single cache item's flush value
 * against this single-value sum tells us whether or not a new wildcard flush
 * has affected the cached item.
 */
function memcache_wildcard_flushes($cid, $table) {
  return array_sum(memcache_wildcards($cid, $table));
}

/**
 * Utilize multiget to retrieve all possible wildcard matches, storing
 * statically so multiple cache requests for the same item on the same page
 * load doesn't add overhead.
 */
function memcache_wildcards($cid, $table, $flush = FALSE) {
  static $wildcards = array();
  $matching = array();

  $wildcard_flushes = variable_get('memcache_wildcard_flushes', array());
  $wildcard_invalidate = variable_get('memcache_wildcard_invalidate', MEMCACHE_WILDCARD_INVALIDATE);
  if (isset($wildcard_flushes[$table]) &&
      is_array($wildcard_flushes[$table])) {
    // Determine which lookups we need to perform to determine whether or not
    // our cid was impacted by a wildcard flush.
    $lookup = array();

    // Find statically cached wildcards, and determine possibly matching
    // wildcards for this cid based on a history of the lengths of past valid
    // wildcard flushes in this bin.
    foreach ($wildcard_flushes[$table] as $length => $timestamp) {
      if ($timestamp >= ($_SERVER['REQUEST_TIME'] - $wildcard_invalidate)) {
        $key = '.wildcard-' . substr($cid, 0, $length);
        $wildcard = dmemcache_key($key, $table);
        if (isset($wildcards[$table][$wildcard])) {
          $matching[$wildcard] = $wildcards[$table][$wildcard];
        }
        else {
          $lookup[$wildcard] = $key;
        }
      }
    }

    // Do a multi-get to retrieve all possibly matching wildcard flushes.
    if (!empty($lookup)) {
      $values = dmemcache_get_multi($lookup, $table);
      if (is_array($values)) {
        // Build an array of matching wildcards.
        $matching = array_merge($matching, $values);
        if (isset($wildcards[$table])) {
          $wildcards[$table] = array_merge($wildcards[$table], $values);
        }
        else {
          $wildcards[$table] = $values;
        }
        $lookup = array_diff_key($lookup, $values);
      }

      // Also store failed lookups in our static cache, so we don't have to
      // do repeat lookups on single page loads.
      foreach ($lookup as $wildcard => $key) {
        $wildcards[$table][$wildcard] = 0;
      }
    }
  }
  if ($flush) {
   // Avoid too many calls to variable_set() by only recording a flush for a
   // fraction of the wildcard invalidation variable, per cid length.  Defaults
   // to 28 / 4, or one week.
    $length = strlen($cid);
    if (!isset($wildcard_flushes[$table][$length]) ||
        ($_SERVER['REQUEST_TIME'] - $wildcard_flushes[$table][$length] > $wildcard_invalidate / 4)) {
      $wildcard_flushes[$table][$length] = $_SERVER['REQUEST_TIME'];
      variable_set('memcache_wildcard_flushes', $wildcard_flushes);
    }
    $wildcard = dmemcache_key('.wildcard-' . $cid, $table);
    if (isset($wildcards[$table][$wildcard]) && $wildcards[$table][$wildcard] != 0) {
      $mc = dmemcache_object($table);
      $mc->increment($wildcard);
      $wildcards[$table][$wildcard]++;
    }
    else {
      $wildcards[$table][$wildcard] = 1;
      dmemcache_set('.wildcard-' . $cid, '1', 0, $table);
    }
  }
  return $matching;
}

/**
 * Provide a substitute clone() function for PHP4. This is a copy of drupal_clone
 * because common.inc isn't included early enough in the bootstrap process to
 * be able to depend on drupal_clone.
 */
function memcache_clone($object) {
  return version_compare(phpversion(), '5.0') < 0 ? $object : clone($object);
}

