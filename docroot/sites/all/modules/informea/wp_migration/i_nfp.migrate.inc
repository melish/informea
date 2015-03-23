<?php

class MigrateNationalFocalPoints extends Migration {

  protected $countries = array();
  protected $treaties = array();
  protected $treaty_assignments = array();

  protected function generateMachineName() {
    return 'NationalFocalPoints';
  }

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->dependencies = array('Treaties');
    $this->description = 'Import InforMEA national focal points';
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

      if(empty($this->treaty_assignments) && !empty($this->treaties)) {
        $query = Database::getConnection('default', 'for_migration')
          ->select('ai_people_treaty', 'c')->fields('c')->execute();
        $rows = $query->fetchAll();
        foreach($rows as $row) {
          $this->treaty_assignments[$row->id_people][]
            = $this->treaties[$row->id_treaty];
        }
      }
    } catch(Exception $e) {
      // Table might not be available yet
    }

    $query = Database::getConnection('default', 'for_migration')
      ->select('ai_people', 'e')
      ->fields('e');

    $this->dependencies = array('Treaties');
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('contact_person');

    $this->addFieldMapping('title_field', 'name');
    $this->addFieldMapping('title_field:language')->defaultValue('en');
    $this->addFieldMapping('title', 'name');

    $this->addFieldMapping('field_original_id', 'original_id');
    $this->addFieldMapping('field_country', 'id_country');

    $this->addFieldMapping('field_person_prefix', 'prefix');
    $this->addFieldMapping('field_person_first_name', 'first_name');
    $this->addFieldMapping('field_person_last_name', 'last_name');

    $this->addFieldMapping('field_person_position', 'position');
    $this->addFieldMapping('field_person_institution', 'institution');
    $this->addFieldMapping('field_person_department', 'department');
    $this->addFieldMapping('field_address', 'address');
    $this->addFieldMapping('field_person_email', 'email');
    $this->addFieldMapping('field_contact_telephone', 'telephone');
    $this->addFieldMapping('field_contact_fax', 'fax');
    $this->addFieldMapping('field_contact_primary_nfp', 'is_primary');

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
      'rec_author', 'rec_updated_author', 'is_indexed'
    ));
    $this->addUnmigratedDestinations(array(
      'body', 'body:format', 'body:language', 'field_original_id:language',
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary',
    ));

  }

  function prepareRow($row) {
    $name = '';
    if (!empty($row->first_name)) {
      $name = $row->first_name;
    }
    if (!empty($row->last_name)) {
      if (!empty($row->first_name)) {
        $name .= ' ';
      }
      $name .= $row->last_name;;
    }
    if (empty($name) && !empty($row->position)) {
      $name = $row->position;
    }
    if (empty($name) && !empty($row->institution)) {
      $name = $row->institution;
    }
    $row->name = trim($name);
    if (empty($row->name)) {
      $row->name = '<unknown>';
    }

    $row->id_treaty = $this->treaty_assignments[$row->id];

    if ($row->rec_created == '0000-00-00 00:00:00') {
      $row->rec_created = NULL;
    }
    if (!empty($row->rec_created)) {
      $row->rec_created = strtotime($row->rec_created);
    }
    if ($row->rec_updated == '0000-00-00 00:00:00') {
      $row->rec_updated = NULL;
    }
    $row->id_country = wp_migration_get_country_id($this->countries[$row->id_country]);
    return TRUE;
  }
}
