<?php


class ODataConsumerTestConfig extends ODataConsumerConfig {

  public function __construct(array $arguments) {
    parent::__construct($arguments);
    // Override URL endpoints
    self::$configuration['endpoints'][self::$ODATA_NAME_CBD]['default'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v3';
    self::$configuration['endpoints'][self::$ODATA_NAME_ROTTERDAM]['Contacts'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    self::$configuration['endpoints'][self::$ODATA_NAME_WHC]['default'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    self::$configuration['endpoints'][self::$ODATA_NAME_STOCKHOLM]['Meetings'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    self::$configuration['endpoints'][self::$ODATA_NAME_STOCKHOLM]['NationalPlans'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    self::$configuration['endpoints'][self::$ODATA_NAME_STOCKHOLM]['Decisions'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    self::$configuration['endpoints'][self::$ODATA_NAME_AEWA]['default'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
  }

  public function getDecisionMeetingMappingTable() {
    $machine = Migration::currentMigration()->getMachineName();
    if ($machine == 'test_decisions_odata_v3') {
      return 'migrate_map_test_decisions_meetings_odata_v3';
    }
    return 'migrate_map_test_decisions_meetings_odata_v1';
  }
}
