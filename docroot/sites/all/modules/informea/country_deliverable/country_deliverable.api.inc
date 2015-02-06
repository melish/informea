<?php

function country_deliverable_get_country_national_reports($id_country) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'national_report')
                  ->fieldCondition('field_country', 'target_id', $id_country)
                  ->execute();
  if (isset($result['node'])) {
    return node_load_multiple(array_keys($result['node']));
  }
  return array();
}

function country_deliverable_get_country_action_plans($id_country) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'action_plan')
                  ->fieldCondition('field_country', 'target_id', $id_country)
                  ->execute();
  if (isset($result['node'])) {
    return node_load_multiple(array_keys($result['node']));
  }
  return array();
}

function country_deliverable_get_treaty_national_reports($id_treaty) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'national_report')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->execute();
  if (isset($result['node'])) {
    return node_load_multiple(array_keys($result['node']));
  }
  return array();
}

function country_deliverable_get_treaty_action_plans($id_treaty) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'action_plan')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->execute();
  if (isset($result['node'])) {
    return node_load_multiple(array_keys($result['node']));
  }
  return array();
}

function country_deliverable_national_reports_group_by_treaty($id_country) {
  $rows = country_deliverable_get_country_national_reports($id_country);
  if (!empty($rows)) {
    $parties = array();
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $treaty  = $wrapper->field_treaty->value()[0];
      $parties[$treaty->nid] = $treaty;
    }
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $treaty = $wrapper->field_treaty->value()[0];
      $treaty = $parties[$treaty->nid];
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

function country_deliverable_action_plans_group_by_treaty($id_country) {
  $rows = country_deliverable_get_country_action_plans($id_country);
  if (!empty($rows)) {
    $parties = array();
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $treaty  = $wrapper->field_treaty->value()[0];
      $parties[$treaty->nid] = $treaty;
    }
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $treaty = $wrapper->field_treaty->value()[0];
      $treaty = $parties[$treaty->nid];
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

function country_deliverable_count_treaty_national_reports($id_treaty) {
  return EdwCacheDomain::cache_get_array('country_deliverable', __FUNCTION__, function($id_treaty) {
    $query  = new EntityFieldQuery();
    return $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'national_report')
      ->fieldCondition('field_treaty', 'target_id', $id_treaty)
      ->count()
      ->execute();
  }, $id_treaty);
}

function country_deliverable_count_treaty_action_plans($id_treaty) {
  return EdwCacheDomain::cache_get_array('country_deliverable', __FUNCTION__, function($id_treaty) {
    $query  = new EntityFieldQuery();
    return $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'action_plan')
      ->fieldCondition('field_treaty', 'target_id', $id_treaty)
      ->count()
      ->execute();
  }, $id_treaty);
}

function country_deliverable_national_reports_group_by_country($id_treaty) {
  $rows = country_deliverable_get_treaty_national_reports($id_treaty);
  if (!empty($rows)) {
    $parties = array();
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $country  = $wrapper->field_country->value()[0];
      $parties[$country->nid] = $country;
    }
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $country = $wrapper->field_country->value()[0];
      $country = $parties[$country->nid];
      $country->national_reports[] = $row;
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

function country_deliverable_action_plans_group_by_country($id_treaty) {
  $rows = country_deliverable_get_treaty_action_plans($id_treaty);
  if (!empty($rows)) {
    $parties = array();
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $country  = $wrapper->field_country->value()[0];
      $parties[$country->nid] = $country;
    }
    foreach ($rows as $row) {
      $wrapper = entity_metadata_wrapper('node', $row);
      $country = $wrapper->field_country->value()[0];
      $country = $parties[$country->nid];
      $country->action_plans[] = $row;
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

function country_deliverable_get_reporting_obligation_cycles($id_treaty) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'reporting_obligation_cycle')
    ->fieldCondition('field_treaty', 'target_id', $id_treaty)
    ->execute();
  if (isset($result['node'])) {
    return node_load_multiple(array_keys($result['node']));
  }
  return array();
}
