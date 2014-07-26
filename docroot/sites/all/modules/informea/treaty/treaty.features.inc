<?php
/**
 * @file
 * treaty.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function treaty_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function treaty_node_info() {
  $items = array(
    'member_party' => array(
      'name' => t('Member Party'),
      'base' => 'node_content',
      'description' => t('Member party to a treaty'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'organization' => array(
      'name' => t('Organization'),
      'base' => 'node_content',
      'description' => t('An organization which hosts a number of treaties (ex. UNEP)'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
    'treaty' => array(
      'name' => t('Treaty'),
      'base' => 'node_content',
      'description' => t('Political treaty'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
