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
