<?php
/**
 * @file
 * treaty.path_breadcrumbs.inc
 */

/**
 * Implements hook_path_breadcrumbs_settings_info().
 */
function treaty_path_breadcrumbs_settings_info() {
  $export = array();

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'treaties';
  $path_breadcrumb->name = 'Treaties';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Treaties',
      1 => '%node:title',
    ),
    'paths' => array(
      0 => 'treaties',
      1 => '%node:url',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'treaty' => 'treaty',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'node_treaty_parent_value',
          'settings' => array(
            'is_not_empty' => 0,
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['treaties'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'treaties_protocols';
  $path_breadcrumb->name = 'Treaties';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Treaties',
      1 => '%node:field-parent-treaty:title',
      2 => 'Protocols',
      3 => '%node:title',
    ),
    'paths' => array(
      0 => 'treaties',
      1 => '%node:field-parent-treaty:url',
      2 => '%node:field-parent-treaty:url/protocols',
      3 => '%node:url',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'treaty' => 'treaty',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'node_treaty_parent_value',
          'settings' => array(
            'is_not_empty' => 1,
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['treaties_protocols'] = $path_breadcrumb;

  return $export;
}
