<?php
/**
 * @file
 * informea.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function informea_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'update front_page_slider entityqueue'.
  $permissions['update front_page_slider entityqueue'] = array(
    'name' => 'update front_page_slider entityqueue',
    'roles' => array(),
    'module' => 'entityqueue',
  );

  return $permissions;
}
