<?php
// $Id: trix.inc,v 1.1 2009/03/27 21:01:13 arto Exp $

//////////////////////////////////////////////////////////////////////////////
// TriX writer

function rdf_serialize_trix($data, array $options = array()) {
  $namespaces = @$options['namespaces'];

  $xml = new XMLWriter(); // requires PHP 5.1.2+
  $xml->openMemory();
  $xml->setIndent(TRUE);
  $xml->setIndentString('  ');
  $xml->startDocument('1.0', 'utf-8');
  $xml->startElement('TriX');
  $xml->writeAttribute('xmlns', 'http://www.w3.org/2004/03/trix/trix-1/');

  $xml->startElement('graph'); // FIXME?
  foreach ($data as $subject => $predicates) {
    foreach ($predicates as $predicate => $objects) {
      foreach ($objects as $object) {
        $xml->startElement('triple');
        $xml->writeElement('uri', (string)$subject);
        $xml->writeElement('uri', (string)$predicate);

        if (!is_object($object)) { // plain literal w/o xml:lang
          $xml->writeElement('plainLiteral', (string)$object);
        }
        else if ($object instanceof RDF_Literal) { // typed literal
          $xml->startElement(!$object->datatype ? 'plainLiteral' : 'typedLiteral');
          if ($object->language)
            $xml->writeAttribute('xml:lang', $object->language);
          if ($object->datatype)
            $xml->writeAttribute('datatype', $object->datatype);
          $xml->text((string)$object->value);
          $xml->endElement();
        }
        else { // RDF_URIRef, or the like
          $xml->writeElement('uri', (string)$object);
        }

        $xml->endElement(); // triple
      }
    }
  }
  $xml->endElement(); // graph

  $xml->endElement(); // TriX
  $xml->endDocument();
  print $xml->outputMemory(TRUE);
}
