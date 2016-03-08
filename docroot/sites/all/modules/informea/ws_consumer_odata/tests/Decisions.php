<?php

require_once 'vendor/autoload.php';
require_once 'Base.php';

/**
 * Use drush scr filename to run these tests
 */
class DecisionsODataImportTest extends PHPUnit_Framework_TestCase {

  function setUp() {
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_MEETINGS,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_CBD,
    );
    MigrationBase::registerMigration('MeetingsODataMigration', 'test_decisions_meetings_odata_v3', $config);

    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_DECISIONS,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_CBD,
    );
    MigrationBase::registerMigration('DecisionsODataMigration', 'test_decisions_odata_v3', $config);

    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_MEETINGS,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_STOCKHOLM,
    );
    MigrationBase::registerMigration('MeetingsODataMigration', 'test_decisions_meetings_odata_v1', $config);

    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_DECISIONS,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_STOCKHOLM,
    );
    MigrationBase::registerMigration('DecisionsODataMigration', 'test_decisions_odata_v1', $config);
  }

  function testV3() {
    $migration = MigrationBase::getInstance('test_decisions_meetings_odata_v3');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    // Ensure parent meetings were migrated correctly
    $count = db_select('migrate_map_test_decisions_meetings_odata_v3')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);
    $nid = db_select('migrate_map_test_decisions_meetings_odata_v3', 'a')->fields('a', array('destid1'))->condition('sourceid1', '52000000cbd0050000001595')->execute()->fetchField();
    $this->assertNotNull($nid);

    $migration = MigrationBase::getInstance('test_decisions_odata_v3');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_decisions_odata_v3')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_decisions_odata_v3', 'a')->fields('a', array('destid1'))->condition('sourceid1', '52000000cbd0070000003465')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);
    $node = node_load($nid);

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('CBD', $treaties[0]->title);

    $this->assertEquals('52000000cbd0070000003465', $w->field_original_id->value());

    $this->assertEquals('Programme budget for the biennium following the entry into force of the Nagoya Protocol', $w->label());
    $this->assertEquals('Programme budget for the biennium following the entry into force of the Nagoya Protocol', $node->title_field['en'][0]['value']);
    //@todo: multilingual title
    //@todo: body & summary

    $this->assertEquals('active', strtolower($w->field_decision_status->value()->name));
    $this->assertEquals('decision', strtolower($w->field_decision_type->value()->name));
    $this->assertEquals('NP-1/13', $w->field_decision_number->value());
    $this->assertEquals(1423583065, $w->field_sorting_date->value());
    $this->assertEquals(401130, $w->field_sorting_order->value());

    $meeting = $w->field_meeting->value();
    $mw = entity_metadata_wrapper('node', $meeting);
    $this->assertEquals('52000000cbd0050000001595', $mw->field_original_id->value());
  }


  function testV1() {
    $migration = MigrationBase::getInstance('test_decisions_meetings_odata_v1');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    // Ensure parent meetings were migrated correctly
    $count = db_select('migrate_map_test_decisions_meetings_odata_v1')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);
    $nid = db_select('migrate_map_test_decisions_meetings_odata_v1', 'a')->fields('a', array('destid1'))->condition('sourceid1', '0066da14-412c-e411-855b-005056856044')->execute()->fetchField();
    $this->assertNotNull($nid);


    $migration = MigrationBase::getInstance('test_decisions_odata_v1');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_decisions_odata_v1')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_decisions_odata_v1', 'a')->fields('a', array('destid1'))->condition('sourceid1', '8fc906c1-820c-4a38-ad7c-00879971fee8')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);
    $node = node_load($nid);

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('Stockholm Convention', $treaties[0]->title);

    $this->assertEquals('8fc906c1-820c-4a38-ad7c-00879971fee8', $w->field_original_id->value());

    $this->assertEquals('Measures to reduce or eliminate releases from wastes', $w->label());
    $this->assertEquals('Measures to reduce or eliminate releases from wastes', $node->title_field['en'][0]['value']);
    $this->assertEquals('French title', $node->title_field['fr'][0]['value']);

    $body = $node->body;
    $this->assertEquals('Content in english', $body['en'][0]['value']);
    $this->assertEquals('Measures to reduce or eliminate releases from wastes', $body['en'][0]['summary']);
    $this->assertEquals('Content in spanish', $body['es'][0]['value']);
    $this->assertEquals('Spanish summary', $body['es'][0]['summary']);

    $this->assertEquals('active', strtolower($w->field_decision_status->value()->name));
    $this->assertEquals('decision', strtolower($w->field_decision_type->value()->name));
    $this->assertEquals('SC-3/7', $w->field_decision_number->value());
    $this->assertEquals(1206271611, $w->field_sorting_date->value());

    $meeting = $w->field_meeting->value();
    $mw = entity_metadata_wrapper('node', $meeting);
    $this->assertEquals('0066da14-412c-e411-855b-005056856044', $mw->field_original_id->value());
    $this->assertEquals('Another meeting', $w->field_meeting_title_en->value());
    $this->assertEquals('http://www.google.com/', $w->field_meeting_url->value()['url']);
    $this->assertEquals(3370, $w->field_sorting_order->value());

    $this->assertEquals('http://www.yahoo.com/', $w->field_url->value()['url']);
    $this->assertEquals(1206271611, $w->field_last_update->value());

    $nid = db_select('migrate_map_test_decisions_odata_v1', 'a')->fields('a', array('destid1'))->condition('sourceid1', 'e5cee8ae-91f5-41b8-8c2e-03c8dbb5d7a4')->execute()->fetchField();
    $this->assertNotNull($nid);

    $th = entity_translation_get_handler('node', $node);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));
    $this->assertTrue(array_key_exists('ar', $translations->data), 'Missing arabic translation');

    $node = node_load($nid);

    $files = $node->field_files;
    $this->assertEquals('UNEP-POPS-POPRC.7-POPRC-7-6.English.doc', $files['en'][0]['filename']);
    $this->assertEquals('UNEP-POPS-POPRC.7-POPRC-7-6.Spanish.doc', $files['es'][0]['filename']);
    $this->assertEquals('UNEP-POPS-POPRC.7-POPRC-7-6.French.pdf', $files['fr'][0]['filename']);
  }

  function testValidateRow() {
    /** @var DecisionsODataMigration $migration */
    $migration = MigrationBase::getInstance('test_decisions_odata_v1');
    $ob = new stdClass();
    $ob->id = 'born-to-fail';
    $this->assertFalse($migration->validateRow($ob));
    $ob->title_en = 'Stranger in a strange land';
    $ob->treaty = 255;
    $this->assertTrue($migration->validateRow($ob));
    $messsages = WSConsumerODataLog::findMessages('/Decision with id=born-to-fail has no files/');
    $this->assertEquals(1, count($messsages));
    $this->assertEquals(MigrationBase::MESSAGE_WARNING, $messsages[0]->severity);
  }

  function tearDown() {
    $migration = MigrationBase::getInstance('test_decisions_meetings_odata_v3');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_decisions_meetings_odata_v3');

    $migration = MigrationBase::getInstance('test_decisions_meetings_odata_v1');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_decisions_meetings_odata_v1');

    $migration = MigrationBase::getInstance('test_decisions_odata_v3');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_decisions_odata_v3');
    $migration = MigrationBase::getInstance('test_decisions_odata_v1');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_decisions_odata_v1');
  }
}

$suite = new PHPUnit_Framework_TestSuite('DecisionsODataImportTest');
PHPUnit_TextUI_TestRunner::run($suite);
