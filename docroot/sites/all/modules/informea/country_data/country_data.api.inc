<?php

function country_data_country_get_parties($id_country) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'member_party')
                  ->fieldCondition('field_country', 'target_id', $id_country)
                  ->propertyOrderBy('title')
                  ->execute();
  if (isset($result['node'])) {
    $result_nids = array_keys($result['node']);
    $parties = entity_load('node', $result_nids);
    return $parties;
  }
  return array();
}

function country_data_get_allowed_membership_status() {
  return array('acceptance', 'accession', 'approval', 'continuation', 'ratification', 'succession');
}

function country_data_treaty_get_membership($id_treaty, $other = FALSE) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'member_party')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->propertyOrderBy('title')
                  ->execute();
  if (isset($result['node'])) {
    $allowed = country_data_get_allowed_membership_status();
    foreach ($result['node'] as $key => $row) {
      $w = entity_metadata_wrapper('node', $row->nid);
      $status = $w->field_party_status->value();
      $is_allowed = in_array(strtolower($status->name_original), $allowed);
      $unset_it = $other ? $is_allowed : !$is_allowed;
      if ($unset_it) {
        unset($result['node'][$key]);
      }
    }
    return entity_load('node', array_keys($result['node']));
  }
  return array();
}

function country_data_treaty_count_membership($id_treaty) {
  return EdwCacheDomain::cache_get_array('country_data', __FUNCTION__, function($id_treaty) {
    $query = new EntityFieldQuery();
    $count = 0;
    $rows = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'member_party')
      ->fieldCondition('field_treaty', 'target_id', $id_treaty)
      ->propertyOrderBy('title')
      ->execute();
    $allowed = country_data_get_allowed_membership_status();
    if (!empty($rows)) {
      foreach($rows['node'] as $row) {
        $w = entity_metadata_wrapper('node', $row->nid);
        $status = $w->field_party_status->value();
        if (in_array(strtolower($status->name_original), $allowed)) {
          $count++;
        }
      }
    }
    return $count;
  }, $id_treaty);
}

function country_data_get_treaty_focal_points($id_country, $id_treaty) {
  $q = db_select('node', 'a')->fields('a', array('nid'));
  $q->innerJoin('field_data_field_treaty', 'b', 'a.nid = b.entity_id AND a.vid = b.revision_id');
  $q->innerJoin('field_data_field_country', 'c', 'a.nid = c.entity_id AND a.vid = c.revision_id');
  $q->condition('a.type', 'contact_person');
  $q->condition('b.field_treaty_target_id', $id_treaty);
  $q->condition('c.field_country_target_id', $id_country);
  $q->orderBy('a.title');
  $rows = $q->execute()->fetchCol();
  return node_load_multiple($rows);
}


function country_data_render_focal_points($rows) {
  $nfp_rows = array();
  foreach ($rows as $row) {
    $nfp_rows[] = array(
      'data' => theme('country_data_contact_person', array('contact_person' => $row)),
      'class' => array('list-group-item'),
    );
  }
  return array(
    '#theme' => 'item_list',  '#attributes' => array('class' => array('list-group')),
    '#items' => $nfp_rows,
  );
}
