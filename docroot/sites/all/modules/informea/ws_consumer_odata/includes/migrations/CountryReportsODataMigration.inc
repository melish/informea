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
    $this->source      = new InforMEAODataCountryReportsMigrateSource($arguments, $this->config);
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
    $this->addFieldMapping('field_sorting_date', 'submission');
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
    $this->addFieldMapping('field_files:file_replace')->defaultValue(MigrateFile::FILE_EXISTS_REUSE);

    $this->addUnmigratedDestinations(array(
      'created', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'body', 'body:summary', 'body:format', 'path',
      'body:language',
      'field_sorting_date:timezone', 'field_sorting_date:rrule',
      'field_sorting_date:to', 'field_document_url:title',
      'field_document_url:attributes', 'field_document_url:language',
      'field_files:file_class', 'field_files:preserve_files',
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
    return TRUE;
  }

  function prepare($entity, $row) {
    $this->setTranslation($entity, $row->files_language);
  }

}

class InforMEAODataCountryReportsMigrateSource extends InforMEAAbstractODataMigrateSource {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'title' => 'Translated titles',
      'title_en' => 'Report title in English',
      'title_languages' => 'Title languages',
      'treaty' => 'The meeting is linked to this treaty',
      'country' => 'Country',
      'type' => 'Type',
      'url' => 'Document URL',
      'submission' => 'Submission date',
      'files' => 'Files',
      'files_language' => 'Files language',
      'filename' => 'filename',
      'updated' => 'Updated',
    );
  }

  protected function pullRemoteData() {
    migrate_instrument_start(get_class($this) . ' pullRemoteData', TRUE);
    try {
      $query = '&$expand=title,files&$orderby=updated%20desc';
      $highwater = $this->activeMigration->getHighwater();
      if (!empty($highwater)) {
        $query .= '&$filter=updated%20gt%20datetime%27' . date('Y-m-d\TH:i:s', $highwater) . '%27';
      }
      $this->remote_queried = TRUE;
      $this->items = array();
      $rows = $this->consumer->getRemoteEntities($this->config->odata_entity, $query);
      foreach($rows as $row) {
        if (!property_exists($row,'updated')) {
          $row->updated = time();
        }
        $this->items[$row->id] = $row;
      }
    } catch(Exception $e) {
    }
    migrate_instrument_stop(get_class($this) . ' pullRemoteData');
  }

  protected function populateRow($row) {
    $all_languages = array('en');
    $titles = $this->consumer->loadNavigationProperty($row, 'title');
    $row->title_en = ODataMigrationUtil::prepareTitle($titles);
    list($titles, $languages) = ODataMigrationUtil::getSingleValuedMultilingualField($titles);
    $row->title = $titles;
    $row->title_languages = $languages;
    $all_languages = array_merge($all_languages, $languages);
    $row->languages = array_unique($all_languages);
  }
}
