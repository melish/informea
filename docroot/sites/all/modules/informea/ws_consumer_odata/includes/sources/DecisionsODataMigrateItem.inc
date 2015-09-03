<?php

/**
 * Class DecisionsODataMigrateItem handles Decisions specific properties.
 */
class DecisionsODataMigrateItem extends ODataMigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($id) {
    $ob = parent::getItem($id);
    $this->prepareTitle($ob);
    $this->prepareFiles($ob);

    //Get body
    $content_langs = array();
    $content = array();
    $values = $this->getComplexProperty($ob, 'content');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->value)) {
          $content_langs[] = $value->language;
          $content[] = $value->value;
        }
      }
    }
    $ob->content_langs = $content_langs;
    $ob->content = $content;

    //Get summary
    $summary = array();
    $values = $this->getComplexProperty($ob, 'summary');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->value)) {
          $summary[] = $value->value;
        }
      }
    }
    $ob->summary = $summary;

    if (!property_exists($ob,'updated')) {
      $ob->updated = '';
    }
    return $ob;
  }
}
