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
      'odata_cbd_Contacts'        => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_stockholm_Contacts'  => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_rotterdam_Contacts'  => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ROTTERDAM, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_basel_Contacts'      => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_BASEL, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_cites_Contacts'      => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),
      'odata_ramsar_Contacts'      => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_CONTACTS),

      /* Meetings migrations */
      'odata_cbd_Meetings'        => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_basel_Meetings'      => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_BASEL, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_stockholm_Meetings'  => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_rotterdam_Meetings'  => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ROTTERDAM, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_cites_Meetings'      => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_cms_Meetings'        => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CMS, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_ascobans_Meetings'   => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ASCOBANS, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_aewa_Meetings'       => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_AEWA, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_whc_Meetings'        => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_montreal_Meetings'   => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_MONTREAL, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),
      'odata_ramsar_Meetings'     => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_MEETINGS),

      /* NationalPlans migrations */
      'odata_stockholm_NationalPlans' => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_ACTION_PLAN),
      'odata_cbd_NationalPlans'       => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_ACTION_PLAN),

      /* Decisions migrations */
      'odata_cms_Decisions'       => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CMS, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_cms_Meetings')),
      'odata_ascobans_Decisions'  => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ASCOBANS, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_ascobans_Meetings')),
      'odata_aewa_Decisions'      => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_AEWA, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_aewa_Meetings')),
      'odata_cites_Decisions'     => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_cites_Meetings')),
      'odata_cbd_Decisions'       => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_cbd_Meetings')),
      'odata_whc_Decisions'       => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_whc_Meetings')),
      'odata_basel_Decisions'     => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_BASEL, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_basel_Meetings')),
      'odata_stockholm_Decisions' => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_STOCKHOLM, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_stockholm_Meetings')),
      'odata_rotterdam_Decisions' => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ROTTERDAM, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_rotterdam_Meetings')),
      'odata_montreal_Decisions'  => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_MONTREAL, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_montreal_Meetings')),
      'odata_ramsar_Decisions'  => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_DECISIONS, array('odata_ramsar_Meetings')),

      /* CountryReports migrations */
      'odata_ascobans_CountryReports'  => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_ASCOBANS, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_cms_CountryReports'       => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CMS, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_aewa_CountryReports'      => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_AEWA, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_cites_CountryReports'     => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CITES, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_cbd_CountryReports'       => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_CBD, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_whc_CountryReports'       => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),
      'odata_ramsar_CountryReports'       => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT),

      /* Sites migrations */
      'odata_whc_Sites' => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_WHC, ODataConsumerConfig::$ODATA_ENTITY_SITES),
      'odata_ramsar_Sites' => ODataMigrationUtil::createMigrationConfig(ODataConsumerConfig::$ODATA_NAME_RAMSAR, ODataConsumerConfig::$ODATA_ENTITY_SITES),
    )
  );

  return $ret;
}


abstract class InforMEAAbstractODataMigrateSource extends MigrateSource {

  protected $data = array();
  /** @var ODataConsumerConfig */
  protected $config = NULL;
  /** @var ODataConsumer */
  protected $consumer = NULL;

  protected $currentPage = 0;
  protected $currentCount = 0;
  protected $pageSize = 100;
  protected $count = 0;

  public function __construct(array $options, $config) {
    parent::__construct($options);
    $this->config = $config;
    $klass = $this->config->getODataConsumerClass();
    $this->consumer = new $klass($config);
  }

  public function __toString() {
    return __CLASS__ . '-' . $this->config->odata_name . '-' . $this->config->odata_entity;
  }

  public function performRewind() {
    reset($this->data);
  }

  public function computeCount() {
    if (empty($this->count)) {
      $this->count = $this->consumer->countTotal($this->config->odata_entity);
    }
    return $this->count;
  }

  public function getNextRow() {
    migrate_instrument_start(__METHOD__, TRUE);
    $next_call_count = $this->currentPage * $this->pageSize;
    if ($this->currentCount == $this->count()) {
      return NULL;
    }
    if ($this->currentCount == $next_call_count && $next_call_count < $this->count()) {
      $start = $this->currentPage * $this->pageSize;
      if ($this->data = $this->consumer->getPage($this->config->odata_entity, $start, $this->activeMigration)) {
        $this->currentPage++;
      }
    }
    $item = NULL;
    if (count($this->data)) {
      $item = current($this->data);
      next($this->data);
      $this->currentCount++;
    }
    migrate_instrument_stop(__METHOD__);
    return $item;
  }

  public function getLimit() {
    $limit = NULL;
    if (!empty($this->activeMigration->getOption('limit')) && $this->activeMigration->getOption('limit')['unit'] == 'items') {
      $limit = $this->activeMigration->getOption('limit')['value'];
    }
    return $limit;
  }

  public function resetData() {
    $this->data = array();
  }

  public function getConsumer() {
    return $this->consumer;
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

  static function getOrCreateTaxonomyTermByName($name, $vid) {
    /** @var SelectQuery $query */
    $query = db_select('taxonomy_term_data', 'a')->fields('a', array('tid'))->condition('vid', $vid)->condition('name', $name);
    if ($tid = $query->execute()->fetchField()) {
      return $tid;
    }
    else {
      // Create the term
      $term = new stdClass();
      $term->language = 'en';
      $term->vid = $vid;
      $term->name = $name;
      $term->name_field['en'][0]['value'] = $name;
      taxonomy_term_save($term);
      if (!empty($term->tid)) {
        return $term->tid;
      }
      return NULL;
    }
  }

  /**
   * Make relative HTML anchors absolute, or remove if cannot resolve them properly.
   * @param string $text
   *   HTML text to check
   * @param string $domain
   *   Domain to append when making the anchors absolute
   * @return string
   *   Fixed string
   */
  static function fixHtmlAnchors($text, $domain) {
    $doc = new DOMDocument();
    if (@$doc->loadHTML($text, LIBXML_HTML_NOIMPLIED | LIBXML_HTML_NODEFDTD)) {
      /** @var DOMNodeList $urls */
      $anchors = $doc->getElementsByTagName('a');
      /** @var DOMElement $anchor */
      for($i = $anchors->length - 1; $i >= 0; $i--) {
        $anchor = $anchors->item($i);
        $href = $anchor->getAttribute('href');
        if (preg_match('/^http/', $href)) {
          $anchor->setAttribute('target', '_blank');
        }
        // Relative URL to the root of the domain, make it absolute
        else if (preg_match('/^\//', $href) && $domain) {
          $anchor->setAttribute('href', $domain . $href);
          $anchor->setAttribute('target', '_blank');
        }
        // Relative URL, remove it - we don't know how to fix it
        else {
          $replacement = $doc->createTextNode($anchor->textContent);
          $anchor->parentNode->replaceChild($replacement, $anchor);
        }
      }
      return $doc->saveHTML();
    }
    else {
      // Unparseable - clobber all anchors the REGEX way
      return preg_replace('/<a[^>]*>|<\/a>/', '', $text);
    }
  }
}
