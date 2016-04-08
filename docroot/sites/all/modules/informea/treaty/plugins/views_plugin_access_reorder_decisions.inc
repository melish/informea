<?php
// $Id$

/**
 * A plugin to handle access control based on the arguments.
 */
class views_plugin_access_reorder_decisions extends views_plugin_access {

  function summary_title() {
    return t('Permission to reorder decisions');
  }

  function access($account) {
    treaty_check_permission_reorder_decisions($account);
  }

  function get_access_callback() {
    global $user;
    return array('treaty_check_permission_reorder_decisions', array($user));
  }
}
