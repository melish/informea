<?php

/**
 * Implements hook_migrate_api().
 */
function leo_migrate_migrate_api() {
  /**
   * Declare the api version and migration group.
   */
  $api = array(
    'api' => 2,
    'groups' => array(
      'imea_migrate' => array(
        'title' => t('Migrations from LEO website'),
      ),
      'migrations' => array(),
    ),
  );

  $common_arguments = array(
    'source_connection' => 'legacy',
    'source_database' => Database::getConnection('default', 'leo_informea')->getConnectionOptions(),
    'source_version' => 7,
    'group_name' => 'leo_migrate',
  );

  $vocabulary_arguments = array(
    'type_of_goal' => array(
      'description' => t('Migration of \'Type of goal\' terms from LEO.'),
      'source_vocabulary' => 'type_of_goal',
      'destination_vocabulary' => 'type_of_goal',
      'class_name' => 'LeoDefaultTaxonomyMigration',
    ),
    'goal_sources' => array(
      'description' => t('Migration of \'Goal sources\' terms from LEO.'),
      'source_vocabulary' => 'goal_sources',
      'destination_vocabulary' => 'goal_sources',
      'class_name' => 'LeoDefaultTaxonomyMigration',
    ),
  );

  foreach ($vocabulary_arguments as $migration_name => $arguments) {
    $arguments += $common_arguments;
    $api['migrations'][$migration_name] = $arguments;
  }

  return $api;
}