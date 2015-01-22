<?php
/**
 * @file
 * template.php
 */

function leo_theme_preprocess_page(&$vars) {
  if(isset($vars['node'])) {
    $node = $vars['node'];

    if($node->type == 'country') {
      $vars['content_column_class'] = ' class="col-sm-9"';
      $vars['countries'] = country_get_countries_select_options();

      array_unshift($vars['page']['sidebar_second'], menu_secondary_local_tasks());
    }
  }

  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }
}

/**
 * Returns HTML for an inactive facet item.
 *
 * @param $variables
 *   An associative array containing the keys 'text', 'path', 'options', and
 *   'count'. See the l() and theme_facetapi_count() functions for information
 *   about these variables.
 *
 * @ingroup themeable
 */
function leo_theme_facetapi_link_inactive($variables) {
  // Builds accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => FALSE,
  );
  $accessible_markup = theme('facetapi_accessible_markup', $accessible_vars);

  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);
  $variables['text'] = ($sanitize) ? check_plain($variables['text']) : $variables['text'];

  // Adds count to link if one was passed.
  if (isset($variables['count'])) {
    $variables['text'] = theme('facetapi_count', $variables) . ' ' . $variables['text'];
  }

  // Resets link text, sets to options to HTML since we already sanitized the
  // link text and are providing additional markup for accessibility.
  $variables['text'] .= $accessible_markup;
  $variables['options']['html'] = TRUE;

  return theme_link($variables);
}

/**
 * Returns HTML for the active facet item's count.
 *
 * @param $variables
 *   An associative array containing:
 *   - count: The item's facet count.
 *
 * @ingroup themeable
 */
function leo_theme_facetapi_count($variables) {
  return '<span class="pull-right">' . (int) $variables['count'] . '</span>';
}

/**
 * Returns HTML for the deactivation widget.
 *
 * @param $variables
 *   An associative array containing the keys 'text', 'path', and 'options'. See
 *   the l() function for information about these variables.
 *
 * @see l()
 * @see theme_facetapi_link_active()
 *
 * @ingroup themable
 */
function leo_theme_facetapi_deactivate_widget($variables) {
  return '&times;';
}
