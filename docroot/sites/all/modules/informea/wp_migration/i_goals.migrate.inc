<?php

class MigrateGoals extends DynamicMigration {

  protected $regions = array();


  protected function generateMachineName() {
    return 'Goals';
  }

  public function __construct($arguments) {
    parent::__construct();

    $this->dependencies = array('ThesaurusGEG');
    $this->description = 'Import InforMEA sites';
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
                     ->select('ai_goals', 'e')
                     ->fields('e');
    $this->source = new GoalsMigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode(
      'goal',
      array('language' => 'en', 'text_format' => 'full_html')
    );

    $this->addFieldMapping('field_sorting_order', 'order');

    $this->addFieldMapping('field_goal_type', 'type');
    $this->addFieldMapping('field_goal_type:create_term')->defaultValue(TRUE);

    $this->addFieldMapping('title', 'name');

    $this->addFieldMapping('body', 'name');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    $this->addFieldMapping('field_geg_tags', 'focus');
    $this->addFieldMapping('field_geg_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_geg_tags:create_term')->defaultValue(FALSE);

    $this->addFieldMapping('field_goal_indicators', 'indicators');
    $this->addFieldMapping('field_goal_tools', 'tools');

    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('uid')->defaultValue(1);
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(FALSE);

    $this->addUnmigratedSources(array(
      'rec_author', 'rec_updated_author'
    ));
    $this->addUnmigratedDestinations(array(
      'body:language',
      'field_url:attributes',
      'log', 'tnid', 'translate', 'revision_uid', 'is_new', 'body:summary',
    ));


    if(empty($this->regions)) {
      $query = Database::getConnection('default', 'for_migration')
                       ->select('geg_ai_region', 'c')->fields('c')->execute();
      $rows = $query->fetchAll();
      foreach($rows as $row) {
        $this->regions[$row->id] = $row->title;
      }
    }

    function fields() {

    }
  }

  function prepareRow($row) {
    $this->prepareGoalsTags($row);
    $this->prepareGoalName($row);
    return TRUE;
  }

  public function prepare($entity, $row) {

    // Region
    $query = Database::getConnection('default', 'for_migration')
                     ->select('geg_ai_goal_region', 'c')
                     ->fields('c')
                     ->condition('id_goal', $row->id)
                     ->execute();
    $rows = $query->fetchAll();
    foreach($rows as $i => $r) {
      $region_name = $this->regions[$r->id_region];
      if ($region = MigrationUtil::getOrCreateTerm($region_name, 'geographical_region')) {
        $entity->field_region[LANGUAGE_NONE][$i]['tid'] = $region->tid;
      }
    }

    // $this->addFieldMapping('field_theme', 'id_theme_geg'); //@todo unmap
    // $this->addFieldMapping('field_strategic_goal', 'id_strategic_goal'); // @todo:
    // geg_ai_goal_source
  }


  function prepareGoalsTags(&$row) {
    $old_tags = Database::getConnection('default', 'for_migration')
                        ->select('geg_ai_goal_focus', 'd')
                        ->where('id_goal=:id', array(':id' => $row->id))
                        ->fields('d', array('id_focus'))
                        ->execute()
                        ->fetchCol(0);
    $row->focus = wp_migrationn_new_old_tags($old_tags, 'migrate_map_thesaurusgeg');
  }


  function prepareGoalName(&$row) {
    if ($row->type == 'Strategic Goal') {
    }
    else if ($row->type == 'Aichi Target') {
      switch ($row->name) {
        case 'Aware of the values of biodiversity':
          $row->name = 'Aichi Target 1: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 1;
          break;

        case 'Integration of biodiversity':
          $row->name = 'Aichi Target 2: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 2;
          break;

        case 'Elimination of incentives harmful to biodiversity':
          $row->name = 'Aichi Target 3: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 3;
          break;

        case 'Development and/or implementation of plans for sustainable production and consumption':
          $row->name = 'Aichi Target 4: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 4;
          break;

        case 'Halving the rate of loss of all natural habitats':
          $row->name = 'Aichi Target 5: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 5;
          break;

        case 'All fish and invertebrate stocks and aquatic plants are managed and harvested sustainably':
          $row->name = 'Aichi Target 6: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 6;
          break;

        case 'Areas under agriculture, aquaculture and forestry are managed sustainably':
          $row->name = 'Aichi Target 7: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 7;
          break;

        case 'Reducing pollution':
          $row->name = 'Aichi Target 8: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 8;
          break;

        case 'Invasive alien species and pathways are identified and prioritized':
          $row->name = 'Aichi Target 9: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 9;
          break;

        case '(2015) Minimize the anthropogenic pressures on coral reefs, and other vulnerable ecosystems':
          $row->name = 'Aichi Target 10: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 10;
          break;

        case 'Conservation of terrestrial and marine areas':
          $row->name = 'Aichi Target 11: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 11;
          break;

        case 'Prevent extinction of known threatened species':
          $row->name = 'Aichi Target 12: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 12;
          break;

        case 'Minimizing genetic erosion and safeguarding genetic diversity':
          $row->name = 'Aichi Target 13: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 13;
          break;

        case 'Restoring and safeguarding ecosystems':
          $row->name = 'Aichi Target 14: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 14;
          break;

        case 'Enhanced ecosystem resilience':
          $row->name = 'Aichi Target 15: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 15;
          break;

        case 'Implementation of Nagoya Protocol on Access to Genetic Resources':
          $row->name = 'Aichi Target 16: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 16;
          break;

        case 'Implementation of national biodiversity strategy and action plan':
          $row->name = 'Aichi Target 17: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 17;
          break;

        case 'Traditional knowledge, innovations and practices of indigenous and local communities respected':
          $row->name = 'Aichi Target 18: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 18;
          break;

        case 'Knowledge, the science base and technologies relating to biodiversity, improved':
          $row->name = 'Aichi Target 19: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 19;
          break;

        case 'Mobilization of financial resources':
          $row->name = 'Aichi Target 20: ' . $row->name;
          $row->field_sorting_order[LANGUAGE_NONE][0]['value'] = 20;
          break;

      }
    }
    else {
      $row->name = 'Goal #' . $row->id;
    }
  }
}

class GoalsMigrateSourceSQL extends MigrateSourceSQL {

  function __construct($query) {
    parent::__construct($query);
  }

  function fields() {
    $fields = parent::fields();
    $fields['focus'] = 'InforMEA Tags';
    return $fields;
  }
}
