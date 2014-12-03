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

    return TRUE;
  }

  public function prepare($entity, $row) {
    $entity->title = 'Goal #' . $row->id;

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
