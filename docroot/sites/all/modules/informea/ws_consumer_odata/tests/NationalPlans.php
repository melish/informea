<?php

require_once 'vendor/autoload.php';
require_once 'Base.php';

/**
 * Use drush scr filename to run these tests
 */
class NationalPlansODataImportTest extends PHPUnit_Framework_TestCase {

  function setUp() {
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_ACTION_PLAN,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_CBD,
    );
    MigrationBase::registerMigration('NationalPlansODataMigration', 'test_nationalplans_odata_v3', $config);
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_ACTION_PLAN,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_STOCKHOLM,
    );
    MigrationBase::registerMigration('NationalPlansODataMigration', 'test_nationalplans_odata_v1', $config);
  }

  function testV3() {
    $migration = MigrationBase::getInstance('test_nationalplans_odata_v3');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_nationalplans_odata_v3')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_nationalplans_odata_v3', 'a')->fields('a', array('destid1'))->condition('sourceid1', '52000000cbd0800000031349')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);

    $this->assertEquals('52000000cbd0800000031349', $w->field_original_id->value());
    $this->assertEquals('Austria - NBSAP v.1 (1998)', $w->label());

    $this->assertEquals('nbsap', strtolower($w->field_action_plan_type->value()->name));
    $this->assertEquals('1401302438', $w->field_sorting_date->value());
    $this->assertEquals('Austria', $w->field_country->value()[0]->title);
    $this->assertEquals('http://chm.cbd.int/database/record?documentID=201545', $w->field_document_url->value()[0]['url']);

    $files = $w->field_files->value();
    $this->assertEquals(2, count($files));
    $this->assertTrue(in_array($files[0]['filename'], array('at-nbsap-01-en.doc', 'at-nbsap-01-en.pdf')));
    $this->assertTrue(in_array($files[1]['filename'], array('at-nbsap-01-en.doc', 'at-nbsap-01-en.pdf')));
  }


  function testV1() {
    $migration = MigrationBase::getInstance('test_nationalplans_odata_v1');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_nationalplans_odata_v1')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_nationalplans_odata_v1', 'a')->fields('a', array('destid1'))->condition('sourceid1', 'UNEP-POPS-NIP-Albania-1')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);

    $this->assertEquals('UNEP-POPS-NIP-Albania-1', $w->field_original_id->value());
    $this->assertEquals('National Implementation Plan for Reduction and Disposal of Persistent Organic Pollutants', $w->label());
    $this->assertEquals('nip', strtolower($w->field_action_plan_type->value()->name));
    $this->assertEquals('1171238400', $w->field_sorting_date->value());
    $this->assertEquals('Albania', $w->field_country->value()[0]->title);
    $this->assertEquals('https://www.google.com', $w->field_document_url->value()[0]['url']);

    $files = $w->field_files->value();
    $this->assertEquals(1, count($files));
    $this->assertEquals('UNEP-POPS-NIP-Albania-1.English.pdf', $files[0]['filename']);
    $this->assertEquals('1429694503', $w->field_last_update->value());

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('Stockholm Convention', $treaties[0]->title);
  }

  function tearDown() {
    $migration = MigrationBase::getInstance('test_nationalplans_odata_v3');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_nationalplans_odata_v3');
    $migration = MigrationBase::getInstance('test_nationalplans_odata_v1');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_nationalplans_odata_v1');
  }
}

$suite = new PHPUnit_Framework_TestSuite('NationalPlansODataImportTest');
PHPUnit_TextUI_TestRunner::run($suite);
