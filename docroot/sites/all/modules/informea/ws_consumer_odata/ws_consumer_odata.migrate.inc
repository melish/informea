<?php

/**
 * Implements hook_migrate_api().
 *
 * Set the API level to 2, for migration classes to be recognized by Migrate.
 */
function ws_consumer_odata_migrate_api() {
  $config = new ODataConsumerConfig();
  $ret = array(
    'api' => 2,
    'groups' => array(
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CBD => array( 'title' => ODataConsumerConfig::$ODATA_NAME_CBD . ' OData importers'),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_STOCKHOLM => array( 'title' => ODataConsumerConfig::$ODATA_NAME_STOCKHOLM . ' OData importers'),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_ROTTERDAM => array( 'title' => ODataConsumerConfig::$ODATA_NAME_ROTTERDAM . ' OData importers'),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_BASEL => array( 'title' => ODataConsumerConfig::$ODATA_NAME_BASEL . ' OData importers'),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CITES => array( 'title' => ODataConsumerConfig::$ODATA_NAME_CITES . ' OData importers'),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CMS => array( 'title' => ODataConsumerConfig::$ODATA_NAME_CMS . ' OData importers'),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_ASCOBANS => array( 'title' => ODataConsumerConfig::$ODATA_NAME_ASCOBANS . ' OData importers'),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_AEWA => array( 'title' => ODataConsumerConfig::$ODATA_NAME_AEWA . ' OData importers'),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_WHC => array( 'title' => ODataConsumerConfig::$ODATA_NAME_WHC . ' OData importers'),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_MONTREAL => array( 'title' => ODataConsumerConfig::$ODATA_NAME_MONTREAL . ' OData importers'),
    ),
    'migrations' => array(
      /* Contacts migrations */
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CBD . '_' . ODataConsumerConfig::$ODATA_ENTITY_CONTACTS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_STOCKHOLM . '_' . ODataConsumerConfig::$ODATA_ENTITY_CONTACTS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_ROTTERDAM . '_' . ODataConsumerConfig::$ODATA_ENTITY_CONTACTS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ROTTERDAM, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_BASEL . '_' . ODataConsumerConfig::$ODATA_ENTITY_CONTACTS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_BASEL, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CITES . '_' . ODataConsumerConfig::$ODATA_ENTITY_CONTACTS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),

      /* Meetings migrations */
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CBD . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_BASEL . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_BASEL, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_STOCKHOLM . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_ROTTERDAM . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ROTTERDAM, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CITES . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CMS . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CMS, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_ASCOBANS . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ASCOBANS, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_AEWA . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_AEWA, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_WHC . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_MONTREAL . '_' . ODataConsumerConfig::$ODATA_ENTITY_MEETINGS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_MONTREAL, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),

      /* NationalPlans migrations */
      'odata_' . ODataConsumerConfig::$ODATA_NAME_STOCKHOLM . '_' . ODataConsumerConfig::$ODATA_ENTITY_ACTION_PLAN
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_ACTION_PLAN),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CBD . '_' . ODataConsumerConfig::$ODATA_ENTITY_ACTION_PLAN
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_ACTION_PLAN),

      /* Decisions migrations */
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CMS . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CMS, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_ASCOBANS . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ASCOBANS, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_AEWA . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_AEWA, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CITES . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CBD . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_WHC . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_BASEL . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_BASEL, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_STOCKHOLM . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_ROTTERDAM . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ROTTERDAM, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_MONTREAL . '_' . ODataConsumerConfig::$ODATA_ENTITY_DECISIONS
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_MONTREAL, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS),

      /* CountryReports migrations */
      'odata_' . ODataConsumerConfig::$ODATA_NAME_ASCOBANS . '_' . ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ASCOBANS, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CMS . '_' . ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CMS, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CITES . '_' . ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_CBD . '_' . ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_' . ODataConsumerConfig::$ODATA_NAME_WHC . '_' . ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),

      /* Sites migrations */
      'odata_' . ODataConsumerConfig::$ODATA_NAME_WHC . '_' . ODataConsumerConfig::$ODATA_ENTITY_SITES
          => $config->createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_SITES),
    )
  );

  return $ret;
}


/**
 * Class ODataMigrateList used by all migrations. See MigrateSourceList pattern.
 *
 * @see https://www.drupal.org/node/1152152
 */
class ODataMigrateList extends MigrateList {

  /** @var ODataConsumer object */
  protected $consumer = NULL;

  /** @var ODataConsumerConfig */
  protected $config = NULL;

  public function __construct($config) {
    $this->config = $config;
    $klass = $this->config->getODataConsumerClass();
    $uri = $this->config->getEndpointURL();
    $this->consumer = new $klass($uri);
  }

  /** {@inheritdoc} */
  public function __toString() {
    return sprintf('Extract %s from MEA OData endpoint', $this->config->odata_entity);
  }

  /** {@inheritdoc} */
  public function getIDList() {
    return $this->consumer->getIdList($this->config->odata_entity);
  }

  /** {@inheritdoc} */
  public function computeCount() {
    return $this->consumer->countTotal($this->config->odata_entity);
  }
}

/**
 * Class ODataMigrateItem is the base class for all OData migrated items
 *
 * @see https://www.drupal.org/node/1152152
 */
class ODataMigrateItem extends MigrateItem {

  /** @var ODataConsumer object */
  protected $consumer = NULL;

  /** @var ODataConsumerConfig */
  protected $config = NULL;

  /** {@inheritdoc} */
  public function __construct($config) {
    $this->config = $config;
    $klass = $this->config->getODataConsumerClass();
    $uri = $this->config->getEndpointURL();
    $this->consumer = new $klass($uri);
  }

  /** {@inheritdoc} */
  public function getItem($id, $odata_extra_params = '') {
    // Make sure we actually have an ID.
    if (empty($id)) {
      return NULL;
    }
    return $this->consumer->getItem($this->config->odata_entity, $id, $odata_extra_params);
  }

  /**
   * Load a complex property for the item (OData navigation property).
   * @param stdClass $ob
   *   OData object loaded with getItem()
   * @param string $property_name
   *   Name of the navigation property
   *
   * @return array
   *   Array with the values of the navigation property
   */
  public function getComplexProperty($ob, $property_name) {
    return $this->consumer->loadNavigationProperty($ob, $property_name);
  }
}
