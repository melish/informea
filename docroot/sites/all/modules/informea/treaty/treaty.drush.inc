<?php
/**
 * Implementation of hook_drush_command().
 *
 * @return
 *   An associative array describing available command(s).
 */
function treaty_drush_command() {
  $items = array();

  $items['treaty-fix-broken'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'description' => 'Fix broken treaty target_id in treaty articles',
    'examples' => array(
      'drush treaty-fix-broken' => 'Fix broken treaty target_id in treaty articles'
    ),
  );

  $items['treaty-check-double'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'description' => 'Check double treaty titles',
    'examples' => array(
      'drush treaty-check-double' => 'Check double treaty titles'
    ),
  );
  return $items;
}

/**
 * Check double treaty titles
 */
function drush_treaty_check_double() {
  $query = db_select('node', 'n');
  $query->fields('n', array('title'));
  $query->addExpression('COUNT(title)', 'total');
  $query->condition('n.type', 'treaty');
  $query->groupBy('n.title');
  $query->havingCondition('total', '1', '>');
  $titles = $query->execute()->fetchCol();

  foreach($titles as $title) {
    echo $title . "\n";
    $q = db_select('node', 'a');
    $q->fields('a', array('nid', 'status', 'language'));
    $q->condition('a.type', 'treaty');
    $q->condition('a.title', $title);
    $items = $q->execute()->fetchAll();
    foreach($items as $item){
      echo $item->nid .' '.$item->status  . ' ' . $item->language . "\n";
    }
  }
  drush_log(dt('Double treaty titles: ') . count($titles), 'ok');
}

/**
 * Fix broken treaty target_id in treaty articles
 */
function drush_treaty_fix_broken() {
  $fix_nid = 48205;
  $new_nid = 77747;
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', ['treaty_article', 'treaty_paragraph', 'decision', 'member_party'], 'in')
    ->fieldCondition('field_treaty', 'target_id', $fix_nid)
    ->execute();
  drush_log(dt('Found broken articles: ') . count($result['node']), 'ok');
  if (!$result['node']) {
    return;
  }
  $updated = 0;
  foreach($result['node'] as $row) {
    $node = node_load($row->nid);
    if (@$node->field_treaty['und'][0]['target_id'] == $fix_nid) {
      $node->field_treaty['und'][0]['target_id'] = $new_nid;
      node_save($node);
      $updated++;
    }
  }

  drush_log(dt('Fixed articles: ') . $updated, 'ok');
}
