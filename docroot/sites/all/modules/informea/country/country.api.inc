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


function country_get_parties($id_country) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'member_party')
      ->fieldCondition('field_country', 'target_id', $id_country)
      ->execute();
  if (isset($result['node'])) {
    $result_nids = array_keys($result['node']);
    $parties = entity_load('node', $result_nids);
    uasort($parties, function($a, $b) { return $a->title < $b->title; });
    return $parties;
  }
  return array();
}

function country_get_view_country_related_content_count($nid, $display) {
  $view = country_get_view_country_related_content($nid, $display);
  return $view->total_rows;
}