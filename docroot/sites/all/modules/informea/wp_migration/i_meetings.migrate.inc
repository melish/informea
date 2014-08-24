<?php

class MigrateMeetings extends DynamicMigration {

  protected $countries = array();
  protected $treaties = array();

  protected function generateMachineName() {
    return 'Meetings';
  }

  public function __construct($arguments) {
    parent::__construct();

    $this->description = 'Import InforMEA meetings';
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array('type' => 'int',
          'length' => 2,
          'not null' => TRUE,
          'description' => 'Source PK',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    if(empty($this->countries)) {
      $query = Database::getConnection('default', 'for_migration')
        ->select('ai_country', 'c')->fields('c')->execute();
      $rows = $query->fetchAll();
      foreach($rows as $row) {
        $this->countries[$row->id] = $row->code2l;
      }
    }
    try {
      if(empty($this->treaties)) {
        $query = db_select('migrate_map_treaties', 'm')->fields('m')->execute();
        $rows = $query->fetchAll();
        foreach($rows as $row) {
          $this->treaties[$row->sourceid1] = $row->destid1;
        }
      }
    } catch(Exception $e) {
      // Table might not be available yet
    }

    $query = Database::getConnection('default', 'for_migration')
      ->select('ai_event', 'e')
      ->fields('e');

    $this->dependencies = array('Treaties');
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('event_calendar');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'title');

    $this->addFieldMapping('field_abbreviation', 'abbreviation');
    $this->addFieldMapping('body', 'description');
    $this->addFieldMapping('body:language')->defaultValue('en');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    $this->addFieldMapping('field_url', 'event_url');
    $this->addFieldMapping('field_url:title')->defaultValue('View meeting website');
    $this->addFieldMapping('field_url:language')->defaultValue('en');

    $this->addFieldMapping('event_calendar_date', 'start');
    $this->addFieldMapping('event_calendar_date:to', 'end');

    $this->addFieldMapping('field_event_repetition', 'repetition');
    $this->addFieldMapping('field_event_repetition:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_repetition:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_event_kind', 'kind');
    $this->addFieldMapping('field_event_kind:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_kind:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_event_type', 'type');
    $this->addFieldMapping('field_event_type:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_type:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_event_access', 'access');
    $this->addFieldMapping('field_event_access:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_access:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('event_calendar_status', 'status');
    $this->addFieldMapping('event_calendar_status:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('event_calendar_status:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_event_images', 'image');
    $this->addFieldMapping('field_event_images:language')->defaultValue('en');
    $this->addFieldMapping('field_event_images:file_replace')->defaultValue(TRUE);

    #$this->addFieldMapping('', 'image_copyright');

    $this->addFieldMapping('field_location', 'location');
    $this->addFieldMapping('field_location:language')->defaultValue('en');

    $this->addFieldMapping('field_city', 'city');
    $this->addFieldMapping('field_city:language')->defaultValue('en');
    $this->addFieldMapping('field_country', 'id_country');
    $this->addFieldMapping('field_latitude', 'latitude');
    $this->addFieldMapping('field_longitude', 'longitude');

    $this->addFieldMapping('field_original_id', 'original_id');
    $this->addFieldMapping('field_treaty', 'id_treaty');

    $this->addFieldMapping('created', 'rec_created');
    $this->addFieldMapping('changed', 'rec_updated');
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(FALSE);

    $this->addUnmigratedSources(array(
      'id_organization', 'id_event_previous', 'id_person', 'use_informea', 'image_copyright',
      'rec_author', 'rec_updated_author', 'is_indexed'
    ));
    $this->addUnmigratedDestinations(array(
      'field_informea_tags', 'field_informea_tags:source_type', 'field_informea_tags:create_term',
      'field_informea_tags:ignore_case',
      'field_tags', 'field_tags:source_type', 'field_tags:create_term', 'field_tags:ignore_case',
      'event_calendar_date:timezone', 'event_calendar_date:rrule', 'event_calendar_status:source_type',
      'field_abbreviation:language',
      'field_event_access:source_type',
      'field_event_images:file_class', 'field_event_images:destination_dir', 'field_event_images:destination_file',
      'field_event_images:preserve_files', 'field_event_images:source_dir', 'field_event_images:alt', 'field_event_images:title',
      'field_event_kind:source_type',
      'field_event_repetition:source_type',
      'field_event_type:source_type',
      'field_original_id:language',
      'field_url:attributes',
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary', 'path',
    ));
  }

  function prepareRow($row) {
    if ($row->end == '0000-00-00 00:00:00') {
      $row->end = NULL;
    }
    if ($row->rec_created == '0000-00-00 00:00:00') {
      $row->rec_created = NULL;
    }
    if ($row->rec_updated == '0000-00-00 00:00:00') {
      $row->rec_updated = NULL;
    }
    if (!empty($row->rec_created)) {
      $row->rec_created = strtotime($row->rec_created);
    }
    $row->id_country = $this->countries[$row->id_country];
    $row->id_treaty = $this->treaties[$row->id_treaty];
    return TRUE;
  }
}