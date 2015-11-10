<?php
/**
 * @file
 * analytics_integration.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function analytics_integration_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'analytics_keys';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Analytics keys';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Analytics keys';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer site configuration';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_analytics_key' => 'field_analytics_key',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_analytics_key' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<ul class="action-links"><li><a href="/node/add/analytics-key">Add new key</a></li>
</ul>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_analytics_key_type']['id'] = 'field_analytics_key_type';
  $handler->display->display_options['fields']['field_analytics_key_type']['table'] = 'field_data_field_analytics_key_type';
  $handler->display->display_options['fields']['field_analytics_key_type']['field'] = 'field_analytics_key_type';
  $handler->display->display_options['fields']['field_analytics_key_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_analytics_key_type']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Analytics key */
  $handler->display->display_options['fields']['field_analytics_key']['id'] = 'field_analytics_key';
  $handler->display->display_options['fields']['field_analytics_key']['table'] = 'field_data_field_analytics_key';
  $handler->display->display_options['fields']['field_analytics_key']['field'] = 'field_analytics_key';
  $handler->display->display_options['fields']['field_analytics_key']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_analytics_key']['settings'] = array(
    'title_style' => '',
    'title_link' => '',
    'title_class' => '',
  );
  /* Field: Entity translation: URL: translated */
  $handler->display->display_options['fields']['field_url_et']['id'] = 'field_url_et';
  $handler->display->display_options['fields']['field_url_et']['table'] = 'field_data_field_url';
  $handler->display->display_options['fields']['field_url_et']['field'] = 'field_url_et';
  $handler->display->display_options['fields']['field_url_et']['label'] = 'Piwik URL';
  $handler->display->display_options['fields']['field_url_et']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_url_et']['click_sort_column'] = 'url';
  /* Field: Content: Piwik ID */
  $handler->display->display_options['fields']['field_piwik_id']['id'] = 'field_piwik_id';
  $handler->display->display_options['fields']['field_piwik_id']['table'] = 'field_data_field_piwik_id';
  $handler->display->display_options['fields']['field_piwik_id']['field'] = 'field_piwik_id';
  $handler->display->display_options['fields']['field_piwik_id']['element_label_colon'] = FALSE;
  /* Field: Content: Treaty */
  $handler->display->display_options['fields']['field_treaty']['id'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['table'] = 'field_data_field_treaty';
  $handler->display->display_options['fields']['field_treaty']['field'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treaty']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_treaty']['delta_offset'] = '0';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'analytics_key' => 'analytics_key',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/config/services/analytics/keys';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Analytics keys';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Analytics';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'devel';
  $translatables['analytics_keys'] = array(
    t('Master'),
    t('Analytics keys'),
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
    t('<ul class="action-links"><li><a href="/node/add/analytics-key">Add new key</a></li>
</ul>'),
    t('Title'),
    t('Type'),
    t('Analytics key'),
    t('Piwik URL'),
    t('Piwik ID'),
    t('Treaty'),
    t('Edit'),
    t('Page'),
  );
  $export['analytics_keys'] = $view;

  return $export;
}
