<?php

/**
 * Class NationalPlansODataMigration migrate OData contacts
 */
class NationalPlansODataMigration extends AbstractODataMigration {

  /**
   * @var ODataConsumerConfig
   */
  protected $config = NULL;

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->config = new ODataConsumerConfig($arguments);
    $this->arguments   = $arguments;
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_ACTION_PLAN, $this->config->odata_name);
    $this->source      = new NationalPlansMigrateSourceList(
      new ODataMigrateList($this->config),
      new NationalPlansODataMigrateItem($this->config)
    );
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Original ID from the MEA website',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode(
      ODataConsumerConfig::$DRUPAL_TYPE_ACTION_PLAN,
      array('text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'title_orig');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'title_langs');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_action_plan_type', 'type');
    $this->addFieldMapping('field_report_submission_date', 'submission');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_document_url', 'url');

    $this->addFieldMapping('field_action_plan_type:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_action_plan_type:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('changed', 'updated');

    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');

    $this->addUnmigratedDestinations(array(
      'created', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'body', 'body:summary', 'body:format', 'path',
      'body:language', 'field_action_plan_type:source_type',
      'field_report_submission_date:timezone', 'field_report_submission_date:rrule',
      'field_report_submission_date:to','field_document_url:title',
      'field_document_url:attributes', 'field_document_url:language',
      'field_files', 'field_files:file_class', 'field_files:language', 'field_files:preserve_files',
      'field_files:destination_dir', 'field_files:destination_file', 'field_files:file_replace',
      'field_files:source_dir', 'field_files:urlencode', 'field_files:display',
      'field_files:description', 'field_informea_tags', 'field_informea_tags:source_type',
      'field_informea_tags:create_term', 'field_informea_tags:ignore_case',
    ));
  }

  /**
   * Add some Contacts specific preparations.
   *
   * {@inheritdoc}
   */
  function prepareRow($row) {
    parent::prepareRow($row);

    if (!empty($row->submission)) {
      $row->submission = $this->fixDateValue($row->submission);
    }

    $row->treaty = $this->getTreatyByODataIdentifier($row->treaty)->nid;

  }

}
