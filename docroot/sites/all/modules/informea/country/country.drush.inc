<?php
/**
 * Implementation of hook_drush_command().
 *
 * @return
 *   An associative array describing available command(s).
 */
function country_drush_command() {
  $items = array();

  $items['country_import'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'description' => 'Imports data from country.json.',
    'examples' => array(
      'drush country_import' => 'Imports data from country.json.'
    ),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * @return
 *   A string with the help text for the command.
 */
function country_drush_help() {
  return dt('Imports data from country.json.');
}

/**
 * Imports data from country.json.
 *
 * @return
 *   Nothing.
 */
function drush_country_import() {
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
