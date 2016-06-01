<?php

/**
 * Implementation of hook_drush_command().
 */
function goal_drush_command() {
  $items = array();

  $items['informea-sdg-full-import'] = array(
    'drupal dependencies' => array('phpexcel'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'description' => 'SDG Full Import',
    'aliases' => array('sdg-fi'),
  );

  return $items;
}

/**
 * @param array $info
 *  Array containing:
 *    - title_field
 *    - field_goal_source
 *    - field_goal_type
 *    - field_parent_goal
 *    - field_original_id
 */
function _goal_create_node($info) {
  $node = [
    'title' => $info['title_field'],
    'status' => '1',
    'type' => 'goal',
    'language' => 'en',
    'title_original' => $info['title_field'],
  ];
  foreach (['field_goal_source', 'field_goal_type'] as $field) {
    if (!empty($info[$field])) {
      $node[$field] = [
        LANGUAGE_NONE => [
          0 => [
            'tid' => $info[$field],
          ],
        ],
      ];
    }
  }
  if (!empty($info['field_parent_goal'])) {
    $node['field_parent_goal'] = [
      LANGUAGE_NONE => [
        0 => [
          'target_id' => $info['field_parent_goal'],
        ],
      ],
    ];
  }
  foreach (['title_field', 'field_original_id'] as $field) {
    if (!empty($info[$field])) {
      $node[$field] = [
        'en' => [
          0 => [
            'value' => $info[$field],
          ],
        ],
      ];
    }
  }
  $node = (object) $node;
  $node = node_submit($node);
  node_save($node);
  return $node;
}

/**
 * Imports SDG goals, targets & indicators from SDG_datasheet.xlsx file.
 */
function drush_goal_informea_sdg_full_import() {
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
  $errors = [];
  foreach ($data as $key => $row) {
    $missing = 0;
    foreach (['goal_text', 'target_text', 'indicator_text'] as $req_col) {
      if (empty($row[$columns[$req_col]])) {
        $missing ++;
      }
    }
    if ($missing > 0) {
      if ($missing < 3) {
        $rownum = $key + 2;
        $errors[] = "Found an empty column on row {$rownum}";
      }
      continue;
    }
    $goal = $row[$columns['goal_no']] . ' ' . $row[$columns['goal_text']];
    $target = $row[$columns['target_no']] . ' ' . $row[$columns['target_text']];
    $indicator = $row[$columns['indicator_no']] . ' ' . $row[$columns['indicator_text']];

    if (empty($goals[$goal])) {
      $goals[$goal] = [
        'title' => $goal,
        'id' => trim(str_replace(['Goal', '.'], '', $row[$columns['goal_no']])),
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
    $goal_node = _goal_create_node([
      'title_field' => $goal['title'],
      'field_goal_source' => $sdg_tid,
      'field_goal_type' => $goal_tid,
      'field_original_id' => $goal['id'],
    ]);
    if (!empty($goal_node->nid)) {
      drush_log("Created goal ({$goal_node->nid}): {$goal['title']}", 'ok');
      drush_log("Creating targets...", 'ok');

      foreach ($goal['children'] as $target) {
        // ToDo: field_informea_tags !!
        $target_node = _goal_create_node([
          'title_field' => $target['title'],
          'field_goal_source' => $sdg_tid,
          'field_goal_type' => $target_tid,
          'field_parent_goal' => $goal_node->nid,
          'field_original_id' => $target['id'],
        ]);
        if (!empty($target_node->nid)) {
          drush_log("  * Created target ({$target_node->nid}): {$target['title']}", 'ok');
          drush_log("  Creating indicators...", 'ok');

          foreach ($target['children'] as $indicator) {
            // ToDo: field_informea_tags !!
            $indicator_node = _goal_create_node([
              'title_field' => $indicator['title'],
              'field_goal_source' => $sdg_tid,
              'field_goal_type' => $indicator_tid,
              'field_parent_goal' => $target_node->nid,
              'field_original_id' => $indicator['id'],
            ]);
            if (!empty($indicator_node->nid)) {
              drush_log("    - Created indicator ({$indicator_node->nid}): {$indicator['title']}", 'ok');
            }
          }
        }
      }
    }
  }

  foreach ($errors as $error) {
    drush_log($error, 'error');
  }
}
