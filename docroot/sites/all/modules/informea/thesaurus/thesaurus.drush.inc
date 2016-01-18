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

  $items['informea-thesaurus-migrate-tags'] = array(
    'drupal dependencies' => array('easyrdf', 'phpexcel'),
    'description' => 'Migrate terms from vocbench and fix field_informea_tags.',
  );

  return $items;
}

function drush_thesaurus_informea_thesaurus_sync() {
  thesaurus_informea_sync_vocbench();
  echo "Synchronisation finished ...\n";
}

function drush_thesaurus_informea_thesaurus_migrate_tags() {
  module_load_include('inc', 'phpexcel');

  $path = drupal_get_path('module', 'thesaurus') . '/data/informea-old-new-mappings.xlsx';

  $data = phpexcel_import($path)[0];

  if (!is_array($data)) {
    drush_log("We could not get the data from the excel file.", 'error');
    return;
  }
  $voc = taxonomy_vocabulary_machine_name_load('thesaurus_informea');

  /*
   * STEP 1: Delete all terms.
   */
  drush_log("Deleting all old terms", "ok");
  foreach (taxonomy_get_tree($voc->vid) as $term) {
    drush_log("Deleting term: " . $term->name, "ok");
    taxonomy_term_delete($term->tid);
  }

  /*
   * STEP 2: Synchronization with vocbench
   */
  drush_thesaurus_informea_thesaurus_sync();

  /*
   * STEP 3: Add new tags
   */
  foreach ($data as $row) {
    $old_tid = $row['OLD TERM (INFORMEA.ORG/TERMS)'];
    $new_tids = array();
    for ($i = 1 ; $i < 7 ; $i++) {
      if($row[$i]) {
        if (($term = thesaurus_term_load_by_uri($row[$i], 'thesaurus_informea')) != NULL) {
          $new_tids[] = $term;
        }
      }
      var_dump($new_tids);die;
    }
  }
}

