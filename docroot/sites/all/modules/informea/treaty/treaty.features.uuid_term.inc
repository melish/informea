<?php
/**
 * @file
 * treaty.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function treaty_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Latin America and the Caribbean',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 3,
    'uuid' => '35efe0fc-d3d0-40f2-85eb-3e35fc7bee27',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'geographical_regions',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 43,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875718,
          'changed' => 1408875718,
        ),
      ),
    ),
    'parent' => array(
      0 => '85410461-118e-4303-98d7-43ae78b2f8ba',
    ),
  );
  $terms[] = array(
    'name' => 'Europe',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 2,
    'uuid' => '435b3a56-186f-47b6-a14f-203a1533f0f9',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'geographical_regions',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 42,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875687,
          'changed' => 1408875687,
        ),
      ),
    ),
    'parent' => array(
      0 => '85410461-118e-4303-98d7-43ae78b2f8ba',
    ),
  );
  $terms[] = array(
    'name' => 'Asia and the Pacific',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 1,
    'uuid' => '4defe430-d212-4808-a420-c47e0cd3a941',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'geographical_regions',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 41,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875677,
          'changed' => 1408875677,
        ),
      ),
    ),
    'parent' => array(
      0 => '85410461-118e-4303-98d7-43ae78b2f8ba',
    ),
  );
  $terms[] = array(
    'name' => 'West Asia',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 5,
    'uuid' => '4fe67bfc-8587-4c61-8548-ab1bbf23236a',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'geographical_regions',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 45,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875739,
          'changed' => 1408875739,
        ),
      ),
    ),
    'parent' => array(
      0 => '85410461-118e-4303-98d7-43ae78b2f8ba',
    ),
  );
  $terms[] = array(
    'name' => 'Africa',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '522168ed-71d4-4f06-9ac7-140553ac402b',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'geographical_regions',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 40,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875660,
          'changed' => 1408875660,
        ),
      ),
    ),
    'parent' => array(
      0 => '85410461-118e-4303-98d7-43ae78b2f8ba',
    ),
  );
  $terms[] = array(
    'name' => 'Global',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 6,
    'uuid' => '85410461-118e-4303-98d7-43ae78b2f8ba',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'geographical_regions',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 39,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875654,
          'changed' => 1408875654,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'North America',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 4,
    'uuid' => 'ff9c779b-0017-48a8-80fb-9271b4a724c7',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'geographical_regions',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 44,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875732,
          'changed' => 1408875732,
        ),
      ),
    ),
    'parent' => array(
      0 => '85410461-118e-4303-98d7-43ae78b2f8ba',
    ),
  );
  return $terms;
}
