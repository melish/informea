<?php
/**
 * @file
 * country_data.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function country_data_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Acceptance',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '0f9f9a0e-8672-4f58-af0d-112faac0916e',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'party_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 6,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874536,
          'changed' => 1408874536,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Ratified',
    'description' => '<p>Party ratified the treaty/convention/protocol</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '5ac4ca8e-04ed-4d08-bfab-ce21d3ecd4ec',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'party_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 4,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874501,
          'changed' => 1408874501,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Accession',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '80e84c3f-9f2a-4f6d-91b6-24721a8c0d60',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'party_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 5,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874525,
          'changed' => 1408874525,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Approval',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'd3b2ed0e-2964-4fdd-b9a5-55efce0c654a',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'party_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 7,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874547,
          'changed' => 1408874547,
        ),
      ),
    ),
  );
  return $terms;
}
