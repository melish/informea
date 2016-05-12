<?php

namespace Drupal\akoma_ntoso;

class AkomaNtoso {

  /**
   * @return \SimpleXMLElement
   */
  public function render() {
    $xml = new \SimpleXMLElement('<xml/>');
    $akomaNtoso = $xml->addChild('<akomantoso>');
    return $xml;
  }
}