<?php
/**
 * @file
 * analytics_integration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function analytics_integration_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function analytics_integration_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function analytics_integration_node_info() {
  $items = array(
    'analytics_key' => array(
      'name' => t('Analytics key'),
      'base' => 'node_content',
      'description' => t('Configuration for various MEAs page tracking systems (GA, Piwik, etc.)'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
