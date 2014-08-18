<?php

class MigrateTreaties extends DynamicMigration {

  public function __construct($arguments) {
    parent::__construct();

    $this->description = 'Import InforMEA treaties';
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
      ->select('ai_treaty', 't')
      ->fields('t');


    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationNode('treaty');

    $this->addFieldMapping('title_field', 'short_title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'short_title');

    $this->addFieldMapping('field_treaty_long_name', 'long_title');
    $this->addFieldMapping('body', 'abstract');
    $this->addFieldMapping('body:language')->defaultValue('en');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('field_treaty_primary', 'primary');
    $this->addFieldMapping('field_enter_into_force', 'start');

    $this->addFieldMapping('field_url_treaty_text', 'url_treaty_text');
    $this->addFieldMapping('field_url_treaty_text:language')->defaultValue('en');
    $this->addFieldMapping('field_url_treaty_text:title')->defaultValue('View on MEA website');

    $this->addFieldMapping('field_url_treaty_website', 'url');
    $this->addFieldMapping('field_url_treaty_website:language')->defaultValue('en');
    $this->addFieldMapping('field_url_treaty_website:title')->defaultValue('Visit website');

    $this->addFieldMapping('field_url_treaty_parties', 'url_parties');
    $this->addFieldMapping('field_url_treaty_parties:language')->defaultValue('en');

    $this->addFieldMapping('field_number_of_parties', 'number_of_parties');
    $this->addFieldMapping('field_url_treaty_parties:title')->defaultValue('View on MEA website');

    $this->addFieldMapping('field_sorting_order', 'order');
    $this->addFieldMapping('field_treaty_is_protocol', 'is_protocol');
    $this->addFieldMapping('field_odata_identifier', 'odata_name');
    $this->addFieldMapping('field_ratification_xml_url', 'ratification_xml_url');

    $this->addFieldMapping('field_logo', 'logo_medium');
    $this->addFieldMapping('field_logo:file_replace')->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_logo:source_dir')->defaultValue('/Work/informea/www.old/wp-content/uploads');

    $this->addFieldMapping('created', 'rec_created');
    $this->addFieldMapping('changed', 'rec_updated');
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('status', 'enabled')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(FALSE);

    $this->addUnmigratedSources(array(
      'id_organization', 'id_parent', 'short_title_alternative', 'year',
      'regional', 'use_informea', 'rec_author', 'rec_updated_author', 'is_indexed'
    ));
    $this->addUnmigratedDestinations(array(
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary',
      'field_enter_into_force:timezone', 'field_enter_into_force:rrule', 'field_enter_into_force:to',
      'field_logo:file_class',
      'field_logo:destination_dir', 'field_logo:destination_file', 'field_logo:preserve_files', 'field_logo:alt', 'field_logo:title',
      'field_odata_identifier:language',
      'field_ratification_xml_url:title', 'field_ratification_xml_url:attributes', 'field_ratification_xml_url:language',
      'field_treaty_long_name:language', 'field_url_treaty_website:attributes',
      'field_treaty_year:timezone', 'field_treaty_year:rrule', 'field_treaty_year:to',
      'field_url_treaty_parties:attributes', 'field_url_treaty_text:attributes',
      'field_region:source_type',
      'field_region:ignore_case'
    ));
  }

  protected function generateMachineName() {
    return 'Treaties';
  }

  function prepareRow($row) {
    if ($row->rec_created == '0000-00-00 00:00:00') {
      $row->rec_created = NULL;
    }
    if ($row->rec_updated == '0000-00-00 00:00:00') {
      $row->rec_updated = NULL;
    }
    if (!empty($row->rec_created)) {
      $row->rec_created = strtotime($row->rec_created);
    }
  }

  function complete($entity, $row) {
      $args = array(
        'source' => 'node/' . $entity->nid,
        'alias' => 'treaties/' . $row->odata_name,
        'language' => 'en',
      );
      path_save($args);
  }
}



class MigrateTreatiesArticles extends DynamicMigration {

  public function __construct($arguments) {
    parent::__construct();

    $this->dependencies = array('Treaties');
    $this->description = 'Import articles of treaties';
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
      ->select('ai_treaty_article', 'ta')
      ->fields('ta');


    $this->source = new MigrateSourceSQL($query);

    $opt = MigrateDestinationNode::options('en', 'full_html');
    $this->destination = new MigrateDestinationNode('treaty_article', $opt);

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title', 'title');

    $this->addFieldMapping('body', 'content');

    $this->addFieldMapping('field_treaty', 'id_treaty');
    $this->addFieldMapping('field_sorting_order', 'order');
    $this->addFieldMapping('field_official_order', 'official_order');

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
      'use_informea', 'rec_author', 'rec_updated_author', 'is_indexed'
    ));
    $this->addUnmigratedDestinations(array(
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary',
      'field_enter_into_force:timezone', 'field_enter_into_force:rrule', 'field_enter_into_force:to',
      'field_logo:file_class',
      'field_logo:destination_dir', 'field_logo:destination_file', 'field_logo:preserve_files', 'field_logo:alt', 'field_logo:title',
      'field_odata_identifier:language',
      'field_ratification_xml_url:title', 'field_ratification_xml_url:attributes', 'field_ratification_xml_url:language',
      'field_treaty_long_name:language', 'field_url_treaty_website:attributes',
      'field_treaty_year:timezone', 'field_treaty_year:rrule', 'field_treaty_year:to',
      'field_url_treaty_parties:attributes', 'field_url_treaty_text:attributes',
      'field_region:source_type',
      'field_region:ignore_case'
    ));
  }

  protected function generateMachineName() {
    return 'TreatiesArticles';
  }

  function prepareRow($row) {
    $row->id_treaty = db_select('migrate_map_treaties', 't')
      ->fields('t', array('destid1'))->where('sourceid1=:id', array('id' => $row->id_treaty))
      ->execute()->fetchCol(0);

    if ($row->rec_created == '0000-00-00 00:00:00') {
      $row->rec_created = NULL;
    }
    if ($row->rec_updated == '0000-00-00 00:00:00') {
      $row->rec_updated = NULL;
    }
    if (!empty($row->rec_created)) {
      $row->rec_created = strtotime($row->rec_created);
    }
  }

  function complete($entity) {
    $entity->path['pathauto'] = 0;
  }
}



class MigrateTreatiesParagraphs extends DynamicMigration {

  public function __construct($arguments) {
    parent::__construct();

    $this->dependencies = array('TreatiesArticles');
    $this->description = 'Import articles of treaties';
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
      ->select('ai_treaty_article_paragraph', 'ta')
      ->fields('ta');


    $this->source = new MigrateSourceSQL($query);

    $opt = MigrateDestinationNode::options('en', 'full_html');
    $this->destination = new MigrateDestinationNode('treaty_paragraph', $opt);

    $this->addFieldMapping('title_field', 'order');
    $this->addFieldMapping('title', 'order');

    $this->addFieldMapping('body', 'content');
    $this->addFieldMapping('field_parent_treaty_article', 'id_treaty_article');
    $this->addFieldMapping('field_paragraph_indentation', 'indent');

    $this->addFieldMapping('field_sorting_order', 'order');
    $this->addFieldMapping('field_official_order', 'official_order');
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
      'id_organization', 'id_parent', 'short_title_alternative', 'year',
      'enabled', 'regional', 'use_informea', 'rec_author', 'rec_updated_author', 'is_indexed'
    ));
    $this->addUnmigratedDestinations(array(
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary'
    ));
  }

  protected function generateMachineName() {
    return 'TreatiesParagraphs';
  }

  function prepareRow($row) {
    static $articles_treaty = array();
    static $old_new_articles = array();
    if(empty($articles_treaty)) {
      $mappings_new_old = db_select('migrate_map_treaties', 'e')
        ->fields('e', array('destid1', 'sourceid1'))
        ->execute()->fetchAllKeyed(0);

      $rows = Database::getConnection('default', 'for_migration')
        ->select('ai_treaty_article', 'c')
        ->fields('c', array('id', 'id_treaty'))
        ->execute()
        ->fetchAllKeyed(0);
      foreach($rows as $id_article => $id_treaty_old) {
        $articles_treaty[$id_article] = $mappings_new_old[$id_treaty_old];
      }
    }
    if(empty($old_new_articles)) {
      $old_new_articles = db_select('migrate_map_treatiesarticles', 't')
        ->fields('t')
        ->execute()->fetchAllKeyed(0);
    }

    $row->id_treaty = $articles_treaty[$row->id_treaty_article];
    $row->id_treaty_article = $old_new_articles[$row->id_treaty_article];

    if ($row->rec_created == '0000-00-00 00:00:00') {
      $row->rec_created = NULL;
    }
    if ($row->rec_updated == '0000-00-00 00:00:00') {
      $row->rec_updated = NULL;
    }
    if (!empty($row->rec_created)) {
      $row->rec_created = strtotime($row->rec_created);
    }
  }

  function complete($entity) {
    $entity->path['pathauto'] = 0;
  }
}