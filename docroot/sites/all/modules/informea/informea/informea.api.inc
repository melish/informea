<?php

/**
 * Map existing ecolex terms to InforMEA glossary.
 *
 * @param array $ecolex_terms
 *   Array of ecolex term names
 *
 * @return array
 *   Array of InforMEA terms keyed by tid
 */
function informea_map_ecolex_terms($ecolex_terms) {
  $ret = array();
  // mapped_informea_keywords
  $t = array();
  foreach($ecolex_terms as $ecolex_term) {
    $t += taxonomy_get_term_by_name($ecolex_term, 'keywords');
    $t += taxonomy_get_term_by_name($ecolex_term, 'thesaurus_ecolex');
  }

  $query = new EntityFieldQuery();
  $r1 = $query->entityCondition('entity_type', 'taxonomy_term')
    ->entityCondition('bundle', 'thesaurus_informea')
    ->fieldCondition('field_keywords', 'tid', array_keys($t))
    ->execute();
  if (isset($r1['taxonomy_term'])) {
    $ret = array_replace($ret, taxonomy_term_load_multiple(array_keys($r1['taxonomy_term'])));
  }

  $r2 = $query->entityCondition('entity_type', 'taxonomy_term')
    ->entityCondition('bundle', 'thesaurus_informea')
    ->fieldCondition('field_thesaurus_map_ecolex', 'tid', array_keys($t))
    ->execute();
  if (isset($r2['taxonomy_term'])) {
    $ret = array_replace($ret, taxonomy_term_load_multiple(array_keys($r2['taxonomy_term'])));
  }
  return $ret;
}
