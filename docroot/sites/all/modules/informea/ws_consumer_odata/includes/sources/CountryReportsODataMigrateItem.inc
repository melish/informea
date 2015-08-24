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
    $title_langs = array();
    $titles = array();
    $title_orig = NULL;
    $values = $this->getComplexProperty($ob, 'title');
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
      $ob->title_orig = $titles[0];
    }

    //Get files
    $files = array();
    $files_language = array();
    $values = $this->getComplexProperty($ob, 'files');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->url)) {
          $files_language[] = $value->language;
          $files[] = $value->url;
        }
      }
    }
    $ob->files_language = $files_language;
    $ob->files = $files;

    if (!property_exists($ob,'submission')) {
      $ob->submission = '';
    }
    if (!property_exists($ob,'updated')) {
      $ob->updated = '';
    }
    return $ob;
  }
}
