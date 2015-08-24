<?php

/**
 * Class CountryReportsMigrateSourceList provides fields for CountryReports migration.
 */
class CountryReportsMigrateSourceList extends MigrateSourceList {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'title' => 'Meeting title',
      'title_orig' => 'Original title',
      'title_langs' => 'Title languages list',
      'treaty' => 'The meeting is linked to this treaty',
      'country' => 'Country',
      'submission' => 'Submission date',
      'files' => 'Decision files',
      'files_language' => 'Files language',
      'updated' => 'Updated',
    );
  }
}
