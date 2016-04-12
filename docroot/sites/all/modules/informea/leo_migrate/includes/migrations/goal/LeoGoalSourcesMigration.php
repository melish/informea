<?php

class LeoGoalSourcesMigration extends DrupalTerm7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('name_field', 'name', FALSE);
    $this->addFieldMapping('description_field', 'description', FALSE);

    $this->addSimpleMappings(array(
      'field_binding', 'field_abbreviation', 'field_abbreviation:language',
      'field_url', 'field_url:title', 'field_url:attributes', 'field_url:language',
    ));

    $this->addUnmigratedSources(array(
      'field_binding:language',
    ));

    $this->addUnmigratedDestinations(array(
      'name_field:language', 'description_field:summary', 'description_field:format', 'description_field:language',
    ));

  }

}
