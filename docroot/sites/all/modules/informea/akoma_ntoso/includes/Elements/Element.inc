<?php

namespace Drupal\akoma_ntoso\Elements;

class Element {

  protected $type;
  protected $attributes = array();
  protected $children = array();

  public function __construct($type) {
    $this->type = $type;
  }

  public function addAttribute($name, $value) {
    $this->attributes[$name] = $value;
  }

  public function addChild(Element $element) {
    $this->children[] = $element;
  }

  public function appendToXML(\SimpleXMLElement &$parent) {
    $current = $parent->addChild($this->type);
    foreach ($this->attributes as $name => $value) {
      $current->addAttribute($name, $value);
    }
    foreach ($this->children as $child) {
      /** @var Element $child */
     $child->appendToXML($current);
    }
  }

}