<?php
/**
 * @file
 * informea.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function informea_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'country-country-field_country_party_count'
  $field_instances['country-country-field_country_party_count'] = array(
    'bundle' => 'country',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'country',
    'field_name' => 'field_country_party_count',
    'label' => 'Party count',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max' => '',
      'min' => 0,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => -13,
    ),
  );

  // Exported field_instance: 'country-country-field_is_eu_member'
  $field_instances['country-country-field_is_eu_member'] = array(
    'bundle' => 'country',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'country',
    'field_name' => 'field_is_eu_member',
    'label' => 'EU member',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => -12,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('EU member');
  t('Party count');

  return $field_instances;
}
