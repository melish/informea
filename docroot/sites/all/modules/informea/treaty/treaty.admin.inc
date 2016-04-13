<?php

/**
 * Replace entityreference callback to filter the data for
 */
function informea_entityreference_treaty_article_autocomplete_callback($type, $field_name, $entity_type, $bundle_name, $entity_id = '', $string = '') {
  global $user;

  /*
   * SELECT a.nid, CONCAT(SUBSTR(c.title, 1, 16), '... - ', a.title) FROM node a
   * INNER JOIN field_data_field_treaty b ON (a.nid = b.entity_id AND b.bundle = 'treaty_article')
   * INNER JOIN node c ON b.field_treaty_target_id = c.nid
   * WHERE a.`type` = 'treaty_article'
   * AND b.field_treaty_target_id IN (255)
   * AND a.title LIKE '%ar%'
   */
  $q = db_select('node', 'a')->fields('a', array('nid'));
  $q->innerJoin('field_data_field_treaty', 'b', "(a.nid = b.entity_id AND b.bundle = 'treaty_article')");
  $q->innerJoin('node', 'c', 'b.field_treaty_target_id = c.nid');
  $q->condition('a.type', 'treaty_article');
  $q->condition('a.title', '%' . $string . '%', 'LIKE');
  $q->addExpression("CONCAT(SUBSTR(c.title, 1, 16), '... - ', a.title)", 'label');
  if ($treaties = informea_user_get_assigned_treaties($user)) {
    $q->condition('b.field_treaty_target_id', $treaties, 'IN');
  }
  $q->range(0, 10);

  $matches = array();
  foreach ($q->execute()->fetchAllAssoc('nid') as $nid => $row) {
    $key = "{$row->label} ($nid)";
    // Strip things like starting/trailing white spaces, line breaks and tags.
    $key = preg_replace('/\s\s+/', ' ', str_replace("\n", '', trim(decode_entities(strip_tags($key)))));
    // Names containing commas or quotes must be wrapped in quotes.
    if (strpos($key, ',') !== FALSE || strpos($key, '"') !== FALSE) {
      $key = '"' . str_replace('"', '""', $key) . '"';
    }
    $matches[$key] = '<div class="reference-autocomplete">' . $row->label . '</div>';
  }
  drupal_json_output($matches);
}
