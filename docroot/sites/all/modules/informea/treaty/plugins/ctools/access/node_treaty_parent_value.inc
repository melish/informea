<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Treaty parent not empty"),
  'description' => t('Control access by checking if treaty_parent field is empty or not.'),
  'callback' => 'treaty_node_treaty_parent_value_ctools_access_check',
  'default' => array('theme' => variable_get('is_not_empty', TRUE)),
  'settings form' => 'treaty_node_treaty_parent_value_ctools_access_settings',
  'summary' => 'treaty_node_treaty_parent_value_ctools_access_summary',
);

/**
 * Create a context from manual configuration.
 */
function treaty_node_treaty_parent_value_ctools_access_check($conf, $context) {
  $node = menu_get_object('node');
  if (!empty($node->nid)) {
    if (!empty($conf['is_not_empty']) && !empty($node->field_parent_treaty)) {
      return TRUE;
    }
    elseif (empty($conf['is_not_empty']) && empty($node->field_parent_treaty)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Settings form for the 'field_treaty_parent not empty' access plugin.
 */
function treaty_node_treaty_parent_value_ctools_access_settings($form, &$form_state, $conf) {
  $form['settings']['is_not_empty'] = array(
    '#title' => 'Is not empty',
    '#type' => 'checkbox',
    '#default_value' => $conf['is_not_empty'],
  );
  return $form;
}

/**
 * Provide a summary description based upon the checked roles.
 */
function treaty_node_treaty_parent_value_ctools_access_summary($conf, $context) {
  if (!isset($conf['is_not_empty'])) {
    return t('Error, unset is_not_empty');
  }
  return t('Field treaty should be not empty "@set"', array('@set' => $conf['is_not_empty']));
}
