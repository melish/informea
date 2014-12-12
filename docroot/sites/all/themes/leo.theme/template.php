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
      $secondary = menu_secondary_local_tasks();

      array_unshift($vars['page']['sidebar_second'], $secondary);
    }
  }

  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }
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
  return '<span class="glyphicon glyphicon-remove"></span>';
}
