<?php

class MigrateDecisionsDocuments extends DynamicMigration {
  protected function generateMachineName() {
    return 'DecisionsDocuments';
  }

  public function __construct($arguments) {
    parent::__construct();
    $this->source_dir = '/Work/informea/resources/';

    $this->description = 'Import InforMEA decisions documents';
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array('type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Source PK',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $query = Database::getConnection('default', 'for_migration')
      ->select('ai_document', 'd')
      ->fields('d');

    $this->source = new DecisionsDocumentsMigrateSourceSQL($query);
    $this->destination = new MigrateDestinationFile();

    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('value', 'path');
    $this->addFieldMapping('destination_file', 'destination_file');
    $this->addFieldMapping('file_replace')->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('preserve_files')->defaultValue(FALSE);
    $this->addFieldMapping('source_dir')->defaultValue($this->source_dir);

    /* TODO: Add support in file_entity for these fields (comes from MEA)
    $this->addFieldMapping('file_original_url', 'url');
    $this->addFieldMapping('file_language', 'language');
    */

    $this->addUnmigratedDestinations(array(
      'timestamp', 'destination_dir'
    ));
    $this->addUnmigratedSources(array(
      'original_id', 'mime', 'id_decision', 'size',
      'is_indexed', 'rec_created', 'rec_author', 'rec_updated',
      'rec_updated_author', 'id', 'filename'
    ));
  }

  public function prepareRow($row) {
    if(!file_exists($this->source_dir . $row->path)) {
      return FALSE;
    }
    $dest = preg_replace('/\/?uploads\/decisions\//i', '', $row->path);
    $info = pathinfo($dest);
    $destination = 'decisions' . DIRECTORY_SEPARATOR . $info['dirname'] . DIRECTORY_SEPARATOR . $row->filename;
    $row->destination_file = $destination;
    return TRUE;
  }
}

class MigrateDecisions extends DynamicMigration {

  protected $meetings = array();
  protected $treaties = array();

  protected function generateMachineName() {
    return 'Decisions';
  }

  public function __construct($arguments) {
    parent::__construct();

    $this->dependencies = array('ThesaurusInforMEA');
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

    $this->dependencies = array('Treaties', 'Meetings', 'DecisionsDocuments');
    $this->source = new DecisionsMigrateSourceSQL($query);

    $op = MigrateDestinationNode::options('en', 'full_html');
    $this->destination = new MigrateDestinationNode('decision', $op);

    $this->addFieldMapping('title_field', 'short_title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'short_title');

    $this->addFieldMapping('field_original_id', 'original_id');
    $this->addFieldMapping('field_url', 'link');

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:summary', 'summary');
    $this->addFieldMapping('body:language')->defaultValue('en');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    $this->addFieldMapping('field_decision_type', 'type');
    $this->addFieldMapping('field_decision_type:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_decision_status', 'status');
    $this->addFieldMapping('field_decision_status:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_decision_number', 'number');

    $this->addFieldMapping('field_informea_tags', 'tags');
    $this->addFieldMapping('field_informea_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_informea_tags:create_term')->defaultValue(FALSE);

    $this->addFieldMapping('field_treaty', 'id_treaty');
    $this->addFieldMapping('field_decision_published', 'published');
    $this->addFieldMapping('field_decision_updated', 'updated');
    $this->addFieldMapping('field_meeting', 'id_meeting');

    $this->addFieldMapping('field_meeting_title_en', 'meeting_title');
    $this->addFieldMapping('field_meeting_url', 'meeting_url');
    $this->addFieldMapping('field_sorting_order', 'display_order');

    $this->addFieldMapping('created', 'rec_created');
    $this->addFieldMapping('changed', 'rec_updated');
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(FALSE);

    #$this->addFieldMapping('field_files', 'documents')->arguments(array('source_type' => 'fid'));


    $this->addUnmigratedDestinations(array(
      'field_decision_number:language',
      'field_decision_published:timezone', 'field_decision_published:rrule',
      'field_decision_updated:timezone', 'field_decision_updated:rrule',
      'field_decision_updated:to', 'field_meeting_title_en:language',
      'field_decision_published:to', 'field_decision_status:source_type',
      'field_decision_status:ignore_case', 'field_decision_type:source_type',
      'field_decision_type:ignore_case',
      'field_meeting_url:title', 'field_meeting_url:attributes', 'field_meeting_url:language',
      'field_original_id:language', 'field_url:title', 'field_url:attributes', 'field_url:language',

      // Migrated above
      'field_files',
      'field_files:file_class', 'field_files:language', 'field_files:destination_dir',
      'field_files:destination_file', 'field_files:file_replace', 'field_files:preserve_files',
      'field_files:source_dir', 'field_files:description', 'field_files:display',
      'field_last_update', 'field_last_update:timezone', 'field_last_update:rrule',
      'field_last_update:to',

      'field_informea_tags:ignore_case',
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'path',
    ));
    $this->addUnmigratedSources(array(
        'id_organization', 'long_title',
        'rec_author', 'rec_updated_author',
        'is_indexed'
      )
    );
  }

  public function prepareRow($row) {
    $row->language = 'en';
    if ($row->rec_created == '0000-00-00 00:00:00') {
      $row->rec_created = NULL;
    }
    if (!empty($row->rec_created)) {
      $row->rec_created = strtotime($row->rec_created);
    }
    if ($row->rec_updated == '0000-00-00 00:00:00') {
      $row->rec_updated = NULL;
    }
    $row->id_meeting = $this->meetings[$row->id_meeting];
    $row->id_treaty = $this->treaties[$row->id_treaty];
    $this->prepareDecisionDocuments($row);
    return TRUE;
  }

  public function prepare($entity, $row) {
    if(!empty($row->documents)) {
      $migration = Migration::currentMigration();
      $entity_type = $migration->getDestination()->getEntityType();
      $translation_handler = entity_translation_get_handler($entity_type, $entity);
      foreach(array_keys($row->documents) as $language) {
        $value = $row->documents[$language];
        $entity->field_files[$language] = $value;
        if($language != 'en') {
          $translation_handler->setTranslation(array(
            'translate' => 0, 'status' => 1, 'uid' => 1,
            'language' => $language,
            'source' => 'en',
          ));
        }
      }
    }
  }

  function prepareDecisionDocuments(&$row) {
    static $old_new = array();
    if(empty($old_new)) {
      $old_new = db_select('migrate_map_decisionsdocuments', 'm')
        ->fields('m', array('sourceid1', 'destid1'))
        ->execute()->fetchAllKeyed(0);
    }

    $rows = Database::getConnection('default', 'for_migration')
      ->select('ai_document', 'd')->where('id_decision=:id', array(':id' => $row->id))
      ->fields('d', array('id', 'language', 'filename'))->execute()->fetchAll();
    foreach($rows as $d) {
      $language = ($d->language == 'und') ? 'en' : $d->language;
      $row->documents[$language][] = array(
        'fid' => $old_new[$d->id],
        'display' => 1,
        'description' => ''
      );
    }
  }
}

class DecisionsDocumentsMigrateSourceSQL extends MigrateSourceSQL {

  public function fields() {
    $fields = parent::fields() + array(
        'destination_file' => 'Computed destination file',
      );
    return $fields;
  }
}

class DecisionsMigrateSourceSQL extends MigrateSourceSQL {

  public function fields() {
    $fields = parent::fields() + array(
        'documents' => 'Attached fids from DecisionDocuments migration',
        'tags' => 'Decision tags',
      );
    return $fields;
  }
}
