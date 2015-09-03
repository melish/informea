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
    $this->prepareTitle($ob);

    if (!property_exists($ob,'updated')) {
      $ob->updated = '';
    }
    return $ob;
  }
}
