<?php

require_once 'vendor/autoload.php';
require_once 'Base.php';

/**
 * Use drush scr filename to run these tests
 */
class CountryReportsODataImportTest extends PHPUnit_Framework_TestCase {

  function setUp() {
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_NATIONAL_REPORT,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_CBD,
    );
    MigrationBase::registerMigration('CountryReportsODataMigration', 'test_countryreports_odata_v3', $config);
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_NATIONAL_REPORT,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_AEWA,
    );
    MigrationBase::registerMigration('CountryReportsODataMigration', 'test_countryreports_odata_v1', $config);
  }

  function testV3() {
    $migration = MigrationBase::getInstance('test_countryreports_odata_v3');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);
  }


  function testV1() {
    $migration = MigrationBase::getInstance('test_countryreports_odata_v1');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_countryreports_odata_v1')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_countryreports_odata_v1', 'a')->fields('a', array('destid1'))->condition('sourceid1', '00874795-9e78-4ff7-81ca-5f42126f9186')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);
    $node = node_load($nid);

    $this->assertEquals('00874795-9e78-4ff7-81ca-5f42126f9186', $w->field_original_id->value());
    $this->assertEquals('National Report of Senegal', $w->label());
    $this->assertEquals('National Report of Senegal', $node->title_field['en'][0]['value']);
    $this->assertEquals('National Report of Senegal French', $node->title_field['fr'][0]['value']);

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('AEWA', $treaties[0]->title);

    $this->assertEquals('Senegal', $w->field_country->value()[0]->title);
    $this->assertEquals('http://www.unep-aewa.org/node/1778', $w->field_document_url->value()[0]['url']);
    $this->assertEquals('1221436800', $w->field_sorting_date->value());
    $this->assertEquals('1384878704', $w->field_last_update->value());

    $files = $w->field_files->value();
    $this->assertEquals(1, count($files));
    $this->assertEquals('senegal2008_fr_mop4_0.pdf', $files[0]['filename']);
  }

  function tearDown() {
    $migration = MigrationBase::getInstance('test_countryreports_odata_v3');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_countryreports_odata_v3');
    $migration = MigrationBase::getInstance('test_countryreports_odata_v1');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_countryreports_odata_v1');
  }
}

$suite = new PHPUnit_Framework_TestSuite('CountryReportsODataImportTest');
PHPUnit_TextUI_TestRunner::run($suite);
