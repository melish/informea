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
    $this->config = new ODataConsumerConfig($arguments);
    $this->arguments   = $arguments;
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_SITES, $this->config->odata_name);
    $this->source      = new SitesMigrateSourceList(
      new ODataMigrateList($this->config),
      new SitesODataMigrateItem($this->config)
    );
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
      array('text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'title_orig');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'title_langs');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_url', 'url');
    $this->addFieldMapping('field_latitude', 'latitude');
    $this->addFieldMapping('field_longitude', 'longitude');

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
    ));
  }

  /**
   * Add some Contacts specific preparations.
   *
   * {@inheritdoc}
   */
  function prepareRow($row) {
    parent::prepareRow($row);

    if (!$row->title) {
      ws_consumer_odata_log('Skipping Site with source id=' . $row->id .' because no title could be found.', MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }

    if (!empty($row->updated)) {
      $row->updated = $this->fixDateValue($row->updated);
    }

    $row->treaty = $this->getTreatyByODataIdentifier($row->treaty)->nid;

  }

}
