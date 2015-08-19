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
    $titles_langs = array();
    $titles = array();
    $title_orig = NULL;
    $values = $this->getComplexProperty($ob, 'title');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->value)) {
          $titles_langs[] = $value->language;
          $titles[] = $value->value;
          if ($value->language == 'en') {
            $title_orig = $value->value;
          }
        }
      }
    }
    $ob->titles_langs = $titles_langs;
    $ob->title = $titles;
    if ($title_orig) {
      $ob->title_orig = $title_orig;
    }
    else {
      $ob->title_orig = $titles[0];
    }
    if (!property_exists($ob,'updated')) {
      $ob->updated = '';
    }
    return $ob;
  }
}
