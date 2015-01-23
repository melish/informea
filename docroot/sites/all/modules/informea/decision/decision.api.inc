<?php

function decision_count_treaty_decisions($id_treaty) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'decision')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->execute();
  return isset($result['node']) ? count($result['node']) : 0;
}

function decision_get_treaty_decisions($id_treaty) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'decision')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->execute();
  return isset($result['node']) ? node_load_multiple(array_keys($result['node'])) : array();
}

function decision_get_treaty_decisions_group_by_meeting($id_treaty) {
  $rows = decision_get_treaty_decisions($id_treaty);
  $ret = array();
  foreach ($rows as $row) {
    $wrapper = entity_metadata_wrapper('node', $row);
    $meeting = $wrapper->field_meeting->value();
    $ret[$meeting->nid] = $meeting;
  }
  foreach ($rows as $row) {
    $wrapper = entity_metadata_wrapper('node', $row);
    $m = $wrapper->field_meeting->value();
    $meeting = $ret[$m->nid];
    $meeting->decisions[] = $row;
  }
  uasort($ret, function($m1, $m2) {
    $w1 = entity_metadata_wrapper('node', $m1);
    $w2 = entity_metadata_wrapper('node', $m2);
    return strtotime($w1->event_calendar_date->value()['value']) < strtotime($w2->event_calendar_date->value()['value']);
  });
  return $ret;
}
