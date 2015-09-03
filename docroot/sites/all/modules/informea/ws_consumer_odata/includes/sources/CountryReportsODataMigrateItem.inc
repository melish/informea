<?php

/**
 * Class CountryReportsODataMigrateItem handles CountryReports specific properties.
 */
class CountryReportsODataMigrateItem extends ODataMigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($id) {
    $ob = parent::getItem($id, '$expand=title');
    // Download the Meeting navigable properties
    $this->prepareTitle($ob);
    $this->prepareFiles($ob);

    if (!property_exists($ob,'submission')) {
      $ob->submission = '';
    }
    if (!property_exists($ob,'updated')) {
      $ob->updated = '';
    }
    return $ob;
  }
}
