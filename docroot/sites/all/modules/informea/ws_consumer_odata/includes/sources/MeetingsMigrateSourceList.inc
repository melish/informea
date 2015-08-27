<?php

/**
 * Class MeetingsMigrateSourceList provides fields for Meetings migration.
 */
class MeetingsMigrateSourceList extends MigrateSourceList {

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
      'url' => 'Url',
      'start' => 'Start date',
      'end' => 'End date',
      'repetition' => 'Period of repetition',
      'kind' => 'Kind',
      'type' => 'Type',
      'access' => 'Access',
      'status' => 'Status',
      'imageUrl' => 'Image url',
      'location' => 'Location',
      'city' => 'City',
      'country' => 'Country',
      'latitude' => 'Latitude',
      'longitude' => 'Longitude',
      'updated' => 'Updated',
    );
  }
}
