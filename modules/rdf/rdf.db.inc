<?php
// $Id: rdf.db.inc,v 1.16 2009/03/28 02:37:22 arto Exp $

//////////////////////////////////////////////////////////////////////////////
// RDF repository API

// TODO: remove these compatibility wrappers once installation code in
// dependent modules has been updated to use the renamed functions.

/**
 * @deprecated
 */
function rdf_db_create_repository($name, array $options = array()) {
  return rdf_create_repository($name, $options);
}

/**
 * @deprecated
 */
function rdf_db_update_repository($name, array $options = array()) {
  return rdf_update_repository($name, $options);
}

/**
 * @deprecated
 */
function rdf_db_rename_repository($old_name, $new_name) {
  return rdf_rename_repository($old_name, $new_name);
}

/**
 * @deprecated
 */
function rdf_db_delete_repository($name) {
  return rdf_delete_repository($name);
}

/**
 * @deprecated
 */
function rdf_db_get_schema($table = RDF_DB_TABLE_DEFAULT, $rebuild = FALSE) {
  return rdf_get_schema($table, $rebuild);
}
