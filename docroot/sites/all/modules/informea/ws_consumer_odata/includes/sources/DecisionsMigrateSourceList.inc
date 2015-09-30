<?php

/**
 * Class DecisionsMigrateSourceList provides fields for Decisions migration.
 */
class DecisionsMigrateSourceList extends MigrateSourceList {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'title' => 'Decision title',
      'title_orig' => 'Original title',
      'title_langs' => 'Title languages list',
      'treaty' => 'The decision is linked to this treaty',
      'status' => 'Status',
      'type' => 'Type',
      'meetingId' => 'The decision is linked to this meeting',
      'meetingTitle' => 'Meeting title',
      'meetingUrl' => 'Meeting URL',
      'displayOrder' => 'Decisions display order',
      'number' => 'Number',
      'published' => 'Publication date',
      'files' => 'Decision files',
      'files_language' => 'Files language',
      'content' => 'Body field',
      'content_langs' => 'Body field language',
      'summary' => 'Body summary',
      'link' => 'URL',
      'filename' => 'filename',
      'updated' => 'Updated',
    );
  }
}
