<?php

require_once 'vendor/autoload.php';
require_once 'Base.php';

/**
 * Use drush scr filename to run these tests
 */
class SitesODataImportTest extends PHPUnit_Framework_TestCase {

  function setUp() {
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_SITES,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_WHC,
    );
    MigrationBase::registerMigration('SitesODataMigration', 'test_sites_odata_v1', $config);
  }

  function testV1() {
    $migration = MigrationBase::getInstance('test_sites_odata_v1');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_sites_odata_v1')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_sites_odata_v1', 'a')->fields('a', array('destid1'))->condition('sourceid1', '1')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);
    $node = node_load($nid);

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('World Heritage Convention', $treaties[0]->title);

    $countries = $w->field_country->value();
    $this->assertEquals(1, count($countries));
    $this->assertEquals('Ecuador', $countries[0]->title);

    $this->assertEquals('1', $w->field_original_id->value());
    $this->assertEquals('Galápagos Islands', $w->label());
    $this->assertEquals('Îles Galápagos', $node->title_field['fr'][0]['value']);
    $this->assertEquals('http://whc.unesco.org/en/list/1', $w->field_url->value()['url']);
    $this->assertEquals(-0.81667, $w->field_latitude->value());
    $this->assertEquals(-91.0, $w->field_longitude->value());
    $this->assertEquals('1456924040', $w->field_last_update->value());

    $th = entity_translation_get_handler('node', $node);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
  }

  function tearDown() {
    $migration = MigrationBase::getInstance('test_sites_odata_v1');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_sites_odata_v1');
  }
}

$suite = new PHPUnit_Framework_TestSuite('SitesODataImportTest');
PHPUnit_TextUI_TestRunner::run($suite);
