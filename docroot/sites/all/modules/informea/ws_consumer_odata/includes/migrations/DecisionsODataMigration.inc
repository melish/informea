<?php

/**
 * Class DecisionsODataMigration migrate OData contacts
 */
class DecisionsODataMigration extends AbstractODataMigration {

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
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_DECISIONS, $this->config->odata_name);
    $this->source      = new DecisionsMigrateSourceList(
      new ODataMigrateList($this->config),
      new DecisionsODataMigrateItem($this->config)
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
      ODataConsumerConfig::$DRUPAL_TYPE_DECISIONS,
      array('text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'title_en');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'title_languages');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_decision_status', 'status');
    $this->addFieldMapping('field_decision_type', 'type');
    $this->addFieldMapping('field_decision_number', 'number');
    $this->addFieldMapping('field_sorting_date', 'published');
    $this->addFieldMapping('field_meeting', 'meetingId');
    $this->addFieldMapping('field_meeting_title_en', 'meetingTitle');
    $this->addFieldMapping('field_meeting_url', 'meetingUrl');
    $this->addFieldMapping('body', 'content');
    $this->addFieldMapping('body:language', 'content_languages');
    $this->addFieldMapping('body:summary', 'summary');
    $this->addFieldMapping('field_url', 'link');

    $this->addFieldMapping('field_files', 'files');
    $this->addFieldMapping('field_files:description', 'files');
    $this->addFieldMapping('field_files:language', 'files_language');
    $this->addFieldMapping('field_files:destination_dir')->defaultValue('public://decisions/' . $this->config->odata_name);
    $this->addFieldMapping('field_files:destination_file', 'filename');
    $this->addFieldMapping('field_files:file_replace')->defaultValue(MigrateFile::FILE_EXISTS_REUSE);

    $this->addFieldMapping('field_decision_status:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_decision_status:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_decision_type:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_decision_type:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_last_update', 'updated');
    $this->addFieldMapping('changed', 'updated');

    $this->addFieldMapping('field_sorting_order', 'displayOrder');

    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');

    $this->addUnmigratedDestinations(array(
      'created', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'body:format', 'path', 'field_decision_type:source_type',
      'field_decision_status:source_type',
      'field_sorting_date:timezone', 'field_sorting_date:rrule',
      'field_sorting_date:to',
      'field_last_update:timezone', 'field_last_update:rrule',
      'field_last_update:to',
      'field_meeting_url:title',
      'field_decision_updated:timezone', 'field_decision_updated:rrule',
      'field_decision_updated:to', 'field_decision_updated',
      'field_meeting_url:attributes', 'field_meeting_url:language',
      'field_url:attributes', 'field_url:language', 'field_url:title',
      'field_informea_tags', 'field_informea_tags:source_type',
      'field_informea_tags:create_term', 'field_informea_tags:ignore_case',
      'field_files:preserve_files',
      'field_files:source_dir', 'field_files:urlencode', 'field_files:display',
      'field_files:file_class',
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
      ws_consumer_odata_log('Skipping Decision with source id=' . $row->id .' because no title could be found.', MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }

    if (!empty($row->published)) {
      $row->published = $this->fixDateValue($row->published);
    }
    if (!empty($row->updated)) {
      $row->updated = $this->fixDateValue($row->updated);
    }

    $row->meetingId = $this->map_source_meeting($row->meetingId);

    $row->treaty = $this->getTreatyByODataIdentifier($row->treaty)->nid;

    $row->filename = array();
    foreach ($row->files as $file) {
      if ($filename = $this->extractFilenameFromURL($file)) {
        $row->filename[] = $filename;
      }
    }
    return TRUE;
  }

  public function map_source_meeting($id) {
    $table_name = 'migrate_map_odata_' . $this->config->odata_name . '_meetings';
    $query = db_select($table_name, 'm')
      ->fields('m', array('destid1'))
      ->condition('m.sourceid1', $id);
    $result = $query->execute()->fetchField();
    if (!$result) {
      ws_consumer_odata_log('Meeting with source id=' . $id .' has not been found.', MigrationBase::MESSAGE_WARNING);
    }
    return $result;
  }

}


class InforMEAODataDecisionsMigrateSource extends InforMEAAbstractODataMigrateSource {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'title' => 'Decision title',
      'title_en' => 'Decision title in English',
      'title_languages' => 'Title languages list',
      'treaty' => 'The decision is linked to this treaty',
      'status' => 'Status',
      'type' => 'Type',
      'meetingId' => 'The decision is linked to this meeting entity (sourcedi1)',
      'meetingTitle' => 'Meeting title',
      'meetingUrl' => 'Meeting URL',
      'displayOrder' => 'Decisions display order',
      'number' => 'Number',
      'published' => 'Publication date',
      'files' => 'Decision files',
      'files_language' => 'Files language',
      'content' => 'Body field',
      'content_languages' => 'Body field languages',
      'summary' => 'Body summary',
      'link' => 'URL',
      'filename' => 'filename',
      'updated' => 'Updated',
    );
  }

  protected function pullRemoteData() {
    migrate_instrument_start(get_class($this) . ' pullRemoteData', TRUE);
    try {
      $query = '&$expand=title,files,content,summary&$orderby=updated%20desc';
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

    $content = $this->consumer->loadNavigationProperty($row, 'content');
    list($contents, $languages) = ODataMigrationUtil::getSingleValuedMultilingualField($content);
    $row->content = $contents;
    $row->content_languages = $languages;
    $all_languages = array_merge($all_languages, $languages);
    $row->languages = array_unique($all_languages);

    $summary = $this->consumer->loadNavigationProperty($row, 'summary');
    list($summaries, $languages) = ODataMigrationUtil::getSingleValuedMultilingualField($summary);
    $row->summary = $summaries;

    $files = $this->consumer->loadNavigationProperty($row, 'files');
    $row->files = array();
    $row->files_language = array();
    $row->filename = array();
    foreach($files as $file) {
      if (empty($file->url)) {
        ws_consumer_odata_log('Invalid file for Decision id=' . $row->id, MigrationBase::MESSAGE_WARNING);
        continue;
      }

      // Filename validation
      $filename = NULL;
      if (!empty($row->filename)) {
        $filename = $row->filename;
      }
      else {
        $filename = ODataMigrationUtil::filenameFromURL($file->url);
      }
      if (empty($filename)) {
        ws_consumer_odata_log('Invalid filename for Decision id=' . $row->id . '. File URL: ' . $file->url, MigrationBase::MESSAGE_WARNING);
        continue;
      }

      // File language handling
      $language = NULL;
      if (empty($language)) {
        ws_consumer_odata_log('Missing language for file, Decision id=' . $row->id . '. File URL: ' . $file->url, MigrationBase::MESSAGE_WARNING);
        continue;
      }

      $row->files[] = $file->url;
      $row->filename[] = $filename;
      $row->files_language = $language;
    }
  }
}
