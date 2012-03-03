<?php
/**
 * @file Calais.inc
 * The main interface to the calais web service
 */

class Calais {
  
  const PATH = '/enlighten/rest/';
  
  private $defaults = array(
    'protocol' => 'http',
    'contentType' => 'TEXT/HTML',
    'outputFormat' => 'XML/RDF',
    'externalID' => '',
    'submitter' => 'Drupal',
    'calculateRelevanceScore' => 'true',
    'enableMetadataType' => 'SocialTags',
    'allowSearch' => 'false',
    'allowDistribution' => 'false',
    'caller' => 'Drupal',
  );
  
  public $parameters;
  public $rdf;
  public $triples = array();
  public $flatTriples = array();
  public $keywords = array();
  
  /**
   * Constructs an instance of the Calais facade.
   *
   * Valid parameters are specified in the options array as key/value pairs with the
   * parameter name being the key and the parameter setting being the value
   * e.g. array('allowSearch' => 'false')
   *
   * @param options  An array of parameter options for the Calais Web Service. 
   *                  These will override the defaults.
   *
   * @see http://opencalais.com/APIcalls#inputparameters
   */
  function __construct($options = array()) {
    $this->defaults['externalID'] = time();
    $this->defaults['host'] = variable_get('calais_api_server', 'api1.opencalais.com');
    
    $this->parameters = array_merge($this->defaults, $options);
  }
  
  /**
   * Analyze the provided content, passing it to Calais in XML format for more accurate data processing.
   *
   * @param $title  The title of the content to process
   * @param $body   The body ofd the content to process
   * @param $date   The date of the content, if left blank/null analysis will use "today"
   * @return The processed Calais results. The raw RDF result is contained in the $this->rdf field.
   */
  public function analyzeXML($title, $body, $date) {
    $content = $this->build_xml_content($title, $body, $date);
    $this->parameters['contentType'] = 'TEXT/XML';
    return $this->analyze($content);
  }
  
  /**
   * Analyze the content via Calais.
   *
   * @param $content The content to ship off to Calais for analysis
   * @return The processed Calais results. The raw RDF result is contained in the $this->rdf field.
   */
  public function analyze($content) {

    $headers = array('Content-Type' => 'application/x-www-form-urlencoded');
    $data    = array(
      'licenseID' => variable_get('calais_api_key', NULL),
      'content' => $content,
      'paramsXML' => $this->build_xml_params(),
    );

    $data_enc = http_build_query($data, '', '&');
    $uri = $this->parameters['protocol'] . '://' . $this->parameters['host'] . self::PATH;
    $ret = drupal_http_request($uri, $headers, 'POST', $data_enc);
    if (isset($ret->error)) {
      self::log_calais_error($ret);
      return array();
    }

    $this->rdf = $ret->data;
    $this->processor = new CalaisRdfProcessor();
    $this->keywords = $this->processor->parse_rdf($this->rdf);    
    $this->triples = $this->processor->triples;
    $this->flatTriples = $this->processor->flatTriples;
    return $this->keywords;    
  }

  private static function log_calais_error($ret) {
    $msg = t('Calais processing error: @msg', array('@msg' => $ret->data));
    drupal_set_message($msg, 'error');
    watchdog('calais', 'Calais processing error: (@code - @error) @msg', array('@code' => $ret->code, '@error' => $ret->error, '@msg' => $ret->data), WATCHDOG_ERROR);
  }
  
  /**
   * Build the XML Parameters required by the Calais Web-Service
   *
   * @return XML document of Calais parameters.
   */
  protected function build_xml_params() {
    $attributes = $this->parameters;
    $ret = <<<EOD
    <c:params xmlns:c="http://s.opencalais.com/1/pred/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
    <c:processingDirectives c:contentType="$attributes[contentType]" 
                            c:outputFormat="$attributes[outputFormat]"
                            c:enableMetadataType="$attributes[enableMetadataType]">
                            c:calculateRelevanceScore="$attributes[calculateRelevanceScore]">
    </c:processingDirectives>
    <c:userDirectives c:allowDistribution="$attributes[allowDistribution]" 
                      c:allowSearch="$attributes[allowSearch]"           
                      c:externalID="$attributes[externalID]" 
                      c:submitter="$attributes[submitter]">
    </c:userDirectives>
    <c:externalMetadata>
      <rdf:description>
        <c:caller>$attributes[caller]</c:caller>
      </rdf:description>
    </c:externalMetadata>
    </c:params>
EOD;
    return $ret;
  }
  
  /**
   * Build the XML document request format expected by Calais
   *
   * @return an xml string to be submitted to Calais
   * @see http://opencalais.com/APIcalls#inputcontentformat
   */
  protected function build_xml_content($title, $body, $date) {
    $req = "<DOCUMENT>";
    $req .= "<TITLE><![CDATA[$title]]></TITLE>";
    $req .= "<DATE>$date</DATE>";
    $req .= "<BODY><![CDATA[$body]]></BODY>";
    $req .= "</DOCUMENT>";
    return $req;
  }  
}
