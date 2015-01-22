<?php

function country_data_country_get_parties($id_country) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'member_party')
                  ->fieldCondition('field_country', 'target_id', $id_country)
                  ->execute();
  if (isset($result['node'])) {
    $result_nids = array_keys($result['node']);
    $parties = entity_load('node', $result_nids);
    uasort($parties, function($a, $b) { return $a->title < $b->title; });
    return $parties;
  }
  return array();
}

function country_data_treaty_get_membership($id_treaty) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'member_party')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->execute();
  if (isset($result['node'])) {
    $result_nids = array_keys($result['node']);
    $parties = entity_load('node', $result_nids);
    uasort($parties, function($a, $b) { return $a->title < $b->title; });
    return $parties;
  }
  return array();
}
