<?php

class MigrateThesaurus extends DynamicMigration {

  protected function generateMachineName() {
    return 'Thesaurus';
  }

  public function __construct($arguments) {
    parent::__construct();

    $this->description = 'Import InforMEA thesaurus';
    $this->map = new MigrateSQLMap($this->machineName,
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
      ->select('voc_concept', 'e')
      ->fields('e');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTerm(INFORMEA_VOC_INFORMEA);

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
  }

  public function prepare($entity, $row) {
    $row->path['pathauto'] = 0;
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
    // new => old
    $mappings_new_old = db_select('migrate_map_thesaurus', 'e')
      ->fields('e', array('destid1', 'sourceid1'))
      ->execute()->fetchAllKeyed(0);
    $mappings_old_new = db_select('migrate_map_thesaurus', 'e')
      ->fields('e')
      ->execute()->fetchAllKeyed(0);

    $relations = Database::getConnection('default', 'for_migration')
      ->select('voc_relation', 'e')->where('relation=1')
      ->fields('e', array('id_concept', 'target_term'))->execute()->fetchAll();

    $terms = taxonomy_get_tree($voc->vid);
    foreach($terms as &$term) {
      $original_id = $mappings_new_old[$term->tid];
      $parents = array();
      foreach($relations as $oterm) {
        if($original_id == $oterm->id_concept) {
          $oparent_id = $oterm->target_term;
          $parent_id = $mappings_old_new[$oparent_id];
          $parents[] = $parent_id;
        }
      }
      if(!empty($parents)) {
        $term->parent = $parents;
        taxonomy_term_save($term);
      }
    }
  }
}
