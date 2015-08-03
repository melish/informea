<?php

/**
 * Class ContactsMigrateSourceList provides fields for Contacts migration.
 */
class ContactsMigrateSourceList extends MigrateSourceList {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'country' => 'Contact country',
      'prefix' => 'Name prefix (Mr.)',
      'name' => 'Computed name of the contact',
      'firstName' => 'Given name',
      'lastName' => 'Family name',
      'position' => 'Work position',
      'institution' => 'Working institution',
      'department' => 'Department',
      'address' => 'Working address',
      'email' => 'Work e-mail address',
      'phone' => 'Contact telephone number',
      'type' => 'Type of contact (i.e. licenced focal point)',
      'fax' => 'Work fax number',
      'primary' => 'Is primary focal point',
      'updated' => 'RSS updated field - when record was updated',
      'treaties' => 'List of treaties (odata_name) the focal point is working for',
    );
  }
}
