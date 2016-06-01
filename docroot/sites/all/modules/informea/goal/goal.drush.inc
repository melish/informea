<?php

/**
 * Implementation of hook_drush_command().
 */
function goal_drush_command() {
  $items = array();

  $items['informea-sdg-indicators-import'] = array(
    'drupal dependencies' => array('phpexcel'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'description' => 'SDG Indicators Import',
    'aliases' => array('sdg-ii'),
  );

  return $items;
}

/**
 * Imports SDG indicators from SDG_datasheet.xlsx file.
 */
function drush_goal_informea_sdg_indicators_import() {
  $columns = [
    'goal_no' => 'SDG Goal No.',
    'goal_text' => 'SDG Goal Text',
    'target_no' => 'SDG Target No.',
    'target_text' => 'SDG Target Text',
    'indicator_no' => 'SDG Indicator No.',
    'indicator_text' => 'SDG Indicator Text*',
  ];
  module_load_include('inc', 'phpexcel');
  $path = drupal_get_path('module', 'goal') . '/files/SDG_datasheet.xlsx';
  $data = phpexcel_import($path)[0];
  if (!is_array($data)) {
    drush_log("We could not get the data from the excel file.", 'error');
    return;
  }
  $goals = [];
  foreach ($data as $row) {
    if (empty($indicator = $row[$columns['indicator_text']])) {
      continue;
    }
    $goal = $row[$columns['goal_no']] . ' ' . $row[$columns['goal_text']];
    $target = $row[$columns['target_no']] . ' ' . $row[$columns['target_text']];
    $indicator = $row[$columns['indicator_no']] . ' ' . $indicator;

    if (empty($goals[$goal])) {
      $goals[$goal] = [
        'title' => $goal,
        'id' => $row[$columns['goal_no']],
        'children' => [],
      ];
    }
    if (!array_key_exists($target, $goals[$goal]['children'])) {
      $goals[$goal]['children'][$target] = [
        'title' => $target,
        'id' => $row[$columns['target_no']],
        'children' => [],
      ];
    }
    $goals[$goal]['children'][$target]['children'][] = [
      'title' => $indicator,
      'id' => $row[$columns['indicator_no']],
      'children' => [],
    ];
  }

  // ToDo: Do we need to retrieve these tids programmatically matched by term name?
  $sdg_tid = 1753;
  $goal_tid = 1734;
  $target_tid = 1737;
  $indicator_tid = 1735;

  foreach ($goals as $goal) {
    // ToDo: field_goal_tools ??
    // ToDo: field_informea_tags !!
    $node = [
      'title' => $goal['title'],
      'status' => '1',
      'type' => 'goal',
      'language' => 'en',
      'field_goal_source' => [
        LANGUAGE_NONE => [
          0 => [
            'tid' => $sdg_tid,
          ],
        ],
      ],
      'field_goal_type' => [
        LANGUAGE_NONE => [
          0 => [
            'tid' => $goal_tid,
          ],
        ],
      ],
      'title_field' => [
        'en' => [
          0 => [
            'value' => $goal['title'],
          ],
        ],
      ],
      'field_original_id' => [
        LANGUAGE_NONE => [
          0 => [
            'value' => $goal['id'],
          ],
        ],
      ],
    ];
  }
}
