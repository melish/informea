<?php

class MigrateActionPlans extends Migration {

  protected $countries = array();
  protected $treaties = array();

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = 'Import InforMEA action plans';
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
      ->select('ai_country_plan', 'e')
      ->fields('e');

    $this->dependencies = array('Treaties');
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('action_plan');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'title');

    $this->addFieldMapping('field_original_id', 'original_id');
    $this->addFieldMapping('field_country', 'id_country');
    $this->addFieldMapping('field_treaty', 'id_treaty');
    $this->addFieldMapping('field_report_submission_date', 'submission');
    $this->addFieldMapping('field_files', 'document_url');
    $this->addFieldMapping('field_document_url', 'document_url');
    $this->addFieldMapping('field_document_url:title')->defaultValue('View on MEA website');
    $this->addFieldMapping('field_files:language')->defaultValue('en');
    $this->addFieldMapping('field_files:file_replace')->defaultValue(FILE_EXISTS_REPLACE);

    $this->addFieldMapping('field_action_plan_type', 'type');
    $this->addFieldMapping('field_action_plan_type:create_term')->defaultValue(TRUE);

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
      'id_event',
      'rec_author', 'rec_updated_author', 'is_indexed'
    ));
    $this->addUnmigratedDestinations(array(
      'body', 'body:summary', 'body:format', 'body:language',
      'field_action_plan_type:source_type', 'field_action_plan_type:ignore_case',
      'field_files:preserve_files', 'field_files:source_dir', 'field_files:description', 'field_files:display',
      'field_files:destination_dir', 'field_files:destination_file', 'field_files:file_class',

      'field_original_id:language',
      'field_document_url:attributes', 'field_document_url:language',
      'field_informea_tags', 'field_informea_tags:source_type', 'field_informea_tags:create_term',
      'field_informea_tags:ignore_case',
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'path',
    ));

  }

  function prepareRow($row) {
    if ($row->id_treaty != 5) {
      return FALSE;
    }
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

    // Check for files in ai_document
    $q = Database::getConnection('default', 'for_migration')
      ->select('ai_document')->fields(NULL, array('path'))
      ->condition('id_country_plan', $row->id);
    $urls = $q->execute()->fetchCol();
    if ($row->id_treaty == 5) {
      foreach($urls as &$url) {
        $url = 'http://demo.informea.org/' . $url;
      }
    }
    if (!empty($urls)) {
      $row->document_url = $urls;
    }
    $row->id_country = wp_migration_get_country_id($this->countries[$row->id_country]);
    $row->id_treaty = $this->treaties[$row->id_treaty];
    return TRUE;
  }
}
