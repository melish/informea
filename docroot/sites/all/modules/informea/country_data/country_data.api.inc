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
  return array('acceptance', 'accession', 'approval', 'continuation', 'ratification', 'succession', 'party');
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
  // Look first into the 'roles' property to check for data there
  $ret = country_data_get_treaty_focal_points_by_role($id_country, $id_treaty);
  if (!empty($ret)) {
    return $ret;
  }

  // Fallback to old method
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

function country_data_get_treaty_focal_points_by_role($id_country, $id_treaty) {
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'field_collection_item')
    ->propertyCondition('field_name', 'field_contact_roles')
    ->fieldCondition('field_contact_treaty', 'target_id', $id_treaty)
    ->execute();
  if (empty($result['field_collection_item'])) {
    return array();
  }
  $children = array_keys($result['field_collection_item']);

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'contact_person')
    ->fieldCondition('field_contact_roles', 'value', $children, 'IN')
    ->fieldCondition('field_country', 'target_id', $id_country);
  $result = $query->execute();
  if (empty($result['node'])) {
    return array();
  }

  $contacts = node_load_multiple(array_keys($result['node']));
  country_data_sort_contacts_by_role($contacts);
  return $contacts;
}

/**
 * Order the contacts by their role. Depends on terms position inside taxonomy contact_roles
 *
 * @param array $contacts
 */
function country_data_sort_contacts_by_role(&$contacts) {
  foreach($contacts as $contact) {
    $w = entity_metadata_wrapper('node', $contact);
    $roles = $w->field_contact_roles->value();
    $position_min = 9999;
    // Find the role with the lowest term weight (order inside the taxonomy)
    foreach ($roles as $role) {
      $iw = entity_metadata_wrapper('field_collection_item', $role);
      $role_term = $iw->field_contact_role->value();
      if ($role_term->weight < $position_min) {
        $position_min = $role_term->weight;
      }
    }
    $contact->position = $position_min;
  }
  uasort($contacts, function($a, $b) { return $a->position > $b->position; });
}


function country_data_render_focal_points($rows, $treaty) {
  $nfp_rows = array();
  foreach ($rows as $row) {
    $row->roles = array();
    $wrapper = entity_metadata_wrapper('node', $row);
    // Compute the roles property
    $roles_raw = $wrapper->field_contact_roles->value();
    foreach($roles_raw as $role_raw) {
      $w = entity_metadata_wrapper('field_collection_item', $role_raw);
      $tr = $w->field_contact_treaty->value();
      if ($tr->nid == $treaty->nid) {
        $role = $w->field_contact_role->value();
        $tw = entity_metadata_wrapper('taxonomy_term', $role->tid);
        $row->roles[] = $tw->label();
      }
    }

    $nfp_rows[] = array(
      'data' => theme('country_data_contact_person', array('contact_person' => $row, 'treaty' => $treaty)),
      'class' => array('list-group-item'),
    );
  }
  return array(
    '#theme' => 'item_list',  '#attributes' => array('class' => array('list-group')),
    '#items' => $nfp_rows,
  );
}
