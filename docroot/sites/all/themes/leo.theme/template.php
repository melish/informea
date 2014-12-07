<?php
/**
 * @file
 * template.php
 */

function leo_theme_preprocess_page(&$variables) {
  if(isset($variables['node'])) {
    $node = $variables['node'];
    if($node->type == 'country') {
      $variables['content_column_class'] = ' class="col-sm-9"';
      $secondary = menu_secondary_local_tasks();
      array_unshift($variables['page']['sidebar_second'], $secondary);
    }
  }
}
