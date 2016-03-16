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
    $node = node_load($nid);

    $this->assertEquals('52000000cbd02200000018e9', $w->field_original_id->value());
    $countries = $w->field_country->value();
    $this->assertEquals(1, count($countries));
    $this->assertEquals('Barbados', $countries[0]->title);
    $this->assertEquals('Mr.', $node->field_person_prefix['en'][0]['value']);
    $this->assertEquals('John', $w->field_person_first_name->value());
    $this->assertEquals('Doe', $w->field_person_last_name->value());
    $this->assertEquals('Permanent Secretary', $node->field_person_position['en'][0]['value']);
    $this->assertEquals('Ministry of Environment and Drainage', $node->field_person_institution['en'][0]['value']);
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
    $roles = $w->field_contact_roles->value();
    $this->assertEquals(3, count($roles));
    foreach($roles as $role) {
      /** @var stdClass $rw */
      $rw = entity_metadata_wrapper('field_collection_item', $role);
      $rt = $rw->field_contact_treaty->value();
      $this->assertTrue(in_array($rt->nid, array(262, 263)));

      $rr = $rw->field_contact_role->value();
      $this->assertTrue(in_array($rr->name, array('Cartagena Protocol Primary NFP', 'BCH NFP', 'Nagoya Protocol Primary NFP')));
    }

    // Alter the URL to change to the new OData feed
    // Test update of the Contact 'roles' property
    ODataConsumerTestConfig::$overrides['endpoints'][ODataConsumerConfig::$ODATA_NAME_CBD] = array('default' => 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v3-updates');
    $migration->getSource()->resetData();
    $migration->resetStatus();

    $migration->prepareUpdate();
    $result = $migration->processImport(array('update' => TRUE));
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);
    drupal_static_reset();

    /** @var stdClass $node */
    $node = node_load($nid);
    $w = entity_metadata_wrapper('node', $node);
    $roles = $w->field_contact_roles->value();
    foreach($roles as $role) {
      /** @var stdClass $rw */
      $rw = entity_metadata_wrapper('field_collection_item', $role);
      $rt = $rw->field_contact_treaty->value();
      $this->assertTrue(in_array($rt->nid, array(262, 263, 255)));
      $rr = $rw->field_contact_role->value();
      $this->assertTrue(
        in_array($rr->name,
          array('Cartagena Protocol Primary NFP', 'Nagoya Protocol Primary NFP', 'CBD Primary NFP'))
      );
    }
    $this->assertEquals(3, count($roles));
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
    $node = node_load($nid);

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('Rotterdam Convention', $treaties[0]->title);

    $countries = $w->field_country->value();
    $this->assertEquals(1, count($countries));
    $this->assertEquals('Hungary', $countries[0]->title);

    $this->assertEquals('Ms.', $node->field_person_prefix['en'][0]['value']);
    $this->assertEquals('Silvia', $w->field_person_first_name->value());
    $this->assertEquals('Daim', $w->field_person_last_name->value());
    $this->assertEquals('Deputy Director General', $node->field_person_position['en'][0]['value']);
    $this->assertEquals('National Public Health Centre', $node->field_person_institution['en'][0]['value']);
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
    // Restore the endpoint
    ODataConsumerTestConfig::$overrides['endpoints'][ODataConsumerConfig::$ODATA_NAME_CBD] = array('default' => 'http://informea.local.ro/sites/all/modules/informea/ws_consumer_odata/tests/resources/v3');
  }

  function testValidateRow() {
    /** @var ContactsODataMigration $migration */
    $migration = MigrationBase::getInstance('test_contacts_odata_v1');
    $ob = new stdClass();
    $ob->id = 'born-to-fail';
    $this->assertFalse($migration->validateRow($ob));
    $ob->title_en = 'John Doe';
    $ob->email = 'stranger@mailinator.com';
    $ob->treaties = array(255);
    $this->assertTrue($migration->validateRow($ob));
    $ob->email = '1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF@mailinator.com';
    $this->assertFalse($migration->validateRow($ob));
  }
}

$suite = new PHPUnit_Framework_TestSuite('ContactsODataImportTest');
PHPUnit_TextUI_TestRunner::run($suite);

