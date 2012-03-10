<?php
// $Id: rdfa.lib.inc,v 1.1.2.1 2010/07/09 21:34:02 tirdadc Exp $

/**
 * Returns a date with proper RDFa mark-up data
 * 
 * @param $timestamp
 *    the date in timestamp format
 * @param $date
 *    The date in whatever string format it is being displayed in
 * 
 * @return
 *    the RDFa-enriched HTML markup for the date 
 */
function _openpublish_get_rdfa_date($timestamp, $date) {
  if (empty($timestamp)) {
    return '';
  }
  //date in RFC 3339 format
  $rdfa_date = date('c', $timestamp);
  $datetime = date('Y-m-d', $timestamp);
  return '<time property="dc:issued" datatype="xsd:dateTime" datetime="' . $datetime . '" content="' . $rdfa_date . '">' . $date . '</time>';
}

/**
 * Returns a title with proper RDFa mark-up data 
 *
 * @param $title
 *    the title
 * @param $nid
 *    the node id that will be used for the link
 * 
 * @return
 *    the RDFa-enriched HTML markup for the title
 */
function _openpublish_get_rdfa_title($title, $nid) {
  if (empty($title) || empty($nid)) {
    return '';
  }
  return l($title, 'node/' . $nid, array('attributes' => array('property' => "dc:title")));
}

/**
 * Returns an author with proper RDFa mark-up data
 *
 * @param $title
 *    the title
 * @param $nid
 *    the node id that will be used for the link
 * 
 * @return
 *    the RDFa-enriched HTML markup for the title
 */
function _openpublish_get_rdfa_author($title, $nid) {
  if (empty($title) || empty($nid)) {
    return '';
  }
  return l($title, 'node/' . $nid, array('attributes' => array(
    'property' => 'dc:creator',
    'rel' => 'foaf:publications',
    'typeof' => 'foaf:person',
    'content' => $title,
  )));
}