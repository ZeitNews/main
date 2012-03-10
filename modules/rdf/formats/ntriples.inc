<?php
// $Id: ntriples.inc,v 1.1 2009/03/27 21:01:13 arto Exp $

//////////////////////////////////////////////////////////////////////////////
// N-Triples reader

function rdf_unserialize_ntriples($text, array $options = array()) {
  //return rdf_unserialize_turtle($text, $options);
  $parser = ARC2::getTurtleParser();
  $parser->parse(@$options['uri'], $text);
  return array_map('_rdf_deconstruct_arc2_triple', $parser->getTriples());
}

//////////////////////////////////////////////////////////////////////////////
// N-Triples writer

function rdf_serialize_ntriples($data, array $options = array()) {
  $namespaces = @$options['namespaces'];

  foreach ($data as $subject => $predicates) {
    foreach ($predicates as $predicate => $objects) {
      foreach (rdf_objects($objects) as $object) {

        printf('<%s> <%s> ', (string)$subject, (string)$predicate);

        if (!is_object($object)) { // plain literal
          printf('"%s"', _rdf_serialize_ntriples_escape((string)$object));
        }
        else if ($object instanceof RDF_Literal) { // typed literal
          printf('"%s"', _rdf_serialize_ntriples_escape((string)$object->value));
          if ($object->language)
            printf('@%s', $object->language);
          if ($object->datatype)
            printf('^^<%s>', $object->datatype);
        }
        else { // RDF_URIRef, or the like
          printf('<%s>', (string)$object);
        }

        printf(" .\n");
      }
    }
  }
}

function _rdf_serialize_ntriples_escape($string) {
  return str_replace(array('\\', '"', "\t", "\n", "\r"), array('\\\\', '\\"', '\\t', '\\n', '\\r'), $string);
}
