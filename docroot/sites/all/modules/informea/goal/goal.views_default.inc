<?php
/**
 * @file
 * goal.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function goal_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'goals';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Goals';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Aichi Targets';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_strategic_goal',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'field_strategic_goal' => 'field_strategic_goal',
    'title' => 'title',
    'field_goal_type' => 'field_goal_type',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_strategic_goal' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_goal_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Strategic goal */
  $handler->display->display_options['fields']['field_strategic_goal']['id'] = 'field_strategic_goal';
  $handler->display->display_options['fields']['field_strategic_goal']['table'] = 'field_data_field_strategic_goal';
  $handler->display->display_options['fields']['field_strategic_goal']['field'] = 'field_strategic_goal';
  $handler->display->display_options['fields']['field_strategic_goal']['label'] = '';
  $handler->display->display_options['fields']['field_strategic_goal']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_strategic_goal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_strategic_goal']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Field: Order (field_sorting_order) */
  $handler->display->display_options['sorts']['field_sorting_order_value']['id'] = 'field_sorting_order_value';
  $handler->display->display_options['sorts']['field_sorting_order_value']['table'] = 'field_data_field_sorting_order';
  $handler->display->display_options['sorts']['field_sorting_order_value']['field'] = 'field_sorting_order_value';
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
    'goal' => 'goal',
  );
  /* Filter criterion: Content: Goal Type (field_goal_type) */
  $handler->display->display_options['filters']['field_goal_type_tid']['id'] = 'field_goal_type_tid';
  $handler->display->display_options['filters']['field_goal_type_tid']['table'] = 'field_data_field_goal_type';
  $handler->display->display_options['filters']['field_goal_type_tid']['field'] = 'field_goal_type_tid';
  $handler->display->display_options['filters']['field_goal_type_tid']['value'] = '';
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['operator_id'] = 'field_goal_type_tid_op';
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['label'] = 'Goal Type (field_goal_type)';
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['operator'] = 'field_goal_type_tid_op';
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['identifier'] = 'field_goal_type_tid';
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_goal_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_goal_type_tid']['vocabulary'] = 'type_of_goal';

  /* Display: All goals */
  $handler = $view->new_display('page', 'All goals', 'page');
  $handler->display->display_options['path'] = 'goals';

  /* Display: Aichi Targets */
  $handler = $view->new_display('page', 'Aichi Targets', 'page_1');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'goal' => 'goal',
  );
  /* Filter criterion: Content: Goal Type (field_goal_type) */
  $handler->display->display_options['filters']['field_goal_type_tid']['id'] = 'field_goal_type_tid';
  $handler->display->display_options['filters']['field_goal_type_tid']['table'] = 'field_data_field_goal_type';
  $handler->display->display_options['filters']['field_goal_type_tid']['field'] = 'field_goal_type_tid';
  $handler->display->display_options['filters']['field_goal_type_tid']['value'] = array(
    838 => '838',
  );
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['operator_id'] = 'field_goal_type_tid_op';
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['label'] = 'Goal Type (field_goal_type)';
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['operator'] = 'field_goal_type_tid_op';
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['identifier'] = 'field_goal_type_tid';
  $handler->display->display_options['filters']['field_goal_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_goal_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_goal_type_tid']['vocabulary'] = 'type_of_goal';
  $handler->display->display_options['path'] = 'goals/aichi-targets';
  $translatables['goals'] = array(
    t('Master'),
    t('Aichi Targets'),
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
    t('Title'),
    t('Goal Type (field_goal_type)'),
    t('All goals'),
  );
  $export['goals'] = $view;

  return $export;
}
