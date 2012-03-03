<?php
/**
 * @file CalaisRdfProcessor.inc
 *  The parser for the Calais RDF/XML responses.
 */

class CalaisRdfProcessor {
  
  const RDF_TYPE = 'http://www.w3.org/1999/02/22-rdf-syntax-ns#type';
  const CALAIS_SUBJECT = 'http://s.opencalais.com/1/pred/subject';
  const CALAIS_NAME = 'http://s.opencalais.com/1/pred/name';
  const CALAIS_LAT = 'http://s.opencalais.com/1/pred/latitude';
  const CALAIS_LON = 'http://s.opencalais.com/1/pred/longitude';
  const CALAIS_SCORE = 'http://s.opencalais.com/1/pred/score';
  const SAMEAS = 'http://www.w3.org/2002/07/owl#sameAs';
  /**
   * Parse the RDF.  First render it into an indexed fashion, then have at it. We need to process
   * in 2 stages. The first stage identifies all of the entities, events, and facts. The second
   * stage then adds relevance and geo info to those previously identified terms.  The 2nd pass i
   * is required b/c sometimes the relevance/geo data appears in the document before the term
   * has been identified.
   *
   * @param $rdf_xml
   *    The RDF to parse
   * @return
   *    An array of CalaisMetadata objects.
   * @see 
   *    CalaisMetadata.inc
   */
  public function parse_rdf($rdf_xml) {
    $parser = ARC2::getRDFXMLParser();
    $parser->parse(NULL, $rdf_xml);
    $this->triples = $parser->getSimpleIndex();
    $this->flatTriples = array_map('_rdf_deconstruct_arc2_triple', $parser->getTriples());

    $this->keywords = new stdClass();
    $this->extract_document();
    $this->build_entities($this->keywords);
    $this->extract_entity_metadata($this->keywords);
    return $this->keywords;
  }

  /**
   * Build the set of entities from this RDF triples returned from Calais.
   *
   * @param $keywords 
   *    The object containing type keyed CalaisMetadata
   */
  protected function extract_document() {
    foreach ($this->triples as $guid => $data) {
      $type = $data[self::RDF_TYPE];
      if(isset($type) && $type[0] == 'http://s.opencalais.com/1/type/sys/DocInfo') {
        $this->document = $data['http://s.opencalais.com/1/pred/document'][0];
        $this->document = preg_replace('/<!\[CDATA\[/ims', '', $this->document);
        $this->document = preg_replace('/\]\]>/ims', '', $this->document);
        if(preg_match('@<BODY>(.*)</BODY>@ims', $this->document, $matches) > 0) {
          if(count($matches) == 4) {
            $this->document = $matches[2];
          }
          else {
            $this->document = $matches[1];
          }
        }
        return;
      }
    }
  }

  /**
   * Build the set of entities from this RDF triples returned from Calais.
   *
   * @param $keywords 
   *    The object containing type keyed CalaisMetadata
   */
  protected function build_entities(&$keywords) {
    foreach ($this->triples as $guid => $data) {
      $type = $data[self::RDF_TYPE];
      
      if (!isset($type)) 
        continue;
        
      if (strpos($type[0], "http://s.opencalais.com/1/type/em/e") !== FALSE) {
        $this->extract_entities($keywords, $type, $guid, $data);
      }
      else if (strpos($type[0], 'http://s.opencalais.com/1/type/em/r') !== FALSE) {
        $this->extract_events($keywords, $type, $guid, $data);
      }
      else if ($type[0] == 'http://s.opencalais.com/1/type/cat/DocCat') {
        $this->extract_categories($keywords, $type, $guid, $data);
      }      
      else if ($type[0] == 'http://s.opencalais.com/1/type/tag/SocialTag') {
        $this->extract_tags($keywords, $type, $guid, $data);
      }      
    }
  }

  /**
   * Process the RDF triple and grab the additional metadata on entities.
   * Additional metadata is relevance score and a slew of resolved entity dismbiguation
   *
   * @param $keywords 
   *    The object containing type keyed CalaisMetadata
   */
  protected function extract_entity_metadata(&$keywords) {
    foreach ($this->triples as $guid => $data) {
      $type = $data[self::RDF_TYPE];
      
      if (!isset($type)) 
        continue;
        
      if ($type[0] == 'http://s.opencalais.com/1/type/sys/RelevanceInfo') {
        $this->set_relevance($keywords, $data);
      }
      else if (strpos($type[0], 'http://s.opencalais.com/1/type/er') !== FALSE) {
        $er_type = preg_replace('@http://s.opencalais.com/1/type/er/@ims', '', $type[0]);
        $er_type = drupal_strtolower(str_replace('/', '_', $er_type));
        $func = 'apply_resolved_' . $er_type;
        
        if (!method_exists($this, $func)) {
          $func = 'apply_resolved_data';
        }
        
        $this->{$func}($keywords, $guid, $data, $er_type);
      }
    }
  }

  /**
   * Extracts the entities from the returned data
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $type The RDF type for this record
   * @param $guid The guid for the current Calais Term
   * @param $data The indexed triple for the current Calais Term/GUID
   */
  protected function extract_entities(&$keywords, $type, $guid, $data) {
    $entity_type_guid = $type[0];
    $entity_type = preg_replace('/.*\//ims', '', $entity_type_guid);

    $entity_value = $data[self::CALAIS_NAME][0];
    
    if (!property_exists($keywords, $entity_type)) {
      $keywords->{$entity_type} = new CalaisMetadata($entity_type_guid, $entity_type);
    }

    $metadata = &$keywords->{$entity_type};
    $metadata->set_term_data($guid, $entity_value);        
  }
  
  /**
   * Extracts the events & facts from the returned data. For now it is considered best that all
   * Events & Facts are put into one Vocabulary and identified by their type.
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $type The RDF type for this record
   * @param $guid The guid for the current Calais Term
   * @param $data The indexed triple for the current Calais Term/GUID
   */
   protected function extract_events(&$keywords, $type, $guid, $data) {
     $type_guid = $type[0];
     $type_value = preg_replace('/.*\//ims', '', $type_guid);
     $type_value = calais_api_make_readable($type_value);
   
     if (!property_exists($keywords, 'EventsFacts')) {
       $keywords->EventsFacts = new CalaisMetadata('http://drupal.org/project/opencalais/EventsFacts', 'EventsFacts');
     }

     // Not sure if the best number for relevance of an Event/Fact, for now 1 will always include
     $keywords->EventsFacts->set_term_data($type_guid, $type_value, 1.000);      
   }
   
  /**
   * Extracts the document level categorization from the returned data.
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $type The RDF type for this record
   * @param $guid The guid for the current Calais Term
   * @param $data The indexed triple for the current Calais Term/GUID
   */
   protected function extract_categories(&$keywords, $type, $guid, $data) {
     $cat_guid = $data['http://s.opencalais.com/1/pred/category'][0];
     $cat_val = $data['http://s.opencalais.com/1/pred/categoryName'][0];
     $cat_score = array_key_exists('http://s.opencalais.com/1/pred/score', $data)
                     ? $data['http://s.opencalais.com/1/pred/score'][0]
                     : 0;

     if (!property_exists($keywords, 'CalaisDocumentCategory')) {
       $keywords->CalaisDocumentCategory = new CalaisMetadata($type[0], 'CalaisDocumentCategory');
     }

     $cat_val = preg_replace('/_.*/ims', '', $cat_val); // remove everything after the first underscore
     $keywords->CalaisDocumentCategory->set_term_data($cat_guid, $cat_val, $cat_score);      
   }

   /**
    * Extracts the Social Tags from the returned data.
    * 
    * @param $keywords The result array for CalaisMetadata
    * @param $type The RDF type for this record
    * @param $guid The guid for the current Calais Term
    * @param $data The indexed triple for the current Calais Term/GUID
    */
    protected function extract_tags(&$keywords, $type, $guid, $data) {
      $tag_guid = $data['http://s.opencalais.com/1/pred/socialtag'][0];
      $tag_val = $data['http://s.opencalais.com/1/pred/name'][0];
      $importance = $data['http://s.opencalais.com/1/pred/importance'][0];
      
      // This is built off of the Calais documentation:
      // A topic extracted by Categorization with a score higher than 0.6 
      // will also be extracted as a SocialTag. If its score is higher 
      // than 0.8, its importance (as a SocialTag) will be set to 1. If 
      // the score is between 0.6 and 0.8 its importance is set to 2.
      switch ($importance) {
        case 1:
          $tag_score = 0.9;
          break;
        case 2:
          $tag_score = 0.7;
          break;
        default:
          $tag_score = 0;
      }

      if (!property_exists($keywords, 'SocialTags')) {
        $keywords->SocialTags = new CalaisMetadata($type[0], 'SocialTags');
      }

      // When certain Document Category tags get here, they have underscores, remove them
      $tag_val = preg_replace('/_.*/ims', '', $tag_val); // remove everything after the first underscore
      $keywords->SocialTags->set_term_data($tag_guid, $tag_val, $tag_score);      
    }

  /**
   * Extracts the relevance score from the returned data
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $data The indexed triple for the current Calais Term
   */
  protected function set_relevance(&$keywords, $data) {
    $subject = $data[self::CALAIS_SUBJECT][0];
    $relevance = $data['http://s.opencalais.com/1/pred/relevance'][0];
    foreach ($keywords as &$entity) {
      if ($entity->has_guid($subject)) {
        $entity->set_term_relevance($subject, $relevance);      
      }
    }
  }

  /**
   * Extracts the basic resolved entity data.
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $guid The resolved entity guid
   * @param $data The indexed triple for the current Calais Term
   * @param $extra Any extra domain specific data
   */
  protected function apply_resolved_data(&$keywords, $guid, $data, $type, $extra = array()) {
    $subject = $data[self::CALAIS_SUBJECT][0];
    $resolved_name = $data[self::CALAIS_NAME][0];
      
    foreach ($keywords as &$entity) {
      if ($entity->has_guid($subject)) {
        $uris = variable_get('calais_lookup_loduri', FALSE) ? self::lookup_linked_data_uris($guid) : array();
        $entity->set_term_resolved_data($subject, $resolved_name, $guid, $type, $extra, $uris);      
      }
    }
  }

  /**
   * Extracts the disambiguation geo city data
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $guid The resolved entity guid
   * @param $data The indexed triple for the current Calais Term
   */
  protected function apply_resolved_geo_city(&$keywords, $guid, $data) {
    $extra = array(
      'latitude' => $data[self::CALAIS_LAT][0],
      'longitude' => $data[self::CALAIS_LON][0],
      'shortname' => $data['http://s.opencalais.com/1/pred/shortname'][0],
      'containedbystate' => $data['http://s.opencalais.com/1/pred/containedbystate'][0],
      'containedbycountry' => $data['http://s.opencalais.com/1/pred/containedbycountry'][0],
    );
    $this->apply_resolved_data($keywords, $guid, $data, 'geo', $extra);
  }
  
  /**
   * Extracts the disambiguation geo province or state data
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $guid The resolved entity guid
   * @param $data The indexed triple for the current Calais Term
   */
  protected function apply_resolved_geo_provinceorstate(&$keywords, $guid, $data) {
    $extra = array(
      'latitude' => $data[self::CALAIS_LAT][0],
      'longitude' => $data[self::CALAIS_LON][0],
      'shortname' => $data['http://s.opencalais.com/1/pred/shortname'][0],
      'containedbycountry' => $data['http://s.opencalais.com/1/pred/containedbycountry'][0],
    );
    $this->apply_resolved_data($keywords, $guid, $data, 'geo', $extra);
  }
  
  /**
   * Extracts the disambiguation geo country data
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $guid The resolved entity guid
   * @param $data The indexed triple for the current Calais Term
   */
  protected function apply_resolved_geo_country(&$keywords, $guid, $data) {
    $extra = array(
      'latitude' => $data[self::CALAIS_LAT][0],
      'longitude' => $data[self::CALAIS_LON][0],
    );
    $this->apply_resolved_data($keywords, $guid, $data, 'geo', $extra);
  }
  
  /**
   * Extracts the disambiguated company data
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $guid The resolved entity guid
   * @param $data The indexed triple for the current Calais Term
   */
  protected function apply_resolved_company(&$keywords, $guid, $data) {
   $extra = array(
     'score' => $data[self::CALAIS_SCORE][0],
     'ticker' => $data['http://s.opencalais.com/1/pred/ticker'][0],
   );
   $this->apply_resolved_data($keywords, $guid, $data, 'company', $extra);
  }
  
  /**
   * Extracts the disambiguation geo country data
   * 
   * @param $keywords The result array for CalaisMetadata
   * @param $guid The resolved entity guid
   * @param $data The indexed triple for the current Calais Term
   */
  protected function apply_resolved_product_electronics(&$keywords, $guid, $data) {
    $extra = array(
      'score' => $data[self::CALAIS_SCORE][0],
    );
    $this->apply_resolved_data($keywords, $guid, $data, 'geo', $extra);
  } 
  
  /**
   * For a give Calais URI, lookup the RDF document and creat the connected Linked Open Data URIs
   * to other places like DBPedia, Freebase, Crunchbase, Musicbrainz, Geonames, etc.
   */
  protected function lookup_linked_data_uris($guid) {
    $headers = array(
      'Accept' => 'application/rdf+xml',
    );
    $ret = drupal_http_request("$guid.rdf", $headers);
    if (isset($ret->error)) {
      return array();
    }
  
    $parser = ARC2::getRDFXMLParser();
    $parser->parse(NULL, $ret->data);
    $triples = $parser->getSimpleIndex();

    $uris = array();
    if (array_key_exists($guid, $triples)) {
      $sameas = $triples[$guid][self::SAMEAS];
      if (count($sameas)) {
        foreach ($sameas as $uri) {
          $parts = parse_url($uri);
          $uris[$parts['host']] = $uri;
        }
      }
    }
  
    return $uris;
  }
}