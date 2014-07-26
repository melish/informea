<?php
/**
 * @file
 * meeting.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function meeting_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function meeting_node_info() {
  $items = array(
    'event_calendar' => array(
      'name' => t('Event Calendar'),
      'base' => 'node_content',
      'description' => t('A content type to create events for calendar.'),
      'has_title' => '1',
      'title_label' => t('Event Title'),
      'help' => '',
    ),
  );
  return $items;
}
