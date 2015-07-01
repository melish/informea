<?php

/**
 * @file
 */

/**
 * Implements hook_drush_command().
 */
function informea_drush_command() {
  $items = array();
  $items['informea-sync-production'] = array(
    'description' => "Devify local installation",
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
  );
  $items['informea-cache-warm'] = array(
    'description' => "Warm the cache",
    'options' => array(
      'prefix' => 'URL prefix to append to the URLs',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );
  return $items;
}

function drush_informea_sync_production() {
  if (drush_confirm('Start to import the production database here?')) {
    drush_invoke_process('@self', 'sql-drop', array(), array('yes' => TRUE));
    drush_invoke_process('@self', 'sql-sync', array('@prod', '@self'), array('yes' => TRUE));
    drush_invoke_process('@self', 'devify', array(), array('yes' => TRUE));
  }
}


function drush_informea_cache_warm() {
  $prefix = drush_get_option('prefix', 'http://www.informea.org/');
  $output = array();

  // Treaties
  $rows = db_select('field_data_field_odata_identifier')->fields(NULL, array('field_odata_identifier_value'))->execute()->fetchCol();
  $output[] = $prefix . 'treaties';
  foreach($rows as $row) {
    $output[] = $prefix . 'treaties/' . $row;
    $output[] = $prefix . 'treaties/'. $row . '/protocols';
    $output[] = $prefix . 'treaties/'. $row . '/text';
    $output[] = $prefix . 'treaties/'. $row . '/decisions';
    $output[] = $prefix . 'treaties/'. $row . '/parties';
    $output[] = $prefix . 'treaties/'. $row . '/national-reports';
    $output[] = $prefix . 'treaties/'. $row . '/action-plans';
  }

  // Countries
  $output[] = $prefix . 'countries';
  $rows = db_select('field_data_field_country_iso2')->fields(NULL, array('field_country_iso2_value'))->execute()->fetchCol();
  foreach($rows as $row) {
    $output[] = $prefix . 'countries/' . $row;
    $output[] = $prefix . 'countries/' . $row . '/parties';
    $output[] = $prefix . 'countries/' . $row . '/action-plans';
    $output[] = $prefix . 'countries/' . $row . '/national-reports';
  }
  print implode("\n", $output);
  print "\n";
}
