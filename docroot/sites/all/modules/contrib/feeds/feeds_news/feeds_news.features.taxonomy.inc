<?php
/**
 * @file
 * feeds_news.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function feeds_news_taxonomy_default_vocabularies() {
  return array(
    'mea_topic' => array(
      'name' => 'MEA Topic',
      'machine_name' => 'mea_topic',
      'description' => 'Biological diversity, Chemicals etc.',
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
    ),
  );
}
