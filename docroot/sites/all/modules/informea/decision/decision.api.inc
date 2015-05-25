<?php

function decision_count_treaty_decisions($id_treaty) {
  return EdwCacheDomain::cache_get_array('decision', __FUNCTION__, function($id_treaty) {
    $query  = new EntityFieldQuery();
    return $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'decision')
      ->fieldCondition('field_treaty', 'target_id', $id_treaty)
      ->count()
      ->execute();
  }, $id_treaty);
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
  $ret = array();
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'decision')
    ->fieldCondition('field_treaty', 'target_id', $id_treaty)
    ->execute();
  if (!empty($result['node'])) {
    $decisions = $result['node'];
    $fields = field_info_instances('node', 'decision');
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_meeting']['field_id']));
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_number']['field_id']));
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_status']['field_id']));
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['title_field']['field_id']));
    foreach ($decisions as $decision) {
      $meeting_id = $decision->field_meeting[LANGUAGE_NONE][0]['target_id'];
      $meeting = node_load($meeting_id);
      $meeting->decisions = array();
      $meeting_w = entity_metadata_wrapper('node', $meeting);
      $type = $meeting_w->field_event_type->value();
      if (($type && strtolower($type->name_original) == 'cop') || empty($type)) {
        $ret[$meeting_id] = $meeting;
      }
    }
    foreach ($decisions as $decision) {
      $meeting_id = $decision->field_meeting[LANGUAGE_NONE][0]['target_id'];
      if(array_key_exists($meeting_id, $ret)) {
        $meeting = $ret[$meeting_id];
        $meeting->decisions[] = $decision;
      }
    }
    uasort($ret, function($a, $b) {
      $wa = entity_metadata_wrapper('node', $a);
      $wb = entity_metadata_wrapper('node', $b);
      $a_st = $wa->event_calendar_date->value();
      $b_st = $wb->event_calendar_date->value();
      if(empty($a_st)) {
        return 1;
      }
      else if (empty($b_st)) {
        return -1;
      }
      else {
        $starta = strtotime($a_st['value']);
        $startb = strtotime($b_st['value']);
        if ($starta == $startb) { return 0; }
        return $starta > $startb ? -1 : 1;
      }
    });
    foreach($ret as $id => $meeting) {
      decision_sort_decisions($meeting->decisions);
    }

  }
  return $ret;
}

function decision_sort_decisions(&$decisions) {
  $ret = array();
  foreach($decisions as $decision) {
    $w = entity_metadata_wrapper('node', $decision);
    $original = $w->field_decision_number->value();
    $number = preg_replace('/\(.*\)/', '', $original);
    $number = preg_replace('/[^0-9\/.]/', '', $number);
    $number = preg_replace('/\./', '/', $number);
    $number = preg_replace('/\/\//', '/', $number);
    $number = preg_replace('/^\//', '', $number);
    $exploded = explode('/', $number);
    $exploded = array_reverse(array_filter($exploded));
    $sum = 0;
    foreach($exploded as $idx => $v) {
      $sum += $v * pow(10, $idx);
    }
    if(array_key_exists($sum, $ret)) {
      $dup =$ret[$sum];
      drupal_set_message('Duplicate decision number:' . $original . ':' . $number . ':' . $dup->nid . ':' . $decision->nid, 'error');
    }
    $ret[$sum] = $decision;
  }
  ksort($ret);
  $decisions = $ret;
}