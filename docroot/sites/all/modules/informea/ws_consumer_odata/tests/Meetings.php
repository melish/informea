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

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('CBD', $treaties[0]->title);

    $this->assertEquals('52000000cbd0050000001595', $w->field_original_id->value());
    $this->assertEquals('Workshop on an Inter-sectoral Dialogue for Enhancing the Mainstreaming of Biodiversity and Ecosystem Services in National and Sectoral Policies', $w->label());
    $this->assertEquals('Meeting description', $w->body->value()['value']);
    $this->assertEquals('http://www.cbd.int/kb/record/meeting/5525', $w->field_url->value()['url']);
    $this->assertEquals('2014-05-06 15:00:00', $w->event_calendar_date->value()['value']);
    $this->assertEquals('2014-05-06 16:00:00', $w->event_calendar_date->value()['value2']);
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

    $treaties = $w->field_treaty->value();
    $this->assertEquals(1, count($treaties));
    $this->assertEquals('Stockholm Convention', $treaties[0]->title);

    $this->assertEquals('0066da14-412c-e411-855b-005056856044', $w->field_original_id->value());
    $this->assertEquals('NIP Updating in view of the entry into force of the amendment listing HBCD under the Stockholm Convention', $w->label());
    $this->assertEquals('The objective of this webinar', $w->body->value()['value']);
    $this->assertEquals('http://synergies.pops.int/Default.aspx?tabid=3574&meetId=0066da14-412c-e411-855b-005056856044', $w->field_url->value()['url']);
    $this->assertEquals('2014-05-06 15:00:00', $w->event_calendar_date->value()['value']);
    $this->assertEquals('2014-05-06 16:00:00', $w->event_calendar_date->value()['value2']);
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

  }

  function tearDown() {
    $migration = MigrationBase::getInstance('test_meetings_odata_v3');
    // $migration->processRollback();
    MigrationBase::deregisterMigration('test_meetings_odata_v3');
    $migration = MigrationBase::getInstance('test_meetings_odata_v1');
    // $migration->processRollback();
    MigrationBase::deregisterMigration('test_meetings_odata_v1');
  }
}

$suite = new PHPUnit_Framework_TestSuite('MeetingsODataImportTest');
PHPUnit_TextUI_TestRunner::run($suite);
