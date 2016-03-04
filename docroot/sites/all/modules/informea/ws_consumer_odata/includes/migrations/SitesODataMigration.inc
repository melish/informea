<?php

/**
 * Class SitesODataMigration migrate OData contacts
 */
class SitesODataMigration extends AbstractODataMigration {

  /**
   * @var ODataConsumerConfig
   */
  protected $config = NULL;

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_SITES, $this->config->odata_name);
    $this->source      = new InforMEAODataSitesMigrateSource($arguments, $this->config);
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Original ID from the MEA website',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode(
      ODataConsumerConfig::$DRUPAL_TYPE_SITES,
      array('language' => 'en', 'text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'name_en');
    $this->addFieldMapping('title_field', 'names');
    $this->addFieldMapping('title_field:language', 'names_languages');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_url', 'url');
    $this->addFieldMapping('field_latitude', 'latitude');
    $this->addFieldMapping('field_longitude', 'longitude');

    $this->addFieldMapping('field_last_update', 'updated');
    $this->addFieldMapping('field_last_update:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('changed', 'updated');

    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');

    $this->addUnmigratedDestinations(array(
      'created', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'body', 'body:summary', 'body:format', 'path',
      'body:language', 'field_informea_tags', 'field_informea_tags:source_type',
      'field_informea_tags:create_term', 'field_informea_tags:ignore_case',
      'field_url:language', 'field_url:attributes', 'field_url:title',
      'field_last_update:rrule', 'field_last_update:to',
    ));
  }

  /**
   * Add some Contacts specific preparations.
   *
   * {@inheritdoc}
   */
  function prepareRow($row) {
    parent::prepareRow($row);

    if (!$row->name_en) {
      ws_consumer_odata_log('Skipping Site with source id=' . $row->id .' because name in English could be found.', MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }

    $row->treaty = $this->getTreatyByODataIdentifier($row->treaty)->nid;
    return TRUE;
  }
}


class InforMEAODataSitesMigrateSource extends InforMEAAbstractODataMigrateSource {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'name_en' => 'Site name in English',
      'names' => 'Site name translations',
      'names_languages' => 'Site name languages',
      'treaty' => 'Site treaty',
      'country' => 'Country',
      'url' => 'Site URL on MEA website',
      'latitude' => 'Geographical latitude',
      'longitude' => 'Geographical longitude',
      'updated' => 'Date of last update',
    );
  }

  protected function pullRemoteData() {
    $query = '&$expand=name&$orderby=updated%20desc';
    $highwater = $this->activeMigration->getHighwater();
    if (!empty($highwater)) {
      $query .= '&$filter=updated%20gt%20datetime%27' . date('Y-m-d\TH:i:s', $highwater) . '%27';
    }
    return $this->consumer->getRemoteEntities($this->config->odata_entity, $query);
  }

  protected function populateRow($row) {
    $all_languages = array('en');
    $names = $this->consumer->loadNavigationProperty($row, 'name');
    $row->name_en = ODataMigrationUtil::prepareTitle($names);
    list($names, $languages) = ODataMigrationUtil::getSingleValuedMultilingualField($names);
    $row->names = $names;
    $row->names_languages = $languages;
    $all_languages = array_merge($all_languages, $languages);
    $row->languages = array_unique($all_languages);
  }
}
