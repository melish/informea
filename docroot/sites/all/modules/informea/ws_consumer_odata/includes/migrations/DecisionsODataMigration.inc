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
    $this->addFieldMapping('title', 'title_orig');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'title_langs');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_decision_status', 'status');
    $this->addFieldMapping('field_decision_type', 'type');
    $this->addFieldMapping('field_decision_number', 'number');
    $this->addFieldMapping('field_sorting_date', 'published');
    $this->addFieldMapping('field_meeting', 'meetingId');
    $this->addFieldMapping('field_meeting_title_en', 'meetingTitle');
    $this->addFieldMapping('field_meeting_url', 'meetingUrl');
    $this->addFieldMapping('body', 'content');
    $this->addFieldMapping('body:language', 'content_langs');
    $this->addFieldMapping('body:summary', 'summary');
    $this->addFieldMapping('field_url', 'link');

    $this->addFieldMapping('field_files', 'files');
    $this->addFieldMapping('field_files:description', 'files');
    $this->addFieldMapping('field_files:language', 'files_language');
    $this->addFieldMapping('field_files:destination_dir')->defaultValue('public://decisions/' . $this->config->odata_name);
    $this->addFieldMapping('field_files:destination_file', 'filename');

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
      'field_files:preserve_files', 'field_files:file_replace',
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
