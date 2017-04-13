<?php
function informea_get_entityreference_fields() {
  $instances = field_info_instances();
  $fields = [];
  foreach($instances['node'] as $content_type) {
    foreach($content_type as $field_name => $field_settings) {
      if ($field_settings['widget']['module'] == 'entityreference') {
        @$fields[$field_name] += intval($field_settings['required']);
      }
    }
  }
  return $fields;
}

function informea_orphaned_rows($field) {
  $q = db_select('field_data_' . $field, 'a');
  $q->fields('a', [$field . '_target_id', 'entity_id']);
  $q->fields('c', ['type', 'title']);
  $q->leftJoin('node', 'b', 'a.' . $field . '_target_id = b.nid');
  $q->join('node', 'c', 'a.entity_id = c.nid');
  $q->condition('b.nid', null);
  $q->condition('c.status', 1);
  $q->range(0, 3);

  return $q->execute()->fetchAll();
}

function informea_orphaned() {
  $fields = informea_get_entityreference_fields();
  $data = [];
  $options['attributes']['target'] = '_blank';
  foreach ($fields as $field => $required) {
    $all = informea_orphaned_rows($field);
    if ($all) {
      $name = $field . '_target_id';
      foreach ($all as $err) {
        $err->required = $required;
        $err->filed_name = $name;
        $err->nid = $err->$name;
        unset($err->$name);
        $err->title = l($err->title, 'node/'.$err->entity_id, $options);
        $err->type = l($err->type, 'node/'.$err->entity_id, $options);
        $data[] = $err;
      }
    }
  }
  $headers = array();
  $rows = array();
  foreach ($data as $v) {
    if (!$headers) {
      $headers = array_keys((array)$v);
    }
    $rows[] = array_values((array)$v);
  }
  return theme('table', array('header' => $headers, 'rows' => $rows) );
}

function informea_analytics_form() {
  $form = array();
  $form['ga_informea_key'] = array(
    '#title' => t('InforMEA GA key'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ga_informea_key', NULL),
    '#size' => 20,
    '#maxlength' => 20,
    '#description' => t('Google Analytics key for InforMEA (UA-XXXXXXXX-X) - InforMEA content will register traffic'),
    '#required' => FALSE,
    '#label_display' => 'inline',
    '#weight' => -40,
  );
  return system_settings_form($form);
}


/**
 * Replace entityreference callback to filter the data
 */
function informea_entityreference_autocomplete_field_treaty_callback($type, $field_name, $entity_type, $bundle_name, $entity_id = '', $string = '') {
  global $user;
  /*
   * SELECT a.nid, a.title FROM node a
   * WHERE a.`type` = 'treaty'
   * AND a.title LIKE '%ar%'
   * AND a.nid IN (user treaties)
   */
  $q = db_select('node', 'a')->fields('a', array('nid', 'title'));
  $q->condition('a.type', 'treaty');
  $q->condition('a.title', '%' . $string . '%', 'LIKE');
  if ($treaties = informea_user_get_assigned_treaties($user)) {
    $q->condition('a.nid', $treaties, 'IN');
  }
  $q->orderBy('a.title');
  $q->range(0, 10);
  $matches = array();
  foreach ($q->execute()->fetchAllAssoc('nid') as $nid => $row) {
    $key = "{$row->title} ($nid)";
    // Strip things like starting/trailing white spaces, line breaks and tags.
    $key = preg_replace('/\s\s+/', ' ', str_replace("\n", '', trim(decode_entities(strip_tags($key)))));
    // Names containing commas or quotes must be wrapped in quotes.
    if (strpos($key, ',') !== FALSE || strpos($key, '"') !== FALSE) {
      $key = '"' . str_replace('"', '""', $key) . '"';
    }
    $matches[$key] = '<div class="reference-autocomplete">' . $row->title . '</div>';
  }
  drupal_json_output($matches);
}


/**
 * Replace entityreference callback to filter the data
 */
function informea_entityreference_autocomplete_field_meeting_callback($type, $field_name, $entity_type, $bundle_name, $entity_id = '', $string = '') {
  global $user;
  /**
   * SELECT a.nid, CONCAT(SUBSTR(f.title, 1, 20), '... -', a.title) AS label FROM node a
   * INNER JOIN field_data_field_event_type b ON a.nid = b.entity_id
   * INNER JOIN taxonomy_term_data c ON b.field_event_type_tid = c.tid
   * INNER JOIN taxonomy_vocabulary d ON c.vid = d.vid
   * INNER JOIN field_data_field_treaty e ON a.nid = e.entity_id
   * INNER JOIN node f ON e.field_treaty_target_id = f.nid
   *   WHERE a.`type` = 'event_calendar'
   *     AND (c.name = 'cop' AND d.machine_name = 'event_type')
   *     AND a.title LIKE '%ar%'
   *     ORDER BY label;
   */
  $q = db_select('node', 'a')->fields('a', array('nid'));
  $q->innerJoin('field_data_field_event_type', 'b', 'a.nid = b.entity_id');
  $q->innerJoin('taxonomy_term_data', 'c', 'b.field_event_type_tid = c.tid');
  $q->innerJoin('taxonomy_vocabulary', 'd', 'c.vid = d.vid');
  $q->innerJoin('field_data_field_treaty', 'e', 'a.nid = e.entity_id');
  $q->innerJoin('node', 'f', 'e.field_treaty_target_id = f.nid');
  $q->condition('a.type', 'event_calendar');
  $q->condition('c.name', 'cop');
  $q->condition('d.machine_name', 'event_type');
  $q->condition('a.title', '%' . $string . '%', 'LIKE');
  $q->addExpression("CONCAT(SUBSTR(f.title, 1, 20), '... -', a.title)", 'label');
  $q->orderBy('label');
  $q->range(0, 20);
  if ($treaties = informea_user_get_assigned_treaties($user)) {
    $q->condition('f.nid', $treaties, 'IN');
  }
  $matches = array();
  foreach ($q->execute()->fetchAllAssoc('nid') as $nid => $row) {
    $key = "{$row->label} ($nid)";
    // Strip things like starting/trailing white spaces, line breaks and tags.
    $key = preg_replace('/\s\s+/', ' ', str_replace("\n", '', trim(decode_entities(strip_tags($key)))));
    // Names containing commas or quotes must be wrapped in quotes.
    if (strpos($key, ',') !== FALSE || strpos($key, '"') !== FALSE) {
      $key = '"' . str_replace('"', '""', $key) . '"';
    }
    $matches[$key] = '<div class="reference-autocomplete">' . $row->label . '</div>';
  }
  drupal_json_output($matches);
}
