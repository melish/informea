<?php

class MigrateNationalReports extends DynamicMigration {

  protected $countries = array();
  protected $treaties = array();

  protected function generateMachineName() {
    return 'NationalReports';
  }

  public function __construct($arguments) {
    parent::__construct();

    $this->description = 'Import InforMEA national reports';
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
      ->select('ai_country_report', 'e')
      ->fields('e');

    $this->dependencies = array('Treaties');
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('national_report');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'title');

    $this->addFieldMapping('field_original_id', 'original_id');
    $this->addFieldMapping('field_country', 'id_country');
    $this->addFieldMapping('field_treaty', 'id_treaty');
    $this->addFieldMapping('field_report_submission_date', 'submission');
    $this->addFieldMapping('field_files', 'document_url');
    $this->addFieldMapping('field_document_url', 'document_url');
    $this->addFieldMapping('field_files:language')->defaultValue('en');
    $this->addFieldMapping('field_files:file_replace')->defaultValue(FILE_EXISTS_REPLACE);

    $this->addFieldMapping('created', 'rec_created');
    $this->addFieldMapping('changed', 'rec_updated');
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(FALSE);

    $this->addUnmigratedSources(array('id_event', 'is_indexed', 'rec_author', 'rec_updated_author'));
  }

  function prepareRow($row) {
    if ($row->end == '0000-00-00 00:00:00') {
      $row->end = NULL;
    }
    if ($row->rec_updated == '0000-00-00 00:00:00') {
      $row->rec_updated = NULL;
    }
    if ($row->rec_created == '0000-00-00 00:00:00') {
      $row->rec_created = NULL;
    }
    if (!empty($row->rec_created)) {
      $row->rec_created = strtotime($row->rec_created);
    }
    $row->id_country = wp_migration_get_country_id($this->countries[$row->id_country]);
    $row->id_treaty = $this->treaties[$row->id_treaty];
    return TRUE;
  }
}
