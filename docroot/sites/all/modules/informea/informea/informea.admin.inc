<?php

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
