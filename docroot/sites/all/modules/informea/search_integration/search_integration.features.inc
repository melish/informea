<?php
/**
 * @file
 * search_integration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function search_integration_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function search_integration_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function search_integration_default_search_api_index() {
  $items = array();
  $items['default_node_index'] = entity_import('search_api_index', '{
    "name" : "Default node index",
    "machine_name" : "default_node_index",
    "description" : "An automatically created search index for indexing node data. Might be configured to specific needs.",
    "server" : "local_solr_server",
    "item_type" : "node",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_node_access" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        },
        "search_api_alter_add_viewed_entity" : { "status" : 1, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "uuid" : true,
              "field_city" : true,
              "field_abbreviation" : true,
              "field_location" : true,
              "field_official_name" : true,
              "field_title_abbreviation" : true,
              "field_person_first_name" : true,
              "field_person_institution" : true,
              "field_person_last_name" : true,
              "field_isis_number" : true,
              "field_notes" : true,
              "field_reference_number" : true,
              "field_serial_imprint" : true,
              "field_author" : true,
              "field_author_institution" : true,
              "field_isbn" : true,
              "field_literature_paper_title" : true,
              "field_literature_serial_title" : true,
              "field_organizations" : true,
              "field_publisher" : true,
              "field_court_name" : true,
              "field_justices" : true,
              "field_country_official_name" : true,
              "body:value" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "field_city" : true,
              "field_abbreviation" : true,
              "field_location" : true,
              "field_official_name" : true,
              "field_title_abbreviation" : true,
              "field_person_first_name" : true,
              "field_person_institution" : true,
              "field_person_last_name" : true,
              "field_isis_number" : true,
              "field_notes" : true,
              "field_reference_number" : true,
              "field_serial_imprint" : true,
              "field_author" : true,
              "field_author_institution" : true,
              "field_isbn" : true,
              "field_literature_paper_title" : true,
              "field_literature_serial_title" : true,
              "field_organizations" : true,
              "field_publisher" : true,
              "field_court_name" : true,
              "field_justices" : true,
              "field_country_official_name" : true,
              "body:value" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "field_city" : true,
              "field_abbreviation" : true,
              "field_location" : true,
              "field_official_name" : true,
              "field_title_abbreviation" : true,
              "field_person_first_name" : true,
              "field_person_institution" : true,
              "field_person_last_name" : true,
              "field_isis_number" : true,
              "field_notes" : true,
              "field_reference_number" : true,
              "field_serial_imprint" : true,
              "field_author" : true,
              "field_author_institution" : true,
              "field_isbn" : true,
              "field_literature_paper_title" : true,
              "field_literature_serial_title" : true,
              "field_organizations" : true,
              "field_publisher" : true,
              "field_court_name" : true,
              "field_justices" : true,
              "field_country_official_name" : true,
              "body:value" : true
            },
            "spaces" : "[^\\\\p{L}\\\\p{N}]",
            "ignorable" : "[-]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "field_city" : true,
              "field_abbreviation" : true,
              "field_location" : true,
              "field_official_name" : true,
              "field_title_abbreviation" : true,
              "field_person_first_name" : true,
              "field_person_institution" : true,
              "field_person_last_name" : true,
              "field_isis_number" : true,
              "field_notes" : true,
              "field_reference_number" : true,
              "field_serial_imprint" : true,
              "field_author" : true,
              "field_author_institution" : true,
              "field_isbn" : true,
              "field_literature_paper_title" : true,
              "field_literature_serial_title" : true,
              "field_organizations" : true,
              "field_publisher" : true,
              "field_court_name" : true,
              "field_justices" : true,
              "field_country_official_name" : true,
              "body:value" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      },
      "fields" : {
        "author" : { "type" : "integer", "entity_type" : "user" },
        "body:value" : { "type" : "text" },
        "changed" : { "type" : "date" },
        "comment_count" : { "type" : "integer" },
        "created" : { "type" : "date" },
        "field_abbreviation" : { "type" : "text" },
        "field_author" : { "type" : "list\\u003Ctext\\u003E" },
        "field_author_institution" : { "type" : "list\\u003Ctext\\u003E" },
        "field_city" : { "type" : "text" },
        "field_country" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_country_official_name" : { "type" : "text" },
        "field_court_name" : { "type" : "text" },
        "field_data_source" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_date_of_original_text" : { "type" : "date" },
        "field_decision_status" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_decision_type" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_ecolex_decision_status" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_ecolex_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_eu_member" : { "type" : "boolean" },
        "field_event_access" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_event_calendar_status" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_event_kind" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_event_repetition" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_event_type" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_geg_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_goal_source" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_goal_type" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_informea_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_isbn" : { "type" : "text" },
        "field_isis_number" : { "type" : "text" },
        "field_jurisdiction" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_justices" : { "type" : "list\\u003Ctext\\u003E" },
        "field_keywords" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_literature_paper_title" : { "type" : "text" },
        "field_literature_serial_title" : { "type" : "text" },
        "field_literature_type" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_location" : { "type" : "text" },
        "field_meeting" : { "type" : "integer", "entity_type" : "node" },
        "field_notes" : { "type" : "text" },
        "field_official_name" : { "type" : "text" },
        "field_organizations" : { "type" : "list\\u003Ctext\\u003E" },
        "field_party_status" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_person_first_name" : { "type" : "text" },
        "field_person_institution" : { "type" : "text" },
        "field_person_last_name" : { "type" : "text" },
        "field_primary_topic" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_publisher" : { "type" : "text" },
        "field_reference_number" : { "type" : "text" },
        "field_region" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_repealed" : { "type" : "boolean" },
        "field_report_submission_date" : { "type" : "date" },
        "field_secondary_topic" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_serial_imprint" : { "type" : "text" },
        "field_sorting_order" : { "type" : "integer" },
        "field_strategic_goal" : { "type" : "integer", "entity_type" : "node" },
        "field_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_title_abbreviation" : { "type" : "text" },
        "field_treaty" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_type_of_text" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "promote" : { "type" : "boolean" },
        "search_api_language" : { "type" : "string" },
        "search_api_viewed" : { "type" : "text" },
        "status" : { "type" : "integer" },
        "sticky" : { "type" : "boolean" },
        "title" : { "type" : "text", "boost" : "5.0" },
        "type" : { "type" : "string" },
        "uuid" : { "type" : "text" }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function search_integration_default_search_api_server() {
  $items = array();
  $items['local_solr_server'] = entity_import('search_api_server', '{
    "name" : "Local Solr server",
    "machine_name" : "local_solr_server",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids" : true,
      "site_hash" : true,
      "scheme" : "http",
      "host" : "localhost",
      "port" : "8983",
      "path" : "\\/solr\\/leo",
      "http_user" : "admin",
      "http_pass" : "admin",
      "excerpt" : 0,
      "retrieve_data" : 0,
      "highlight_data" : 0,
      "skip_schema_check" : 0,
      "solr_version" : "",
      "http_method" : "AUTO"
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  return $items;
}
