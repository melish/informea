<?php
/**
 * @file
 * country_deliverable.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function country_deliverable_taxonomy_default_vocabularies() {
  return array(
    'action_plan_type' => array(
      'name' => 'Action plan type',
      'machine_name' => 'action_plan_type',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 1,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
      'tes' => array(
        'enable' => FALSE,
      ),
    ),
  );
}
