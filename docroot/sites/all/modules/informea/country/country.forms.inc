<?php

function country_literature_filter_form($form, $form_state) {
  $form = array(
    '#action' => '/search',
    '#weight' => 15
  );

  $build = array();
  $build['search-string'] = array(
    '#type' => 'textfield',
    '#title' => t('Search string'),
    '#size' => 30,
    '#maxlength' => 128,
  );

  $voc = taxonomy_vocabulary_machine_name_load('literature_type');
  $terms = taxonomy_get_tree($voc->vid);
  $build['field_literature_type'] = array(
    '#prefix' => '<div class="col-md-offset-1">',
    '#suffix' => '</div>',
    '#type' => 'radios',
    '#options' => array_combine(
      array_map(function($t) { return $t->tid; }, $terms),
      array_map(function($t) { return $t->name; }, $terms)
    ),
    '#title' => t('Type of document'),
  );

  $voc = taxonomy_vocabulary_machine_name_load('geographical_region');
  $terms = taxonomy_get_tree($voc->vid);
  $build['field_literature_type'] = array(
    '#type' => 'select',
    '#options' => array_combine(
      array_map(function($t) { return $t->tid; }, $terms),
      array_map(function($t) { return $t->name; }, $terms)
    ),
    '#title' => t('Related region'),
  );

  $build['search-button'] = array(
    '#type' => 'submit',
    '#value' => t('Show results'),
    '#attributes' => array('class' => array('btn-lg', 'btn-success')),
  );

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Find literature'),
    0 => $build,
  );
  return $form;
}

function country_legislation_filter_form($form, $form_state) {
  $form = array(
    '#action' => '/search',
    '#weight' => 15
  );

  $build = array();
  $build['search-string'] = array(
    '#type' => 'textfield',
    '#title' => t('Search string'),
    '#size' => 30,
    '#maxlength' => 128,
  );

  $voc = taxonomy_vocabulary_machine_name_load('type_of_text');
  $terms = taxonomy_get_tree($voc->vid);
  $build['field_type_of_text'] = array(
    '#prefix' => '<div class="col-md-offset-1">',
    '#suffix' => '</div>',
    '#type' => 'radios',
    '#options' => array_combine(
      array_map(function($t) { return $t->tid; }, $terms),
      array_map(function($t) { return $t->name; }, $terms)
    ),
    '#title' => t('Type of document'),
  );

  $build['search-button'] = array(
    '#type' => 'submit',
    '#value' => t('Show results'),
    '#attributes' => array('class' => array('btn-lg', 'btn-success')),
  );

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Find laws'),
    0 => $build,
  );
  return $form;
}