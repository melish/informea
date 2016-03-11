<?php

/**
 * Class ODataConsumer talks to OData endpoints and gets data from the service.
 *
 * Supports OData v1
 */
abstract class ODataConsumer {

  protected $url = NULL;

  /** @var ODataConsumerConfig */
  protected $config = NULL;
  /** @var bool Use /Entity(guid'XXX-XXX-XX') in request URLs */
  protected $useGUIDInURL = FALSE;

  public function __construct($url, $config) {
    $this->url = $url;
    $this->config = $config;
  }

  /**
   * Does an OData remote entity count, this call is not cached.
   *
   * @return int
   *   Number of entities or zero
   */
  public function countTotal($entity) {
    $ret = 0;
    $url = $this->url . '/' . $entity . '/$count';
    ws_consumer_odata_log(get_class($this) . ': Remote counting entities: ' . $url);
    $response = ODataMigrationUtil::http_request($url);
    if (!empty($response)) {
      $ret = intval($response);
    }
    else {
      $url = $this->url . '/' . $entity . '?$inlinecount=allpages';
      $response = ODataMigrationUtil::http_request($url);
      $element_name = 'm:count';
      $found = preg_match(
        '#<'.$element_name.'(?:\s+[^>]+)?>(.*?)'.'</'.$element_name.'>#s',
        $response,
        $matches
      );
      if ($found) {
        $ret = intval($matches[1]);
      }
      else {
        ws_consumer_odata_log('FAIL: ' . get_class($this) . ': Remote counting entities: ' . $url, MigrationBase::MESSAGE_WARNING);
      }
    }
    return $ret;
  }

  /**
   * Retrieve OData records from the remote service.
   *
   * Important! Only the primitive properties are loaded, without the
   * navigation properties.
   *
   * @return array
   *   Array of stdClass objects
   */
  public function getRemoteEntities($entity) {
    $rows = $this->getPaginatedData($entity);
    $ids = array();
    foreach($rows as $row) {
      $ids[] = $row;
    }
    ws_consumer_odata_log(__METHOD__ . "($entity): Remote service returned " . count($rows) . ' results');
    return $ids;
  }


  /**
   * Retrieve a single entity from the service, given its type and id.
   *
   * @param string string $entity
   *   Type of data (ie. Contacts)
   * @param string $id
   *   Unique identifier in the target service
   * @param string $odata_extra_params
   *   Extra query to pass to OData service (ex. &$expand=treaties to get inline data)
   *
   * @return stdClass
   *   Object build from the JSON parsed data
   */
  public function getItem($entity, $id, $odata_extra_params = '') {
    $ret = NULL;
    $url = $this->url . '/' . $entity . "('" . $id . "')?" . $odata_extra_params;
    ws_consumer_odata_log(__METHOD__ . "($entity, $id): Retrieving data from : $url", MigrationBase::MESSAGE_NOTICE);
    $response = ODataMigrationUtil::http_request($url, array('Accept: application/json'));
    if (empty($response)) {
      if ($this->useGUIDInURL) {
        $url = $this->url . '/' . $entity . "(guid'" . $id . "')?" . $odata_extra_params;
      }
      else {
        $url = $this->url . '/' . $entity . "('" . $id . "')?" . $odata_extra_params;
      }
      $response = ODataMigrationUtil::http_request($url, array('Accept: application/json'));
      if (empty($response)) {
        ws_consumer_odata_log(__METHOD__ . "($entity, $id): HTTP request failure ({$response->code}) for URL: $url", MigrationBase::MESSAGE_ERROR);
        return $ret;
      }
    }
    if ($json = json_decode($response)) {
      $ret = $json->d;
    }
    else {
      ws_consumer_odata_log(__METHOD__ . "($entity, $id): Failed to unpack JSON data from $url", MigrationBase::MESSAGE_ERROR);
    }
    return $ret;
  }

  /**
   * Check the item exists in the remote source
   *
   * @param string $entity
   *   OData entity
   * @param $id
   *   OData entity ID
   *
   * @return boolean
   *   TRUE if the record exists
   */
  public function itemExists($entity, $id) {
    $url = $this->url . '/' . $entity . "('" . $id . "')";
    $ch = curl_init($url);
    curl_setopt ($ch, CURLOPT_TIMEOUT, 30);
    curl_setopt ($ch, CURLOPT_FOLLOWLOCATION, TRUE);
    curl_setopt($ch,CURLOPT_MAXREDIRS, 3);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($ch, CURLOPT_NOBODY, FALSE);
    curl_exec($ch);
    $code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    if ($code != 200 && $code != 301) {
      return FALSE;
    }
    return TRUE;
  }


  /**
   * Return a single page of results
   *
   * @return array
   *   Array of stdClass objects
   */
  protected function getPaginatedData($entity) {
    $ret = array();
    $pageSize = ODataConsumerConfig::getODataPageSize();
    $page = 0;
    $base_url = $this->url . '/' . $entity;
    $url = sprintf($base_url . '?$top=%d&$skip=%d', $pageSize, $page);
    $odata_filter = $this->config->getListingQueryString($entity);
    if ($odata_filter) {
      $url .= $odata_filter;
    }
    $previous = NULL;
    while ($rows = $this->parseJSONRemoteListPage($url)) {
      // Detect infinite loop when the service does not recognise pagination
      if (json_encode($rows) === json_encode($previous)) {
        break;
      };
      if (!empty($rows)) {
        foreach ($rows as $row) {
          if (array_key_exists($row->id, $ret)) {
            ws_consumer_odata_log(__METHOD__ . ": Found duplicate row, id:" . $row->id . " feed: " . $url, MigrationBase::MESSAGE_WARNING);
          }
          else {
            $ret[$row->id] = $ret;
          }
        }
      }
      $page += $pageSize;
      $url = sprintf($base_url . '?$top=%d&$skip=%d', $pageSize, $page);
      $url .= $odata_filter;
      $previous = $rows;
    }
    return $ret;
  }


  /**
   * Parse the JSON OData feed.
   *
   * @param string $url
   *   The URL to download the data
   *
   * @return array
   *   Array of stdClass
   */
  protected function parseJSONRemoteListPage($url) {
    $ret = array();
    if ($remote = $this->loadRemoteData($url)) {
      $results = gettype($remote) == 'object' ? $remote->results : $remote;
      foreach ($results as $row) {
        $ret[$row->id] = $row;
      }
    }
    return $ret;
  }

  public function loadRemoteData($url) {
    $ret = NULL;
    ws_consumer_odata_log(__METHOD__ . ": Retrieving OData result from: " . $url, MigrationBase::MESSAGE_NOTICE);
    $response = ODataMigrationUtil::http_request($url, array('Accept: application/json'));
    if (!empty($response) && $json = json_decode($response)) {
      $ret = $json->d;
    }
    return $ret;
  }

  public function loadNavigationProperty($ob, $property_name) {
    // OData v1, property expanded using $expand=property_name
    // No need for an additional HTTP request, data already there
    $results = array();
    if (!empty($ob->{$property_name})) {
      if (gettype($ob->{$property_name}) == 'object') {
        if (property_exists($ob->{$property_name}, 'results')) {
          return $ob->{$property_name}->results;
        }
      }
      else {
        $results = $ob->{$property_name};
      }
    }
    if (!empty($ob->{$property_name}) && !empty($results)) {
      return $results;
    }
    // OData v1, without $expand.
    if (!empty($ob->{$property_name}->__deferred->uri)) {
      /** @var stdClass $result */
      if ($result = $this->loadRemoteData($ob->{$property_name}->__deferred->uri)) {
        if ($property_name == 'files') {
          if (is_object($result) && property_exists($result, 'results')) {
            return $result->results;
          }
          else {
            return $result;
          }
        }
        return $result->results;
      }
    }
    return NULL;
  }
}
