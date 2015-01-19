<?php

function country_literature_filter_form($form, $form_state, $country) {
  $form = array(
    '#action' => '/search',
    '#method' => 'get',
    '#weight' => 15
  );

  $build = array();
  // Add the hidden fields
  // &f[0]=field_country%3A4&f[1]=type%3Alegislation&f[2]=field_type_of_text%3A839
  $build['f[0]'] = array('#type' => 'hidden', '#value' => 'field_country:' . $country->nid);
  $build['f[1]'] = array('#type' => 'hidden', '#value' => 'type:' . 'literature');
  $build['search_api_views_fulltext_op'] = array('#type' => 'hidden', '#value' => 'AND');
  $build['search_api_views_fulltext'] = array(
    '#type' => 'textfield',
    '#title' => t('Search string'),
    '#size' => 30,
    '#maxlength' => 128,
  );

  $terms = country_get_court_literature_statistics($country->nid);
  $build['f[2]'] = array(
    '#type' => 'select',
    '#options' => array_combine(
      array_map(function($t) { return 'field_literature_type:' . $t->tid; }, $terms),
      array_map(function($t) { return sprintf('%s (%d)', $t->name, $t->count) ; }, $terms)
    ),
    '#title' => t('Type of literature'),
  );

  $build['search-button'] = array(
    '#type' => 'submit',
    '#value' => t('Show results'),
    '#attributes' => array('class' => array('btn-lg', 'btn-success')),
  );

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search literature metadata'),
    0 => $build,
  );
  return $form;
}

function country_legislation_filter_form($form, $form_state, $country) {
  $form = array(
    '#action' => '/search',
    '#method' => 'get',
    '#weight' => 15
  );
  $build = array();
  // Add the hidden fields
  // &f[0]=field_country%3A4&f[1]=type%3Alegislation&f[2]=field_type_of_text%3A839
  $build['f[0]'] = array('#type' => 'hidden', '#value' => 'field_country:' . $country->nid);
  $build['f[1]'] = array('#type' => 'hidden', '#value' => 'type:' . 'legislation');
  $build['search_api_views_fulltext_op'] = array('#type' => 'hidden', '#value' => 'AND');
  $build['search_api_views_fulltext'] = array(
    '#type' => 'textfield',
    '#title' => t('Search string'),
    '#size' => 30,
    '#maxlength' => 128,
  );
  $terms = country_get_legislation_statistics($country->nid);
  $build['f[2]'] = array(
    '#prefix' => '<div class="col-md-offset-1">',
    '#suffix' => '</div>',
    '#type' => 'radios',
    '#options' => array_combine(
      array_map(function($t) { return 'field_type_of_text:' . $t->tid; }, $terms),
        array_map(function($t) { return sprintf('%s (%d)', $t->name, $t->count) ; }, $terms)
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