<?php
/**
 * @file
 * informea.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function informea_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views--exp-events-page'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '-exp-events-page',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'events',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -17,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['views--exp-news-page'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '-exp-news-page',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'news',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -16,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  return $export;
}