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
    // Download the Meeting navigable properties
    $title_langs = array();
    $titles = array();
    $title_orig = NULL;
    $values = $this->getComplexProperty($ob, 'name');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->value)) {
          $title_langs[] = $value->language;
          $titles[] = $value->value;
          if ($value->language == 'en') {
            $title_orig = $value->value;
          }
        }
      }
    }
    $ob->title_langs = $title_langs;
    $ob->title = $titles;
    if ($title_orig) {
      $ob->title_orig = $title_orig;
    }
    else {
      $ob->title_orig = empty($titles) ? '' : $titles[0];
    }
    if (!property_exists($ob,'updated')) {
      $ob->updated = '';
    }
    return $ob;
  }
}
