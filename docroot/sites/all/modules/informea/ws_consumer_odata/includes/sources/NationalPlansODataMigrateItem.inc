<?php

/**
 * Class NationalPlansODataMigrateItem handles NationalPlans specific properties.
 */
class NationalPlansODataMigrateItem extends ODataMigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($id) {
    $ob = parent::getItem($id, '$expand=title');
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
