<?php

/**
 * Class ContactsODataMigration migrate OData contacts
 */
class ContactsODataMigration extends AbstractODataMigration {

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
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_CONTACTS, $this->config->odata_name);
    $this->source      = new ContactsMigrateSourceList(
      new ODataMigrateList($this->config),
      new ContactsODataMigrateItem($this->config)
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
      ODataConsumerConfig::$DRUPAL_TYPE_CONTACTS,
      array('text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'name');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_treaty', 'treaties');
    $this->addFieldMapping('field_person_prefix', 'prefix');
    $this->addFieldMapping('field_person_first_name', 'firstName');
    $this->addFieldMapping('field_person_last_name', 'lastName');
    $this->addFieldMapping('field_person_position', 'position');
    $this->addFieldMapping('field_person_institution', 'institution');
    $this->addFieldMapping('field_person_department', 'department');
    $this->addFieldMapping('field_address', 'address');
    $this->addFieldMapping('field_person_email', 'email');
    $this->addFieldMapping('field_contact_telephone', 'phone');
    $this->addFieldMapping('field_contact_fax', 'fax');
    $this->addFieldMapping('field_contact_primary_nfp', 'primary');

    $this->addFieldMapping('field_person_type', 'type');
    $this->addFieldMapping('field_person_type:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_person_type:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('changed', 'updated');

    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue(LANGUAGE_NONE);

    $this->addUnmigratedDestinations(array(
      'created', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'body', 'body:summary', 'body:format',
      'field_person_position:language', 'field_person_institution:language',
      'field_person_prefix:language', 'field_person_type:source_type', 'path',
      'body:language',
    ));
  }

  /**
   * Add some Contacts specific preparations.
   *
   * {@inheritdoc}
   */
  function prepareRow($row) {
    parent::prepareRow($row);
    $row->name = $this->getContactName($row);

    // Prepare the treaties property
    foreach($row->treaties as &$identifier) {
      $node = $this->getTreatyByODataIdentifier($identifier);
      $identifier = $node->nid;
    }
    return $this->validateRow($row);
  }

  /**
   * Validate Contact. Must have 'treaties' and 'name' not empty.
   *
   * @param stdClass $row
   *   Object to validate.
   *
   * @return bool
   *   FALSE if row is invalid
   */
  function validateRow($row) {
    $valid = (!empty($row->treaties) && !empty($row->name));
    if (!$valid) {
      ws_consumer_odata_log(__METHOD__ . "(): Validation failed for Contact({$row->id})", MigrationBase::MESSAGE_ERROR);
    }
    return $valid;
  }

  /**
   * Try our best to build the contact name from the data we have available.
   *
   * @param stdClass $row
   *   OData object
   *
   * @return null|string
   *   Contact name or NULL when everything fails
   */
  protected function getContactName($row) {
    $name = NULL;
    if (!empty($row->firstName)) {
      $name = $row->firstName;
    }
    if (!empty($row->lastName)) {
      if (!empty($row->firstName)) {
        $name .= ' ';
      }
      $name .= $row->lastName;;
    }
    if (empty($name) && !empty($row->position)) {
      $name = $row->position;
    }
    if (empty($name) && !empty($row->institution)) {
      $name = $row->institution;
    }
    $name = trim($name);
    return $name;
  }
}
