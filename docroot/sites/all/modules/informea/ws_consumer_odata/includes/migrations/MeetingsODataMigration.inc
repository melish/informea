<?php

/**
 * Class ContactsODataMigration migrate OData contacts
 */
class MeetingsODataMigration extends AbstractODataMigration {

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
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_MEETINGS, $this->config->odata_name);
    $this->source      = new MeetingsMigrateSourceList(
      new ODataMigrateList($this->config),
      new MeetingsODataMigrateItem($this->config)
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
      ODataConsumerConfig::$DRUPAL_TYPE_MEETINGS,
      array('text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
//    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_url', 'url');
    $this->addFieldMapping('event_calendar_date', 'start');
    $this->addFieldMapping('event_calendar_date:to', 'end');
    $this->addFieldMapping('field_event_repetition', 'repetition');
    $this->addFieldMapping('field_event_kind', 'kind');
    $this->addFieldMapping('field_event_type', 'type');
    $this->addFieldMapping('field_event_access', 'access');
    $this->addFieldMapping('field_event_calendar_status', 'status');
    $this->addFieldMapping('field_event_images', 'imageUrl');
    $this->addFieldMapping('field_location', 'location');
    $this->addFieldMapping('field_city', 'city');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_latitude', 'latitude');
    $this->addFieldMapping('field_longitude', 'longitude');

    $this->addFieldMapping('field_event_images:source_dir')
      ->defaultValue('http://www.basel.int');

    $this->addFieldMapping('field_event_calendar_status:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_calendar_status:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_access:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_access:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_kind:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_kind:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_repetition:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_repetition:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_type:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_type:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('changed', 'updated');

    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue(LANGUAGE_NONE);
    $this->addFieldMapping('field_city:language')->defaultValue(LANGUAGE_NONE);
    $this->addFieldMapping('field_location:language')->defaultValue(LANGUAGE_NONE);
    $this->addFieldMapping('field_event_images:language')->defaultValue(LANGUAGE_NONE);

    $this->addUnmigratedDestinations(array(
      'created', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'body', 'body:summary', 'body:format', 'path',
      'body:language', 'field_event_calendar_status:source_type',
      'event_calendar_date:timezone', 'event_calendar_date:rrule',
      'field_abbreviation', 'field_event_access:source_type',
      'event_calendar_status', 'event_calendar_status:ignore_case',
      'event_calendar_status:create_term', 'event_calendar_status:source_type',
      'field_event_images:file_replace', 'field_event_images:destination_file',
      'field_event_images:destination_dir', 'field_event_images:preserve_files',
      'field_event_images:file_class', 'field_informea_tags:ignore_case',
      'field_event_images:title', 'field_event_images:alt', 'field_event_images:urlencode',
      'field_event_repetition:source_type', 'field_event_kind:source_type',
      'field_event_type:source_type', 'field_informea_tags',
      'field_informea_tags:source_type', 'field_informea_tags:create_term',
      'field_tags', 'field_tags:source_type', 'field_tags:create_term',
      'field_tags:ignore_case', 'field_url:title', 'field_url:attributes',
      'field_url:language', 'title_field:language',
    ));
  }

  /**
   * Add some Contacts specific preparations.
   *
   * {@inheritdoc}
   */
  function prepareRow($row) {
    parent::prepareRow($row);

//    var_dump($row);
//    die();

    if (!empty($row->start)) {
      $row->start = $this->fixDateValue($row->start);
    }
    if (!empty($row->end)) {
      $row->end = $this->fixDateValue($row->end);
    }

    $row->treaty = $this->getTreatyByODataIdentifier($row->treaty)->nid;
  }

}
