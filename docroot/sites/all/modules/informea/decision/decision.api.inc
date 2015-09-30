<?php

/**
 * Decisions count for treaty.
 *
 * @param $id_treaty
 *
 * @return integer
 *   Number of decisions or -1 if n/a
 */
function decision_count_treaty_decisions($id_treaty) {
  if (treaty_can_have_decisions($id_treaty)) {
    return EdwCacheDomain::cache_get_array('decision', __FUNCTION__, function ($id_treaty) {
      $query = new EntityFieldQuery();
      return $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'decision')
        ->fieldCondition('field_treaty', 'target_id', $id_treaty)
        ->count()
        ->execute();
    }, $id_treaty);
  }
  return -1;
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
  // Get all the meetings with decisions
  $q = db_select('field_data_field_treaty', 'a')->fields('a', array('entity_id'));
  $q->innerJoin('field_data_field_meeting', 'b', 'a.entity_id = b.field_meeting_target_id');
  $q->innerJoin('field_data_field_treaty', 'c', 'a.field_treaty_target_id = c.field_treaty_target_id');
  $q->innerJoin('field_data_event_calendar_date', 'd', 'a.entity_id = d.entity_id ');
  $q->condition('a.field_treaty_target_id', $id_treaty);
  $q->condition('a.bundle', 'event_calendar');
  $q->condition('c.bundle', 'decision');
  $q->groupBy('a.entity_id');
  $q->orderBy('d.event_calendar_date_value', 'DESC');
  $meetings = $q->execute()->fetchCol();
  $meetings = node_load_multiple($meetings);

  $allowed_status = array(840 /* active */, 846 /* adopted */, 845 /* amended */);
  $fields = field_info_instances('node', 'decision');
  foreach ($meetings as $meeting) {
    // Get the decisions for each meeting, ordered by draggable views.
    $q = db_select('field_data_field_meeting', 'a')->fields('a', array('entity_id'))->fields('n', array('title'));
    $q->join('node', 'n', "a.entity_id = n.nid AND n.type = 'decision'");
    $q->leftJoin('field_data_field_sorting_order', 'b', 'b.entity_id = a.entity_id');
    $q->condition('a.bundle', 'decision');
    $q->condition('a.field_meeting_target_id', $meeting->nid);
    $q->orderBy('b.field_sorting_order_value', 'ASC');
    $dids = $q->execute()->fetchAllKeyed();
    $decisions = array();
    foreach($dids as $key => $ob) {
      $decisions[$key] = (object)array('nid' => $key, 'vid' => NULL, 'type' => 'decision');
    }
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_number']['field_id']));
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_status']['field_id']));
    if ($id_treaty == 257 /* CITES */) {
      field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_type']['field_id']));
    }
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['title_field']['field_id']));
    // Remove non-active decisions
    array_filter($decisions, function ($d) use ($allowed_status) {
      $status = !empty($d->field_decision_status[LANGUAGE_NONE][0]['tid']) ? $d->field_decision_status[LANGUAGE_NONE][0]['tid'] : '';
      return in_array($status, $allowed_status);
    });
    foreach ($decisions as $decision) {
      $decision->title = $dids[$decision->nid];
    }
    $meeting->decisions = $decisions;
    $ret[$meeting->nid] = $meeting;
  }
  return $ret;
}
