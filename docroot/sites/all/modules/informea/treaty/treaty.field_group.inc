<?php
/**
 * @file
 * treaty.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function treaty_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ecolex|node|treaty|form';
  $field_group->group_name = 'group_ecolex';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'treaty';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_treaty_field_group';
  $field_group->data = array(
    'label' => 'Ecolex',
    'weight' => '19',
    'children' => array(
      0 => 'field_abstract',
      1 => 'field_alternative_record_id',
      2 => 'field_amends_treaty',
      3 => 'field_available_in',
      4 => 'field_cited_treaties',
      5 => 'field_date_of_text',
      6 => 'field_depositary',
      7 => 'field_ecolex_tags',
      8 => 'field_ecolex_url',
      9 => 'field_field_of_application',
      10 => 'field_internet_reference',
      11 => 'field_jurisdiction',
      12 => 'field_number_of_pages',
      13 => 'field_obsolete',
      14 => 'field_official_publication',
      15 => 'field_place_of_adoption',
      16 => 'field_related_url',
      17 => 'field_related_website',
      18 => 'field_type_of_text',
      19 => 'field_date_of_entry',
      20 => 'field_date_of_modification',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_ecolex|node|treaty|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_external_links|node|treaty|form';
  $field_group->group_name = 'group_external_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'treaty';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_treaty_field_group';
  $field_group->data = array(
    'label' => 'External links',
    'weight' => '18',
    'children' => array(
      0 => 'field_faolex_url',
      1 => 'field_treaty_parties_url',
      2 => 'field_treaty_text_url',
      3 => 'field_treaty_website_url',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_external_links|node|treaty|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_technical_data|node|treaty|form';
  $field_group->group_name = 'group_technical_data';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'treaty';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_treaty_field_group';
  $field_group->data = array(
    'label' => 'Technical data',
    'weight' => '21',
    'children' => array(
      0 => 'field_odata_identifier',
      1 => 'field_ratification_xml_url',
      2 => 'field_sorting_order',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-technical-data field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_technical_data|node|treaty|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_treaty_field_group|node|treaty|form';
  $field_group->group_name = 'group_treaty_field_group';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'treaty';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional information',
    'weight' => '23',
    'children' => array(
      0 => 'group_ecolex',
      1 => 'group_external_links',
      2 => 'group_technical_data',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Additional information',
      'instance_settings' => array(
        'classes' => 'group-treaty-field-group field-group-htabs',
      ),
    ),
  );
  $export['group_treaty_field_group|node|treaty|form'] = $field_group;

  return $export;
}
