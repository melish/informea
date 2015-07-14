<?php
$query = new EntityFieldQuery();

$query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'treaty_article')
  ->propertyCondition('status', NODE_PUBLISHED);

$result = $query->execute();

if (isset($result['node'])) {
  $nids = array_keys($result['node']);
  $nodes = entity_load('node', $nids);

  foreach ($nodes as $node) {
    $wrapper = entity_metadata_wrapper('node', $node);

    $nid = $wrapper->getIdentifier();
    $treaty_id = $wrapper->field_treaty->value()[0]->vid;
    $weight = $wrapper->field_sorting_order->value();

    $query = db_select('draggableviews_structure', 'd')
      ->condition('d.entity_id', $nid)
      ->fields('d', array('entity_id'));

    $result = $query->execute()->fetchAllKeyed();

    if (!empty($result)) {
      $entity_id = array_keys($result)[0];

      db_update('draggableviews_structure')
        ->fields(array(
          'weight' => $weight,
        ))
        ->condition('entity_id', $nid)
        ->execute();
    } else {
      db_insert('draggableviews_structure')
        ->fields(array(
          'view_name' => 'treaties_reorder',
          'view_display' => 'page_articles',
          'args' => sprintf('{"field_treaty_target_id":"%d"}', $treaty_id),
          'entity_id' => $nid,
          'weight' => $weight,
          'parent' => 0
        ))
        ->execute();
    }
  }
}
