<?php

class MigrateNationalReports extends Migration {

  protected $countries = array();
  protected $treaties = array();

  public function __construct($arguments) {
    parent::__construct($arguments);

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
    $this->addFieldMapping('field_sorting_date', 'submission');
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

    // Check for files in ai_document
    $urls = Database::getConnection('default', 'for_migration')
      ->select('ai_document')->fields(NULL, array('url'))
      ->condition('id_national_report', $row->id)
      ->execute()->fetchCol();
    if (!empty($urls)) {
      $row->document_url = $urls;
    }
    return TRUE;
  }
}

class MigrateReportingObligations extends Migration {

  protected $treaties = array();
  protected $treaties_articles = array();
  protected $treaties_paragraphs = array();
  protected $decisions = array();
  protected $decisions_paragraphs = array();

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = 'Import InforMEA reporting obligations database';
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
    } catch(Exception $e) {
      // Table might not be available yet
    }
    try {
      if(empty($this->treaties_articles)) {
        $query = db_select('migrate_map_treatiesarticles', 'm')->fields('m')->execute();
        $rows = $query->fetchAll();
        foreach($rows as $row) {
          $this->treaties_articles[$row->sourceid1] = $row->destid1;
        }
      }
    } catch(Exception $e) {
      // Table might not be available yet
    }
    try {
      if(empty($this->decisions)) {
        $query = db_select('migrate_map_decisions', 'm')->fields('m')->execute();
        $rows = $query->fetchAll();
        foreach($rows as $row) {
          $this->decisions[$row->sourceid1] = $row->destid1;
        }
      }
    } catch(Exception $e) {
      // Table might not be available yet
    }
    try {
      if(empty($this->decisions_paragraphs)) {
        $query = db_select('migrate_map_decisionsparagraphs', 'm')->fields('m')->execute();
        $rows = $query->fetchAll();
        foreach($rows as $row) {
          $this->decisions_paragraphs[$row->sourceid1] = $row->destid1;
        }
      }
    } catch(Exception $e) {
      // Table might not be available yet
    }

    try {
      if(empty($this->treaties_paragraphs)) {
        $query = db_select('migrate_map_treatiesparagraphs', 'm')->fields('m')->execute();
        $rows = $query->fetchAll();
        foreach($rows as $row) {
          $this->treaties_paragraphs[$row->sourceid1] = $row->destid1;
        }
      }
    } catch(Exception $e) {
      // Table might not be available yet
    }

    $query = Database::getConnection('default', 'for_migration')
      ->select('rod_obligation_format', 'a')
      ->fields('a', array('id', 'rec_updated', 'rec_created', 'title', 'instrument_id',
        'format_source_decision_id', 'cycle', 'document', 'weight'));

    $fields = array(
      'id' => t('Obligation PK'),
      'rec_updated' => t('Update date'),
      'rec_created' => t('Date of creation'),
      'title' => t('Obligation title'),
      'instrument_id' => t('Treaty'),
      'format_source_decision_id' => t('Decision from which obligation stems'),
      'cycle' => t('Reporting cycle'),
      'document' => t('Relevant decision document(s)'),
      'weight' => t('Sorting order in the front-end'),
      'decision_paragraph' => t('Decision paragraph from rod_obligation_format_paragraph'),
    );
    $this->dependencies = array('Treaties', 'Decisions', 'TreatiesArticles', 'TreatiesParagraphs', 'DecisionsParagraphs');
    $this->source = new MigrateSourceSQL($query, $fields);
    $this->destination = new MigrateDestinationNode('reporting_obligation_cycle');

    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');

    $this->addFieldMapping('changed', 'rec_updated');
    $this->addFieldMapping('created', 'rec_created');

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'title');

    $this->addFieldMapping('field_treaty', 'instrument_id');
    $this->addFieldMapping('field_decision', 'format_source_decision_id');
    $this->addFieldMapping('field_decision_paragraph', 'decision_paragraph');
    $this->addFieldMapping('field_reporting_frequency', 'cycle');
    $this->addFieldMapping('field_official_order', 'weight');
    $this->addFieldMapping('field_files', 'document');
    $this->addFieldMapping('field_files:file_replace')->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_files:preserve_files')->defaultValue(FALSE);
    $this->addFieldMapping('field_files:source_dir')->defaultValue('/Users/cristiroma/Work/informea/resources/wp-content/uploads');

    $this->addUnmigratedSources(array('weight'));
    $this->addUnmigratedDestinations(array('path', 'comment', 'field_files:display',
      'field_files:description', 'revision', 'log', 'tnid', 'translate',
      'revision_uid', 'is_new', 'body:language', 'field_official_order:language',
      'field_files:file_class', 'field_files:language',
      'body', 'body:format', 'body:summary', 'field_files:destination_dir', 'field_files:destination_file'));
  }

  function prepareRow($row) {
    $row->instrument_id = $this->treaties[$row->instrument_id];
    $row->format_source_decision_id = $this->decisions[$row->format_source_decision_id];

    // instrument_article_id
    $query = Database::getConnection('default', 'for_migration')
      ->select('rod_obligation', 'a')
      ->fields('a')->where('id=:id', array('id' =>$row->obligation_id));
    $ob = $query->execute()->fetchObject();
    $row->instrument_article_id = $this->treaties_articles[$ob->instrument_article_id];

    // aidecisionparagraph_id
    $query = Database::getConnection('default', 'for_migration')
      ->select('rod_obligation_format_paragraph', 'a')
      ->fields('a')->where('reportingobligationformat_id=:id', array('id' =>$row->id));
    $ob1 = $query->execute()->fetchObject();
    $row->field_decision_paragraph = $this->decisions_paragraphs[$ob1->id];
    return TRUE;
  }

  /**
   * After import attach the ROD data to treaty entity.
   */
  public function postImport() {
    parent::postImport();
    // Attach ROD information to treaty
    $query = Database::getConnection('default', 'for_migration')
      ->select('rod_obligation', 'a')
      ->fields('a', array('id', 'instrument_id', 'instrument_article_id'));
    $old_treaties = $query->execute()->fetchAll();
    foreach ($old_treaties as $old) {
      $id_treaty_old = $old->instrument_id;
      $id_treaty = $this->treaties[$id_treaty_old];

      // Treaty articles
      $id_article_old = $old->instrument_article_id;
      $id_article = $this->treaties_articles[$id_article_old];
      $w = entity_metadata_wrapper('node', $id_treaty);
      $w->field_treaty_article->set(array($id_article));

      // Treaty articles paragraphs
      $qp = Database::getConnection('default', 'for_migration')
        ->select('rod_obligation_paragraph', 'a')
        ->fields('a', array('reportingobligation_id', 'aitreatyarticleparagraph_id'))
        ->where('a.reportingobligation_id=:id', array('id' => $old->id));
      $old_paragraphs = $qp->execute()->fetchAll();
      $paragraphs = array();
      foreach ($old_paragraphs as $old_paragraph) {
        if (!empty($old_paragraph->aitreatyarticleparagraph_id)) {
          $id_paragraph_old = $old_paragraph->aitreatyarticleparagraph_id;
          if ($id_paragraph = $this->treaties_paragraphs[$id_paragraph_old]) {
            $paragraphs[] = $id_paragraph;
          }
        }
      }
      if (!empty($paragraphs)) {
        $w->field_treaty_article_paragraph->set($paragraphs);
      }
      $w->save();
    }
  }
}
