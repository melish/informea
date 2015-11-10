<?php
/**
 * @file
 * analytics_integration.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function analytics_integration_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_google_analytics|node|analytics_key|form';
  $field_group->group_name = 'group_google_analytics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'analytics_key';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Google Analytics',
    'weight' => '5',
    'children' => array(
      0 => 'field_analytics_key',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-google-analytics field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_google_analytics|node|analytics_key|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_piwik|node|analytics_key|form';
  $field_group->group_name = 'group_piwik';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'analytics_key';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Piwik',
    'weight' => '6',
    'children' => array(
      0 => 'field_url',
      1 => 'field_piwik_id',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-piwik field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_piwik|node|analytics_key|form'] = $field_group;

  return $export;
}
