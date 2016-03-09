<?php

function ws_consumer_odata_admin_config_form() {
  $form = array('#tree' => TRUE);
  $config = ODataConsumerConfig::getConfiguration();
  $form['title'] = array(
    '#type' => 'item',
    '#markup' => '<h1>Configure data providers</h1>' .
      '<p>Use this form to configure URL endpoints to the OData services</p>'
  );
  $meas = ODataConsumerConfig::getODataNames();
  $entities = ODataConsumerConfig::getEntityNames();
  asort($meas);
  foreach($meas as $mea) {
    $form['endpoints'][$mea] = array(
      '#type' => 'fieldset',
      '#title' => $mea . ' configuration',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['endpoints'][$mea]['default'] = array(
      '#type' => 'textfield',
      '#title' => t('Default/Common endpoint'),
      '#description' => t('Enter the endpoint common to all entities, if applicable'),
      '#default_value' => $config['endpoints'][$mea]['default'],
    );
    foreach($entities as $entity) {
      $form['endpoints'][$mea][$entity] = array(
        '#type' => 'textfield',
        '#title' => t('Endpoint for ' . $entity),
        '#description' => t('Enter custom endpoint, leave empty to use default above'),
        '#default_value' => $config['endpoints'][$mea][$entity],
      );
    }
  }
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}


function ws_consumer_odata_admin_config_form_validate($form, &$form_state) {
  //@todo: validate endpoints using cURL?
}

function ws_consumer_odata_admin_config_form_submit($form, $form_state) {
  $current = ODataConsumerConfig::getConfiguration();
  $meas = ODataConsumerConfig::getODataNames();
  $entities = ODataConsumerConfig::getEntityNames();
  array_unshift($entities, 'default');
  asort($meas);
  $values = $form_state['values'];
  foreach($meas as $mea) {
    foreach($entities as $entity) {
      $current['endpoints'][$mea][$entity] = $values['endpoints'][$mea][$entity];
    }
  }
  ODataConsumerConfig::saveConfiguration($current);
  drupal_set_message('Configuration successfully saved');
}


function ws_consumer_odata_admin_config_migrations_form() {
  $form = array('#tree' => FALSE);
  $form['title'] = array(
    '#type' => 'item',
    '#markup' => '<h1>Data import configuration</h1>' .
      '<p>Uncheck the items you wish to disable, then save configuration.</p>'
  );

  module_load_include('inc', 'ws_consumer_odata', 'ws_consumer_odata.migrate');
  $migrations = ws_consumer_odata_migrate_api();
  $groups = $migrations['groups'];
  ksort($groups);

  foreach($groups as $name => $data) {
    $form[$name] = array(
      '#type' => 'fieldset',
      '#title' => $data['title'],
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
  }

  foreach($migrations['migrations'] as $name => $config) {
    $group = $config['group_name'];
    $form[$group][$name] = array(
      '#type' => 'checkbox',
      '#title' => $config['odata_entity'] . ' (' . $name . ')',
      '#default_value' => ODataConsumerConfig::isEnabled($name),
    );
  }

  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

function ws_consumer_odata_admin_config_migrations_form_validate($form, &$form_state) {

}

function ws_consumer_odata_admin_config_migrations_form_submit($form, &$form_state) {
  $disabled = array();
  module_load_include('inc', 'ws_consumer_odata', 'ws_consumer_odata.migrate');
  $migrations = ws_consumer_odata_migrate_api();
  foreach($migrations['migrations'] as $name => $config) {
    if (empty($form_state['values'][$name])) {
      $disabled[$name] = 1;
    }
  }
  $config = ODataConsumerConfig::getConfiguration();
  $config['disabled'] = $disabled;
  ODataConsumerConfig::saveConfiguration($config);
  drupal_set_message('Configuration successfully saved');
}
