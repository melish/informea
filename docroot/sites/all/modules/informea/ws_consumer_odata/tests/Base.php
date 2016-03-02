<?php


class ODataConsumerTestConfig extends ODataConsumerConfig {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Override URL endpoints
    $this->endpoints[self::$ODATA_NAME_CBD]['default'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v3';
    $this->endpoints[self::$ODATA_NAME_ROTTERDAM]['Contacts'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $this->endpoints[self::$ODATA_NAME_WHC]['default'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $this->endpoints[self::$ODATA_NAME_STOCKHOLM]['Meetings'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $this->endpoints[self::$ODATA_NAME_STOCKHOLM]['NationalPlans'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $this->endpoints[self::$ODATA_NAME_STOCKHOLM]['Decisions'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
  }
}
