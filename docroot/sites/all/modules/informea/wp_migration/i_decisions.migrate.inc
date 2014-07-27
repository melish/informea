<?php

class MigrateDecisions extends DynamicMigration {

  protected $meetings = array();
  protected $treaties = array();

  protected function generateMachineName() {
    return 'Decisions';
  }

  public function __construct($arguments) {
    parent::__construct();

    $this->description = 'Import InforMEA decisions and documents';
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

    try {
      if(empty($this->treaties)) {
        $query = db_select('migrate_map_treaties', 'm')->fields('m')->execute();
        $rows = $query->fetchAll();
        foreach($rows as $row) {
          $this->treaties[$row->sourceid1] = $row->destid1;
        }
      }

      if(empty($this->meetings)) {
        $query = db_select('migrate_map_meetings', 'm')->fields('m')->execute();
        $rows = $query->fetchAll();
        foreach($rows as $row) {
          $this->meetings[$row->sourceid1] = $row->destid1;
        }
      }
    } catch(Exception $e) {
      // Table might not be available yet
    }

    $query = Database::getConnection('default', 'for_migration')
      ->select('ai_decision', 'd')
      ->fields('d');

    $this->dependencies = array('Treaties', 'Meetings');
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('decision');

    $this->addFieldMapping('field_original_id', 'original_id');
    $this->addFieldMapping('field_url', 'link');

    $this->addFieldMapping('title_field', 'short_title');
    $this->addFieldMapping('title', 'short_title');

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:summary', 'summary');
    $this->addFieldMapping('body:language')->defaultValue('en');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    $this->addFieldMapping('field_decision_type', 'type');
    $this->addFieldMapping('field_decision_type:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_decision_status', 'status');
    $this->addFieldMapping('field_decision_status:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_decision_number', 'number');

    $this->addFieldMapping('field_treaty', 'id_treaty');
    $this->addFieldMapping('field_decision_published', 'published');
    $this->addFieldMapping('field_decision_updated', 'updated');
    $this->addFieldMapping('field_meeting', 'id_meeting');

    $this->addFieldMapping('field_meeting_title_en', 'meeting_title');
    $this->addFieldMapping('field_meeting_url', 'meeting_url');
    $this->addFieldMapping('field_sorting_order', 'display_order');

    $this->addFieldMapping('created', 'rec_created');
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('uid')->defaultValue(1);

    //TODO: Migrate files
    //$this->addFieldMapping('field_files', '');
  }

  function prepareRow($row) {
    if ($row->rec_created == '0000-00-00 00:00:00') {
      $row->rec_created = NULL;
    }
    if (!empty($row->rec_created)) {
      $row->rec_created = strtotime($row->rec_created);
    }
    $row->id_meeting = $this->meetings[$row->id_meeting];
    $row->id_treaty = $this->treaties[$row->id_treaty];
    return TRUE;
  }
}