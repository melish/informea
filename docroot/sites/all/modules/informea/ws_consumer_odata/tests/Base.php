<?php


class ODataConsumerTestConfig extends ODataConsumerConfig {

  public static $overrides = array();

  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }

  static function getConfiguration() {
    $config = parent::getConfiguration();
    // Override URL endpoints
    $config['endpoints'][self::$ODATA_NAME_CBD]['default'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v3';
    $config['endpoints'][self::$ODATA_NAME_ROTTERDAM]['Contacts'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $config['endpoints'][self::$ODATA_NAME_WHC]['default'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $config['endpoints'][self::$ODATA_NAME_STOCKHOLM]['Meetings'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $config['endpoints'][self::$ODATA_NAME_STOCKHOLM]['NationalPlans'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $config['endpoints'][self::$ODATA_NAME_STOCKHOLM]['Decisions'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $config['endpoints'][self::$ODATA_NAME_AEWA]['default'] = 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v1';
    $full = array_replace_recursive($config, self::$overrides);
    return $full;
  }

  public function getDecisionMeetingMappingTable() {
    $machine = Migration::currentMigration()->getMachineName();
    if ($machine == 'test_decisions_odata_v3') {
      return 'migrate_map_test_decisions_meetings_odata_v3';
    }
    return 'migrate_map_test_decisions_meetings_odata_v1';
  }
}
