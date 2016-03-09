<?php

/**
 * Implements hook_migrate_api().
 *
 * Set the API level to 2, for migration classes to be recognized by Migrate.
 */
function ws_consumer_odata_migrate_api() {
  $ret = array(
    'api' => 2,
    'groups' => array(
      'odata_cbd' => array('title' => 'CBD OData importers'),
      'odata_stockholm' => array('title' => 'Stockholm Convention OData importers'),
      'odata_rotterdam' => array('title' => 'Rotterdam Convention OData importers'),
      'odata_basel' => array('title' => 'Basel OData importers'),
      'odata_cites' => array('title' => 'CITES OData importers'),
      'odata_cms' => array('title' => 'CMS OData importers'),
      'odata_ascobans' => array('title' => 'ASCOBANS OData importers'),
      'odata_aewa' => array('title' => 'AEWA OData importers'),
      'odata_whc' => array('title' => 'WHC/UNESCO OData importers'),
      'odata_montreal' => array('title' => 'OZONE OData importers'),
      'odata_ramsar' => array('title' => 'Ramsar OData importers'),
    ),
    'migrations' => array(
      /* Contacts migrations */
      'odata_cbd_Contacts'        => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_stockholm_Contacts'  => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_rotterdam_Contacts'  => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ROTTERDAM, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_basel_Contacts'      => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_BASEL, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_cites_Contacts'      => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_ramsar_Contacts'      => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),

      /* Meetings migrations */
      'odata_cbd_Meetings'        => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_basel_Meetings'      => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_BASEL, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_stockholm_Meetings'  => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_rotterdam_Meetings'  => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ROTTERDAM, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_cites_Meetings'      => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_cms_Meetings'        => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CMS, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_ascobans_Meetings'   => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ASCOBANS, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_aewa_Meetings'       => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_AEWA, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_whc_Meetings'        => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_montreal_Meetings'   => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_MONTREAL, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_ramsar_Meetings'     => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),

      /* NationalPlans migrations */
      'odata_stockholm_NationalPlans' => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_ACTION_PLAN),
      'odata_cbd_NationalPlans'       => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_ACTION_PLAN),

      /* Decisions migrations */
      'odata_cms_Decisions'       => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CMS, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_cms_Meetings')),
      'odata_ascobans_Decisions'  => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ASCOBANS, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_ascobans_Meetings')),
      'odata_aewa_Decisions'      => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_AEWA, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_aewa_Meetings')),
      'odata_cites_Decisions'     => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_cites_Meetings')),
      'odata_cbd_Decisions'       => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_cbd_Meetings')),
      'odata_whc_Decisions'       => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_whc_Meetings')),
      'odata_basel_Decisions'     => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_BASEL, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_basel_Meetings')),
      'odata_stockholm_Decisions' => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_stockholm_Meetings')),
      'odata_rotterdam_Decisions' => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ROTTERDAM, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_rotterdam_Meetings')),
      'odata_montreal_Decisions'  => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_MONTREAL, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_montreal_Meetings')),
      'odata_ramsar_Decisions'  => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_ramsar_Meetings')),

      /* CountryReports migrations */
      'odata_ascobans_CountryReports'  => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ASCOBANS, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_cms_CountryReports'       => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CMS, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_aewa_CountryReports'      => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_AEWA, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_cites_CountryReports'     => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_cbd_CountryReports'       => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_whc_CountryReports'       => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_ramsar_CountryReports'       => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),

      /* Sites migrations */
      'odata_whc_Sites' => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_SITES),
      'odata_ramsar_Sites' => ODataConsumerConfig::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_SITES),
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

  function prepareTitle($odata_ob) {
    //Get titles
    $title_langs = array();
    $titles = array();
    $title_orig = NULL;
    $values = $this->getComplexProperty($odata_ob, 'title');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->value)) {
          $title_langs[] = $value->language;
          $titles[] = strip_tags($value->value);
          if ($value->language == 'en') {
            $title_orig = strip_tags($value->value);
          }
        }
      }
    }
    $odata_ob->title_langs = $title_langs;
    $odata_ob->title = $titles;
    if ($title_orig) {
      $odata_ob->title_orig = $title_orig;
    }
    else {
      $odata_ob->title_orig = empty($titles) ? '' : $titles[0];
    }
  }

  function prepareFiles($odata_ob) {
    //Get files
    $files = array();
    $files_language = array();
    $values = $this->getComplexProperty($odata_ob, 'files');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->url)) {
          $lang = 'en';
          // Handle UND
          if (!empty($value->language)) {
            switch ($value->language) {
              case 'esp':
                $lang = 'es';
                break;
              case 'fra':
                $lang = 'fr';
            }
          }
          $files_language[] = $lang;
          $files[] = $value->url;
        }
      }
    }
    $odata_ob->files_language = $files_language;
    $odata_ob->files = $files;
  }
}

abstract class InforMEAAbstractODataMigrateSource extends MigrateSource {

  protected $items = array();
  /** @var ODataConsumerConfig */
  protected $config = NULL;
  /** @var ODataConsumer */
  protected $consumer = NULL;
  /** @var bool Data  */
  protected $remote_queried = FALSE;

  protected abstract function pullRemoteData();

  protected abstract function populateRow($row);

  public function __construct(array $options, $config) {
    parent::__construct($options);
    $this->config = $config;
    $klass = $this->config->getODataConsumerClass();
    $uri = $this->config->getEndpointURL();
    $this->consumer = new $klass($uri);
  }

  public function __toString() {
    return __CLASS__ . '-' . $this->config->odata_name . '-' . $this->config->odata_entity;
  }

  public function performRewind() {
    $this->readRemoteItems();
    reset($this->items);
  }

  public function computeCount() {
    return $this->consumer->countTotal($this->config->odata_entity);
  }

  protected function readRemoteItems() {
    if (empty($this->items) && !$this->remote_queried) {
      migrate_instrument_start(get_class($this) . ' pullRemoteData', TRUE);
      $this->items = array();
      $this->remote_queried = TRUE;
      try {
        $rows = $this->pullRemoteData();
        foreach ($rows as $row) {
          if (empty($row->updated)) {
            $row->updated = time();
          }
          $this->items[$row->id] = $row;
        }
      } catch (Exception $e) {
        //@todo: Do we need to do anything here?
      }
      migrate_instrument_stop(get_class($this) . ' pullRemoteData');
    }
  }

  public function getNextRow() {
    $this->readRemoteItems();
    if ($item = current($this->items)) {
      $this->populateRow($item);
    }
    next($this->items);
    return $item;
  }
}


class ODataMigrationUtil {

  /**
   * Prepare English title (node.title).
   *
   * @param $values
   *
   * @return string title
   */
  static function prepareTitle($values) {
    if(empty($values) || !is_array($values)) {
      return NULL;
    }
    foreach ($values as $value) {
      if ($value->language == 'en') {
        return $value->value;
      }
    }
    return NULL;
  }

  static function getSingleValuedMultilingualField($data) {
    $languages = array();
    $values = array();
    if (!empty($data) && is_array($data)) {
      foreach ($data as $value) {
        if (!empty($value->value)) {
          $languages[] = $value->language;
          $values[] = $value->value;
        }
      }
    }
    return array($values, $languages);
  }


  static function extractNavigationPropertyValues($ob, $property_name) {
    // OData v1, property expanded using $expand=property_name
    // No need for an additional HTTP request, data already there
    $results = array();
    if (!empty($ob->{$property_name})) {
      if (gettype($ob->{$property_name}) == 'object' && property_exists($ob->{$property_name}, 'results')) {
        $results = $ob->{$property_name}->results;
      }
      else {
        $results = $ob->{$property_name};
      }
    }
    if (!empty($ob->{$property_name}) && !empty($results)) {
      return $results;
    }
    return NULL;
  }


  static public function http_request($url, $headers = array()) {
    migrate_instrument_start(__CLASS__ . ' http_request');
    ws_consumer_odata_log(__METHOD__ . ": HTTP request: $url", MigrationBase::MESSAGE_INFORMATIONAL);
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 3);
    curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
    curl_setopt($ch, CURLOPT_NOBODY, 0);
    $ret = curl_exec($ch);
    $info = curl_getinfo($ch);
    if ($info['http_code'] != 200) {
      $code = $info['http_code'];
      ws_consumer_odata_log(__METHOD__ . ": HTTP request failure ({$code}) for URL: $url", MigrationBase::MESSAGE_ERROR);
      $ret = NULL;
    }
    curl_close($ch);
    migrate_instrument_stop(__CLASS__ . ' http_request');
    return $ret;
  }

  static function filenameFromURL($url) {
    $ret = NULL;
    $to_remove = "download.aspx?d=";
    if (strpos($url, $to_remove)) {
      $ret = substr($url, strpos($url, $to_remove) + strlen($to_remove));
    }
    else {
      $l = parse_url($url);
      $ret = basename($l['path']);
    }
    return $ret;
  }

  static function fixLanguage($language) {
    // Sometimes chinese comes as 'zh' instead of 'zh-hans'
    if (empty($language)) {
      return 'en';
    }
    if ($language == 'zh') {
      return 'zh-hans';
    }
    return $language;
  }
}
