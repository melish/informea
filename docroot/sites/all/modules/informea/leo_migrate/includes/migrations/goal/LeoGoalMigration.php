<?php

class LeoGoalMigration extends LeoDefaultNodeMigration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array_keys($this->taxonomyFields()));

    $this->addSimpleMappings(array(
      'field_official_order', 'field_official_order:language',
    ));

    $this->addUnmigratedSources(array(
      'uid', 'revision', 'log', 'revision_uid',
    ));

    $this->addUnmigratedDestinations(array(
    ));
  }

  protected function taxonomyFields() {
    return [
      'field_informea_tags' => 'thesaurus_informea',
      'field_goal_type' => 'type_of_goal',
      'field_goal_source' => 'goal_sources',
    ];
  }

  function prepareRow($row) {
    parent::prepareRow($row);
  }
}