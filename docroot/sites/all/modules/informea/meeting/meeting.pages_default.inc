<?php
/**
 * @file
 * meeting.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function meeting_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_610fa1b3-da70-460d-a4b1-53cb1ae02d42';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'COP',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(
      0 => array(
        'identifier' => 'Content from Content (on Content: Treaty [field_treaty])',
        'keyword' => 'treaty',
        'name' => 'entity_from_field:field_treaty-node-node',
        'delta' => '0',
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
    ),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_field_value:node:event_calendar:field_event_type',
          'settings' => array(
            'field_event_type' => array(
              'und' => array(
                0 => array(
                  'tid' => '821',
                ),
              ),
            ),
            'field_event_type_tid' => array(
              0 => '821',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'event_calendar' => 'event_calendar',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
          1 => 1,
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
        ),
        'parent' => 'canvas',
        'class' => 'col-md-9',
        'hide_empty' => 1,
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      1 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => 'canvas',
        'children' => array(
          0 => 2,
          1 => 3,
        ),
        'class' => 'col-md-3',
        'hide_empty' => 1,
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'right',
        ),
        'parent' => '1',
        'class' => '',
        'hide_empty' => 0,
      ),
      'right' => array(
        'type' => 'region',
        'title' => 'Right',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
        'hide_empty' => 1,
      ),
      3 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'right_2',
        ),
        'parent' => '1',
        'class' => '',
        'hide_empty' => 1,
      ),
      'right_2' => array(
        'type' => 'region',
        'title' => 'right 2',
        'width' => 100,
        'width_type' => '%',
        'parent' => '3',
        'class' => '',
        'hide_empty' => 1,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'right' => NULL,
      'right_2' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title_field';
  $display->uuid = '28410d2f-7636-46f1-93e7-a42ffe221921';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8e59cade-c699-4e5d-ad8f-f43b6293c344';
    $pane->panel = 'center';
    $pane->type = 'views';
    $pane->subtype = 'meeting_decisions';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '10',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block',
      'context' => array(
        0 => '',
      ),
      'override_title' => 1,
      'override_title_text' => '%title',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8e59cade-c699-4e5d-ad8f-f43b6293c344';
    $display->content['new-8e59cade-c699-4e5d-ad8f-f43b6293c344'] = $pane;
    $display->panels['center'][0] = 'new-8e59cade-c699-4e5d-ad8f-f43b6293c344';
    $pane = new stdClass();
    $pane->pid = 'new-f80c54fc-df79-4ade-a695-26760f60c3f8';
    $pane->panel = 'right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_event_images';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'image',
      'delta_limit' => '1',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'image_style' => 'large',
        'image_link' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'f80c54fc-df79-4ade-a695-26760f60c3f8';
    $display->content['new-f80c54fc-df79-4ade-a695-26760f60c3f8'] = $pane;
    $display->panels['right'][0] = 'new-f80c54fc-df79-4ade-a695-26760f60c3f8';
    $pane = new stdClass();
    $pane->pid = 'new-f5dced74-7347-4577-9933-50af3d09d652';
    $pane->panel = 'right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'jquery_expander',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'expandText' => 'Show full text',
        'expandPrefix' => '...',
        'collapseTimer' => '',
        'slicePoint' => '200',
        'userCollapseText' => 'Show less',
        'userCollapsePrefix' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'f5dced74-7347-4577-9933-50af3d09d652';
    $display->content['new-f5dced74-7347-4577-9933-50af3d09d652'] = $pane;
    $display->panels['right'][1] = 'new-f5dced74-7347-4577-9933-50af3d09d652';
    $pane = new stdClass();
    $pane->pid = 'new-d71b7f8c-0cd3-4de8-aef5-013f5f00ef31';
    $pane->panel = 'right_2';
    $pane->type = 'views';
    $pane->subtype = 'other_meetings';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '2',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block',
      'context' => array(
        0 => 'relationship_entity_from_field:field_treaty-node-node_1.nid',
        1 => '',
      ),
      'override_title' => 1,
      'override_title_text' => 'Other meetings',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'd71b7f8c-0cd3-4de8-aef5-013f5f00ef31';
    $display->content['new-d71b7f8c-0cd3-4de8-aef5-013f5f00ef31'] = $pane;
    $display->panels['right_2'][0] = 'new-d71b7f8c-0cd3-4de8-aef5-013f5f00ef31';
    $pane = new stdClass();
    $pane->pid = 'new-2b1f4442-4e11-4353-a94f-15eb931200e8';
    $pane->panel = 'right_2';
    $pane->type = 'block';
    $pane->subtype = 'informea-informea_share';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Share meeting',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '2b1f4442-4e11-4353-a94f-15eb931200e8';
    $display->content['new-2b1f4442-4e11-4353-a94f-15eb931200e8'] = $pane;
    $display->panels['right_2'][1] = 'new-2b1f4442-4e11-4353-a94f-15eb931200e8';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_610fa1b3-da70-460d-a4b1-53cb1ae02d42'] = $handler;

  return $export;
}
