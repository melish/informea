<?php
/**
 * @file
 * thesaurus.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function thesaurus_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'glossary';
  $page->task = 'page';
  $page->admin_title = 'Glossary';
  $page->admin_description = '';
  $page->path = 'terms';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_glossary__panel';
  $handler->task = 'page';
  $handler->subtask = 'glossary';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Glossary';
  $display->uuid = '3e4d41c4-d7f7-476d-a836-0f70f4a70e9b';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-a424f24d-c955-4301-b8c0-127a47e9f8ed';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'thesaurus-terms-listing';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-sm-3',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'a424f24d-c955-4301-b8c0-127a47e9f8ed';
    $display->content['new-a424f24d-c955-4301-b8c0-127a47e9f8ed'] = $pane;
    $display->panels['middle'][0] = 'new-a424f24d-c955-4301-b8c0-127a47e9f8ed';
    $pane = new stdClass();
    $pane->pid = 'new-c42c9f01-3d90-433d-8170-0bb23c77b1be';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'foamtree-foamtree';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-sm-9',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'c42c9f01-3d90-433d-8170-0bb23c77b1be';
    $display->content['new-c42c9f01-3d90-433d-8170-0bb23c77b1be'] = $pane;
    $display->panels['middle'][1] = 'new-c42c9f01-3d90-433d-8170-0bb23c77b1be';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['glossary'] = $page;

  return $pages;

}
