<?php


class ODataConsumerTestConfig extends ODataConsumerConfig {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Override URL endpoints
    $this->endpoints[self::$ODATA_NAME_CBD]['default'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v3';

  }

}
