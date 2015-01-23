<?php

function treaty_url_match_node($path) {
  if (arg(0, $path) == 'treaties') {
    if ($node = treaty_load_by_odata_name(arg(1, $path))) {
      return $node;
    }
  } else if(strlen(arg(0, $path)) == 2) { // Assume language prefix @todo enhance
    if (arg(1, $path) == 'treaties') {
      if ($node = treaty_load_by_odata_name(arg(2, $path))) {
        return $node;
      }
    }
  }
  return FALSE;
}

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

function treaty_get_treaty_text($id_treaty) {
  $query = new EntityFieldQuery();
  // Retrieve treaty articles
  $articles = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'treaty_article')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->fieldOrderBy('field_sorting_order', 'value')
                  ->execute();
  if (isset($articles['node'])) {
    $articles = node_load_multiple(array_keys($articles['node']));
    // Retrieve paragraphs for each article
    foreach ($articles as &$article) {
      $paragraphs = treaty_get_article_paragraphs($article->nid);
      $article->official_title = treaty_format_article_title($article);
      $article->paragraphs = $paragraphs;
    }
  }
  return $articles;
}

function treaty_get_article_paragraphs($id_article) {
  $query = new EntityFieldQuery();
  // Retrieve treaty articles
  $paragraphs = $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'treaty_paragraph')
                    ->fieldCondition('field_parent_treaty_article', 'target_id', $id_article)
                    ->fieldOrderBy('field_sorting_order', 'value')
                    ->execute();
  return isset($paragraphs['node']) ? node_load_multiple(array_keys($paragraphs['node'])) : array();
}

function treaty_format_article_title($article) {
  $w = entity_metadata_wrapper('node', $article);
  $number = '';
  $order = $w->field_official_order->value();
  if (!empty($order)) {
    $number = $order;
    if(substr($number, -1) !== '.') {
      $number .= '. ';
    }
  }
  return sprintf('%s %s', $number, $w->label());
}

function treaty_format_meeting_description($meeting) {
  $ret = '';
  $w = entity_metadata_wrapper('node', $meeting);
  $start = format_date(strtotime($w->event_calendar_date->value()['value']), 'short');
  $ret .= $start;
  $location = $w->field_location->value();
  if (!empty($location)) {
    $ret .= ', ' . $location;
  }
  if (!empty($meeting->decisions)) {
    $ret .= ' - ' . format_plural(count($meeting->decisions), 'one decision', '@count decisions');
  }
  return $ret;
}