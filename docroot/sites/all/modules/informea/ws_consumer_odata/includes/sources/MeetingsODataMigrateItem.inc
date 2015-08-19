<?php

/**
 * Class MeetingsODataMigrateItem handles Meetings specific properties.
 */
class MeetingsODataMigrateItem extends ODataMigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($id) {
    $ob = parent::getItem($id, '$expand=title');
    // Download the Meeting navigable properties
    $titles = array();
    $values = $this->getComplexProperty($ob, 'title');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->value)) {
          $titles[$value->language] = $value->value;
        }
      }
    }
    $ob->title = $titles;
    return $ob;
  }
}
