<?php
/**
 * @file
 * informea_search.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function informea_search_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['facetapi-5dVDefUus1Cng13EbCDnPRh5v5tXEP7B'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '5dVDefUus1Cng13EbCDnPRh5v5tXEP7B',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'informea_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-ABol1qBh79jsfGqF27usDpaBznEzCn7M'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'ABol1qBh79jsfGqF27usDpaBznEzCn7M',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search-court-decisions
search-court-decisions/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -33,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Type of text',
    'visibility' => 1,
  );

  $export['facetapi-C0KfOYe1CTJW1tlSyl3brJVVT4qQLzy0'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'C0KfOYe1CTJW1tlSyl3brJVVT4qQLzy0',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search
search/*
search-bilateral-treaties
search-bilateral-treaties/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -39,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Instrument',
    'visibility' => 1,
  );

  $export['facetapi-EBe4nF0bWIclTeTpPk5EfoKyGT3EgxZw'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'EBe4nF0bWIclTeTpPk5EfoKyGT3EgxZw',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search-legislation
search-legislation/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -31,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Region',
    'visibility' => 1,
  );

  $export['facetapi-EeqfYRvf4OeayxrDPBXmxh0uLs695r1S'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'EeqfYRvf4OeayxrDPBXmxh0uLs695r1S',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search
search/*
search-bilateral-treaties
search-bilateral-treaties/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -38,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Geographical region',
    'visibility' => 0,
  );

  $export['facetapi-I6RVf55CR0muKADP1zTBRoXexXDd7LN4'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'I6RVf55CR0muKADP1zTBRoXexXDd7LN4',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search
search/*
search-bilateral-treaties
search-bilateral-treaties/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -36,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Keywords',
    'visibility' => 1,
  );

  $export['facetapi-IhbpziRRQ04ohXLVPOH1pzkj01ySLvut'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'IhbpziRRQ04ohXLVPOH1pzkj01ySLvut',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search-legislation
search-legislation/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -32,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Country',
    'visibility' => 1,
  );

  $export['facetapi-Pg30Pc0KVb1ixI192kdMOYYpptaM7w81'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'Pg30Pc0KVb1ixI192kdMOYYpptaM7w81',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'informea_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-bhF7dlwZfRYrATVWsYC6eOvTl9pFOHHh'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'bhF7dlwZfRYrATVWsYC6eOvTl9pFOHHh',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search-legislation
search-legislation/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -30,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Type of text',
    'visibility' => 1,
  );

  $export['facetapi-fdq04xNUyxSV1CkoyeTHIwwlufwxjcFK'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'fdq04xNUyxSV1CkoyeTHIwwlufwxjcFK',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search-court-decisions
search-court-decisions/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -34,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Region',
    'visibility' => 1,
  );

  $export['facetapi-jX6n57R09128yKk8mDTq4yM84f6PAh5a'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'jX6n57R09128yKk8mDTq4yM84f6PAh5a',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search-court-decisions
search-court-decisions/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -35,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Country',
    'visibility' => 1,
  );

  $export['facetapi-qTurWYUYYufA4n4p1OFoxmFTW0m9G81J'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'qTurWYUYYufA4n4p1OFoxmFTW0m9G81J',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search
search/*
search-bilateral-treaties
search-bilateral-treaties/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -37,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Country',
    'visibility' => 1,
  );

  $export['facetapi-rm0orTI2PzmJnpZ1x07XLj097DSEjQQJ'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'rm0orTI2PzmJnpZ1x07XLj097DSEjQQJ',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'search
search/*',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -40,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Type',
    'visibility' => 1,
  );

  return $export;
}
