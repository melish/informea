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
    $rows = $result['node'];
    $fields = field_info_instances('node', 'decision');
    field_attach_load('node', $rows, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_meeting']['field_id']));
    field_attach_load('node', $rows, FIELD_LOAD_CURRENT, array('field_id' => $fields['title_field']['field_id']));

    foreach ($rows as $row) {
      $meeting_id = $row->field_meeting[LANGUAGE_NONE][0]['target_id'];
      $ret[$meeting_id] = node_load($meeting_id);
    }
    foreach ($rows as $row) {
      $meeting_id = $row->field_meeting[LANGUAGE_NONE][0]['target_id'];
      $meeting = $ret[$meeting_id];
      $meeting->decisions[] = $row;
    }
  }
  return $ret;
}
