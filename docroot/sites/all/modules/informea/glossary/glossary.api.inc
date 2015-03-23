<?php


function glossary_informea_substantive_root_terms() {
  $ret = array();
  if ($voc = taxonomy_vocabulary_machine_name_load('thesaurus_informea')) {
    $tree = taxonomy_get_tree($voc->vid);
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'taxonomy_term');
    $query->entityCondition('bundle', 'thesaurus_informea');
    $query->fieldCondition('field_term_substantive', 'value', 1);
    $query->fieldOrderBy('name_field', 'value');
    if ($rows = $query->execute()) {
      $terms = $rows['taxonomy_term'];
      array_filter($terms, function($tid) use ($tree) {
        foreach ($tree as $row) {
          if ($row->tid == $tid && $row->depth == 0) {
            return TRUE;
          }
        }
        return FALSE;
      });
      $ret = entity_load('taxonomy_term', array_keys($terms));
    }
  }
  return $ret;
}

function glossary_informea_generic_terms() {
  $ret = array();
  if ($voc = taxonomy_vocabulary_machine_name_load('thesaurus_informea')) {
    $tree = taxonomy_get_tree($voc->vid);
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'taxonomy_term');
    $query->entityCondition('bundle', 'thesaurus_informea');
    $query->fieldCondition('field_term_substantive', 'value', 0);
    $query->fieldOrderBy('name_field', 'value');
    if ($rows = $query->execute()) {
      $terms = $rows['taxonomy_term'];
      $terms = array_filter($terms, function($tmeta) use ($tree) {
        foreach ($tree as $row) {
          if ($row->tid == $tmeta->tid && $row->depth == 0) {
            return TRUE;
          }
        }
        return FALSE;
      });
      // $ret = entity_load('taxonomy_term', array_keys($terms));
      // dpm($ret);
    }
  }
  return $ret;
}