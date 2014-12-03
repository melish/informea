<?php
/**
 * @file
 * goal.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function goal_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-goal-body'
  $field_instances['node-goal-body'] = array(
    'bundle' => 'goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Description',
    'required' => 0,
    'settings' => array(
      'display_summary' => 1,
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-goal-field_goal_indicators'
  $field_instances['node-goal-field_goal_indicators'] = array(
    'bundle' => 'goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_goal_indicators',
    'label' => 'Indicators',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-goal-field_goal_tools'
  $field_instances['node-goal-field_goal_tools'] = array(
    'bundle' => 'goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_goal_tools',
    'label' => 'Tools',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-goal-field_goal_type'
  $field_instances['node-goal-field_goal_type'] = array(
    'bundle' => 'goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'i18n_taxonomy',
        'settings' => array(),
        'type' => 'i18n_taxonomy_term_reference_link',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_goal_type',
    'label' => 'Goal Type',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'select2_integration' => array(
        'allow_add_onfly' => 0,
        'show_voc_terms_page_link' => 0,
        'styling' => array(
          'dropdownAutoWidth' => 0,
          'placeholder' => '',
        ),
        'use_select2' => 0,
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'use_select2' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-goal-field_region'
  $field_instances['node-goal-field_region'] = array(
    'bundle' => 'goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'i18n_taxonomy',
        'settings' => array(),
        'type' => 'i18n_taxonomy_term_reference_link',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_region',
    'label' => 'Coverage',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'select2_integration' => array(
        'allow_add_onfly' => 0,
        'show_voc_terms_page_link' => 0,
        'styling' => array(
          'dropdownAutoWidth' => 0,
          'placeholder' => '',
        ),
        'use_select2' => 0,
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'use_select2' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-goal-field_strategic_goal'
  $field_instances['node-goal-field_strategic_goal'] = array(
    'bundle' => 'goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_strategic_goal',
    'label' => 'Strategic goal',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'select2_integration' => array(
        'styling' => array(
          'dropdownAutoWidth' => 0,
          'placeholder' => '',
        ),
        'use_select2' => 0,
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'use_select2' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-goal-field_theme'
  $field_instances['node-goal-field_theme'] = array(
    'bundle' => 'goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'i18n_taxonomy',
        'settings' => array(),
        'type' => 'i18n_taxonomy_term_reference_link',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_theme',
    'label' => 'Theme',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'select2_integration' => array(
        'allow_add_onfly' => 0,
        'show_voc_terms_page_link' => 0,
        'styling' => array(
          'dropdownAutoWidth' => 0,
          'placeholder' => '',
        ),
        'use_select2' => 0,
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'use_select2' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-goal-field_url'
  $field_instances['node-goal-field_url'] = array(
    'bundle' => 'goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_url',
    'label' => 'URL',
    'required' => 0,
    'settings' => array(
      'absolute_url' => 1,
      'attributes' => array(
        'class' => '',
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'entity_translation_sync' => FALSE,
      'rel_remove' => 'default',
      'title' => 'optional',
      'title_label_use_field_label' => FALSE,
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-goal-title_field'
  $field_instances['node-goal-title_field'] = array(
    'bundle' => 'goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'taxonomy_term-type_of_goal-description_field'
  $field_instances['taxonomy_term-type_of_goal-description_field'] = array(
    'bundle' => 'type_of_goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'description_field',
    'label' => 'Description',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => 0,
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => -5,
    ),
  );

  // Exported field_instance: 'taxonomy_term-type_of_goal-name_field'
  $field_instances['taxonomy_term-type_of_goal-name_field'] = array(
    'bundle' => 'type_of_goal',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'name_field',
    'label' => 'Name',
    'required' => TRUE,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'hide_label' => array(
        'entity' => FALSE,
        'page' => FALSE,
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => -5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Coverage');
  t('Description');
  t('Goal Type');
  t('Indicators');
  t('Name');
  t('Strategic goal');
  t('Theme');
  t('Title');
  t('Tools');
  t('URL');

  return $field_instances;
}
