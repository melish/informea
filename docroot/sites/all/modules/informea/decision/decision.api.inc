<?php

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
  return t('n/a');
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
    $odata_identifier = treaty_get_odata_identifier($id_treaty);
    if ($odata_identifier != 'cites') {
      $decisions = $result['node'];
      $fields = field_info_instances('node', 'decision');
      field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_meeting']['field_id']));
      field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_number']['field_id']));
      field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_status']['field_id']));
      field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['title_field']['field_id']));
      foreach ($decisions as $decision) {
        $dw = entity_metadata_wrapper('node', $decision);
        if ($meeting = $dw->field_meeting->value()) {
          $meeting->decisions = array();
          $mw = entity_metadata_wrapper('node', $meeting);
          $type = $mw->field_event_type->value();
          if (($type && strtolower($type->name_original) == 'cop')) {
            $ret[$mw->getIdentifier()] = $meeting;
          }
        }
      }
      // Remove non-active decisions
      array_filter($decisions, function ($d) {
        $wd = entity_metadata_wrapper('node', $d);
        $status = $wd->field_decision_status->value();
        return in_array($status->name_original, array(
          'active',
          'adopted',
          'amended'
        ));
      });

      foreach ($decisions as $decision) {
        $dw = entity_metadata_wrapper('node', $decision);
        if ($meeting = $dw->field_meeting->value()) {
          $meeting_id = $decision->field_meeting[LANGUAGE_NONE][0]['target_id'];
          if (array_key_exists($meeting_id, $ret)) {
            $meeting = $ret[$meeting_id];
            $meeting->decisions[] = $decision;
          }
        }
      }
      uasort($ret, function ($a, $b) {
        $wa = entity_metadata_wrapper('node', $a);
        $wb = entity_metadata_wrapper('node', $b);
        $a_st = $wa->event_calendar_date->value();
        $b_st = $wb->event_calendar_date->value();
        if (empty($a_st)) {
          return 1;
        }
        else if (empty($b_st)) {
          return -1;
        }
        else {
          $starta = strtotime($a_st['value']);
          $startb = strtotime($b_st['value']);
          if ($starta == $startb) {
            return 0;
          }
          return $starta > $startb ? -1 : 1;
        }
      });
    }
    else {
      $decisions = $result['node'];
      $fields = field_info_instances('node', 'decision');
      field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_meeting']['field_id']));
      field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_number']['field_id']));
      field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_status']['field_id']));
      field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['title_field']['field_id']));
      $sorted_decisions = array();
      $resolutions = array();
      foreach ($decisions as $decision) {
        $dw = entity_metadata_wrapper('node', $decision->nid);
        $type = $dw->field_decision_type->value();
        if ($type->name_original == 'decision') {
          $sorted_decisions[] = node_load($decision->nid);
        }
        else {
          $resolutions[] = node_load($decision->nid);
        }
      }
      return array(
        'decisions' => $sorted_decisions,
        'resolutions' => $resolutions
      );
    }
  }
  return $ret;
}
