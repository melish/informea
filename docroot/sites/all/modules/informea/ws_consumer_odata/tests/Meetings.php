<?php

require_once 'vendor/autoload.php';
require_once 'Base.php';

/**
 * Use drush scr filename to run these tests
 */
class MeetingsODataImportTest extends PHPUnit_Framework_TestCase {

  function setUp() {
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_MEETINGS,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_CBD,
    );
    MigrationBase::registerMigration('MeetingsODataMigration', 'test_meetings_odata_v3', $config);
    $config = array(
      'config_class' => 'ODataConsumerTestConfig',
      'odata_entity' => ODataConsumerTestConfig::$ODATA_ENTITY_MEETINGS,
      'odata_name' => ODataConsumerTestConfig::$ODATA_NAME_STOCKHOLM,
    );
    MigrationBase::registerMigration('MeetingsODataMigration', 'test_meetings_odata_v1', $config);
  }

  function testV3() {
    $migration = MigrationBase::getInstance('test_meetings_odata_v3');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_meetings_odata_v3')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_meetings_odata_v3', 'a')->fields('a', array('destid1'))->condition('sourceid1', '52000000cbd0050000001595')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);
    $node = node_load($nid);

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('CBD', $treaties[0]->title);
    $this->assertEquals('52000000cbd0050000001595', $w->field_original_id->value());
    $this->assertEquals('Workshop on an Inter-sectoral Dialogue for Enhancing the Mainstreaming of Biodiversity and Ecosystem Services in National and Sectoral Policies', $node->title_field['en'][0]['value']);
    $this->assertEquals('French Workshop on an Inter-sectoral Dialogue for Enhancing the Mainstreaming of Biodiversity and Ecosystem Services in National and Sectoral Policies', $node->title_field['fr'][0]['value']);
    $this->assertEquals('Meeting description', $node->body['en'][0]['value']);
    $this->assertEquals('French Meeting description', $node->body['fr'][0]['value']);
    $this->assertEquals('http://www.cbd.int/kb/record/meeting/5525', $w->field_url->value()['url']);
    $this->assertEquals(1399388400, strtotime($w->event_calendar_date->value()['value']));
    $this->assertEquals(1399392000, strtotime($w->event_calendar_date->value()['value2']));
    $this->assertEquals('yearly', strtolower($w->field_event_repetition->value()->name));
    $this->assertEquals('official', strtolower($w->field_event_kind->value()->name));
    $this->assertEquals('mop', strtolower($w->field_event_type->value()->name));
    $this->assertEquals('public', strtolower($w->field_event_access->value()->name));
    $this->assertEquals('confirmed', strtolower($w->field_event_calendar_status->value()->name));
    $this->assertEquals('logo_Webinars_s.jpg', $w->field_event_images->value()[0]['filename']);
    $this->assertEquals('Image copyright', $w->field_event_images->value()[0]['alt']);
    $this->assertEquals('Image copyright', $w->field_event_images->value()[0]['title']);
    $this->assertEquals('Earth', $w->field_location->value());
    $this->assertEquals('Copenhagen', $w->field_city->value());
    $this->assertEquals('Romania', $w->field_country->value()[0]->title);
    $this->assertEquals(12, $w->field_latitude->value());
    $this->assertEquals(21, $w->field_longitude->value());
    $this->assertEquals('1424944431', $w->field_last_update->value());

    $th = entity_translation_get_handler('node', $node);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
  }

  function testV1() {
    $migration = MigrationBase::getInstance('test_meetings_odata_v1');
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_meetings_odata_v1')->fields(NULL, array('destid1'))->isNotNull('destid1')->countQuery()->execute()->fetchField();
    $this->assertEquals(2, $count);

    $nid = db_select('migrate_map_test_meetings_odata_v1', 'a')->fields('a', array('destid1'))->condition('sourceid1', '0066da14-412c-e411-855b-005056856044')->execute()->fetchField();
    $this->assertNotNull($nid);
    $w = entity_metadata_wrapper('node', $nid);
    $node = node_load($nid);

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('Stockholm Convention', $treaties[0]->title);

    $this->assertEquals('0066da14-412c-e411-855b-005056856044', $w->field_original_id->value());
    $this->assertEquals('NIP Updating in view of the entry into force of the amendment listing HBCD under the Stockholm Convention', $node->title_field['en'][0]['value']);
    $this->assertEquals('French NIP Updating in view of the entry into force of the amendment listing HBCD under the Stockholm Convention', $node->title_field['fr'][0]['value']);
    $this->assertEquals('The objective of this webinar', $node->body['en'][0]['value']);
    $this->assertEquals('Spanish The objective of this webinar', $node->body['es'][0]['value']);
    $this->assertEquals('http://synergies.pops.int/Default.aspx?tabid=3574&meetId=0066da14-412c-e411-855b-005056856044', $w->field_url->value()['url']);
    $this->assertEquals(1399388400, strtotime($w->event_calendar_date->value()['value']));
    $this->assertEquals(1399392000, strtotime($w->event_calendar_date->value()['value2']));
    $this->assertEquals('yearly', strtolower($w->field_event_repetition->value()->name));
    $this->assertEquals('official', strtolower($w->field_event_kind->value()->name));
    $this->assertEquals('mop', strtolower($w->field_event_type->value()->name));
    $this->assertEquals('public', strtolower($w->field_event_access->value()->name));
    $this->assertEquals('confirmed', strtolower($w->field_event_calendar_status->value()->name));
    $this->assertEquals('logo_Webinars_s.jpg', $w->field_event_images->value()[0]['filename']);
    $this->assertEquals('Image copyright', $w->field_event_images->value()[0]['alt']);
    $this->assertEquals('Image copyright', $w->field_event_images->value()[0]['title']);
    $this->assertEquals('Earth', $w->field_location->value());
    $this->assertEquals('Copenhagen', $w->field_city->value());
    $this->assertEquals('Romania', $w->field_country->value()[0]->title);
    $this->assertEquals(12, $w->field_latitude->value());
    $this->assertEquals(21, $w->field_longitude->value());
    $this->assertEquals('1424944431', $w->field_last_update->value());

    $th = entity_translation_get_handler('node', $node);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));
  }

  function testValidateRow() {
    /** @var MeetingsODataMigration $migration */
    $migration = MigrationBase::getInstance('test_meetings_odata_v1');
    $ob = new stdClass();
    $ob->id = 'born-to-fail';
    $this->assertFalse($migration->validateRow($ob));
    $ob->title_en = 'Stranger in a strange land';
    $ob->treaty = 255;
    $ob->start = time();
    $this->assertTrue($migration->validateRow($ob));

    $messsages = WSConsumerODataLog::findMessages('/born-to-fail has no type/');
    $this->assertEquals(1, count($messsages));
    $messsages = WSConsumerODataLog::findMessages('/born-to-fail has no URL/');
    $this->assertEquals(1, count($messsages));
    $messsages = WSConsumerODataLog::findMessages('/born-to-fail has no country/');
    $this->assertEquals(1, count($messsages));
    $messsages = WSConsumerODataLog::findMessages('/born-to-fail has no city/');
    $this->assertEquals(1, count($messsages));
    $messsages = WSConsumerODataLog::findMessages('/born-to-fail has no location/');
    $this->assertEquals(1, count($messsages));
  }

  function tearDown() {
    $migration = MigrationBase::getInstance('test_meetings_odata_v3');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_meetings_odata_v3');
    $migration = MigrationBase::getInstance('test_meetings_odata_v1');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_meetings_odata_v1');
  }
}

$suite = new PHPUnit_Framework_TestSuite('MeetingsODataImportTest');
PHPUnit_TextUI_TestRunner::run($suite);
