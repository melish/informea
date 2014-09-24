<?php

/**
 * @file
 *   Drush support for node_export.
 */

/**
 * Implements hook_drush_command().
 */
function ws_consumer_drush_command() {
  $items = array();
  $items['update-ratification'] = array(
    'description' => 'Update treaty ratification data from UN treaty database, if has such information',
    'arguments' => array(
      'treaty' => 'Treaty odata_identifier to update for specific treaty. Use "all" for all treaties',
    ),
    'examples' => array(
      'drush update_ratification cbd' => 'Update ratification for CBD',
      'drush update_ratification all' => 'Update ratification for all treaties',
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function ws_consumer_drush_help() {
  return dt('Update ratification status for a specific treaty or all treaties');
}

function drush_ws_consumer_update_ratification() {
  $target = func_get_args();
  if (empty($target)) {
      drush_log(dt('You must specify what treaty to update'), 'error');
      return;
  }
  $target = $target[0];
  if ($target != 'all') {
    ws_consumer_update_treaty_ratification_odata_name($target);
  }
  else {
    ws_consumer_update_treaties_ratification();
  }
}

/**
 * Implements shell completion.
 */
function ws_consumer_update_ratification_complete() {
  return array('all');
}
