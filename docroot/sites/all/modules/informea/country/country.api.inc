<?php

/**
 * Hook to alter country contextual menu links.
 *
 * @param array $contextual_menu
 *   Contains links
 * @param $node
 *   Node to build the menu for
 */
function hook_country_contextual_menu_alter(&$contextual_menu, $node) {
  $link = array(
    '#type' => 'link',
    '#title' => 'Sample sub-menu',
    '#href' => 'countries/',
    '#attributes' => array('class' => array('list-group-item')),
    '#options' => array( 'html' => TRUE ),
  );
  $contextual_menu[] = $link;
}

function country_url_context($path) {
  $path = preg_replace('/([A-Za-z]{2})?\/?countries\/[A-Za-z]{2}\/?/', '', $path);
  $parts = explode('/', $path);
  return $parts[0];
}

function country_load_by_iso2($iso2) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'country')
    ->fieldCondition('field_country_iso2', 'value', $iso2)
    ->execute();
  if (!empty($result['node'])) {
    $nid = current($result['node'])->nid;
    $node = node_load($nid);
    return $node;
  }
  return FALSE;
}

function country_load_by_iso3($iso3) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'country')
    ->fieldCondition('field_country_iso3', 'value', $iso3)
    ->execute();
  if (!empty($result['node'])) {
    $nid = current($result['node'])->nid;
    $node = node_load($nid);
    return $node;
  }
  return FALSE;
}


function country_get_by_name($name) {
  $name = strtolower($name);
  $countries = &drupal_static(__FUNCTION__);
  if(empty($countries)) {
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'country')
        ->execute();
    if (isset($result['node'])) {
      $rows = node_load_multiple(array_keys($result['node']));
      foreach ($rows as $row) {
        $wrapper = entity_metadata_wrapper('node', $row);
        $countries[strtolower($wrapper->label())] = $row;
        $official = $wrapper->field_country_official_name->value();
        if (!empty($official)) {
          $countries[strtolower($official)] = $row;
        }
      }
    }
  }
  if(array_key_exists($name, $countries)) {
    return $countries[$name];
  } else {
    if (array_key_exists($name, $countries)) {
      return $countries[$name];
    }
  }
  return FALSE;
}


function country_get_view_country_related_content($nid, $display) {
  $args = array($nid);
  $view = views_get_view('country_related_content');
  $view->set_display($display);
  $view->set_arguments($args);
  $view->get_total_rows = TRUE;
  $view->pre_execute();
  $view->execute();
  return $view;
}

function country_get_view_country_related_content_count($nid, $display) {
  $view = country_get_view_country_related_content($nid, $display);
  return $view->total_rows;
}


function country_get_treaty_focal_points($id_country, $id_treaty) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'contact_person')
      ->fieldCondition('field_treaty', 'target_id', $id_treaty)
      ->fieldCondition('field_country', 'target_id', $id_country)
      ->execute();
  if (isset($result['node'])) {
    $result_nids = array_keys($result['node']);
    $rows = entity_load('node', $result_nids);
    uasort($rows, function($a, $b) { return $a->title < $b->title; });
    return $rows;
  }
  return array();
}


function country_get_sites($id_country) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'geographical_site')
                  ->fieldCondition('field_country', 'target_id', $id_country)
                  ->execute();
  if (isset($result['node'])) {
    return entity_load('node', array_keys($result['node']));
  }
  return array();
}

function country_get_countries() {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'country')
                  ->propertyCondition('status', NODE_PUBLISHED)
                  ->fieldOrderBy('title_field', 'value')
                  ->execute();
  if (isset($result['node'])) {
    return entity_load('node', array_keys($result['node']));
  }
  return array();
}

function country_get_countries_select_options() {
  $nodes = country_get_countries();
  $countries = array();
  foreach ($nodes as $nid => $node) {
    $wrapper = entity_metadata_wrapper('node', $node);
    $countries[$wrapper->field_country_iso2->value()] = $wrapper->title_field->value();
  }
  return $countries;
}

function country_get_legislation_statistics($id_country = NULL, $type = 'legislation') {
  $query = db_select('node', 'n')
    ->fields('td', array('tid'))
    ->condition('n.status', 1)
    ->condition('n.type', $type)
    ->groupBy('td.tid');

  $query->addExpression('COUNT(td.vid)', 'term_count');
  $query->join('field_data_field_type_of_text', 'tt', 'n.nid = tt.entity_id');
  $query->join('taxonomy_term_data', 'td', 'tt.field_type_of_text_tid = td.tid');
  if ($id_country) {
    $query->join('field_data_field_country', 'c', 'n.nid = c.entity_id');
    $query->condition('c.field_country_target_id', $id_country);
  }
  $results = $query->execute()->fetchAllKeyed();

  arsort($results);
  $ret = array();
  foreach($results as $tid => $count) {
    $term = taxonomy_term_load($tid);
    $term->count = $count;
    $ret[] = $term;
  }
  return $ret;
}


function country_get_court_decisions_statistics($id_country = NULL) {
  return country_get_legislation_statistics($id_country, 'court_decisions');
}

function country_get_court_literature_statistics($id_country = NULL) {
  $query = db_select('node', 'n')
    ->fields('td', array('tid'))
    ->condition('n.status', 1)
    ->condition('n.type', 'literature')
    ->groupBy('td.tid');

  $query->addExpression('COUNT(td.vid)', 'term_count');
  $query->join('field_data_field_literature_type', 'tt', 'n.nid = tt.entity_id');
  $query->join('taxonomy_term_data', 'td', 'tt.field_literature_type_tid = td.tid');
  if ($id_country) {
    $query->join('field_data_field_country', 'c', 'n.nid = c.entity_id');
    $query->condition('c.field_country_target_id', $id_country);
  }
  $results = $query->execute()->fetchAllKeyed();

  arsort($results);
  $ret = array();
  foreach($results as $tid => $count) {
    $term = taxonomy_term_load($tid);
    $term->count = $count;
    $ret[] = $term;
  }
  return $ret;
}
