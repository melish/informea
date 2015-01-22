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
