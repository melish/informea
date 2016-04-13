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


  /**
    array(2) {
      [0]=>
      object(stdClass)#4998 (4) {
        ["__metadata"]=> object(stdClass)#5000 (1) {
          ["type"]=>
          string(11) "PersonRoles"
        }
        ["treaty"]=> string(3) "cbd"
        ["roles"]=> array(1) {
          [0]=> string(7) "CHM NFP"
        }
        ["order"]=> string(1) "4"
      }
      [1]=>
      object(stdClass)#5001 (4) {
        ["__metadata"]=> object(stdClass)#4999 (1) {
          ["type"]=> string(11) "PersonRoles"
        }
        ["treaty"]=>
        string(9) "cartagena"
        ["roles"]=>
        array(1) {
          [0]=>
          string(7) "BCH NFP"
        }
        ["order"]=>
        string(1) "2"
      }
    }
  */
  public function loadContactRolesProperty($ob) {
    $roles = array();
    $values = $this->loadNavigationProperty($ob, 'roles');
    foreach($values as $t) {
      foreach($t->roles as $role) {
        $roles[$t->treaty][] = $role;
      }
    }
    return $roles;
  }
}
