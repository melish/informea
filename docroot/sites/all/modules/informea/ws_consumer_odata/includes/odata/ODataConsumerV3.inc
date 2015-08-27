<?php

/** Supports OData v3 specific structures. */
class ODataConsumerV3 extends ODataConsumer {

  /**
   * Adds customizations specific to OData v3 (different navigation properties).
   *
   * {@inheritdoc}
   */
  public function loadNavigationProperty($ob, $property_name) {
    // OData v3, property expanded using $expand=property_name
    // No need for an additional HTTP request, data already there
    if (!empty($ob->{$property_name}) && is_array($ob->{$property_name})) {
      return $ob->{$property_name};
    }
    // OData v1, without $expand.
    else if (!empty($ob->{$property_name}->__deferred->uri)) {
      /** @var stdClass $result */
      if ($result = $this->loadRemoteData($ob->$property_name->__deferred->uri)) {
        return $result->results;
      }
    }
    else {
      // @todo Handle non-expanded OData v3 properties
    }
    return NULL;
  }
}
