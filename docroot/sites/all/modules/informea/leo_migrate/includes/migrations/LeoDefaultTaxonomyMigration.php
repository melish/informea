<?php

class LeoDefaultTaxonomyMigration extends DrupalTerm7Migration {
  public function __construct(array $arguments) {

    parent::__construct($arguments);

    $this->addSimpleMappings(array(
      'description_field',
      'description_field:summary',
      'description_field:format',
      'description_field:language',
      'name_field',
      'name_field:language',
    ));

  }

}
