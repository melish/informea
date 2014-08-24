<?php
/**
 * @file
 * meeting.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function meeting_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Tentative',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '09414ab1-f768-48e8-8e50-a48a7a3adacf',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_calendar_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 17,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875035,
          'changed' => 1408875035,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Nodate',
    'description' => '<p>No event set for this meeting</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '1bcad414-5730-48a6-b816-5a7174d096de',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_calendar_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 21,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875074,
          'changed' => 1408875074,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Workshop',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '2e51ba01-2d49-4285-b70d-aa0434de2229',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 28,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875195,
          'changed' => 1408875195,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'AdC',
    'description' => '<p>Advisory Committee meeting</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '2fad2a21-b9ce-45f2-a7d2-0da3d86b73e1',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 34,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875316,
          'changed' => 1408875316,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'STC',
    'description' => '<p>Standing Committee meeting</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '34657d8a-5f98-40a7-8c9d-e7ff648f7bb2',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 31,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875263,
          'changed' => 1408875263,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Negotiation',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '3f73bc98-ebc4-4237-aaee-fd2106fc0689',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 33,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875280,
          'changed' => 1408875280,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Technical',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '44b991c6-2514-4cf9-882b-2581145aaff9',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 32,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875274,
          'changed' => 1408875274,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Symposium',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '4a4bb483-1367-4bd7-a948-cc3efc48afc6',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 26,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875380,
          'changed' => 1408875380,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Postponed',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '581c6d17-8dd9-400c-96bd-66bb3cbeb1e7',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_calendar_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 19,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875047,
          'changed' => 1408875047,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Subsidiary',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '59283034-a0b8-4a84-9393-5811723e6b55',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 23,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875166,
          'changed' => 1408875166,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Official',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '611cfc8e-c081-4329-8170-a125bd692580',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_kind',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 14,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874677,
          'changed' => 1408874677,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Invitation',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '7259b665-b177-4034-a6fc-8b5b66792241',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_access',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 38,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875499,
          'changed' => 1408875499,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'MOP',
    'description' => '<p>Meeting of the parties</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '76ef62bc-3a9f-45dd-bc83-c881ebd6ccbe',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 3,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408873977,
          'changed' => 1408873977,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'TC',
    'description' => '<p>Technical Committee meeting</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '7d4d6a00-5cc8-41fc-9be5-9123f265eae0',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 36,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875401,
          'changed' => 1408875401,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'WG',
    'description' => '<p>&nbsp;Working group meeting</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '80709cb2-017a-45c1-a1ad-9924d86ae620',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 25,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875430,
          'changed' => 1408875430,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Weekly',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '9757c9fa-1200-40bf-b00a-4af2305e6346',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_repetition',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 8,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874605,
          'changed' => 1408874605,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Partner',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'a54136be-92fd-47f2-9b05-ad5c4ce9fbeb',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_kind',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 15,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874687,
          'changed' => 1408874687,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Conference',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'af528fd2-5009-4f7c-ba72-fc986e1d80b4',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 27,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875190,
          'changed' => 1408875190,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Every three years',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'b1c19af9-ece3-4a7d-9aaa-0fcd5079f858',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_repetition',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 12,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874645,
          'changed' => 1408874645,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Every four years',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'b50adebb-05e8-4e57-9c34-ae10b90934ed',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_repetition',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 13,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874650,
          'changed' => 1408874650,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Interest',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'b5ceac6b-fd7f-4fbb-b352-079f612ff68f',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_kind',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 16,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874694,
          'changed' => 1408874694,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Monthly',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'bd6d0d9f-63ce-45f9-90f2-ee3a788c356c',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_repetition',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 9,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874626,
          'changed' => 1408874626,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Public',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'be086561-1209-44f0-874f-cdfa10fbc4be',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_access',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 37,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875493,
          'changed' => 1408875493,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Every two years',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'c70e99ce-eadf-422b-ad64-15d475848dd4',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_repetition',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 11,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874641,
          'changed' => 1408874641,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Confirmed',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'c9e79055-8a44-4e98-88b1-f3474ee6e87f',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_calendar_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 18,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875040,
          'changed' => 1408875040,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'COP',
    'description' => '<p>Conference of the parties</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'ced9ec32-9ed7-4ba1-bc33-9051d96d41aa',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 2,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408873963,
          'changed' => 1408873963,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'News',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'd2e695f0-a30b-466c-a0d1-40b6efff900c',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 1,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408873936,
          'changed' => 1408873936,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Expert',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'd6f8ec19-7a20-439d-b16f-3fb02555352d',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 24,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875172,
          'changed' => 1408875172,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'SCC',
    'description' => '<p>Scientific Council meeting</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'd8cbc164-b26b-47de-af04-91a95a10f011',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 30,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875250,
          'changed' => 1408875250,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'MOS',
    'description' => '<p>Meeting of Signatories</p>',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'e24b5626-a45e-4c2f-a968-442a7bd75685',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 35,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875341,
          'changed' => 1408875341,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Over',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'e8293bf8-f617-45a1-b400-1375eea5f1f7',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_calendar_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 22,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875081,
          'changed' => 1408875081,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Cancelled',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'efbf51cc-7617-4c92-ba7c-2c18c288a04a',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_calendar_status',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 20,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875052,
          'changed' => 1408875052,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Yearly',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'f1055820-1d51-4ad8-99c4-ecd947c09ccd',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_repetition',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 10,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408874632,
          'changed' => 1408874632,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Informal',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'fc530987-be24-4d89-962f-ffd5bd32796b',
    'language' => 'en',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'event_type',
    'translations' => array(
      'original' => 'en',
      'data' => array(
        'en' => array(
          'entity_type' => 'taxonomy_term',
          'entity_id' => 29,
          'language' => 'en',
          'source' => '',
          'uid' => 1,
          'status' => 1,
          'translate' => 0,
          'created' => 1408875202,
          'changed' => 1408875202,
        ),
      ),
    ),
  );
  return $terms;
}
