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
