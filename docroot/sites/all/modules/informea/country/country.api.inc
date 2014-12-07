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