<?php

/**
 * Class SitesODataMigrateItem handles Sites specific properties.
 */
class SitesODataMigrateItem extends ODataMigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($id) {
    $ob = parent::getItem($id, '$expand=name');
    $this->prepareTitle($ob);

    if (!property_exists($ob,'updated')) {
      $ob->updated = '';
    }
    return $ob;
  }
}
