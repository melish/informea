<?php
/**
 * @file
 * thesaurus.drush.inc
 */

/**
 * Implements hook_drush_command().
 */
function thesaurus_drush_command() {
  $items = array();

  $items['informea-thesaurus-sync'] = array(
    'drupal dependencies' => array('easyrdf'),
    'description' => 'Updates InforMEA thesaurus.',
    'aliases' => array('imea-tu')
  );

  return $items;
}

function drush_thesaurus_informea_thesaurus_sync() {
  thesaurus_informea_sync_vocbench();
  echo "Synchronisation finished ...\n";
}