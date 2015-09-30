<?php

/**
 * Class CountryReportsODataMigration migrate OData contacts
 */
class CountryReportsODataMigration extends AbstractODataMigration {

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
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_NATIONAL_REPORT, $this->config->odata_name);
    $this->source      = new CountryReportsMigrateSourceList(
      new ODataMigrateList($this->config),
      new CountryReportsODataMigrateItem($this->config)
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
      ODataConsumerConfig::$DRUPAL_TYPE_NATIONAL_REPORT,
      array('text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'title_orig');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'title_langs');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_report_submission_date', 'submission');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_document_url', 'url');

    $this->addFieldMapping('field_last_update', 'updated');
    $this->addFieldMapping('changed', 'updated');

    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');


    $this->addFieldMapping('field_files', 'files');
    $this->addFieldMapping('field_files:description', 'files');
    $this->addFieldMapping('field_files:language', 'files_language');
    $this->addFieldMapping('field_files:destination_dir')->defaultValue('public://reports/national/' . $this->config->odata_name);
    $this->addFieldMapping('field_files:destination_file', 'filename');

    $this->addUnmigratedDestinations(array(
      'created', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'body', 'body:summary', 'body:format', 'path',
      'body:language',
      'field_report_submission_date:timezone', 'field_report_submission_date:rrule',
      'field_report_submission_date:to', 'field_document_url:title',
      'field_document_url:attributes', 'field_document_url:language',
      'field_files:file_class', 'field_files:preserve_files', 'field_files:file_replace',
      'field_files:source_dir', 'field_files:urlencode', 'field_files:display',
      'field_informea_tags', 'field_informea_tags:source_type',
      'field_informea_tags:create_term', 'field_informea_tags:ignore_case',
      'field_last_update:timezone', 'field_last_update:rrule',
      'field_last_update:to',
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
      ws_consumer_odata_log('Skipping Country Report with source id=' . $row->id .' because no title could be found.', MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }

    if (!empty($row->submission)) {
      $row->submission = $this->fixDateValue($row->submission);
    }
    $row->treaty = $this->getTreatyByODataIdentifier($row->treaty)->nid;

    $row->filename = array();
    foreach ($row->files as $file) {
      if ($filename = $this->extractFilenameFromURL($file)) {
        $row->filename[] = $filename;
      }
    }
  }

  function prepare($entity, $row) {
    $this->setTranslation($entity, $row->files_language);
  }

}
