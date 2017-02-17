<?php

function hook_foamtree_data_alter(&$clusters) {
  $query = db_select('field_data_field_informea_tags','t');
  $query->addField('t', 'field_informea_tags_tid', 'id');
  $query->groupBy('field_informea_tags_tid');
  $query->addExpression('COUNT(*)', 'size');
  $query->orderBy('size', 'DESC');
  $query->range(0,15);
  $results = $query->execute()->fetchAll();

  foreach ($results as $term) {
    $taxonomy_term = taxonomy_term_load($term->id);
    $term->phrases = array($taxonomy_term->name);
    $term->size = (int) $term->size;
  }

  $clusters = $results;
}

function hook_foamtree_block_config_alter(&$form) {
  $options = array();
  $vocabulary =  taxonomy_vocabulary_machine_name_load('thesaurus_informea');
  $tree = taxonomy_get_tree($vocabulary->vid);
  foreach ($tree as $voc_item) {
    $options[$voc_item->tid] = $voc_item->name;
  }
  $form['items'] = array(
    '#type' => 'select',
    '#title' => t('Foamtree items'),
    '#multiple' => TRUE,
    '#default_value' => variable_get('foamtree_items'),
    '#options' => $options,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Change items'),
  );
}
