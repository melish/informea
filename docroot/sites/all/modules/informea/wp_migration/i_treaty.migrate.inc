<?php

class MigrateTreaties extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->dependencies = array('ThesaurusInforMEA');
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

    $this->source = new EntityWithTagsMigrateSourceSQL($query);

    $this->destination = new MigrateDestinationNode('treaty', array(
      'language' => 'en', 'text_format' => 'full_html',
    ));

    $this->addFieldMapping('title_field', 'short_title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'short_title');

    $this->addFieldMapping('field_data_source')->defaultValue('InforMEA');
    $this->addFieldMapping('field_data_source:create_term')->defaultValue(TRUE);

    $this->addFieldMapping('field_official_name', 'long_title');
    $this->addFieldMapping('body', 'abstract');
    $this->addFieldMapping('body:language')->defaultValue('en');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('field_primary', 'primary');
    $this->addFieldMapping('field_sorting_date', 'start');

    $this->addFieldMapping('field_treaty_text_url', 'url_treaty_text');
    $this->addFieldMapping('field_treaty_text_url:language')->defaultValue('en');
    $this->addFieldMapping('field_treaty_text_url:title')->defaultValue('View on MEA website');

    $this->addFieldMapping('field_treaty_website_url', 'url');
    $this->addFieldMapping('field_treaty_website_url:language')->defaultValue('en');
    $this->addFieldMapping('field_treaty_website_url:title')->defaultValue('Visit website');

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

    $this->addFieldMapping('field_informea_tags', 'tags');
    $this->addFieldMapping('field_informea_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_informea_tags:create_term')->defaultValue(FALSE);

    // All InforMEA treaties are multilateral
    $this->addFieldMapping('field_type_of_text')->defaultValue('Multilateral');
    $this->addFieldMapping('field_type_of_text:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_type_of_text:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_parent_treaty', 'id_parent');
    $this->addFieldMapping('field_region', 'regions');

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
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary', 'field_entry_into_force',
      'field_entry_into_force:timezone', 'field_entry_into_force:rrule', 'field_entry_into_force:to',
      'field_logo:file_class',
      'field_logo:destination_dir', 'field_logo:destination_file', 'field_logo:preserve_files', 'field_logo:alt', 'field_logo:title',
      'field_odata_identifier:language',
      'field_ratification_xml_url:title', 'field_ratification_xml_url:attributes', 'field_ratification_xml_url:language',
      'field_official_name:language', 'field_treaty_website_url:attributes',
      'field_treaty_year:timezone', 'field_treaty_year:rrule', 'field_treaty_year:to',
      'field_url_treaty_parties:attributes', 'field_treaty_text_url:attributes',
      'field_region:source_type',
      'field_region:ignore_case'
    ));
  }

  function createStub(Migration $migration, array $source_id) {
    $node = new stdClass();
    $node->title = t('Stub for treaty @id', array('@id' => $source_id[0]));
    $node->body['en'][0] = t('Stub body');
    $node->type = $this->destination->getBundle();
    $node->uid = 1;
    $node->status = 1;
    node_object_prepare($node);
    node_save($node);
    if (isset($node->nid)) {
      return array($node->nid);
    }
    else {
      return FALSE;
    }
  }

  function prepareRow($row) {
    $row->logo_medium = 'http://www.informea.org/wp-content/uploads/' . $row->logo_medium;
    $id_parent = db_select('migrate_map_treaties', 't')
      ->fields('t', array('destid1'))->where('sourceid1=:id', array('id' => $row->id_parent))
      ->execute()->fetchCol(0);
    if (!$id_parent) {
      $id_parent =  $this->handleSourceMigration('Treaties', array($id_parent));
    }
    $row->id_parent = $id_parent;

    // Region
    $region_ids = Database::getConnection('default', 'for_migration')
      ->select('ai_treaty_region', 't')
      ->condition('aitreaty_id', $row->id)
      ->fields('t', array('airegion_id'))
      ->execute()
      ->fetchCol(0);

    if (!empty($region_ids)) {
      $region_names = Database::getConnection('default', 'for_migration')
                              ->select('ai_region', 't')
                              ->condition('id', $region_ids, 'IN')
                              ->fields('t', array( 'name' ))
                              ->execute()
                              ->fetchCol(0);
      $row->regions = $region_names;
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
    $this->prepareTags($row);
  }

  function complete($entity, $row) {
      $args = array(
        'source' => 'node/' . $entity->nid,
        'alias' => 'treaties/' . $row->odata_name,
        'language' => 'en',
      );
      path_save($args);
  }

  function prepareTags(&$row) {
    $old_tags = Database::getConnection('default', 'for_migration')
      ->select('ai_treaty_vocabulary', 'd')
      ->where('id_treaty=:id', array(':id' => $row->id))
      ->fields('d', array('id_concept'))
      ->execute()
      ->fetchCol(0);
    $row->tags = wp_migrationn_new_old_tags($old_tags);
  }
}



class MigrateTreatiesArticles extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);

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


    $this->source = new EntityWithTagsMigrateSourceSQL($query);

    $opt = MigrateDestinationNode::options('en', 'full_html');
    $this->destination = new MigrateDestinationNode('treaty_article', $opt);

    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('title_field:language')->defaultValue('en');

    $this->addFieldMapping('body', 'content');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('body:language')->defaultValue('en');

    $this->addFieldMapping('field_treaty', 'id_treaty');
    $this->addFieldMapping('field_sorting_order', 'order');
    $this->addFieldMapping('field_official_order', 'official_order');
    $this->addFieldMapping('field_official_order:language')->defaultValue('en');

    $this->addFieldMapping('field_informea_tags', 'tags');
    $this->addFieldMapping('field_informea_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_informea_tags:create_term')->defaultValue(FALSE);
    $this->addFieldMapping('field_informea_tags:ignore_case')->defaultValue(TRUE);

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
      'rec_author', 'rec_updated_author', 'is_indexed'
    ));
    $this->addUnmigratedDestinations(array(
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary', 'path',
    ));
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
    $this->prepareTags($row);
  }

  function complete($entity) {
    $entity->path['pathauto'] = 0;
  }

  function prepareTags(&$row) {
    $old_tags = Database::getConnection('default', 'for_migration')
      ->select('ai_treaty_article_vocabulary', 'd')
      ->where('id_treaty_article=:id', array(':id' => $row->id))
      ->fields('d', array('id_concept'))
      ->execute()
      ->fetchCol(0);
    $row->tags = wp_migrationn_new_old_tags($old_tags);
  }
}


class MigrateTreatiesParagraphs extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);

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


    $this->source = new TreatiesParagraphsMigrateSourceSQL($query);

    $opt = MigrateDestinationNode::options('en', 'full_html');
    $this->destination = new MigrateDestinationNode('treaty_paragraph', $opt);

    $this->addFieldMapping('title_field', 'order');
    $this->addFieldMapping('title', 'order');
    $this->addFieldMapping('title_field:language')->defaultValue('en');

    $this->addFieldMapping('body', 'content');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('body:language')->defaultValue('en');
    $this->addFieldMapping('field_parent_treaty_article', 'id_treaty_article');
    $this->addFieldMapping('field_paragraph_indentation', 'indent');

    $this->addFieldMapping('field_sorting_order', 'order');
    $this->addFieldMapping('field_official_order', 'official_order');
    $this->addFieldMapping('field_official_order:language')->defaultValue('en');
    $this->addFieldMapping('field_treaty', 'id_treaty');

    $this->addFieldMapping('field_informea_tags', 'tags');
    $this->addFieldMapping('field_informea_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_informea_tags:create_term')->defaultValue(FALSE);

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
      'rec_author', 'rec_updated_author', 'is_indexed'
    ));
    $this->addUnmigratedDestinations(array(
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary', 'path'
    ));
  }

  function prepareRow($row) {
    static $articles_treaty = array();
    static $old_new_articles = array();
    if(empty($articles_treaty)) {
      $mappings_old_new = db_select('migrate_map_treaties', 'e')
        ->fields('e', array('sourceid1', 'destid1'))
        ->execute()->fetchAllKeyed(0);

      $rows = Database::getConnection('default', 'for_migration')
        ->select('ai_treaty_article', 'c')
        ->fields('c', array('id', 'id_treaty'))
        ->execute()
        ->fetchAllKeyed(0);
      foreach($rows as $id_article => $id_treaty_old) {
        $articles_treaty[$id_article] = $mappings_old_new[$id_treaty_old];
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
    $this->prepareTags($row);
  }

  function complete($entity) {
    $entity->path['pathauto'] = 0;
  }

  function prepareTags(&$row) {
    $old_tags = Database::getConnection('default', 'for_migration')
      ->select('ai_treaty_article_paragraph_vocabulary', 'd')
      ->where('id_treaty_article_paragraph=:id', array(':id' => $row->id))
      ->fields('d', array('id_concept'))
      ->execute()
      ->fetchCol(0);
    $row->tags = wp_migrationn_new_old_tags($old_tags);
  }
}

class TreatiesParagraphsMigrateSourceSQL extends MigrateSourceSQL {

  public function fields() {
    $fields = parent::fields() + array(
        'id_treaty' => 'Parent treaty taken from its article',
        'tags' => 'Associated InforMEA tags',
      );
    return $fields;
  }
}

class EntityWithTagsMigrateSourceSQL extends MigrateSourceSQL {

  public function fields() {
    $fields = parent::fields() + array(
        'tags' => 'Associated InforMEA tags',
      );
    return $fields;
  }
}