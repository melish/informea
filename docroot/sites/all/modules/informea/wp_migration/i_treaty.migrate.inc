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
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(FALSE);

    $this->addUnmigratedSources(array(
      'id_organization', 'id_parent', 'short_title_alternative', 'year',
      'enabled', 'regional', 'use_informea', 'rec_author', 'rec_updated_author', 'is_indexed'
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

  protected function generateMachineName() {
    return 'Treaties';
  }
}