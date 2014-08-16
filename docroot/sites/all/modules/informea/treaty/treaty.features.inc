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
    'treaty_article' => array(
      'name' => t('Treaty Article'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'treaty_paragraph' => array(
      'name' => t('Treaty Paragraph'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
