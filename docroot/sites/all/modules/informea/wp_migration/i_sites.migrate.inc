<?php

class MigrateSites extends DynamicMigration {

  protected $countries = array();
  protected $treaties = array();

  protected function generateMachineName() {
    return 'Sites';
  }

  public function __construct($arguments) {
    parent::__construct();

    $this->description = 'Import InforMEA sites';
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
      ->select('ai_country_site', 'e')
      ->fields('e');

    $this->dependencies = array('Treaties');
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('geographical_site');

    $this->addFieldMapping('title_field', 'name');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'name');

    $this->addFieldMapping('field_original_id', 'original_id');
    $this->addFieldMapping('field_country', 'id_country');
    $this->addFieldMapping('field_treaty', 'id_treaty');
    $this->addFieldMapping('field_url', 'url');
    $this->addFieldMapping('field_url:title')->defaultValue('Visit site web page');
    $this->addFieldMapping('field_url:language')->defaultValue('en');
    $this->addFieldMapping('field_latitude', 'latitude');
    $this->addFieldMapping('field_longitude', 'longitude');

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
      'rec_author', 'rec_updated_author'
    ));
    $this->addUnmigratedDestinations(array(
      'body', 'body:format', 'body:language', 'field_original_id:language',
      'field_url:attributes',
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary',
    ));

  }

  function prepareRow($row) {
    if ($row->end == '0000-00-00 00:00:00') {
      $row->end = NULL;
    }
    if ($row->rec_created == '0000-00-00 00:00:00') {
      $row->rec_created = NULL;
    }
    if (!empty($row->rec_created)) {
      $row->rec_created = strtotime($row->rec_created);
    }
    if ($row->rec_updated == '0000-00-00 00:00:00') {
      $row->rec_updated = NULL;
    }
    $row->id_country = $this->countries[$row->id_country];
    $row->id_treaty = $this->treaties[$row->id_treaty];
    return TRUE;
  }
}