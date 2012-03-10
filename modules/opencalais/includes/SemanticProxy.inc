<?php
/**
 * @file SemanticProxy.inc
 * The main interface to the semantic proxy web service
 */

class SemanticProxy {
  
  const SERVICE = 'http://@host/processurl/@apikey/@format/@url';
  
  private $defaults = array(
    'host' => 'service.semanticproxy.com',
    'format' => 'rdf',
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
   * @param options  
   *    An array of parameter options for the Semantic Proxy Web Service. These will override the defaults.
   *    <dl>
   *      <dt>host</dt>
   *      <dd>The server name for the SemanticProxy service (default: service.semanticproxy.com)</dd>
   *      <dt>format</dt>
   *      <dd>The return data format for the SemanticProxy service (default: rdf)</dd>
   *    </dl>
   *    
   */
  function __construct($options = array()) {
    $this->parameters = array_merge($this->defaults, $options);
  }
  
  /**
   * Analyze the url via SemanticProxy/Calais
   *
   * @param $url 
   *    The url to send to SemanticProxy for analysis
   * @return 
   *    The processed Calais results. The raw RDF result is contained in the $this->rdf field.
   */
  public function analyze($url) {

    if (!valid_url($url, TRUE)) {
      self::log_url_error($url);
      return array();
    }

    $data = array(
      '@apikey' => variable_get('calais_api_key', NULL),
      '@host' => $this->parameters['host'],
      '@format' => $this->parameters['format'],
      '@url' => $url,
    );

    $uri = strtr(self::SERVICE, $data);
    $ret = drupal_http_request($uri);
    if (isset($ret->error)) {
      self::log_http_error($ret);
      return array();
    }
    
    if($this->parameters['format'] == 'rdf') {
      $this->rdf = $ret->data;
      $this->processor = new CalaisRdfProcessor();
      $this->keywords = $this->processor->parse_rdf($this->rdf);    
      $this->triples = $this->processor->triples;
      $this->flatTriples = $this->processor->flatTriples;
    }
    return $this->keywords;    
  }

  private static function log_url_error($url) {
    $msg = t('URL for SemanticProxy is invalid: @url', array('@url' => $url));
    drupal_set_message($msg, 'error');
    watchdog('calais', $msg, array(), WATCHDOG_ERROR);    
  }  
  
  private static function log_http_error($ret) {
    $errordoc = @simplexml_load_string($ret->data); 
    if (method_exists($errordoc, 'xpath')) {
      $exception = $errordoc->xpath('/Error/Exception');
      $errormsg = (string) $exception[0];
      $msg = t('SemanticProxy processing error: @msg', array('@msg' => $errormsg));
      drupal_set_message($msg, 'error');
      $errors = array('@code' => $ret->code, '@error' => $ret->error, '@msg' => $errormsg);
      watchdog('calais', 'SemanticProxy processing error: (@code - @error) @msg', $errors, WATCHDOG_ERROR);
    }
    else {
      $msg = t('Unexpected error processing SemanticProxy request.');
      drupal_set_message($msg, 'error');
      watchdog('calais', $msg, WATCHDOG_ERROR);
    }
  }  
}
