<?php

/**
 * Class ODataConsumerConfig provides configuration framework for all migrations
 */
class ODataConsumerConfig {

  public static $ODATA_NAME_STOCKHOLM = 'stockholm';
  public static $ODATA_NAME_BASEL = 'basel';
  public static $ODATA_NAME_ROTTERDAM = 'rotterdam';
  public static $ODATA_NAME_CITES = 'cites';
  public static $ODATA_NAME_CMS = 'cms';
  public static $ODATA_NAME_AEWA = 'aewa';
  public static $ODATA_NAME_ASCOBANS = 'ascobans';
  public static $ODATA_NAME_EUROBATS = 'eurobats';
  public static $ODATA_NAME_CBD = 'cbd';
  public static $ODATA_NAME_OZONE = 'ozone';
  public static $ODATA_NAME_PLANT_TREATY = 'plant_treaty';
  public static $ODATA_NAME_WHC = 'whc';
  public static $ODATA_NAME_MONTREAL = 'montreal';
  public static $ODATA_NAME_TEST = 'test';

  public static $ODATA_ENTITY_CONTACTS = 'Contacts';
  public static $DRUPAL_TYPE_CONTACTS = 'contact_person';

  public static $ODATA_ENTITY_MEETINGS = 'Meetings';
  public static $DRUPAL_TYPE_MEETINGS = 'event_calendar';

  public static $ODATA_ENTITY_NATIONAL_REPORT = 'CountryReports';
  public static $DRUPAL_TYPE_NATIONAL_REPORT = 'national_report';

  public static $ODATA_ENTITY_ACTION_PLAN = 'NationalPlans';
  public static $DRUPAL_TYPE_ACTION_PLAN = 'action_plan';

  public static $ODATA_ENTITY_SITES = 'Sites';
  public static $DRUPAL_TYPE_SITES = 'geographical_site';

  public static $ODATA_ENTITY_DECISIONS = 'Decisions';
  public static $DRUPAL_TYPE_DECISIONS = 'decision';

  public $odata_entity = NULL;
  public $odata_name = NULL;
  public $endpoints = array();

  /**
   * Build new configuration object.
   *
   * @param array $arguments
   *   Endpoint configuration
   */
  public function __construct($arguments = array()) {
    if (isset($arguments['odata_entity'])) {
      $this->odata_entity = $arguments['odata_entity'];
    }
    if (isset($arguments['odata_name'])) {
      $this->odata_name = $arguments['odata_name'];
    }
    $this->endpoints = array(
      self::$ODATA_NAME_STOCKHOLM => array(
        'Contacts' => 'http://informea.pops.int/Contacts2/scContacts.svc',
        'Meetings' => 'http://informea.pops.int/Meetings/scMeetings.svc',
        'NationalPlans' => 'http://informea.pops.int/NationalPlans/scNationalPlans.svc',
        'Decisions' => 'http://informea.pops.int/Documents/sc/Decisions.svc',
      ),
      self::$ODATA_NAME_ROTTERDAM => array(
        'Contacts' => 'http://informea.pops.int/Contacts2/rcContacts.svc',
        'Meetings' => 'http://informea.pops.int/Meetings/rcMeetings.svc',
        'Decisions' => 'http://informea.pops.int/Documents/rc/Decisions.svc',
      ),
      self::$ODATA_NAME_BASEL => array(
        'Contacts' => 'http://informea.pops.int/Contacts2/BcContacts.svc',
        'Meetings' => 'http://informea.pops.int/Meetings/bcMeetings.svc',
        'Decisions' => 'http://informea.pops.int/Documents/bc/Decisions.svc',
      ),
      self::$ODATA_NAME_CITES => array(
        'default' => 'http://odata.cites.org/informea.svc'
      ),
      self::$ODATA_NAME_CMS => array(
        'default' => 'http://odata.cms.eaudeweb.ro/cms/informea.svc'
      ),
      self::$ODATA_NAME_AEWA => array(
        'default' => 'http://odata.cms.eaudeweb.ro/aewa/informea.svc'
      ),
      self::$ODATA_NAME_ASCOBANS => array(
        'default' => 'http://odata.cms.eaudeweb.ro/ascobans/informea.svc'
      ),
      self::$ODATA_NAME_EUROBATS=> array(
        'default' => 'http://odata.cms.eaudeweb.ro/eurobats/services/odata.svc'
      ),
      self::$ODATA_NAME_CBD => array(
        'default' => 'https://api.cbd.int/informea.svc'
      ),
      self::$ODATA_NAME_OZONE => array(
        'default' => 'http://ozone.unep.org:8080/informea/services/odata.svc'
      ),
      self::$ODATA_NAME_PLANT_TREATY => array(
        'default' => 'http://odata.informea.org/odata-fao/services/odata.svc'
      ),
      self::$ODATA_NAME_WHC => array(
        'default' => 'http://whc.unesco.org/informea/informea.svc'
      ),
      self::$ODATA_NAME_MONTREAL => array(
        'default' => 'http://41.191.194.28:8080/informea/services/odata.svc'
      ),
      self::$ODATA_NAME_TEST => array(
        'default' => 'http://odata.informea.org/informea.svc'
      ),
    );
  }

  /**
   * Provide name of the OData consumer class to use, depending on the service.
   *
   * @return string
   *   Class name
   */
  public function getODataConsumerClass() {
    switch($this->odata_name) {
      case ODataConsumerConfig::$ODATA_NAME_CBD:
        $ret = 'ODataConsumerV3';
        break;
      default:
        $ret = 'ODataConsumerV1';
    }
    return $ret;
  }

  /**
   * Utility function to create a migration configuration.
   *
   * @param string $odata_name
   *   Treaty OData identifier - for which treaty we retrieve data?
   * @param string $odata_entity
   *   Name of the OData entity to import (ie. Contacts)
   * @param array $dependencies
   *   Array of dependent migrations (migration names)
   *
   * @return array|bool
   *   FALSE if the treaty does not exist, failing the migration registration
   */
  public static function createMigrationConfig($odata_name, $odata_entity, $dependencies = array()) {
    module_load_include('inc', 'treaty', 'treaty.api');
    $klass = $odata_entity . 'ODataMigration';
    $treaty = treaty_load_by_odata_name($odata_name);
    if (!$treaty || $treaty->status != NODE_PUBLISHED) {
      ws_consumer_odata_log(
        sprintf('Failed to register migration odata_%s_%s, cannot find treaty with odata_name:%s',
          $odata_name, $odata_entity, $odata_name
        ),
        MigrationBase::MESSAGE_ERROR
      );
      return FALSE;
    }
    $disable_hooks = array(
      'entity_update' => array(
        'search_api',
        'search_api_solr',
        'event_calendar',
        'feeds',
        'pathauto',
      ),
      'node_update' => array(
        'search_api',
        'search_api_solr',
        'event_calendar',
        'feeds',
        'pathauto',
      ),
      'entity_insert' => array(
        'feeds',
        'search_api_solr',
        'event_calendar',
        'feeds',
        'search_api'
      ),
    );
    return array(
      'config_class' => 'ODataConsumerConfig',
      'class_name' => $klass,
      'odata_entity' => $odata_entity,
      'odata_name' => $odata_name,
      'dependencies' => $dependencies,
      'group_name' => 'odata_' . $odata_name,
      'disable_hooks' => $disable_hooks,
    );
  }

  /**
   * Retrieve OData endpoint URL for the configured source.
   *
   * @return string
   *   URL to the service SVC
   */
  public function getEndpointURL() {
    $ret = NULL;
    if (!empty($this->endpoints[$this->odata_name][$this->odata_entity])) {
      $ret = $this->endpoints[$this->odata_name][$this->odata_entity];
    } else if (!empty($this->endpoints[$this->odata_name]['default'])) {
      $ret = $this->endpoints[$this->odata_name]['default'];
    }
    return $ret;
  }

  /**
   * Static mapping of the OData entities to Drupal content types.
   *
   * @return string
   *   Name of the drupal content type where data is stored
   */
  public function getTargetContentType() {
    $mappings = array(
      self::$ODATA_ENTITY_CONTACTS => self::$DRUPAL_TYPE_CONTACTS,
      self::$ODATA_ENTITY_MEETINGS => self::$DRUPAL_TYPE_MEETINGS,
      self::$ODATA_ENTITY_NATIONAL_REPORT => self::$DRUPAL_TYPE_NATIONAL_REPORT,
      self::$ODATA_ENTITY_ACTION_PLAN => self::$DRUPAL_TYPE_ACTION_PLAN,
      self::$ODATA_ENTITY_SITES => self::$DRUPAL_TYPE_SITES,
      self::$ODATA_ENTITY_DECISIONS => self::$DRUPAL_TYPE_DECISIONS,
    );
    return $mappings[$this->odata_entity];
  }

  public function getDecisionMeetingMappingTable() {
    return 'migrate_map_odata_' . $this->odata_name . '_meetings';
  }
}
