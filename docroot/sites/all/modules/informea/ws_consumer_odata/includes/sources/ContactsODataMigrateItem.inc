<?php

/**
 * Class ContactsODataMigrateItem handles Contacts specific properties.
 */
class ContactsODataMigrateItem extends ODataMigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($id) {
    $ob = parent::getItem($id, '$expand=treaties');
    // Download the Contact navigable properties
    $treaties = array();
    $values = $this->getComplexProperty($ob, 'treaties');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->value)) {
          $treaties[] = $value->value;
        }
        // CBD OData v3 seem to return this format
        else if (!empty($value) && is_string($value)) {
          $treaties[] = $value;
        }
      }
    }
    $ob->treaties = $treaties;
    return $ob;
  }
}
