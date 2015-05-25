<?php

class MigrateThesaurusBase extends Migration {

  public function __construct($arguments, $source_voc_id, $destination_voc) {
    parent::__construct($arguments);

    $this->addFieldMapping('language')->defaultValue('en');

    $this->addFieldMapping('name_field', 'term');
    $this->addFieldMapping('name_field:language')->defaultValue('en');
    $this->addFieldMapping('name', 'term');

    $this->addFieldMapping('description', 'description');
    $this->addFieldMapping('description_field', 'description');
    $this->addFieldMapping('description_field:language')->defaultValue('en');
    $this->addFieldMapping('description_field:format')->defaultValue('plain_text');

    $this->addFieldMapping('field_term_reference_url', 'reference_url');
    $this->addFieldMapping('field_term_reference_url:language')->defaultValue('en');

    $this->addFieldMapping('field_term_tag', 'tag');
    $this->addFieldMapping('field_term_tag:language')->defaultValue('en');

    $this->addFieldMapping('field_term_popularity', 'popularity');
    $this->addFieldMapping('field_sorting_order', 'order');
    $this->addFieldMapping('field_term_substantive', 'substantive');

    $this->addFieldMapping('field_term_geg_url', 'geg_tools_url');
    $this->addFieldMapping('field_term_geg_url:title')->defaultValue('View GEG goals');

    $this->addFieldMapping('weight', 'order')->defaultValue(0);
    $this->addFieldMapping('format')->defaultValue('plain_text');

    $this->addUnmigratedSources(array(
      'top_concept', 'id_source',
      'rec_created', 'rec_updated',
      'rec_author', 'rec_updated_author'
    ));
    $this->addUnmigratedDestinations(array(
      'field_thesaurus_map_ecolex', 'field_thesaurus_map_ecolex:source_type',
      'field_thesaurus_map_ecolex:create_term', 'field_thesaurus_map_ecolex:ignore_case',
      'field_thesaurus_map_agrovoc', 'field_thesaurus_map_agrovoc:source_type',
      'field_thesaurus_map_agrovoc:create_term', 'field_thesaurus_map_agrovoc:ignore_case',
      'field_thesaurus_map_gemet', 'field_thesaurus_map_gemet:source_type',
      'field_thesaurus_map_gemet:create_term', 'field_thesaurus_map_gemet:ignore_case',
      'description_field:summary',
      'field_term_geg_url:attributes', 'field_term_geg_url:language'
    ));

    $this->map = new MigrateSQLMap($this->getMachineName(),
      array(
        'id' => array('type' => 'int',
          'length' => 4,
          'not null' => TRUE,
          'description' => 'Source PK',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $query = Database::getConnection('default', 'for_migration')
      ->select('voc_concept', 'e')->condition('id_source', $source_voc_id, '=')
      ->fields('e');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTerm($destination_voc);
  }

}

class MigrateThesaurusInforMEA extends MigrateThesaurusBase {

  public function __construct($arguments) {
    parent::__construct($arguments, 9, INFORMEA_VOC_INFORMEA);
    $this->dependencies = array('ThesaurusGEG');
    $this->description = 'Import InforMEA thesaurus';
  }

  /**
   * {@inheritdoc}
   */
  public function postImport() {
    Migration::displayMessage(
      "Setting term hierarchy for " . INFORMEA_VOC_INFORMEA,
      MigrationBase::MESSAGE_INFORMATIONAL
    );
    $voc = taxonomy_vocabulary_machine_name_load(INFORMEA_VOC_INFORMEA);

    $mappings_new_old = db_select('migrate_map_thesaurusinformea', 'e')
      ->fields('e', array('destid1', 'sourceid1'))
      ->execute()->fetchAllKeyed(0);

    $mappings_old_new = db_select('migrate_map_thesaurusinformea', 'e')
      ->fields('e')
      ->execute()->fetchAllKeyed(0);

    $relations = array();
    $relations1 = Database::getConnection('default', 'for_migration')
      ->select('voc_relation', 'e')->where('relation=1')
      ->fields('e', array('id_concept', 'target_term'))->execute()->fetchAll();
    $relations2 = Database::getConnection('default', 'for_migration')
      ->select('voc_relation', 'e')->where('relation=2')
      ->fields('e', array('id_concept', 'target_term'))->execute()->fetchAll();

    foreach ($relations1 as $r) {
      $relations[$r->id_concept][] = $r->target_term;
    }
    foreach ($relations2 as $r) {
      if (array_key_exists($r->target_term, $relations)) {
        if (!in_array($r->id_concept, $relations[$r->target_term])) {
          $relations[$r->target_term][] = $r->id_concept;
        }
      }
      else {
        $relations[$r->target_term][] = $r->id_concept;
      }
    }

    $terms = taxonomy_get_tree($voc->vid);
    foreach($terms as &$term) {
      if (array_key_exists($term->tid, $mappings_new_old)) {
        $original_id = $mappings_new_old[$term->tid];
        $parents = array();

        if (array_key_exists($original_id, $relations)) {
          $ops = $relations[$original_id];
          foreach($ops as $opid) {
            $parents[] = $mappings_old_new[$opid];
          }
        }
        if (!empty($parents)) {
          $term->parent = $parents;
          taxonomy_term_save($term);
        }
      }
      else {
        self::saveMessage("Could not find mapping for term: " . $term->name, MigrationBase::MESSAGE_WARNING);
      }
    }
  }
}


class MigrateThesaurusInforMEAUpdateDescriptions extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = 'Update descriptions from the WordPress version for migrated terms';
    $source_voc_id = 9;
    $this->dependencies = array('ThesaurusInforMEA');
    $destination_voc = INFORMEA_VOC_INFORMEA;
    $this->map = new MigrateSQLMap($this->getMachineName(),
      array(
        'id' => array('type' => 'int',
          'length' => 4,
          'not null' => TRUE,
          'description' => 'Source PK',
        )
      ),
      MigrateDestinationTerm::getKeySchema()
    );
    $query = Database::getConnection('default', 'for_migration')
      ->select('voc_concept', 'e')->condition('id_source', $source_voc_id, '=')
      ->fields('e');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTerm($destination_voc, array('language' => 'en'));
    $this->setSystemOfRecord(Migration::DESTINATION);

    $this->addFieldMapping('tid', 'id')->sourceMigration('ThesaurusInforMEA');

    $this->addFieldMapping('name_field', 'term');
    $this->addFieldMapping('name_field:language')->defaultValue('en');
    $this->addFieldMapping('name', 'term');

    $this->addFieldMapping('description', 'description');
    $this->addFieldMapping('description_field', 'description');
    $this->addFieldMapping('description_field:language')->defaultValue('en');
    $this->addFieldMapping('description_field:format')->defaultValue('plain_text');
  }
}

class MigrateThesaurusGEG extends MigrateThesaurusBase {

  public function __construct($arguments) {
    parent::__construct($arguments, 10, INFORMEA_VOC_GEG);
    $this->description = 'Import GEG thesaurus';
  }
}


class MigrateThesaurusIEG extends MigrateThesaurusBase {

  public function __construct($arguments) {
    parent::__construct($arguments, 13, INFORMEA_VOC_IEG);
    $this->description = 'Import IEG thesaurus';
  }
}


class MigrateThesaurusGEMET extends MigrateThesaurusBase {

  public function __construct($arguments) {
    parent::__construct($arguments, 13, INFORMEA_VOC_GEMET);
    $this->description = 'Import GEMET thesaurus';
  }
}
