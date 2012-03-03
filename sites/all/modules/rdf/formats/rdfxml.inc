<?php
// $Id: rdfxml.inc,v 1.1 2009/03/27 21:01:13 arto Exp $

//////////////////////////////////////////////////////////////////////////////
// RDF/XML reader

function rdf_unserialize_xml($text, array $options = array()) {
  $parser = ARC2::getRDFXMLParser();
  $parser->parse(@$options['uri'], $text);
  return array_map('_rdf_deconstruct_arc2_triple', $parser->getTriples());
}

//////////////////////////////////////////////////////////////////////////////
// RDF/XML writer

function rdf_serialize_xml($data, array $options = array()) {
  $namespaces = array_merge(rdf_get_namespaces(), is_array(@$options['namespaces']) ? @$options['namespaces'] : array());
  $namespaces = rdf_get_prefixes($data, $namespaces);

  $xml = new XMLWriter(); // requires PHP 5.1.2+
  $xml->openMemory();
  $xml->setIndent(TRUE);
  $xml->setIndentString('  ');
  $xml->startDocument('1.0', 'utf-8');
  $xml->startElement('rdf:RDF');

  // Output a default namespace prefix, if one was specified:
  $base_prefix = NULL;
  if (!empty($options['base'])) {
    $base_prefix = array_search($options['base'], $namespaces);
    $xml->writeAttribute('xmlns', $options['base']);
  }

  // Output all namespace prefixes:
  foreach ($namespaces as $prefix => $uri) {
    if (!$base_prefix || $base_prefix != $prefix) {
      $xml->writeAttribute('xmlns:' . $prefix, $uri);
    }
  }

  $bnode_map = array();
  $bnode_id = 0;
  foreach ($data as $subject => $predicates) {
    $type = 'rdf:Description';

    // Support the typed node element syntax where possible:
    foreach ($predicates as $predicate => &$objects) {
      if (($qname = rdf_uri_to_qname($predicate)) == 'rdf:type') {
        $type = rdf_uri_to_qname(array_shift($objects));
        if (empty($objects)) {
          unset($predicates[$predicate]);
        }
        break;
      }
    }
    unset($objects);

    $qname = $base_prefix ? preg_replace('/^' . preg_quote($base_prefix, '/') . ':/', '', $type) : $type;
    $xml->startElement($qname);

    if (RDF_BNode::match($subject)) {
      $xml->writeAttribute('rdf:nodeID', !isset($bnode_map[$subject]) ? ($bnode_map[$subject] = 'b' . ++$bnode_id) : $bnode_map[$subject]);
    }
    else { // RDF_URIRef
      $xml->writeAttribute('rdf:about', $subject);
    }

    foreach ($predicates as $predicate => $objects) {
      $qname = rdf_uri_to_qname($predicate);
      $qname = $base_prefix ? preg_replace('/^' . preg_quote($base_prefix, '/') . ':/', '', $qname) : $qname;

      foreach (is_array($objects) ? $objects : array($object) as $object) {

        if (!is_object($object)) { // plain literal
          $xml->writeElement($qname, (string)$object);
        }
        else if ($object instanceof RDF_Literal) { // typed literal
          $xml->startElement($qname);
          if ($object->language) {
            $xml->writeAttribute('xml:lang', $object->language);
          }
          if ($object->datatype) {
            $xml->writeAttribute('rdf:datatype', $object->datatype);
          }
          $xml->text((string)$object->value);
          $xml->endElement();
        }
        else if ($object instanceof RDF_BNode) { // blank node
          $xml->startElement($qname);
          $xml->writeAttribute('rdf:nodeID', !isset($bnode_map[(string)$object]) ? ($bnode_map[(string)$object] = 'b' . ++$bnode_id) : $bnode_map[(string)$object]);
          $xml->endElement();
        }
        else { // RDF_URIRef, or the like
          $xml->startElement($qname);
          $xml->writeAttribute('rdf:resource', (string)$object);
          $xml->endElement();
        }

      }
    }

    $xml->endElement(); // rdf:Description, or $type
  }

  $xml->endElement(); // rdf:RDF
  $xml->endDocument();
  print $xml->outputMemory(TRUE);
}
