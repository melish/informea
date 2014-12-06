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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Goal Type */
  $handler->display->display_options['fields']['field_goal_type']['id'] = 'field_goal_type';
  $handler->display->display_options['fields']['field_goal_type']['table'] = 'field_data_field_goal_type';
  $handler->display->display_options['fields']['field_goal_type']['field'] = 'field_goal_type';
  $handler->display->display_options['fields']['field_goal_type']['type'] = 'taxonomy_term_reference_plain';
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
    t('Goal Type'),
    t('Goal Type (field_goal_type)'),
    t('All goals'),
  );
  $export['goals'] = $view;

  return $export;
}
