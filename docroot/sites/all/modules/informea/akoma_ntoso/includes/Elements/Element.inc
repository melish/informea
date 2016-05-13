<?php

namespace Drupal\akoma_ntoso\Elements;

class Element {

  protected $type;
  protected $attributes = array();
  protected $children = array();
  protected $content = NULL;

  public function __construct($type, $content = NULL) {
    $this->setType($type);
    $this->setContent($content);
  }

  public function setType($type) {
    $this->type = $type;
  }

  public function addAttribute($name, $value) {
    $this->attributes[$name] = $value;
  }

  public function setContent($value) {
    $this->content = $value;
  }

  public function addChild(Element $element) {
    $this->children[] = $element;
  }

  public function appendToXML(\SimpleXMLElement &$parent) {
    $current = $parent->addChild($this->type, $this->content);
    foreach ($this->attributes as $name => $value) {
      $current->addAttribute($name, $value);
    }
    foreach ($this->children as $child) {
      /** @var Element $child */
     $child->appendToXML($current);
    }
  }

}