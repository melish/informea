<?php
/**
 * @file
 * template.php
 */

/**
 * Preprocesses variables for page template.
 *
 * @param $variables
 *   An associative array with generated variables.
 *
 * @return
 *   Nothing.
 */
function informea_theme_preprocess_page(&$variables) {
  $search_form = drupal_get_form('search_form');
  menu_secondary_local_tasks();
  if (arg(0) == 'taxonomy') {
    // Unset related terms in taxonomy page
    unset($variables['page']['content']['system_main']['nodes']);
    unset($variables['page']['content']['system_main']['pager']);
    unset($variables['page']['content']['system_main']['no_content']);
    $voc = taxonomy_vocabulary_machine_name_load('thesaurus_informea');
    /** @var stdClass $term */
    if ($term = taxonomy_term_load(arg(2))) {
      if ($term->vid == $voc->vid) {
        $variables['theme_hook_suggestions'][] = 'page__taxonomy__thesaurus_informea';
        $variables['content_column_class'] = ' class="col-sm-9"';
        array_unshift($variables['page']['sidebar_first'], menu_secondary_local_tasks());
      }
    }
  }
  if(isset($variables['node'])) {
    $node = $variables['node'];
    switch ($node->type) {
      case 'country':
        $variables['content_column_class'] = ' class="col-sm-9"';
        $variables['countries'] = country_get_countries_select_options();
        array_unshift($variables['page']['sidebar_first'], menu_secondary_local_tasks());
        break;

      case 'treaty':
        $variables['content_column_class'] = ' class="col-sm-9"';
        $variables['treaties'] = treaty_get_treaties_as_select_options();
        array_unshift($variables['page']['sidebar_first'], menu_secondary_local_tasks());
    }
  }
  if (isset($variables['node']->type)) {
    // $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
  }

  $search_form['basic']['keys']['#attributes']['placeholder'] = t('Explore InforMEA');
  $variables['search_box'] = drupal_render($search_form);

  if ($variables['is_front']) {
    // Loads the enabled countries.
    $variables['countries'] = countries_get_countries('name', array('enabled' => COUNTRIES_ENABLED));

    // Adds the front page JavaScript file to the page.
    drupal_add_js(drupal_get_path('theme', 'informea_theme') . '/js/front.js');
  }
}

/**
 * Performs alterations before a form is rendered.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 * @param $form_id
 *   String representing the name of the form itself.
 *
 * @return
 *   Nothing.
 */
function informea_theme_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_form') {
    $form['#attributes']['class'][] = 'navbar-form';
    $form['#attributes']['class'][] = 'navbar-right';
  }
}

function informea_theme_theme() {
  return array(
    'informea_bootstrap_collapse' => array(
      'render element' => 'element',
      'template' => 'templates/informea-bootstrap-collapse',
      'variables' => array('elements' => array(), 'id' => 0, 'no-data-parent' => FALSE, 'no-panel-body' => FALSE),
    ),
    'informea_bootstrap_tabs' => array(
      'render element' => 'element',
      'template' => 'templates/informea-bootstrap-tabs',
      'variables' => array('id' => 0, 'elements' => array(), 'active' => FALSE, 'header-attributes' => array()),
      'path' => drupal_get_path('theme', 'informea_theme'),
    ),
  );
}
