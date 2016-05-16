<?php

namespace Drupal\akoma_ntoso;

use Drupal\akoma_ntoso\Elements\Element;
use Drupal\akoma_ntoso\Elements\Document;


class AkomaNtosoSimpleXMLElement extends \SimpleXMLElement {

  public function addCData($cdata_text) {
    $node = dom_import_simplexml($this);
    $no   = $node->ownerDocument;
    $node->appendChild($no->createCDATASection($cdata_text));
  }

}


class AkomaNtoso {

  /**
   * @var \SimpleXMLElement
   */
  protected $xml;

  /**
   * @var array
   */
  protected $children = array();

  public function __construct() {
    $this->xml = new \SimpleXMLElement('<akomaNtoso/>');
  }

  public function addChild(Document $element) {
    $this->children[] = $element;
  }

  /**
   * @return \SimpleXMLElement
   */
  public function render() {
    foreach ($this->children as $child) {
      /** @var Element $child */
      $child->appendToXML($this->xml);
    }
    return $this->xml;
  }
}