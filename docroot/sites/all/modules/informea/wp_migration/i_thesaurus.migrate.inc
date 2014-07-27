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
    $this->destination = new MigrateDestinationTerm('thesaurus_informea');

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

    $this->addFieldMapping('weight', 'order')->defaultValue(FALSE);
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
}