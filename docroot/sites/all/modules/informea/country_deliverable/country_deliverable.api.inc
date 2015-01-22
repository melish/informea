<?php

function get_national_reports_by_treaty($id_country) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'national_report')
                  ->fieldCondition('field_country', 'target_id', $id_country)
                  ->execute();
  if (isset($result['node'])) {
    $rows = entity_load('node', array_keys($result['node']));
    $parties = array();
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $treaty = $wrapper->field_treaty->value()[0];
      if (!isset($parties[$treaty->nid])) {
        $parties[$treaty->nid] = $treaty;
      }
      else {
        $treaty =& $parties[$treaty->nid];
      }
      if (!isset($treaty->national_reports)) {
        $treaty->national_reports = array();
      }
      $treaty->national_reports[] = $row;
    }
    uasort($parties, function($a, $b) { return strcmp($a->title, $b->title); });
    // Sort the reports by date
    foreach($parties as &$party) {
      uasort($party->national_reports, function($a, $b) {
        $wa = entity_metadata_wrapper('node', $a);
        $wb = entity_metadata_wrapper('node', $b);
        return $wa->field_report_submission_date->value() < $wb->field_report_submission_date->value();
      });
    }
    return $parties;
  }
  return array();
}

function get_action_plans_by_treaty($id_country) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'action_plan')
                  ->fieldCondition('field_country', 'target_id', $id_country)
                  ->execute();
  if (isset($result['node'])) {
    $rows = entity_load('node', array_keys($result['node']));
    $parties = array();
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $treaty = $wrapper->field_treaty->value()[0];
      if (!isset($parties[$treaty->nid])) {
        $parties[$treaty->nid] = $treaty;
      }
      else {
        $treaty =& $parties[$treaty->nid];
      }
      if (!isset($treaty->action_plans)) {
        $treaty->action_plans = array();
      }
      $treaty->action_plans[] = $row;
    }
    uasort($parties, function($a, $b) { return strcmp($a->title, $b->title); });
    // Sort the plans by date
    foreach($parties as &$party) {
      uasort($party->action_plans, function($a, $b) {
        $wa = entity_metadata_wrapper('node', $a);
        $wb = entity_metadata_wrapper('node', $b);
        return $wa->field_report_submission_date->value() < $wb->field_report_submission_date->value();
      });
    }
    return $parties;
  }
  return array();
}