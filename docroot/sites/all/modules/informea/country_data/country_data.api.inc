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

function country_data_treaty_get_membership($id_treaty) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'member_party')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->propertyOrderBy('title')
                  ->execute();
  if (isset($result['node'])) {
    return entity_load('node', array_keys($result['node']));
  }
  return array();
}

function country_data_get_treaty_focal_points($id_country, $id_treaty) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'contact_person')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->fieldCondition('field_country', 'target_id', $id_country)
                  ->propertyOrderBy('title')
                  ->execute();
  if (isset($result['node'])) {
    return entity_load('node', array_keys($result['node']));
  }
  return array();
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
    '#theme' => 'item_list',  '#attributes' => array('class' => array('nav', 'nav-pills', 'nav-stacked')),
    '#items' => $nfp_rows,
  );
}