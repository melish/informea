<?php

function treaty_url_context($path) {
  $path = preg_replace('/([A-Za-z]{2})?\/?treaties\/[A-Za-z\-]*\/?/', '', $path);
  $parts = explode('/', $path);
  return $parts[0];
}

function treaty_load_by_odata_name($odata_name) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'treaty')
                  ->fieldCondition('field_odata_identifier', 'value', $odata_name)
                  ->execute();
  if (!empty($result['node'])) {
    return node_load(current($result['node'])->nid);
  }
  return FALSE;
}

function treaty_get_child_protocols($id_treaty) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'treaty')
                  ->fieldCondition('field_parent_treaty', 'target_id', $id_treaty)
                  ->execute();
  if (!empty($result['node'])) {
    return node_load_multiple(array_keys($result['node']));
  }
  return array();
}

function treaty_get_treaties() {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'treaty')
                  ->fieldOrderBy('title_field', 'value')
                  ->execute();
  if (!empty($result['node'])) {
    $rows = node_load_multiple(array_keys($result['node']));
    return $rows;
  }
  return array();
}

function treaty_get_treaties_as_select_options() {
  $nodes = treaty_get_treaties();
  $rows = array();
  foreach ($nodes as $nid => $node) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $rows[$wrapper->field_odata_identifier->value()] = $wrapper->title_field->value();
  }
  return $rows;
}
