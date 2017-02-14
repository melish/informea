<?php

function thesaurus_foamtree_block_config_alter(&$form) {
  $options = array();
  $vocabulary =  taxonomy_vocabulary_machine_name_load('thesaurus_informea');
  $tree = taxonomy_get_tree($vocabulary->vid);
  foreach ($tree as $voc_item) {
    $options[$voc_item->tid] = $voc_item->name;
  }
  $form['foamtree_block_items'] = array(
    '#type' => 'select',
    '#title' => t('Foamtree terms'),
    '#multiple' => TRUE,
    '#default_value' => variable_get('foamtree_block_items'),
    '#options' => $options,
  );
}

function create_foamtree_object_from_excel($excel, $row, $column) {
  $term = reset(taxonomy_get_term_by_name($excel[$row][$column], 'thesaurus_informea'));
  return (object)array(
    'id' => $term ? $term->tid : 0,
    'phrases' => array($excel[$row][$column]),
    'size' => 1,
    'clusters' => array(),
  );
}

function thesaurus_foamtree_data_alter(&$clusters) {
  if($cached = cache_get('thesaurus_foamtree_items_cache', 'cache'))  {
    $clusters = $cached->data;
    return;
  }
  module_load_include('inc', 'phpexcel');
  $path = drupal_get_path('module', 'thesaurus') . '/foamtree/foamtree-terms.xlsx';
  $result = phpexcel_import($path, FALSE);

  $excel = $result[0];
  $terms = array();
  foreach ($result[0] as $key => $row) {
    if ($row[0]) {
      $item = create_foamtree_object_from_excel($excel, $key, 0);
      $terms[] = $item;
      parse_foamtree_from_excel($excel, $terms[count($terms) - 1], $key);
    }
  }



  $query = db_select('field_data_field_informea_tags','t');
  $query->addField('t', 'field_informea_tags_tid', 'id');
  $query->groupBy('field_informea_tags_tid');
  $query->addExpression('COUNT(*)', 'size');
  $query->orderBy('size', 'DESC');
  $results = $query->execute()->fetchAll();

  $weights = array();

  foreach ($results as $size) {
    $weights[$size->id] = $size->size;
  }

  foreach ($terms as $key => $root) {
    foamtree_set_weight($terms[$key], $weights);
  }

  $clusters = $terms;

  cache_set('thesaurus_foamtree_items_cache', $clusters, 'cache', 60*60);
  return;
}

function parse_foamtree_from_excel($excel, &$term, $row, $column = 0) {
  if ($excel[$row][$column + 1]) {
    $item = create_foamtree_object_from_excel($excel, $row, $column + 1);
    $term->clusters[] = $item;
    parse_foamtree_from_excel($excel, $term->clusters[count($term->clusters) - 1], $row, $column + 1);
    $current_row = $row + 1;
    while (!$excel[$current_row][$column] && $current_row < count($excel)) {
      if ($excel[$current_row][$column + 1]) {
        $item = create_foamtree_object_from_excel($excel, $current_row, $column + 1);
        $term->clusters[] = $item;
        parse_foamtree_from_excel($excel, $term->clusters[count($term->clusters) - 1], $current_row, $column + 1);
      }
      $current_row++;
    }
  }
}

function foamtree_set_weight(&$term, $weights) {
  if (isset($weights[$term->id])) {
    $term->size = $weights[$term->id];
  }
  foreach ($term->clusters as $key => $child) {
    foamtree_set_weight($term->clusters[$key], $weights);
  }
}
