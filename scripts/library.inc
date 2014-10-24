<?php

function project_get_config() {
  static $json = NULL;
  if(empty($json)) {
    $config_file = sprintf('%s/../conf/config.json', dirname(__FILE__));
    if(!is_readable($config_file)) {
      die("Cannot read config file! ($config_file). Please configure your project correctly");
    }
    $json = json_decode(file_get_contents($config_file), TRUE);
  }
  return $json;
}


function project_pre_install_set_config_variables() {
  $json = project_get_config();
  if(!empty($json['variables']) && is_array($json['variables'])) {
    foreach($json['variables'] as $k => $v) {
      variable_set($k, $v);
    }
  }
}


function project_configure_solr() {
  $config_file = sprintf('%s/../conf/config.json', dirname(__FILE__));
  if(!is_readable($config_file)) {
    drupal_set_message("Cannot read configuration file!", 'warning');
    return;
  }
  $cfg = json_decode(file_get_contents($config_file), TRUE);
  if(empty($cfg)) {
    drupal_set_message('Configuration file was empty, nothing to do here', 'warning');
    return;
  }
  if(!empty($cfg['solr_server'])) {
    // Configure Search API: submit search_api_admin_add_server form
    if(module_exists('search_api') && module_load_include('inc', 'search_api', 'search_api.admin')) {
      drupal_set_message('Creating Solr server using machine name: search_server ...');
      $cfg = array_merge(
        array(
          'name' => 'Solr server',
          'enabled' => 1,
          'description' => 'Search server',
          'scheme' => 'http',
          'host' => 'localhost',
          'port' => '8983',
          'path' => '/solr',
          'http_user' => '',
          'http_password' => '',
          'excerpt' => NULL,
          'retrieve_data' => NULL,
          'highlight_data' => NULL,
          'skip_schema_check' => NULL,
          'solr_version' => '',
          'http_method' => 'AUTO'
        ), $cfg['solr_server']
      );
      $form_state = array(
        'values' => array(
          'machine_name' => 'solr_server',
          'class' => 'search_api_solr_service',
          'name' => $cfg['name'],
          'enabled' => $cfg['enabled'],
          'description' => $cfg['description'],
          'options' => array(
            'form' => array(
              'scheme' => $cfg['scheme'],
              'host' => $cfg['host'],
              'port' => $cfg['port'],
              'path' => $cfg['path'],
              'http' => array(
                'http_user' => $cfg['http_user'],
                'http_pass' => $cfg['http_pass'],
              ),
              'advanced' => array(
                'excerpt' => $cfg['excerpt'],
                'retrieve_data' => $cfg['retrieve_data'],
                'highlight_data' => $cfg['highlight_data'],
                'skip_schema_check' => $cfg['skip_schema_check'],
                'solr_version' => $cfg['solr_version'],
                'http_method' => $cfg['http_method'],
              )
            )
          )
        )
      );
      drupal_form_submit('search_api_admin_add_server', $form_state);
    }

    // Configure apachesolr: submit apachesolr_environment_edit_form
    if(module_exists('apachesolr') && module_load_include('inc', 'apachesolr', 'apachesolr.admin')) {
      drupal_set_message('Configuring Apachesolr search environment ...');

      $url = sprintf('%s://%s:%s%s', $cfg['scheme'], $cfg['host'], $cfg['port'], $cfg['path']);
      $env_id = apachesolr_default_environment();
      $environment = apachesolr_environment_load($env_id);

      $environment['url'] = $url;
      $environment['name'] = $cfg['name'];
      $environment['conf']['apachesolr_direct_commit'] = $cfg['apachesolr_direct_commit'];
      $environment['conf']['apachesolr_read_only'] = $cfg['apachesolr_read_only'];
      $environment['conf']['apachesolr_soft_commit'] = $cfg['apachesolr_soft_commit'];

      apachesolr_environment_save($environment);
      // @todo: See ticket #2527 - cannot make the form save new settings!
      // drupal_form_submit('apachesolr_environment_edit_form', $form_state, $environment);
    }
  } else {
    drupal_set_message('Unable to find solr_server section in config. Solr integration may be broken', 'warning');
  }
}


/**
 * Enlarge title field size to 768 characters
 */
function project_change_field_size() {
  $column_size = 2048;
  $spec = array('type' => 'varchar', 'length' => $column_size);
  $table = 'field_data_title_field';
  $column = 'title_field_value';

  if (_get_mysql_column_size($table, $column) < $column_size) {
    drupal_set_message("Changing $table size to $column_size");
    db_change_field($table, $column, $column, $spec);
  }
  $table = 'field_revision_title_field';
  if (_get_mysql_column_size($table, $column) < $column_size) {
    drupal_set_message("Changing $table size to $column_size");
    db_change_field($table, $column, $column, $spec);
  }

  $table = 'node';
  $column = 'title';
  if (_get_mysql_column_size($table, $column) < $column_size) {
    drupal_set_message("Changing $table size to $column_size");
    db_change_field($table, $column, $column, $spec);
  }

  $table = 'node_revision';
  if (_get_mysql_column_size($table, $column) < $column_size) {
    drupal_set_message("Changing $table size to $column_size");
    db_change_field($table, $column, $column, $spec);
  }
}

/**
 * Function to retrive the size of a MySQL varchar column from a table
 * @param string $table Table name
 * @param string $column Target column
 * @return int
 */
function _get_mysql_column_size($table, $column) {
  $result = db_query("
		SELECT CHARACTER_MAXIMUM_LENGTH
		FROM information_schema.columns
		WHERE table_schema = DATABASE()
			AND table_name = :table AND COLUMN_NAME = :column",
    array(':table' => $table, ':column' => $column)
  );
  return $result->fetchField(0);
}


function project_fix_administrator_role() {
  $all_permissions = array();
  foreach (module_list(FALSE, FALSE, TRUE) as $module) {
    if ($permissions = module_invoke($module, 'permission')) {
      $all_permissions += $permissions;
    }
  }
  $administrator = user_role_load_by_name('administrator');
  user_role_change_permissions($administrator->rid, $all_permissions);
}
