<?php
/**
 * Implementation of hook_drush_command().
 *
 * @return
 *   An associative array describing available command(s).
 */
function country_drush_command() {
  $items = array();

  $items['informea-country-import'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'description' => 'Imports data from country.json.',
    'examples' => array(
      'drush informea-country-import' => 'Imports data from country.json.'
    ),
  );

  $items['informea-country-update'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'description' => 'Update data from country.json into the existing nodes.',
    'examples' => array(
      'drush informea-country-update' => 'Updates Drupal nodes'
    ),
  );

  $items['informea-region-update-by-country'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'description' => 'Update data from field_region for all nodes.',
    'aliases' => array('imea-region-up'),
  );

  return $items;
}

/**
 * Imports data from country.json.
 */
function drush_country_informea_country_import() {
  $path = drupal_get_path('module', 'country') . DIRECTORY_SEPARATOR . 'country.json';
  $countries = json_decode(file_get_contents($path));
  $language = language_default()->language;

  foreach ($countries as $country) {
    $node = (object) array(
      'type' => 'country',
      'title' => $country->name,
      'language' => $language
    );
    node_object_prepare($node);
    $node->uid = 1;
    $node->field_country_iso2[LANGUAGE_NONE][0]['value'] = $country->code2l;
    $node->field_country_iso3[LANGUAGE_NONE][0]['value'] = $country->code3l;
    $node->field_country_official_name[$node->language][0]['value'] = '';
    $node = node_submit($node);
    node_save($node);
  }
  drush_log(dt('Country data succesfully imported'), 'ok');
}

/**
 * Updates data from country.json.
 */
function drush_country_informea_country_update() {
  $path = drupal_get_path('module', 'country') . DIRECTORY_SEPARATOR . 'country.json';
  $countries = json_decode(file_get_contents($path));
  foreach ($countries as $country) {
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'country')
                    ->fieldCondition('field_country_iso3', 'value', $country->code3l)
                    ->execute();
    if (isset($result['node'])) {
      $wrapper = entity_metadata_wrapper('node', key($result['node']));
      $wrapper->field_country_official_name->set($country->name_official);
      $wrapper->field_country_iso2->set($country->code2l);
      $wrapper->field_latitude->set($country->latitude);
      $wrapper->field_longitude->set($country->longitude);
      $wrapper->field_zoom->set($country->zoom);
      $wrapper->title->set($country->name);
      $wrapper->save();
    }
  }
  drush_log(dt('Country data succesfully updated'), 'ok');
}

/**
 * Update data from field_region for all nodes.
 */
function drush_country_informea_region_update_by_country() {
  $q = db_select('node', 'n');
  $q->innerJoin('field_data_field_region', 'r', 'n.nid = r.entity_id');
  $q->fields('n', array('nid'));
  $q->fields('r', array('field_region_tid', 'delta'));
  $q->condition('n.type', 'country');

  // TESTING ONLY, PLEASE REMOVE
  $q->condition('n.nid', '111');

  $countries = $q->execute()->fetchAll();

  foreach ($countries as $country) {
    $country_nid = $country->nid;
    $region_tid = $country->field_region_tid;
    $delta = $country->delta;

    $q = db_select('field_data_field_country','c');
    $q->fields('c', array('entity_id', 'bundle'));
    $q->condition('c.field_country_target_id', $country_nid);
    $nodes = $q->execute()->fetchAllKeyed();

    /*
     * First delete the current records in field_data_field_region table because
     * of the following scenario:
     *  - Country has 2 regions selected
     *  - User deletes one of them
     */
    db_delete('field_data_field_region')
      ->condition('entity_id', array_keys($nodes), 'IN')
      ->execute();
    die;

    foreach ($nodes as $node_id => $content_type) {
      try {
        db_insert('field_data_field_region')
          ->fields(array(
            'entity_type' => 'node',
            'bundle' => $content_type,
            'deleted' => 0,
            'entity_id' => $node_id,
            'revision_id' => $node_id,
            'language' => LANGUAGE_NONE,
            'delta' => $delta,
            'field_region_tid' => $region_tid,
          ))
          ->execute();
      }
      catch (PDOException $e) {
        drush_log(dt('ERROR(nid=@node_id): @error_msg', array('@node_id' => $node_id, '@error_msg' => $e->getMessage())), 'error');
      }
    }
    drush_log(dt('Successfully updated @non nodes.', array('@non' => count($nodes))), 'ok');
  }
}