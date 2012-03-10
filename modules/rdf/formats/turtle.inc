<?php
// $Id: turtle.inc,v 1.1 2009/03/27 21:01:13 arto Exp $

//////////////////////////////////////////////////////////////////////////////
// Turtle reader

function rdf_unserialize_turtle($text, array $options = array()) {
  $parser = ARC2::getTurtleParser();
  $parser->parse(@$options['uri'], $text);
  return array_map('_rdf_deconstruct_arc2_triple', $parser->getTriples());
}

//////////////////////////////////////////////////////////////////////////////
// Turtle writer

function rdf_serialize_turtle($data, array $options = array()) {
  $namespaces = @$options['namespaces'];
  $namespaces = rdf_get_prefixes($data, $namespaces);
  foreach ($namespaces as $prefix => $uri) {
    printf("@prefix %s: <%s> .\n", $prefix, $uri);
  }
  printf("\n");

  foreach ($data as $subject => $predicates) {
    printf("<%s>\n", (string)$subject);

    $new_subject = TRUE;
    foreach ($predicates as $predicate => $objects) {
      $qname = rdf_uri_to_qname($predicate);

      foreach ($objects as $object) {
        printf(!$new_subject ? " ;\n\t" : "\t");
        $new_subject = FALSE;

        if (!is_object($object)) { // plain literal
          printf('%s "%s"', $qname, (string)$object); // FIXME: string escaping
        }
        else if ($object instanceof RDF_Literal) { // typed literal
          printf('%s "%s"', $qname, (string)$object->value); // FIXME: string escaping
          if ($object->language)
            printf('@%s', $object->language);
          if ($object->datatype)
            printf('^^%s', $object->datatype);
        }
        else { // RDF_URIRef, or the like
          printf('%s <%s>', $qname, (string)$object);
        }
      }
    }

    printf(" .\n\n");
  }
}
