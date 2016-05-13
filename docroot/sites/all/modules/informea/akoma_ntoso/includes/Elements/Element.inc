<?php

namespace Drupal\akoma_ntoso\Elements;

abstract class Element {

  protected $type;
  protected $attributes = NULL;
  protected $children = array();

  public function addChild(Element $element) {
    $this->children[] = $element;
  }

  public function appendToXML(\SimpleXMLElement &$parent) {
    $current = $parent->addChild($this->type);
    foreach ($this->children as $child) {
      /** @var Element $child */
     $child->render($current);
    }
  }

}