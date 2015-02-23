<?php
/**
 * @file
 * search_integration.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function search_integration_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'the_search_view';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_default_node_index';
  $view->human_name = 'The search view';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'type' => 'type',
    'field_treaty' => 'field_treaty',
    'field_country_1' => 'field_country_1',
    'field_entry_into_force' => 'field_entry_into_force',
  );
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = 'Showing @start&ndash;@end of @total results';
  /* Relationship: Indexed Node: Treaty */
  $handler->display->display_options['relationships']['field_treaty']['id'] = 'field_treaty';
  $handler->display->display_options['relationships']['field_treaty']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['relationships']['field_treaty']['field'] = 'field_treaty';
  /* Relationship: Node: Country */
  $handler->display->display_options['relationships']['field_country']['id'] = 'field_country';
  $handler->display->display_options['relationships']['field_country']['table'] = 'entity_node';
  $handler->display->display_options['relationships']['field_country']['field'] = 'field_country';
  $handler->display->display_options['relationships']['field_country']['relationship'] = 'field_treaty';
  /* Field: Indexed Node: ISO alpha-2 code */
  $handler->display->display_options['fields']['field_country_iso2']['id'] = 'field_country_iso2';
  $handler->display->display_options['fields']['field_country_iso2']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_country_iso2']['field'] = 'field_country_iso2';
  $handler->display->display_options['fields']['field_country_iso2']['label'] = '';
  $handler->display->display_options['fields']['field_country_iso2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_country_iso2']['alter']['text'] = '<img src="/sites/all/themes/leo.theme/img/flags/flag-[field_country_iso2-value].png" alt="[field_country_iso2-value]">';
  $handler->display->display_options['fields']['field_country_iso2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_country_iso2']['hide_empty'] = TRUE;
  /* Field: Indexed Node: Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: Content type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['element_type'] = 'strong';
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['type']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['type']['format_name'] = 1;
  /* Field: Indexed Node: Treaty */
  $handler->display->display_options['fields']['field_treaty']['id'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_treaty']['field'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['label'] = '';
  $handler->display->display_options['fields']['field_treaty']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_treaty']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_treaty']['alter']['text'] = ' &middot; <span class="glyphicon glyphicon-file"></span> [field_treaty]';
  $handler->display->display_options['fields']['field_treaty']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treaty']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_treaty']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_treaty']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_treaty']['bypass_access'] = 0;
  /* Field: Indexed Node: Country */
  $handler->display->display_options['fields']['field_country_1']['id'] = 'field_country_1';
  $handler->display->display_options['fields']['field_country_1']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_country_1']['field'] = 'field_country';
  $handler->display->display_options['fields']['field_country_1']['label'] = '';
  $handler->display->display_options['fields']['field_country_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_country_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_country_1']['alter']['text'] = ' &middot; <span class="glyphicon glyphicon-globe"></span> [field_country_1]';
  $handler->display->display_options['fields']['field_country_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_country_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_country_1']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_country_1']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_country_1']['bypass_access'] = 0;
  /* Field: Indexed Node: Entry into force */
  $handler->display->display_options['fields']['field_entry_into_force']['id'] = 'field_entry_into_force';
  $handler->display->display_options['fields']['field_entry_into_force']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_entry_into_force']['field'] = 'field_entry_into_force';
  $handler->display->display_options['fields']['field_entry_into_force']['label'] = '';
  $handler->display->display_options['fields']['field_entry_into_force']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_entry_into_force']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_entry_into_force']['alter']['text'] = ' &middot; <span class="glyphicon glyphicon-calendar"></span> [field_entry_into_force]';
  $handler->display->display_options['fields']['field_entry_into_force']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_entry_into_force']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_entry_into_force']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="meta"><strong>[type]</strong>[field_treaty][field_country_1][field_entry_into_force]</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Search for';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['search_api_views_fulltext']['group_info']['label'] = 'Fulltext search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['group_info']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'search';
  $translatables['the_search_view'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Showing @start&ndash;@end of @total results'),
    t('Treaty'),
    t('Country'),
    t('<img src="/sites/all/themes/leo.theme/img/flags/flag-[field_country_iso2-value].png" alt="[field_country_iso2-value]">'),
    t('.'),
    t(','),
    t(' &middot; <span class="glyphicon glyphicon-file"></span> [field_treaty]'),
    t(' &middot; <span class="glyphicon glyphicon-globe"></span> [field_country_1]'),
    t(' &middot; <span class="glyphicon glyphicon-calendar"></span> [field_entry_into_force]'),
    t('<div class="meta"><strong>[type]</strong>[field_treaty][field_country_1][field_entry_into_force]</div>'),
    t('Search for'),
    t('Fulltext search'),
    t('Page'),
  );
  $export['the_search_view'] = $view;

  return $export;
}
