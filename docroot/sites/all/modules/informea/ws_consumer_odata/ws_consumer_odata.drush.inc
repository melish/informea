<?php

function ws_consumer_odata_drush_command() {
  return array(
    'ws-consumer-delete-nodes' => array(
      'description' => 'Map taxonomies from Ecolex keywords and GEG into InforMEA',
      'arguments' => array(
        'treaty_odata_identifier' => 'Treaty OData identifier',
        'content_type' => 'Drupal content type'
      ),
      'required-arguments' => 2,
      'options' => array(
        'test' => 'Validate the terms from CSV. Errors are printed in console',
      )
    ),
  );
}

function drush_ws_consumer_odata_ws_consumer_delete_nodes($content_type, $treaty_odata_identifier) {
  if ($treaty = treaty_load_by_odata_name($treaty_odata_identifier)) {
    $q = new EntityFieldQuery();
    $q->entityCondition('bundle', $content_type);
    $q->fieldCondition('field_treaty', 'target_id', $treaty->nid);
    $rows = $q->execute();
    if (!empty($rows['node'])) {
      $nids = array_keys($rows['node']);
      drush_log('Deleting ' . count($nids) . ' nodes of type: ' . $content_type, 'status');
      node_delete_multiple($nids);
    }
  }
  else {
    drush_set_error('Cannot find treaty: ' . $treaty_odata_identifier);
  }
}
