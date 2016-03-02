<?php

require_once 'vendor/autoload.php';
require_once 'Base.php';

/**
 * Use drush scr filename to run these tests
 */
class ContactsODataImportTest extends PHPUnit_Framework_TestCase {

  function setUp() {
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_CONTACTS,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_CBD,
    );
    MigrationBase::registerMigration('ContactsODataMigration', 'test_contacts_odata_v3', $config);
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_CONTACTS,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_ROTTERDAM,
    );
    MigrationBase::registerMigration('ContactsODataMigration', 'test_contacts_odata_v1', $config);
  }

  function testV3() {
    $migration = MigrationBase::getInstance('test_contacts_odata_v3');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_contacts_odata_v3')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_contacts_odata_v3', 'a')->fields('a', array('destid1'))->condition('sourceid1', '52000000cbd02200000018e9')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);

    $this->assertEquals('52000000cbd02200000018e9', $w->field_original_id->value());
    $countries = $w->field_country->value();
    $this->assertEquals(1, count($countries));
    $this->assertEquals('Barbados', $countries[0]->title);
    $this->assertEquals('Mr.', $w->field_person_prefix->value());
    $this->assertEquals('John', $w->field_person_first_name->value());
    $this->assertEquals('Doe', $w->field_person_last_name->value());
    $this->assertEquals('Permanent Secretary', $w->field_person_position->value());
    $this->assertEquals('Ministry of Environment and Drainage', $w->field_person_institution->value());
    $this->assertEquals('Unknown', $w->field_person_department->value());
    $this->assertEquals('No address', $w->field_address->value());
    $this->assertEquals('john.doe@barbados.gov.bb', $w->field_person_email->value());
    $this->assertEquals('12345', $w->field_contact_telephone->value());
    $this->assertEquals('54321', $w->field_contact_fax->value());
    $this->assertTrue($w->field_contact_primary_nfp->value());
    $types = $w->field_person_type->value();
    $this->assertEquals(1, count($types));
    $this->assertEquals('Licensed focal point', $types[0]->name);
    $this->assertEquals('1431103154', $w->field_last_update->value());
    $treaties = $w->field_treaty->value();
    $this->assertEquals(3, count($treaties));
    $this->assertTrue(in_array($treaties[0]->title, array('CBD', 'The Cartagena Protocol on Biosafety', 'Nagoya Protocol')));
  }


  function testV1() {
    $migration = MigrationBase::getInstance('test_contacts_odata_v1');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_contacts_odata_v1')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_contacts_odata_v1', 'a')->fields('a', array('destid1'))->condition('sourceid1', '0047078c-891c-e211-809d-0050569d5de3')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('Rotterdam Convention', $treaties[0]->title);

    $countries = $w->field_country->value();
    $this->assertEquals(1, count($countries));
    $this->assertEquals('Hungary', $countries[0]->title);

    $this->assertEquals('Ms.', $w->field_person_prefix->value());
    $this->assertEquals('Silvia', $w->field_person_first_name->value());
    $this->assertEquals('Daim', $w->field_person_last_name->value());
    $this->assertEquals('Deputy Director General', $w->field_person_position->value());
    $this->assertEquals('National Public Health Centre', $w->field_person_institution->value());
    $this->assertEquals('National Chemical Safety Directorate', $w->field_person_department->value());
    $this->assertEquals('Nagyv', $w->field_address->value());
    $this->assertEquals('eva.doe@yahoo.ca', $w->field_person_email->value());
    $this->assertEquals('12345', $w->field_contact_telephone->value());
    $this->assertEquals('+54321', $w->field_contact_fax->value());
    $this->assertFalse($w->field_contact_primary_nfp->value());
    $types = $w->field_person_type->value();
    $this->assertEquals(1, count($types));
    $this->assertEquals('Designated National Authority for chemicals', $types[0]->name);
    $this->assertEquals('1452156546', $w->field_last_update->value());
  }

  function tearDown() {
    $migration = MigrationBase::getInstance('test_contacts_odata_v3');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_contacts_odata_v3');
    $migration = MigrationBase::getInstance('test_contacts_odata_v1');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_contacts_odata_v1');
  }
}

$suite = new PHPUnit_Framework_TestSuite('ContactsODataImportTest');
PHPUnit_TextUI_TestRunner::run($suite);

