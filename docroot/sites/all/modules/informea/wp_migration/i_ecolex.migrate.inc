<?php

class MigrateEcolexManualCourtDecisions extends DrupalNode7Migration {

  public function __construct($arguments) {
    $arguments['description'] = 'Import court decisions added manually by Anni into ecolex.edw.ro';

    $this->sourceFields['ecolex_tags'] = 'Term names';
    $this->sourceFields['jurisdiction'] = 'Jurisdiction term names';
    $this->sourceFields['type_of_text'] = 'Type of text term names';
    $this->sourceFields['informea_tags'] = 'InforMEA glossary term names';
    $this->sourceFields['keywords'] = 'ECOLEX keywords term names';
    $this->sourceFields['territorial_subdivision'] = 'Territorial subdivisions term names';
    $this->sourceFields['country'] = 'Country nid';
    $this->sourceFields['files'] = 'File URLS';

    parent::__construct($arguments);
    $this->description = $arguments['description'];
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array('type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Source node ID',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('court_decisions');

    $this->addSimpleMappings(array(
      'field_city', 'field_city:language',
      'field_number_of_pages',
      'field_court_decision_id_number', 'field_court_decision_id_number:language',
      'field_url', 'field_url:title', 'field_url:attributes', 'field_url:language',
      'title_field', 'title_field:language',
      'field_court_name', 'field_court_name:language',
      'field_justices', 'field_justices:language',
      'field_reference_number', 'field_reference_number:language',
    ));

    $this->addFieldMapping('uid', NULL, FALSE)->defaultValue(2);
    $this->addFieldMapping('field_sorting_date', 'field_date_of_text');
    $this->addFieldMapping('field_sorting_date:timezone')->defaultValue('UTC');

    $this->addFieldMapping('field_abstract', 'field_abstract');
    $this->addFieldMapping('field_abstract:format', 'field_abstract:format');
    $this->addFieldMapping('field_abstract:language')->defaultValue('en');//, 'field_abstract:language');

    $this->addFieldMapping('field_ecolex_tags', 'ecolex_tags');
    $this->addFieldMapping('field_ecolex_tags:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_ecolex_tags:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_jurisdiction', 'jurisdiction');
    $this->addFieldMapping('field_jurisdiction:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_jurisdiction:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_informea_tags', 'informea_tags');
    $this->addFieldMapping('field_informea_tags:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_informea_tags:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_keywords', 'keywords');
    $this->addFieldMapping('field_keywords:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_keywords:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_territorial_subdivision', 'territorial_subdivision');
    $this->addFieldMapping('field_territorial_subdivision:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_territorial_subdivision:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_country', 'country');

    $this->addFieldMapping('field_type_of_text', 'type_of_text');
    $this->addFieldMapping('field_type_of_text:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_type_of_text:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_data_source')->defaultValue('InforMEA');
    $this->addFieldMapping('field_data_source:create_term')->defaultValue(FALSE);
    $this->addFieldMapping('field_data_source:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('revision', NULL, FALSE)->defaultValue(FALSE);
    $this->addFieldMapping('log', NULL, FALSE)->defaultValue(NULL);

    $this->addFieldMapping('field_files', 'files');
    //@todo: field_source_language, file description

    $this->addUnmigratedSources(array(
      'field_files',
      'uid', 'revision', 'log', 'revision_uid',
      'field_date_of_text:language',
      'field_ecolex_tags', 'field_ecolex_tags:language',
      'field_jurisdiction', 'field_jurisdiction:language',
      'field_type_of_text', 'field_type_of_text:language',
      'field_informea_tags', 'field_informea_tags:language',
      'field_country:language',
      'field_keywords', 'field_keywords:language',
      'field_territorial_subdivision',
      'field_country',
      'field_number_of_pages:language',
    ));
    $this->addUnmigratedDestinations(array(
      'field_sorting_date:rrule', 'field_sorting_date:to',
      'field_alternative_record_id', 'field_alternative_record_id:language',
      'field_ecolex_tags:source_type',

      'field_court_decision_subdivision', 'field_court_decision_subdivision:language',
      'field_date_of_entry', 'field_date_of_entry:timezone', 'field_date_of_entry:rrule', 'field_date_of_entry:to',
      'field_date_of_modification', 'field_date_of_modification:timezone', 'field_date_of_modification:rrule', 'field_date_of_modification:to',
      'field_ecolex_url', 'field_ecolex_url:title', 'field_ecolex_url:attributes', 'field_ecolex_url:language',
      'field_faolex_url', 'field_faolex_url:title', 'field_faolex_url:attributes', 'field_faolex_url:language',
      'field_informea_tags:source_type',
      'field_internet_reference_url', 'field_internet_reference_url:title', 'field_internet_reference_url:attributes', 'field_internet_reference_url:language',
      'field_isis_number', 'field_isis_number:language',
      'field_jurisdiction:source_type',
      'field_keywords:source_type',
      'field_original_id', 'field_original_id:language',
      'field_reference_to_legislation',
      'field_related_url', 'field_related_url:title', 'field_related_url:attributes', 'field_related_url:language',
      'field_territorial_subdivision:source_type', 'field_type_of_text:source_type', 'field_data_source:source_type',
      'field_ecolex_decision_status', 'field_ecolex_decision_status:source_type', 'field_ecolex_decision_status:create_term', 'field_ecolex_decision_status:ignore_case',
    ));

    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:summary', 'body:summary');
    $this->removeFieldMapping('body:format', 'body:format');
    $this->removeFieldMapping('pathauto', 'pathauto');
  }

  function prepareRow($row) {
    parent::prepareRow($row);
    //@todo:
    $row->country = array();
    if (!empty($row->field_country)) {
      $c = Database::getConnection('default', 'ecolex_edw_ro')
        ->select('node', 'n')->fields('n', array('title'))
        ->condition('nid', $row->field_country)
        ->execute()->fetchColumn();
      $c1 = db_select('node', 'n')->fields('n', array('nid'))
        ->condition('title', $c)
        ->execute()->fetchColumn();
      $row->country = array($c1);
    }

    $row->ecolex_tags = array();
    if (!empty($row->field_ecolex_tags)) {
      $c = Database::getConnection('default', 'ecolex_edw_ro')
        ->select('taxonomy_term_data', 't')->fields('t', array('name'))
        ->condition('tid', $row->field_ecolex_tags, 'in')
        ->execute()->fetchCol();
      $row->ecolex_tags = $c;
    }

    $row->type_of_text = array();
    if (!empty($row->field_type_of_text)) {
      $c = Database::getConnection('default', 'ecolex_edw_ro')
        ->select('taxonomy_term_data', 't')->fields('t', array('name'))
        ->condition('tid', $row->field_type_of_text, 'in')
        ->execute()->fetchField();
      $row->type_of_text = $c;
    }

    $row->jurisdiction = array();
    if (!empty($row->field_jurisdiction)) {
      $c = Database::getConnection('default', 'ecolex_edw_ro')
        ->select('taxonomy_term_data', 't')->fields('t', array('name'))
        ->condition('tid', $row->field_jurisdiction, 'in')
        ->execute()->fetchField();
      $row->jurisdiction = $c;
    }

    $row->informea_tags = array();
    if (!empty($row->field_informea_tags)) {
      $c = Database::getConnection('default', 'ecolex_edw_ro')
        ->select('taxonomy_term_data', 't')->fields('t', array('name'))
        ->condition('tid', $row->field_informea_tags, 'in')
        ->execute()->fetchCol();
      $row->informea_tags = $c;
    }

    $row->keywords = array();
    if (!empty($row->field_keywords)) {
      $c = Database::getConnection('default', 'ecolex_edw_ro')
        ->select('taxonomy_term_data', 't')->fields('t', array('name'))
        ->condition('tid', $row->field_keywords, 'in')
        ->execute()->fetchCol();
      $row->keywords = $c;
    }

    $row->files = array();
    if (!empty($row->field_files)) {
      $files = array();
      $field_q = Database::getConnection('default', 'ecolex_edw_ro')
        ->select('file_managed', 'f')->fields('f', array('filename'))
        ->condition('fid', $row->field_files, 'in');
      foreach($field_q->execute() as $t) {
        $files[] = 'http://ecolex.edw.ro/sites/default/files/field_files/' . $t->filename;
      }
      $row->files = $files;
    }
  }

  /**
   * Query for basic node fields from Drupal 7.
   *
   * @return QueryConditionInterface
   */
  protected function query() {
    $query = parent::query();
    $query->condition('n.uid', 2); // anni.lukacs
    return $query;
  }
}

class MigrateInforMEAEcolexLegislation extends Migration {

  protected $countries = array();

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = 'Import manually added legislation from InforMEA back-end';
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

    $query = Database::getConnection('default', 'for_migration')
      ->select('ecolex_legislation', 'e')
      ->fields('e');

    $this->dependencies = array('Treaties');
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('legislation');

    if(empty($this->countries)) {
      $query = Database::getConnection('default', 'for_migration')
        ->select('ai_country', 'c')->fields('c')->execute();
      $rows = $query->fetchAll();
      foreach($rows as $row) {
        $this->countries[$row->id] = $row->code2l;
      }
    }

    $this->addFieldMapping('field_country', 'country_id');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'title');

    $this->addFieldMapping('field_data_source')->defaultValue('InforMEA');
    $this->addFieldMapping('field_data_source:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_data_source:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_sorting_date', 'date');
    $this->addFieldMapping('field_avaiable_web_site', 'source');
    $this->addFieldMapping('field_internet_reference_url', 'website');
    $this->addFieldMapping('field_url', 'link');
    $this->addFieldMapping('body', 'abstract');
    $this->addFieldMapping('body:language')->defaultValue('en');

    $this->addFieldMapping('created', 'rec_created');
    $this->addFieldMapping('changed', 'rec_updated');
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('status')->defaultValue(0);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(FALSE);
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
    $row->country_id = wp_migration_get_country_id($this->countries[$row->country_id]);
    return TRUE;
  }

  function prepare($node, $row) {
    if (!empty($row->link_fr)) {
      $node->field_url['fr'][0] = array('url' => $row->link_fr);
    }
    if (!empty($row->link_es)) {
      $node->field_url['es'][0] = array('url' => $row->link_es);
    }
    if (!empty($row->link_cn)) {
      $node->field_url['zh-hans'][0] = array('url' => $row->link_cn);
    }
    if (!empty($row->link_ru)) {
      $node->field_url['ru'][0] = array('url' => $row->link_ru);
    }
    if (!empty($row->link_ar)) {
      $node->field_url['ar'][0] = array('url' => $row->link_ar);
    }
  }

  function complete($node, $row) {
    $translations = array();
    if (!empty($row->link_fr)) {
      $translations[] = 'fr';
    }
    if (!empty($row->link_es)) {
      $translations[] = 'es';
    }
    if (!empty($row->link_cn)) {
      $translations[] = 'zh-hans';
    }
    if (!empty($row->link_ru)) {
      $translations[] = 'ru';
    }
    if (!empty($row->link_ar)) {
      $translations[] = 'ar';
    }
    // Need to load the node to make sure translations are loaded
    $node = node_load($node->nid);
    $handler = entity_translation_get_handler('node', $node);
    $handler->initTranslations();
    // Preserve other translations (non-migrated)
    $node->translations = $handler->getTranslations();
    foreach ($translations as $language) {
      if ($language != $row->language) {
        $translation = array(
          'translate' => 0,
          'uid' => 1,
          'status' => 1,
          'language' => $language,
          'source' => 'en',
        );
        $handler->setTranslation($translation);
      }
    }
    $handler->saveTranslations();
  }
}

class MigrateInforMEAEcolexCourtDecisions extends Migration {

  protected $countries = array();

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = 'Import manually added court decisions from InforMEA back-end';
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

    $query = Database::getConnection('default', 'for_migration')
      ->select('ecolex_court_decision', 'e')
      ->fields('e');

    $this->dependencies = array('Treaties');
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('court_decisions', array('format' => 'plaint_text'));

    if(empty($this->countries)) {
      $query = Database::getConnection('default', 'for_migration')
        ->select('ai_country', 'c')->fields('c')->execute();
      $rows = $query->fetchAll();
      foreach($rows as $row) {
        $this->countries[$row->id] = $row->code2l;
      }
    }

    $this->addFieldMapping('field_country', 'country_id');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'title');

    $this->addFieldMapping('field_data_source')->defaultValue('InforMEA');
    $this->addFieldMapping('field_data_source:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_data_source:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_sorting_date', 'date');
    $this->addFieldMapping('field_court_name', 'court_name');
    $this->addFieldMapping('field_city', 'court_seat');
    $this->addFieldMapping('field_court_decision_subdivision', 'subdivision');
    $this->addFieldMapping('field_jurisdiction', 'court_jurisdiction');
    //@todo: instance
    $this->addFieldMapping('field_justices', 'justices')->callbacks(function($v) {
      return explode(',', $v);
    });
    //@todo: reference
    $this->addFieldMapping('field_url', 'link');
    $this->addFieldMapping('field_number_of_pages', 'pages_no');
    //@todo: appendices
    $this->addFieldMapping('field_abstract', 'abstract');
    $this->addFieldMapping('field_abstract:language')->defaultValue('en');

    $this->addFieldMapping('created', 'rec_created');
    $this->addFieldMapping('changed', 'rec_updated');
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('status')->defaultValue(0);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(FALSE);
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
    $row->country_id = wp_migration_get_country_id($this->countries[$row->country_id]);
    return TRUE;
  }

  function prepare($node, $row) {
    if (!empty($row->abstract_other)) {
      $node->field_abstract['zh-hans'][0] = array('value' => $row->abstract_other);
    }
  }

  function complete($node, $row) {
    $translations = array();
    if (!empty($row->abstract_other)) {
      $translations[] = 'zh-hans';
    }
    // Need to load the node to make sure translations are loaded
    $node = node_load($node->nid);
    $handler = entity_translation_get_handler('node', $node);
    $handler->initTranslations();
    // Preserve other translations (non-migrated)
    $node->translations = $handler->getTranslations();
    foreach ($translations as $language) {
      if ($language != $row->language) {
        $translation = array(
          'translate' => 0,
          'uid' => 1,
          'status' => 1,
          'language' => $language,
          'source' => 'en',
        );
        $handler->setTranslation($translation);
      }
    }
    $handler->saveTranslations();
  }
}
