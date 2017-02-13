<?php
/**
 * @file
 * thesaurus.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function thesaurus_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'term_view__panel';
  $handler->task = 'term_view';
  $handler->subtask = '';
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
    'access' => array(
      'logic' => 'and',
    ),
    'panels_breadcrumbs_home' => 0,
  );
  $display = new panels_display();
  $display->layout = 'flexible:thesaurus_term_page';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 1,
          1 => 6,
          2 => 11,
        ),
        'parent' => 'canvas',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 12,
          1 => 3,
          2 => 2,
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      2 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '1',
        'children' => array(
          0 => 5,
        ),
        'class' => 'col-sm-3 column-other-information',
        'hide_empty' => 0,
      ),
      3 => array(
        'type' => 'column',
        'width' => 25,
        'width_type' => '%',
        'parent' => '1',
        'children' => array(
          0 => 4,
        ),
        'class' => 'col-sm-6',
        'hide_empty' => 0,
      ),
      4 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'definition',
        ),
        'parent' => '3',
        'class' => '',
        'hide_empty' => 0,
      ),
      5 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'other_information',
        ),
        'parent' => '2',
        'class' => '',
        'hide_empty' => 0,
      ),
      'definition' => array(
        'type' => 'region',
        'title' => 'Definition',
        'width' => 100,
        'width_type' => '%',
        'parent' => '4',
        'class' => '',
        'hide_empty' => 0,
      ),
      'other_information' => array(
        'type' => 'region',
        'title' => 'Other information',
        'width' => 100,
        'width_type' => '%',
        'parent' => '5',
        'class' => '',
        'hide_empty' => 0,
      ),
      6 => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 8,
          1 => 7,
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      7 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '6',
        'children' => array(
          0 => 10,
        ),
        'class' => 'col-sm-3 taxonomy-term-related-content-facets',
        'hide_empty' => 0,
      ),
      8 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '6',
        'children' => array(
          0 => 9,
        ),
        'class' => 'col-sm-9 taxonomy-term-related-content',
        'hide_empty' => 0,
      ),
      9 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'tagged_content',
        ),
        'parent' => '8',
        'class' => '',
        'hide_empty' => 0,
      ),
      10 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'facets',
        ),
        'parent' => '7',
        'class' => '',
        'hide_empty' => 0,
      ),
      'tagged_content' => array(
        'type' => 'region',
        'title' => 'Tagged content',
        'width' => 100,
        'width_type' => '%',
        'parent' => '9',
        'class' => '',
        'hide_empty' => 0,
      ),
      'facets' => array(
        'type' => 'region',
        'title' => 'Facets',
        'width' => 100,
        'width_type' => '%',
        'parent' => '10',
        'class' => '',
        'hide_empty' => 0,
      ),
      11 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'full_width_content',
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      'full_width_content' => array(
        'type' => 'region',
        'title' => 'Full-width content',
        'width' => 100,
        'width_type' => '%',
        'parent' => '11',
        'class' => '',
        'hide_empty' => 0,
      ),
      12 => array(
        'type' => 'column',
        'width' => 25,
        'width_type' => '%',
        'parent' => '1',
        'children' => array(
          0 => 13,
        ),
        'class' => 'col-sm-3',
        'hide_empty' => 0,
      ),
      13 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'menu',
        ),
        'parent' => '12',
        'class' => '',
        'hide_empty' => 0,
      ),
      'menu' => array(
        'type' => 'region',
        'title' => 'Menu',
        'width' => 100,
        'width_type' => '%',
        'parent' => '13',
        'class' => '',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'definition' => NULL,
      'other_information' => NULL,
      'tagged_content' => NULL,
      'facets' => NULL,
      'full_width_content' => NULL,
      'menu' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%term:name_field';
  $display->uuid = 'f15da66a-69d9-457a-801b-753c2387aee3';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-84b6e493-1a73-47ee-8d80-0eb043271475';
    $pane->panel = 'definition';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:description_field';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_term_1',
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
    $pane->uuid = '84b6e493-1a73-47ee-8d80-0eb043271475';
    $display->content['new-84b6e493-1a73-47ee-8d80-0eb043271475'] = $pane;
    $display->panels['definition'][0] = 'new-84b6e493-1a73-47ee-8d80-0eb043271475';
    $pane = new stdClass();
    $pane->pid = 'new-91aa4fbd-98cf-4ca0-9124-ba0574762f7d';
    $pane->panel = 'full_width_content';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'secondary',
      'id' => 'tabs',
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
    $pane->uuid = '91aa4fbd-98cf-4ca0-9124-ba0574762f7d';
    $display->content['new-91aa4fbd-98cf-4ca0-9124-ba0574762f7d'] = $pane;
    $display->panels['full_width_content'][0] = 'new-91aa4fbd-98cf-4ca0-9124-ba0574762f7d';
    $pane = new stdClass();
    $pane->pid = 'new-a6655c2e-30e6-4aad-8ce7-ea4ed9932cca';
    $pane->panel = 'full_width_content';
    $pane->type = 'block';
    $pane->subtype = 'thesaurus-thesaurus-treaties';
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
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'a6655c2e-30e6-4aad-8ce7-ea4ed9932cca';
    $display->content['new-a6655c2e-30e6-4aad-8ce7-ea4ed9932cca'] = $pane;
    $display->panels['full_width_content'][1] = 'new-a6655c2e-30e6-4aad-8ce7-ea4ed9932cca';
    $pane = new stdClass();
    $pane->pid = 'new-76dfe5ee-1e9f-4f3d-9910-ab07146069ee';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'parent',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Broader',
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
    $pane->uuid = '76dfe5ee-1e9f-4f3d-9910-ab07146069ee';
    $display->content['new-76dfe5ee-1e9f-4f3d-9910-ab07146069ee'] = $pane;
    $display->panels['other_information'][0] = 'new-76dfe5ee-1e9f-4f3d-9910-ab07146069ee';
    $pane = new stdClass();
    $pane->pid = 'new-5725b358-3e85-45be-a700-63d519af7315';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'child',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Narrower',
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
    $pane->uuid = '5725b358-3e85-45be-a700-63d519af7315';
    $display->content['new-5725b358-3e85-45be-a700-63d519af7315'] = $pane;
    $display->panels['other_information'][1] = 'new-5725b358-3e85-45be-a700-63d519af7315';
    $pane = new stdClass();
    $pane->pid = 'new-27524512-75b9-453c-b279-6a96a3a97c21';
    $pane->panel = 'other_information';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:field_term_synonyms';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'textformatter_list',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
        'textformatter_type' => 'ul',
        'textformatter_class' => 'textformatter-list',
        'textformatter_comma_full_stop' => 0,
        'textformatter_comma_and' => 0,
        'textformatter_comma_tag' => 'div',
        'textformatter_comma_override' => 0,
        'textformatter_separator_custom' => '',
        'textformatter_separator_custom_tag' => 'span',
        'textformatter_separator_custom_class' => 'textformatter-separator',
      ),
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Synonyms',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '27524512-75b9-453c-b279-6a96a3a97c21';
    $display->content['new-27524512-75b9-453c-b279-6a96a3a97c21'] = $pane;
    $display->panels['other_information'][2] = 'new-27524512-75b9-453c-b279-6a96a3a97c21';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['term_view__panel'] = $handler;

  return $export;
}

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
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
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
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Glossary';
  $display->uuid = 'bff169cb-6a0a-4a4a-bc93-ac75704ee7e1';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-475aa95f-5da5-453f-a8e4-d94ca539b591';
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
    $pane->uuid = '475aa95f-5da5-453f-a8e4-d94ca539b591';
    $display->content['new-475aa95f-5da5-453f-a8e4-d94ca539b591'] = $pane;
    $display->panels['middle'][0] = 'new-475aa95f-5da5-453f-a8e4-d94ca539b591';
    $pane = new stdClass();
    $pane->pid = 'new-68b2f3ad-5970-48f4-9db7-413c59ba1072';
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
    $pane->uuid = '68b2f3ad-5970-48f4-9db7-413c59ba1072';
    $display->content['new-68b2f3ad-5970-48f4-9db7-413c59ba1072'] = $pane;
    $display->panels['middle'][1] = 'new-68b2f3ad-5970-48f4-9db7-413c59ba1072';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-475aa95f-5da5-453f-a8e4-d94ca539b591';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['glossary'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'thesaurus_bilateral_treaties';
  $page->task = 'page';
  $page->admin_title = 'Thesaurus - bilateral treaties';
  $page->admin_description = '';
  $page->path = 'taxonomy/term/%taxonomy_term/bilateral-treaties';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'taxonomy_term' => array(
      'id' => 1,
      'identifier' => 'Taxonomy term: ID',
      'name' => 'term',
      'settings' => array(
        'input_form' => 'tid',
        'vids' => array(
          14 => '14',
          15 => 0,
          16 => 0,
          22 => 0,
          2 => 0,
          21 => 0,
          23 => 0,
          20 => 0,
          17 => 0,
          33 => 0,
          34 => 0,
          6 => 0,
          3 => 0,
          36 => 0,
          41 => 0,
          42 => 0,
          43 => 0,
          24 => 0,
          37 => 0,
          38 => 0,
          39 => 0,
          4 => 0,
          35 => 0,
          5 => 0,
          25 => 0,
          44 => 0,
          26 => 0,
          27 => 0,
          31 => 0,
          18 => 0,
          32 => 0,
          1 => 0,
          19 => 0,
          9 => 0,
          40 => 0,
          11 => 0,
          13 => 0,
          7 => 0,
          10 => 0,
          12 => 0,
          28 => 0,
          30 => 0,
          29 => 0,
        ),
        'breadcrumb' => 0,
        'transform' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_thesaurus_bilateral_treaties__panel';
  $handler->task = 'page';
  $handler->subtask = 'thesaurus_bilateral_treaties';
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
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Glossary
%taxonomy_term:name_field
Legislations',
    'panels_breadcrumbs_paths' => '/terms
%taxonomy_term:url
<none>',
    'panels_breadcrumbs_home' => 1,
  );
  $display = new panels_display();
  $display->layout = 'flexible:thesaurus_term_page';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'definition' => NULL,
      'other_information' => NULL,
      'tagged_content' => NULL,
      'facets' => NULL,
      'full_width_content' => NULL,
      'menu' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%taxonomy_term:name_field';
  $display->uuid = 'f35c60aa-0ba0-4eda-840a-dadfd7ed2dfc';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-a97b66a2-03ab-4c34-b2d9-7d82dcf57f2a';
    $pane->panel = 'definition';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:description_field';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'expandText' => 'Expand »',
        'expandPrefix' => '...',
        'collapseTimer' => '',
        'slicePoint' => '50',
        'userCollapseText' => 'Collapse',
        'userCollapsePrefix' => '',
      ),
      'context' => 'argument_term_1',
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
    $pane->uuid = 'a97b66a2-03ab-4c34-b2d9-7d82dcf57f2a';
    $display->content['new-a97b66a2-03ab-4c34-b2d9-7d82dcf57f2a'] = $pane;
    $display->panels['definition'][0] = 'new-a97b66a2-03ab-4c34-b2d9-7d82dcf57f2a';
    $pane = new stdClass();
    $pane->pid = 'new-52c4d4eb-1127-4430-81a7-c5b530e0cdfb';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-EeqfYRvf4OeayxrDPBXmxh0uLs695r1S';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
    $pane->uuid = '52c4d4eb-1127-4430-81a7-c5b530e0cdfb';
    $display->content['new-52c4d4eb-1127-4430-81a7-c5b530e0cdfb'] = $pane;
    $display->panels['facets'][0] = 'new-52c4d4eb-1127-4430-81a7-c5b530e0cdfb';
    $pane = new stdClass();
    $pane->pid = 'new-40aee080-9765-46b7-93d8-a33b980de132';
    $pane->panel = 'full_width_content';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'secondary',
      'id' => 'tabs',
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
    $pane->uuid = '40aee080-9765-46b7-93d8-a33b980de132';
    $display->content['new-40aee080-9765-46b7-93d8-a33b980de132'] = $pane;
    $display->panels['full_width_content'][0] = 'new-40aee080-9765-46b7-93d8-a33b980de132';
    $pane = new stdClass();
    $pane->pid = 'new-b8ea2b6a-4f24-42f9-bdd1-28fe6be150f2';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'parent',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Broader',
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
    $pane->uuid = 'b8ea2b6a-4f24-42f9-bdd1-28fe6be150f2';
    $display->content['new-b8ea2b6a-4f24-42f9-bdd1-28fe6be150f2'] = $pane;
    $display->panels['other_information'][0] = 'new-b8ea2b6a-4f24-42f9-bdd1-28fe6be150f2';
    $pane = new stdClass();
    $pane->pid = 'new-bdd81592-bf4c-43b2-a0ef-28206a674e4a';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'child',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Narrower',
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
    $pane->uuid = 'bdd81592-bf4c-43b2-a0ef-28206a674e4a';
    $display->content['new-bdd81592-bf4c-43b2-a0ef-28206a674e4a'] = $pane;
    $display->panels['other_information'][1] = 'new-bdd81592-bf4c-43b2-a0ef-28206a674e4a';
    $pane = new stdClass();
    $pane->pid = 'new-ac1d8da1-b969-4f4a-9534-e855043e0c74';
    $pane->panel = 'other_information';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:field_term_synonyms';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'textformatter_list',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'textformatter_type' => 'ul',
        'textformatter_class' => 'textformatter-list',
        'textformatter_comma_full_stop' => 0,
        'textformatter_comma_and' => 0,
        'textformatter_comma_tag' => 'div',
        'textformatter_comma_override' => 0,
        'textformatter_separator_custom' => '',
        'textformatter_separator_custom_tag' => 'span',
        'textformatter_separator_custom_class' => 'textformatter-separator',
      ),
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Synonyms',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'ac1d8da1-b969-4f4a-9534-e855043e0c74';
    $display->content['new-ac1d8da1-b969-4f4a-9534-e855043e0c74'] = $pane;
    $display->panels['other_information'][2] = 'new-ac1d8da1-b969-4f4a-9534-e855043e0c74';
    $pane = new stdClass();
    $pane->pid = 'new-7e5d8635-376d-4a2f-953c-13ac2cd1231c';
    $pane->panel = 'tagged_content';
    $pane->type = 'views';
    $pane->subtype = 'taxonomy_term_related_bilateral_treaties';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '20',
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
        0 => 'argument_term_1.tid',
      ),
      'override_title' => 1,
      'override_title_text' => 'Content tagged with "%taxonomy_term:name_field"',
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
    $pane->uuid = '7e5d8635-376d-4a2f-953c-13ac2cd1231c';
    $display->content['new-7e5d8635-376d-4a2f-953c-13ac2cd1231c'] = $pane;
    $display->panels['tagged_content'][0] = 'new-7e5d8635-376d-4a2f-953c-13ac2cd1231c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['thesaurus_bilateral_treaties'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'thesaurus_court_decisions';
  $page->task = 'page';
  $page->admin_title = 'Thesaurus - court decisions';
  $page->admin_description = '';
  $page->path = 'taxonomy/term/%taxonomy_term/court-decisions';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'taxonomy_term' => array(
      'id' => 1,
      'identifier' => 'Taxonomy term: ID',
      'name' => 'term',
      'settings' => array(
        'input_form' => 'tid',
        'vids' => array(
          14 => '14',
          15 => 0,
          16 => 0,
          22 => 0,
          2 => 0,
          21 => 0,
          23 => 0,
          20 => 0,
          17 => 0,
          33 => 0,
          34 => 0,
          6 => 0,
          3 => 0,
          36 => 0,
          41 => 0,
          42 => 0,
          43 => 0,
          24 => 0,
          37 => 0,
          38 => 0,
          39 => 0,
          4 => 0,
          35 => 0,
          5 => 0,
          25 => 0,
          44 => 0,
          26 => 0,
          27 => 0,
          31 => 0,
          18 => 0,
          32 => 0,
          1 => 0,
          19 => 0,
          9 => 0,
          40 => 0,
          11 => 0,
          13 => 0,
          7 => 0,
          10 => 0,
          12 => 0,
          28 => 0,
          30 => 0,
          29 => 0,
        ),
        'breadcrumb' => 0,
        'transform' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_thesaurus_court_decisions__panel';
  $handler->task = 'page';
  $handler->subtask = 'thesaurus_court_decisions';
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
    'access' => array(
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Glossary
%taxonomy_term:name_field
Court decisions',
    'panels_breadcrumbs_paths' => '/terms
%taxonomy_term:url
<none>',
    'panels_breadcrumbs_home' => 1,
  );
  $display = new panels_display();
  $display->layout = 'flexible:thesaurus_term_page';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'definition' => NULL,
      'other_information' => NULL,
      'tagged_content' => NULL,
      'facets' => NULL,
      'full_width_content' => NULL,
      'menu' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%taxonomy_term:name_field';
  $display->uuid = 'f15da66a-69d9-457a-801b-753c2387aee3';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-84b6e493-1a73-47ee-8d80-0eb043271475';
    $pane->panel = 'definition';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:description_field';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_term_1',
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
    $pane->uuid = '84b6e493-1a73-47ee-8d80-0eb043271475';
    $display->content['new-84b6e493-1a73-47ee-8d80-0eb043271475'] = $pane;
    $display->panels['definition'][0] = 'new-84b6e493-1a73-47ee-8d80-0eb043271475';
    $pane = new stdClass();
    $pane->pid = 'new-5e2ddf60-c47c-4b37-aa45-58f6bf4c934c';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-fdq04xNUyxSV1CkoyeTHIwwlufwxjcFK';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Region',
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
    $pane->uuid = '5e2ddf60-c47c-4b37-aa45-58f6bf4c934c';
    $display->content['new-5e2ddf60-c47c-4b37-aa45-58f6bf4c934c'] = $pane;
    $display->panels['facets'][0] = 'new-5e2ddf60-c47c-4b37-aa45-58f6bf4c934c';
    $pane = new stdClass();
    $pane->pid = 'new-d68d5ebb-82c7-4581-849d-8bf8c88579eb';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-jX6n57R09128yKk8mDTq4yM84f6PAh5a';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Country',
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
    $pane->uuid = 'd68d5ebb-82c7-4581-849d-8bf8c88579eb';
    $display->content['new-d68d5ebb-82c7-4581-849d-8bf8c88579eb'] = $pane;
    $display->panels['facets'][1] = 'new-d68d5ebb-82c7-4581-849d-8bf8c88579eb';
    $pane = new stdClass();
    $pane->pid = 'new-c06ab238-4cc2-45b6-bb1e-80ea20e9f8c3';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-ABol1qBh79jsfGqF27usDpaBznEzCn7M';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Type of text',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'c06ab238-4cc2-45b6-bb1e-80ea20e9f8c3';
    $display->content['new-c06ab238-4cc2-45b6-bb1e-80ea20e9f8c3'] = $pane;
    $display->panels['facets'][2] = 'new-c06ab238-4cc2-45b6-bb1e-80ea20e9f8c3';
    $pane = new stdClass();
    $pane->pid = 'new-5fa30ddb-06fb-4476-9a65-1f0889d35581';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-AXPJXX5P37Swm7dwbcF395wDS4ZQbaYl';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Date of text',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '5fa30ddb-06fb-4476-9a65-1f0889d35581';
    $display->content['new-5fa30ddb-06fb-4476-9a65-1f0889d35581'] = $pane;
    $display->panels['facets'][3] = 'new-5fa30ddb-06fb-4476-9a65-1f0889d35581';
    $pane = new stdClass();
    $pane->pid = 'new-91aa4fbd-98cf-4ca0-9124-ba0574762f7d';
    $pane->panel = 'full_width_content';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'secondary',
      'id' => 'tabs',
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
    $pane->uuid = '91aa4fbd-98cf-4ca0-9124-ba0574762f7d';
    $display->content['new-91aa4fbd-98cf-4ca0-9124-ba0574762f7d'] = $pane;
    $display->panels['full_width_content'][0] = 'new-91aa4fbd-98cf-4ca0-9124-ba0574762f7d';
    $pane = new stdClass();
    $pane->pid = 'new-76dfe5ee-1e9f-4f3d-9910-ab07146069ee';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'parent',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Broader',
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
    $pane->uuid = '76dfe5ee-1e9f-4f3d-9910-ab07146069ee';
    $display->content['new-76dfe5ee-1e9f-4f3d-9910-ab07146069ee'] = $pane;
    $display->panels['other_information'][0] = 'new-76dfe5ee-1e9f-4f3d-9910-ab07146069ee';
    $pane = new stdClass();
    $pane->pid = 'new-5725b358-3e85-45be-a700-63d519af7315';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'child',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Narrower',
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
    $pane->uuid = '5725b358-3e85-45be-a700-63d519af7315';
    $display->content['new-5725b358-3e85-45be-a700-63d519af7315'] = $pane;
    $display->panels['other_information'][1] = 'new-5725b358-3e85-45be-a700-63d519af7315';
    $pane = new stdClass();
    $pane->pid = 'new-27524512-75b9-453c-b279-6a96a3a97c21';
    $pane->panel = 'other_information';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:field_term_synonyms';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'textformatter_list',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => '',
        'title_class' => '',
        'textformatter_type' => 'ul',
        'textformatter_class' => 'textformatter-list',
        'textformatter_comma_full_stop' => 0,
        'textformatter_comma_and' => 0,
        'textformatter_comma_tag' => 'div',
        'textformatter_comma_override' => 0,
        'textformatter_separator_custom' => '',
        'textformatter_separator_custom_tag' => 'span',
        'textformatter_separator_custom_class' => 'textformatter-separator',
      ),
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Synonyms',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '27524512-75b9-453c-b279-6a96a3a97c21';
    $display->content['new-27524512-75b9-453c-b279-6a96a3a97c21'] = $pane;
    $display->panels['other_information'][2] = 'new-27524512-75b9-453c-b279-6a96a3a97c21';
    $pane = new stdClass();
    $pane->pid = 'new-2b8e332f-09f4-4e6c-ac37-bdcbc4a0a8c0';
    $pane->panel = 'tagged_content';
    $pane->type = 'views';
    $pane->subtype = 'taxonomy_term_related_court_decisions';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '20',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 1,
      'override_title_text' => 'Content tagged with "%taxonomy_term:name_field"',
      'override_title_heading' => 'h2',
      'context' => array(
        0 => 'argument_term_1.tid',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '2b8e332f-09f4-4e6c-ac37-bdcbc4a0a8c0';
    $display->content['new-2b8e332f-09f4-4e6c-ac37-bdcbc4a0a8c0'] = $pane;
    $display->panels['tagged_content'][0] = 'new-2b8e332f-09f4-4e6c-ac37-bdcbc4a0a8c0';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['thesaurus_court_decisions'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'thesaurus_legislations';
  $page->task = 'page';
  $page->admin_title = 'Thesaurus - legislations';
  $page->admin_description = '';
  $page->path = 'taxonomy/term/%taxonomy_term/legislations';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'taxonomy_term' => array(
      'id' => 1,
      'identifier' => 'Taxonomy term: ID',
      'name' => 'term',
      'settings' => array(
        'input_form' => 'tid',
        'vids' => array(
          14 => '14',
          15 => 0,
          16 => 0,
          22 => 0,
          2 => 0,
          21 => 0,
          23 => 0,
          20 => 0,
          17 => 0,
          33 => 0,
          34 => 0,
          6 => 0,
          3 => 0,
          36 => 0,
          41 => 0,
          42 => 0,
          43 => 0,
          24 => 0,
          37 => 0,
          38 => 0,
          39 => 0,
          4 => 0,
          35 => 0,
          5 => 0,
          25 => 0,
          44 => 0,
          26 => 0,
          27 => 0,
          31 => 0,
          18 => 0,
          32 => 0,
          1 => 0,
          19 => 0,
          9 => 0,
          40 => 0,
          11 => 0,
          13 => 0,
          7 => 0,
          10 => 0,
          12 => 0,
          28 => 0,
          30 => 0,
          29 => 0,
        ),
        'breadcrumb' => 0,
        'transform' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_thesaurus_legislations__panel';
  $handler->task = 'page';
  $handler->subtask = 'thesaurus_legislations';
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
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Glossary
%taxonomy_term:name_field
Legislations',
    'panels_breadcrumbs_paths' => '/terms
%taxonomy_term:url
<none>',
    'panels_breadcrumbs_home' => 1,
  );
  $display = new panels_display();
  $display->layout = 'flexible:thesaurus_term_page';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'definition' => NULL,
      'other_information' => NULL,
      'tagged_content' => NULL,
      'facets' => NULL,
      'full_width_content' => NULL,
      'menu' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%taxonomy_term:name_field';
  $display->uuid = '79bae11c-52d5-4ddd-a15f-12dd300f4592';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-3d95e9a0-f096-4231-b3e7-f0896c85bddd';
    $pane->panel = 'definition';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:description_field';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'expandText' => 'Expand »',
        'expandPrefix' => '...',
        'collapseTimer' => '',
        'slicePoint' => '50',
        'userCollapseText' => 'Collapse',
        'userCollapsePrefix' => '',
      ),
      'context' => 'argument_term_1',
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
    $pane->uuid = '3d95e9a0-f096-4231-b3e7-f0896c85bddd';
    $display->content['new-3d95e9a0-f096-4231-b3e7-f0896c85bddd'] = $pane;
    $display->panels['definition'][0] = 'new-3d95e9a0-f096-4231-b3e7-f0896c85bddd';
    $pane = new stdClass();
    $pane->pid = 'new-79088584-ec54-4803-8a76-8091bb67474b';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-IhbpziRRQ04ohXLVPOH1pzkj01ySLvut';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Country',
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
    $pane->uuid = '79088584-ec54-4803-8a76-8091bb67474b';
    $display->content['new-79088584-ec54-4803-8a76-8091bb67474b'] = $pane;
    $display->panels['facets'][0] = 'new-79088584-ec54-4803-8a76-8091bb67474b';
    $pane = new stdClass();
    $pane->pid = 'new-d7166f60-3bff-462e-b761-307e263ef38b';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-EBe4nF0bWIclTeTpPk5EfoKyGT3EgxZw';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Region',
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
    $pane->uuid = 'd7166f60-3bff-462e-b761-307e263ef38b';
    $display->content['new-d7166f60-3bff-462e-b761-307e263ef38b'] = $pane;
    $display->panels['facets'][1] = 'new-d7166f60-3bff-462e-b761-307e263ef38b';
    $pane = new stdClass();
    $pane->pid = 'new-6fa8410e-51bc-4fe2-a850-0ede9b70349a';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-bhF7dlwZfRYrATVWsYC6eOvTl9pFOHHh';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Type of text',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '6fa8410e-51bc-4fe2-a850-0ede9b70349a';
    $display->content['new-6fa8410e-51bc-4fe2-a850-0ede9b70349a'] = $pane;
    $display->panels['facets'][2] = 'new-6fa8410e-51bc-4fe2-a850-0ede9b70349a';
    $pane = new stdClass();
    $pane->pid = 'new-7149f866-3985-49ab-b9d2-f6825b9badbe';
    $pane->panel = 'full_width_content';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'secondary',
      'id' => 'tabs',
      'override_title' => 1,
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
    $pane->uuid = '7149f866-3985-49ab-b9d2-f6825b9badbe';
    $display->content['new-7149f866-3985-49ab-b9d2-f6825b9badbe'] = $pane;
    $display->panels['full_width_content'][0] = 'new-7149f866-3985-49ab-b9d2-f6825b9badbe';
    $pane = new stdClass();
    $pane->pid = 'new-704db316-42d4-43ae-b665-a15214973e7e';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'parent',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Broader',
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
    $pane->uuid = '704db316-42d4-43ae-b665-a15214973e7e';
    $display->content['new-704db316-42d4-43ae-b665-a15214973e7e'] = $pane;
    $display->panels['other_information'][0] = 'new-704db316-42d4-43ae-b665-a15214973e7e';
    $pane = new stdClass();
    $pane->pid = 'new-90b964cd-f523-4489-a969-a63b6824d2dd';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'child',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Narrower',
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
    $pane->uuid = '90b964cd-f523-4489-a969-a63b6824d2dd';
    $display->content['new-90b964cd-f523-4489-a969-a63b6824d2dd'] = $pane;
    $display->panels['other_information'][1] = 'new-90b964cd-f523-4489-a969-a63b6824d2dd';
    $pane = new stdClass();
    $pane->pid = 'new-eccecd17-7675-4501-bb54-dac15e2c7e04';
    $pane->panel = 'other_information';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:field_term_synonyms';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'text_default',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(),
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Synonyms',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'eccecd17-7675-4501-bb54-dac15e2c7e04';
    $display->content['new-eccecd17-7675-4501-bb54-dac15e2c7e04'] = $pane;
    $display->panels['other_information'][2] = 'new-eccecd17-7675-4501-bb54-dac15e2c7e04';
    $pane = new stdClass();
    $pane->pid = 'new-0ff8a402-ded1-4dd1-9d24-2b8f11ca8af6';
    $pane->panel = 'tagged_content';
    $pane->type = 'views';
    $pane->subtype = 'taxonomy_term_related_legislations';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '20',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'context' => array(
        0 => 'argument_term_1.tid',
      ),
      'override_title' => 1,
      'override_title_text' => 'Content tagged with "%taxonomy_term:name_field"',
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
    $pane->uuid = '0ff8a402-ded1-4dd1-9d24-2b8f11ca8af6';
    $display->content['new-0ff8a402-ded1-4dd1-9d24-2b8f11ca8af6'] = $pane;
    $display->panels['tagged_content'][0] = 'new-0ff8a402-ded1-4dd1-9d24-2b8f11ca8af6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-3d95e9a0-f096-4231-b3e7-f0896c85bddd';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['thesaurus_legislations'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'thesaurus_literatures';
  $page->task = 'page';
  $page->admin_title = 'Thesaurus - literatures';
  $page->admin_description = '';
  $page->path = 'taxonomy/term/%taxonomy_term/literatures';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'taxonomy_term' => array(
      'id' => 1,
      'identifier' => 'Taxonomy term: ID',
      'name' => 'term',
      'settings' => array(
        'input_form' => 'tid',
        'vids' => array(
          14 => '14',
          15 => 0,
          16 => 0,
          22 => 0,
          2 => 0,
          21 => 0,
          23 => 0,
          20 => 0,
          17 => 0,
          33 => 0,
          34 => 0,
          6 => 0,
          3 => 0,
          36 => 0,
          41 => 0,
          42 => 0,
          43 => 0,
          24 => 0,
          37 => 0,
          38 => 0,
          39 => 0,
          4 => 0,
          35 => 0,
          5 => 0,
          25 => 0,
          44 => 0,
          26 => 0,
          27 => 0,
          31 => 0,
          18 => 0,
          32 => 0,
          1 => 0,
          19 => 0,
          9 => 0,
          40 => 0,
          11 => 0,
          13 => 0,
          7 => 0,
          10 => 0,
          12 => 0,
          28 => 0,
          30 => 0,
          29 => 0,
        ),
        'breadcrumb' => 0,
        'transform' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_thesaurus_literatures__panel';
  $handler->task = 'page';
  $handler->subtask = 'thesaurus_literatures';
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
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Glossary
%taxonomy_term:name_field
Literatures',
    'panels_breadcrumbs_paths' => '/terms
%taxonomy_term:url
<none>',
    'panels_breadcrumbs_home' => 1,
  );
  $display = new panels_display();
  $display->layout = 'flexible:thesaurus_term_page';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'definition' => NULL,
      'other_information' => NULL,
      'tagged_content' => NULL,
      'facets' => NULL,
      'full_width_content' => NULL,
      'menu' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%taxonomy_term:name_field';
  $display->uuid = '4a6ae773-5f26-43cd-b378-491206474aaf';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-287a5eba-4472-41a7-980d-840574a89ad6';
    $pane->panel = 'definition';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:description_field';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_term_1',
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
    $pane->uuid = '287a5eba-4472-41a7-980d-840574a89ad6';
    $display->content['new-287a5eba-4472-41a7-980d-840574a89ad6'] = $pane;
    $display->panels['definition'][0] = 'new-287a5eba-4472-41a7-980d-840574a89ad6';
    $pane = new stdClass();
    $pane->pid = 'new-a6eb2271-2331-48c0-b5b8-3a03653c696e';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-p9WcWVBg1G8eNqrSM10du4dp9e1NAuLR';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Country',
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
    $pane->uuid = 'a6eb2271-2331-48c0-b5b8-3a03653c696e';
    $display->content['new-a6eb2271-2331-48c0-b5b8-3a03653c696e'] = $pane;
    $display->panels['facets'][0] = 'new-a6eb2271-2331-48c0-b5b8-3a03653c696e';
    $pane = new stdClass();
    $pane->pid = 'new-2188a521-20ac-4d4f-920c-384df3aa3278';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-HEmkPZqeT0zhhPkPHy81Br53u3i3pN1x';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Geographical scope',
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
    $pane->uuid = '2188a521-20ac-4d4f-920c-384df3aa3278';
    $display->content['new-2188a521-20ac-4d4f-920c-384df3aa3278'] = $pane;
    $display->panels['facets'][1] = 'new-2188a521-20ac-4d4f-920c-384df3aa3278';
    $pane = new stdClass();
    $pane->pid = 'new-9dba67c3-b1b2-4155-bdeb-6915c413a67d';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-lwGfxWf5h8Kx3R4o7n1RvBsw0ZrJJ4qN';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Publication Place',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '9dba67c3-b1b2-4155-bdeb-6915c413a67d';
    $display->content['new-9dba67c3-b1b2-4155-bdeb-6915c413a67d'] = $pane;
    $display->panels['facets'][2] = 'new-9dba67c3-b1b2-4155-bdeb-6915c413a67d';
    $pane = new stdClass();
    $pane->pid = 'new-e99872fb-a155-4bdf-8636-b0eda6696e51';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-hHFp4hC2AL6C8acdwH93ZO7CG1T9Bdjh';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Literature type',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'e99872fb-a155-4bdf-8636-b0eda6696e51';
    $display->content['new-e99872fb-a155-4bdf-8636-b0eda6696e51'] = $pane;
    $display->panels['facets'][3] = 'new-e99872fb-a155-4bdf-8636-b0eda6696e51';
    $pane = new stdClass();
    $pane->pid = 'new-a15aa67b-6cec-43c9-918b-b36391c77589';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-BE41Y0ukWcJC4Q0JoNSqDH1shcPk05zA';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Region',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'a15aa67b-6cec-43c9-918b-b36391c77589';
    $display->content['new-a15aa67b-6cec-43c9-918b-b36391c77589'] = $pane;
    $display->panels['facets'][4] = 'new-a15aa67b-6cec-43c9-918b-b36391c77589';
    $pane = new stdClass();
    $pane->pid = 'new-06f8a1e1-c8ad-4218-b528-809bed6fc1a2';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-QyLdjrjTJBkP8bCwICExitKlISp0s8fy';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Territorial subdivision',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '06f8a1e1-c8ad-4218-b528-809bed6fc1a2';
    $display->content['new-06f8a1e1-c8ad-4218-b528-809bed6fc1a2'] = $pane;
    $display->panels['facets'][5] = 'new-06f8a1e1-c8ad-4218-b528-809bed6fc1a2';
    $pane = new stdClass();
    $pane->pid = 'new-0edc1a58-fbd7-434e-8ffa-581448358fdd';
    $pane->panel = 'facets';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-2inj02S8SSDr0L3OF8hraGUH3abtqIC6';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Treaty',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 6;
    $pane->locks = array();
    $pane->uuid = '0edc1a58-fbd7-434e-8ffa-581448358fdd';
    $display->content['new-0edc1a58-fbd7-434e-8ffa-581448358fdd'] = $pane;
    $display->panels['facets'][6] = 'new-0edc1a58-fbd7-434e-8ffa-581448358fdd';
    $pane = new stdClass();
    $pane->pid = 'new-bc555204-4c95-4c9a-b02e-92b0d4f4516e';
    $pane->panel = 'full_width_content';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'secondary',
      'id' => 'tabs',
      'override_title' => 1,
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
    $pane->uuid = 'bc555204-4c95-4c9a-b02e-92b0d4f4516e';
    $display->content['new-bc555204-4c95-4c9a-b02e-92b0d4f4516e'] = $pane;
    $display->panels['full_width_content'][0] = 'new-bc555204-4c95-4c9a-b02e-92b0d4f4516e';
    $pane = new stdClass();
    $pane->pid = 'new-5287915e-539f-49c7-97e0-9bac8611410e';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'parent',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Broader',
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
    $pane->uuid = '5287915e-539f-49c7-97e0-9bac8611410e';
    $display->content['new-5287915e-539f-49c7-97e0-9bac8611410e'] = $pane;
    $display->panels['other_information'][0] = 'new-5287915e-539f-49c7-97e0-9bac8611410e';
    $pane = new stdClass();
    $pane->pid = 'new-b62e13d0-d508-4635-8f1f-8b4b241cb4cf';
    $pane->panel = 'other_information';
    $pane->type = 'term_list';
    $pane->subtype = 'term_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'title' => NULL,
      'type' => 'child',
      'include_current_term' => 0,
      'list_type' => 'ul',
      'path' => 'taxonomy/term',
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Narrower',
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
    $pane->uuid = 'b62e13d0-d508-4635-8f1f-8b4b241cb4cf';
    $display->content['new-b62e13d0-d508-4635-8f1f-8b4b241cb4cf'] = $pane;
    $display->panels['other_information'][1] = 'new-b62e13d0-d508-4635-8f1f-8b4b241cb4cf';
    $pane = new stdClass();
    $pane->pid = 'new-6bd77781-58a1-47ac-99c9-108b15d6e244';
    $pane->panel = 'other_information';
    $pane->type = 'entity_field';
    $pane->subtype = 'taxonomy_term:field_term_synonyms';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'text_plain',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(),
      'context' => 'argument_term_1',
      'override_title' => 1,
      'override_title_text' => 'Synonyms',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '6bd77781-58a1-47ac-99c9-108b15d6e244';
    $display->content['new-6bd77781-58a1-47ac-99c9-108b15d6e244'] = $pane;
    $display->panels['other_information'][2] = 'new-6bd77781-58a1-47ac-99c9-108b15d6e244';
    $pane = new stdClass();
    $pane->pid = 'new-cff16a75-7f72-4e16-ab11-25eb5ffe1f2e';
    $pane->panel = 'tagged_content';
    $pane->type = 'views';
    $pane->subtype = 'taxonomy_term_related_literatures';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'context' => array(
        0 => 'argument_term_1.tid',
      ),
      'override_title' => 1,
      'override_title_text' => 'Content tagged with "%taxonomy_term:name_field"',
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
    $pane->uuid = 'cff16a75-7f72-4e16-ab11-25eb5ffe1f2e';
    $display->content['new-cff16a75-7f72-4e16-ab11-25eb5ffe1f2e'] = $pane;
    $display->panels['tagged_content'][0] = 'new-cff16a75-7f72-4e16-ab11-25eb5ffe1f2e';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['thesaurus_literatures'] = $page;

  return $pages;

}
