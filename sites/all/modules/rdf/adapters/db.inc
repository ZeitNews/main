<?php
// $Id: db.inc,v 1.1 2009/03/28 02:37:22 arto Exp $

//////////////////////////////////////////////////////////////////////////////
// Database storage adapter

class RDF_DatabaseRepository {
  function __construct(array $options = array()) {
    $this->name  = !empty($options['name'])  ? $options['name'] : NULL;
    $this->table = !empty($options['table']) ? $options['table'] : NULL;
  }

  function insert($subject, $predicate, $object, array $options = array()) {
    global $user;
    $options = array_merge(array('uid' => $user->uid, 'created' => time()), $options);
    $record  = $this->construct_statement($subject, $predicate, $object, $options);

    // Prevent duplicate record creation, at the administrator's discretion:
    if (variable_get('rdf_db_prevent_duplicates', FALSE)) {
      if (($id = db_result($this->select_statements($record, 1)))) {
        return (int)$id; // previously existing duplicate record found
      }
    }

    return drupal_write_record($this->table, $record) ? (int)$record->did : FALSE;
  }

  function delete($subject, $predicate, $object, array $options = array()) {
    $schema = rdf_db_get_schema($this->table);
    $record = $this->construct_statement($subject, $predicate, $object, $options);

    $conditions = $values = array();
    foreach (get_object_vars($record) as $key => $value) {
      if (!is_null($value)) {
        $conditions[] = $key . ' = ' . db_type_placeholder($schema['fields'][$key]['type']);
        $values[] = $value;
      }
    }

    return !!db_query('DELETE FROM {' . $this->table . '}' . (empty($conditions) ? '' : (' WHERE ' . implode(' AND ', $conditions))), $values);
  }

  protected function construct_statement($subject, $predicate, $object, array $options = array()) {
    global $user;  

    $is_uri     = is_object($object) && ($object instanceof RDF_URIRef);
    $is_literal = is_object($object) && ($object instanceof RDF_Literal);

    $record = (object)array();
    $record->uid     = isset($options['uid']) ? $options['uid'] : NULL;
    $record->created = isset($options['created']) ? $options['created'] : NULL;
    $record->gid     = !empty($options['context']) ? $this->uri_to_id($options['context']) : NULL;
    $record->gid     = !empty($options['graph']) ? $this->uri_to_id($options['graph']) : $record->gid;
    $record->sid     = $subject ? $this->uri_to_id($subject) : NULL;
    $record->pid     = $predicate ? $this->uri_to_id($predicate) : NULL;
    $record->oid     = $object && $is_uri ? $this->uri_to_id((string)$object) : NULL;
    $record->tid     = $object && rdf_get_datatype($object) ? $this->uri_to_id(rdf_qname_to_uri(rdf_get_datatype($object))) : NULL;
    $record->lang    = $object && $is_literal ? $object->language : NULL;
    $record->data    = $object && !$is_uri ? ($is_literal ? $object->value : (string)$object) : NULL;

    return $record;
  }

  protected function uri_to_id($uri) {
    // TODO: CURIE-to-URI normalization, and lookup caching.
    return ($id = $this->uri_to_id_select($uri)) ? $id : $this->uri_to_id_insert($uri);
  }

  protected function uri_to_id_insert($uri) {
    return @drupal_write_record('rdf_resources', $record = (object)array('uri' => $uri)) !== FALSE ? (int)$record->rid : FALSE;
  }

  protected function uri_to_id_select($uri) {
    return (int)db_result(db_query("SELECT r.rid FROM {rdf_resources} r WHERE r.uri = '%s'", $uri));
  }

  function count() {
    return db_result(db_query('SELECT COUNT(did) FROM {' . $this->table . '}'));
  }

  function query($subject, $predicate, $object, array $options = array()) {
    $result = db_query($this->select($subject, $predicate, $object, $options));

    $data = array();
    while ($row = db_fetch_object($result)) {
      $object = $row->o ? rdf_uri($row->o) : rdf_literal($row->data, $row->lang, $row->type);
      $data[] = array($row->s, $row->p, $object);
    }
    return $data;
  }

  function select($subject, $predicate, $object, $options = array()) {
    $query = $where = array();

    $sql = 'SELECT g.uri g, s.uri s, p.uri p, o.uri o, t.uri type, d.lang, d.data FROM {%s} d
              LEFT JOIN  {rdf_resources} g ON d.gid = g.rid
              INNER JOIN {rdf_resources} s ON d.sid = s.rid
              INNER JOIN {rdf_resources} p ON d.pid = p.rid
              LEFT JOIN  {rdf_resources} o ON d.oid = o.rid
              LEFT JOIN  {rdf_resources} t ON d.tid = t.rid';
    $query[] = sprintf($sql, db_escape_table($this->table));

    if (isset($options['graph']) || isset($options['context'])) { // TODO: should decide on one.
      $graph = !empty($options['graph']) ? $options['graph'] : $options['context'];
      $where[] = sprintf("g.uri = '%s'", db_escape_string((string)$graph));
    }

    if ($subject) {
      $where[] = sprintf("s.uri = '%s'", db_escape_string((string)$subject));
    }

    if ($predicate) {
      $where[] = sprintf("p.uri = '%s'", db_escape_string((string)$predicate));
    }

    if ($object) {
      // Assume an object means an RDF_URIRef, but convert it to a URI string
      // using duck typing so that other classes can be substituted
      // TODO: support language-tagged and datatyped literals
      $where[] = sprintf(is_object($object) ? "o.uri = '%s'" : "d.data = '%s'", db_escape_string((string)$object));
    }

    $query[] = empty($where) ? '' : 'WHERE (' . implode(') AND (', $where) . ')';
    $query[] = 'ORDER BY d.did ASC';
    return implode("\n", $query);
  }

  function merge_duplicates() {
    static $fields = array('gid', 'sid', 'pid', 'oid', 'tid', 'lang', 'data');
    $columns = implode(', ', $fields);

    $count = 0;
    $duplicates = db_query("SELECT COUNT(*) AS dups, $columns FROM {" . db_escape_table($this->table) . "} GROUP BY $columns HAVING dups > 1");
    while ($duplicate = db_fetch_array($duplicates)) {
      unset($duplicate['dups']);

      $records = $this->select_statements($duplicate, 100, 1);
      while ($record = db_fetch_object($records)) {
        db_query("DELETE FROM {" . db_escape_table($this->table) . "} WHERE did = %d", $record->did);
        $count++;
      }
    }

    if ($count > 0) {
      watchdog('rdf', 'Deleted @count duplicated RDF statement(s) in table %table.', array('@count' => $count, '%table' => $this->table), WATCHDOG_NOTICE, l(t('settings'), 'admin/settings/rdf'));
    }
  }

  protected function delete_statements($match, $limit = NULL, $offset = NULL) {
    return $this->query_statements('DELETE', $match, $limit, $offset);
  }

  protected function select_statements($match, $limit = NULL, $offset = NULL) {
    unset($match->uid, $match->created); // never match on optional meta-meta fields
    return $this->query_statements('SELECT did', $match, $limit, $offset);
  }

  protected function query_statements($query, $match, $limit = NULL, $offset = NULL) {
    $query .= ' FROM {' . db_escape_table($this->table) . '} WHERE ';
    $values = (array)$match;
    $fields = array();
    foreach ($values as $field => &$value) {
      if ($value === NULL) {
        // special handling for NULL values:
        unset($values[$field]);
        $fields[] = "($field IS NULL)";
      }
      else {
        // 'lang' and 'data' are text fields, the rest are foreign keys
        $fields[] = ($field == 'lang' || $field == 'data') ? "($field = '%s')" : "($field = %d)";
      }
    }
    $query .= implode(' AND ', $fields) . ' ORDER BY did ASC';
    $query .= $limit  ? (' LIMIT '  . (int)$limit)  : '';
    $query .= $offset ? (' OFFSET ' . (int)$offset) : '';
    return db_query($query, $values);
  }
}
