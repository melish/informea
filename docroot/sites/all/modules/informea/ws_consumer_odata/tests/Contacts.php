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

  function tearDown() {
    $migration = MigrationBase::getInstance('test_contacts_odata_v3');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_contacts_odata_v3');
  }
}

$suite = new PHPUnit_Framework_TestSuite('ContactsODataImportTest');
PHPUnit_TextUI_TestRunner::run($suite);

