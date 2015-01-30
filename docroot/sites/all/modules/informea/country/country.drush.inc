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
