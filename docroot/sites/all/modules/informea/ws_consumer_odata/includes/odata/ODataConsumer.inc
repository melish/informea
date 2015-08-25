<?php

/**
 * Class ODataConsumer talks to OData endpoints and gets data from the service.
 *
 * Supports OData v1
 */
abstract class ODataConsumer {

  protected $url = NULL;

  public function __construct($url) {
    $this->url = $url;
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
    $response = drupal_http_request($url);
    if ($response->code == 200) {
      $ret = intval($response->data);
    }
    else {
      ws_consumer_odata_log('FAIL: ' . get_class($this) . ': Remote counting entities: ' . $url, MigrationBase::MESSAGE_WARNING);
      $url = $this->url . '/' . $entity . '?$inlinecount=allpages';
      ws_consumer_odata_log('RETRY: ' . get_class($this) . ': Remote counting entities: ' . $url);
      $response = drupal_http_request($url);

      $element_name = 'm:count';
      $found = preg_match(
        '#<'.$element_name.'(?:\s+[^>]+)?>(.*?)'.'</'.$element_name.'>#s',
        $response->data,
        $matches
      );
      if ($found) {
        $ret = intval($matches[1]);
      }
    }
    return $ret;
  }


  /**
   * Retrieve OData records from the remove service.
   *
   * Important! Only the primitive properties are loaded, without the
   * navigation properties.
   *
   * @param string $odata_filter
   *   Optional OData URL filter (to filter results after a certain date)
   *
   * @return array
   *   Array of stdClass objects
   */
  public function getIdList($entity, $odata_filter = NULL) {
    $rows = $this->getPaginatedData($entity, $odata_filter);
    $ids = array();
    foreach($rows as $row) {
      $ids[] = $row->id;
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
    $response = drupal_http_request($url, array('headers' => array('Accept' => 'application/json')));
    if ($response->code != 200) {
      ws_consumer_odata_log(__METHOD__ . "($entity, $id): HTTP request failure ({$response->code}) for URL: $url", MigrationBase::MESSAGE_ERROR);
      return $ret;
    }
    if ($json = json_decode($response->data)) {
      $ret = $json->d;
    }
    else {
      ws_consumer_odata_log(__METHOD__ . "($entity, $id): Failed to unpack JSON data from $url", MigrationBase::MESSAGE_ERROR);
    }
    return $ret;
  }


  /**
   * Return a single page of results
   * @param string $odata_filter
   *   Optional OData URL filter (to filter results after a certain date)
   *
   * @return array
   *   Array of stdClass objects
   */
  protected function getPaginatedData($entity, $odata_filter = NULL) {
    $ret = array();
    $pageSize = variable_get('ws_consumer_odata_page_size', 100);
    $page = 0;
    $base_url = $this->url . '/' . $entity;
    $url = sprintf($base_url . '?$select=id&$top=%d&$skip=%d', $pageSize, $page);
    if ($odata_filter) {
      $url .= $odata_filter;
    }
    while ($rows = $this->parseJSONRemoteListPage($url)) {
      if (!empty($rows)) {
        $ret = array_merge($ret, $rows);
      }
      $page += $pageSize;
      $url = sprintf($base_url . '?$select=id&$top=%d&$skip=%d', $pageSize, $page);
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
    $response = drupal_http_request($url, array('headers' => array('Accept' => 'application/json')));
    if ($response->code != 200) {
      ws_consumer_odata_log(__METHOD__ . ": HTTP request failure ({$response->code}) for URL: $url", MigrationBase::MESSAGE_ERROR);
      return $ret;
    }
    if ($remote = $this->loadRemoteData($url)) {
      $results = gettype($remote) == 'object' ? $remote->results : $remote;
      foreach ($results as $row) {
        $ret[$row->id] = $row;
      }
    }
    ws_consumer_odata_log(__METHOD__ . ': Loaded ' . count($ret) . ' rows from ' . $url, MigrationBase::MESSAGE_NOTICE);
    return $ret;
  }

  public function loadRemoteData($url) {
    $ret = NULL;
    ws_consumer_odata_log(__METHOD__ . ": Retrieving OData result from: " . $url, MigrationBase::MESSAGE_NOTICE);
    $response = drupal_http_request($url, array('headers' => array('Accept' => 'application/json')));
    if ($response->code != 200) {
      ws_consumer_odata_log(__METHOD__ . ": HTTP request failure ({$response->code}) for URL: $url", MigrationBase::MESSAGE_ERROR);
      return $ret;
    }
    if ($json = json_decode($response->data)) {
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
          $results = $ob->{$property_name}->results;
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
        return $result->results;
      }
    }
    return NULL;
  }
}
