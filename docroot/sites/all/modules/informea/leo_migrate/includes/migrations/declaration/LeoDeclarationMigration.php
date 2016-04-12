<?php

class LeoDeclarationMigration extends LeoDefaultNodeMigration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array_keys($this->taxonomyFields()));

    $this->addSimpleMappings(array(
      'title_field', 'title_field:language',
      'field_abbreviation', 'field_abbreviation:language',
    ));

    $this->addUnmigratedSources(array(
      'uid', 'revision', 'log', 'revision_uid',
    ));
  }

  function prepareRow($row) {
    parent::prepareRow($row);
  }
}
