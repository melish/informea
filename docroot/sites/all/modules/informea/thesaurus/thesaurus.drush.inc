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
   * STEP 3: Delete actual tags
   */
  db_truncate('field_data_field_informea_tags')->execute();

  /*
   * STEP 4: Add new tags
   */
  foreach ($data as $row) {
    $old_term_name = $row['OLD TERM (INFORMEA.ORG/TERMS)'];
    if ($old_term_name) {
      drush_log("Remapping old term: " . $old_term_name, "ok");
      $q = db_select('thesaurus_term_mappings', 'a')->fields('a', array('entity_id', 'entity_id'));
      $q->condition('a.name', $old_term_name);
      $entities_ids = $q->execute()->fetchAllKeyed();

      $new_tids = array();
      for ($i = 1 ; $i < 7 ; $i++) {
        if($row[$i]) {
          $new_tid = thesaurus_term_get_tid_by_uri($row[$i], 'thesaurus_informea');
          if ($new_tid != NULL) {
            $new_tids[] = $new_tid;
          }
        }
      }

      foreach ($entities_ids as $eid) {
        foreach ($new_tids as $tid) {
          db_query("
INSERT INTO field_data_field_informea_tags (entity_type, bundle, deleted, entity_id, revision_id, language, delta, field_informea_tags_tid)
VALUES ('node', 'treaty', '0', :entity_id, :entity_id, 'und', IFNULL((SELECT MAX(delta)+1 as delta from field_data_field_informea_tags b where b.entity_id = :entity_id), 0), :term_id);
        ",
            array(
              ':entity_id' => $eid,
              ':term_id' => $tid,
            ));
        }
      }
    }
  }
}

