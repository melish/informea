<?php

function decision_count_treaty_decisions($id_treaty) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'decision')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->execute();
  return isset($result['node']) ? count($result['node']) : 0;
}
