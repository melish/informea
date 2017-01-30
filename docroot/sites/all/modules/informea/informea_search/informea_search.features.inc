<?php
/**
 * @file
 * informea_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function informea_search_ctools_plugin_api($module = NULL, $api = NULL) {
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
function informea_search_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function informea_search_default_search_api_index() {
  $items = array();
  $items['informea_documents'] = entity_import('search_api_index', '{
    "name" : "InforMEA Documents",
    "machine_name" : "informea_documents",
    "description" : null,
    "server" : "solr_4_informea_documents",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "document" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "attachments_field_document_abstract" : { "type" : "text" },
        "attachments_field_document_other" : { "type" : "text" },
        "attachments_field_files" : { "type" : "text" },
        "body:summary" : { "type" : "text" },
        "body:value" : { "type" : "text" },
        "created" : { "type" : "date" },
        "field_country" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_document_authors" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_document_identifiers" : {
          "type" : "list\\u003Cinteger\\u003E",
          "entity_type" : "field_collection_item"
        },
        "field_document_type" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_image:file" : { "type" : "integer", "entity_type" : "file" },
        "field_informea_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_last_update" : { "type" : "date" },
        "field_sorting_date" : { "type" : "date" },
        "field_sorting_order" : { "type" : "integer" },
        "field_treaty" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "language" : { "type" : "string" },
        "nid" : { "type" : "integer" },
        "promote" : { "type" : "boolean" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title" : { "type" : "text" },
        "title_field" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" },
        "uuid" : { "type" : "text" },
        "vid" : { "type" : "integer" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_node_status" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_attachments_alter_settings" : {
          "status" : 1,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_attachments_entityreference_alter_settings" : {
          "status" : 0,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "uuid" : true,
              "title_field" : true,
              "field_image:alt" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "title_field" : true,
              "field_image:alt" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "title_field" : true,
              "field_image:alt" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "title_field" : true,
              "field_image:alt" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 1,
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
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : [],
    "tes" : { "enable" : false }
  }');
  $items['informea_fulltext_solr_index'] = entity_import('search_api_index', '{
    "name" : "InforMEA fulltext Solr index",
    "machine_name" : "informea_fulltext_solr_index",
    "description" : "Search index containing MEA content retrieved via OData API",
    "server" : "search_solr_server",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [
          "action_plan",
          "contact_person",
          "country",
          "decision",
          "decision_paragraph",
          "event_calendar",
          "geographical_site",
          "national_report",
          "reporting_obligation_cycle",
          "treaty",
          "treaty_article",
          "treaty_paragraph"
        ]
      },
      "index_directly" : 1,
      "cron_limit" : "10",
      "fields" : {
        "attachments_field_files" : { "type" : "text" },
        "body:summary" : { "type" : "text" },
        "body:value" : { "type" : "text" },
        "field_action_plan_type" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_country" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_country_official_name" : { "type" : "text" },
        "field_decision_number" : { "type" : "text" },
        "field_informea_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_informea_tags:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_informea_tags:name_field" : { "type" : "list\\u003Ctext\\u003E", "boost" : "2.0" },
        "field_meeting" : { "type" : "integer", "entity_type" : "node" },
        "field_official_name" : { "type" : "text", "boost" : "2.0" },
        "field_official_publication" : { "type" : "text" },
        "field_region" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_sorting_date" : { "type" : "date" },
        "field_sorting_order" : { "type" : "integer" },
        "field_treaty" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "language" : { "type" : "string" },
        "nid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title" : { "type" : "text", "boost" : "21.0" },
        "title_field" : { "type" : "text", "boost" : "21.0" },
        "type" : { "type" : "string" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_attachments_alter_settings" : {
          "status" : 1,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_attachments_entityreference_alter_settings" : {
          "status" : 0,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "title_field" : true,
              "field_decision_number" : true,
              "field_official_name" : true,
              "field_informea_tags:name_field" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "title_field" : true,
              "field_decision_number" : true,
              "field_official_name" : true,
              "body:value" : true,
              "body:summary" : true,
              "field_informea_tags:name_field" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "title_field" : true,
              "field_decision_number" : true,
              "field_official_name" : true,
              "field_informea_tags:name_field" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "title_field" : true,
              "field_decision_number" : true,
              "field_official_name" : true,
              "field_informea_tags:name_field" : true
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
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : [],
    "tes" : { "enable" : false }
  }');
  $items['law_and_literature'] = entity_import('search_api_index', '{
    "name" : "Law and literature",
    "machine_name" : "law_and_literature",
    "description" : "ECOLEX treaties and literature, FAOLEX legislation, InforMEA treaties and publications",
    "server" : "law_and_literature",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "court_decisions", "document", "legislation", "literature", "treaty" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "attachments_field_document_abstract" : { "type" : "text" },
        "attachments_field_document_other" : { "type" : "text" },
        "attachments_field_files" : { "type" : "text" },
        "author" : { "type" : "integer", "entity_type" : "user" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "field_abstract" : { "type" : "text" },
        "field_alternative_record_id" : { "type" : "text" },
        "field_amends" : { "type" : "integer", "entity_type" : "node" },
        "field_amends_treaty" : { "type" : "integer", "entity_type" : "node" },
        "field_author" : { "type" : "list\\u003Ctext\\u003E" },
        "field_author_institution" : { "type" : "list\\u003Ctext\\u003E" },
        "field_available_in" : { "type" : "text" },
        "field_cited_treaties" : { "type" : "integer", "entity_type" : "node" },
        "field_city" : { "type" : "text" },
        "field_collation" : { "type" : "text" },
        "field_country" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_court_decision_raw" : { "type" : "list\\u003Ctext\\u003E" },
        "field_court_decision_subdivision" : { "type" : "text" },
        "field_court_name" : { "type" : "text" },
        "field_data_source" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_date_of_consolidation" : { "type" : "date" },
        "field_date_of_original_text" : { "type" : "date" },
        "field_depositary" : { "type" : "text" },
        "field_document_authors" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_document_entity_references" : { "type" : "integer", "entity_type" : "node" },
        "field_document_identifiers" : {
          "type" : "list\\u003Cinteger\\u003E",
          "entity_type" : "field_collection_item"
        },
        "field_document_type" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_ecolex_decision_status" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_ecolex_keywords" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_ecolex_legislation_status" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_ecolex_region" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_ecolex_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_ecolex_treaty_raw" : { "type" : "list\\u003Ctext\\u003E" },
        "field_emerging_terms" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_entry_into_force" : { "type" : "date" },
        "field_entry_into_force_notes" : { "type" : "text" },
        "field_faolex_id" : { "type" : "text" },
        "field_faolex_reference_raw" : { "type" : "list\\u003Ctext\\u003E" },
        "field_field_of_application" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_geographical_scope" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_implements" : { "type" : "integer", "entity_type" : "node" },
        "field_informea_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_instance" : { "type" : "text" },
        "field_internet_reference" : { "type" : "text" },
        "field_is_protocol" : { "type" : "boolean" },
        "field_isbn" : { "type" : "text" },
        "field_isis_number" : { "type" : "text" },
        "field_jurisdiction" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_justices" : { "type" : "list\\u003Ctext\\u003E" },
        "field_last_update" : { "type" : "date" },
        "field_literature_call_number" : { "type" : "text" },
        "field_literature_paper_title" : { "type" : "text" },
        "field_literature_serial_title" : { "type" : "text" },
        "field_literature_type" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_mea_topic" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_notes" : { "type" : "text" },
        "field_number_of_pages" : { "type" : "integer" },
        "field_obsolete" : { "type" : "boolean" },
        "field_odata_identifier" : { "type" : "text" },
        "field_official_name" : { "type" : "text" },
        "field_official_publication" : { "type" : "text" },
        "field_organizations" : { "type" : "list\\u003Ctext\\u003E" },
        "field_original_id" : { "type" : "text" },
        "field_parent_treaty" : { "type" : "integer", "entity_type" : "node" },
        "field_place_of_adoption" : { "type" : "text" },
        "field_primary" : { "type" : "boolean" },
        "field_primary_topic" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_publication_place" : { "type" : "text" },
        "field_publisher" : { "type" : "text" },
        "field_ref_to_eu_legislation_raw" : { "type" : "list\\u003Ctext\\u003E" },
        "field_ref_to_nat_legislation_raw" : { "type" : "list\\u003Ctext\\u003E" },
        "field_reference_number" : { "type" : "text" },
        "field_region" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_related_literature" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_related_website" : { "type" : "text" },
        "field_repealed" : { "type" : "boolean" },
        "field_repeals" : { "type" : "integer", "entity_type" : "node" },
        "field_sdg_goals" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_secondary_topic" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_serial_imprint" : { "type" : "text" },
        "field_sorting_date" : { "type" : "date" },
        "field_sorting_order" : { "type" : "integer" },
        "field_sub_file_code" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_territorial_subdivision" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_title_abbreviation" : { "type" : "text" },
        "field_title_of_text_other" : { "type" : "text" },
        "field_title_of_text_short" : { "type" : "text" },
        "field_title_of_text_short_other" : { "type" : "text" },
        "field_treaty" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_treaty_has_parties_from_un" : { "type" : "boolean" },
        "field_type_of_text" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_volume_no" : { "type" : "text" },
        "language" : { "type" : "string" },
        "nid" : { "type" : "integer" },
        "promote" : { "type" : "boolean" },
        "search_api_access_node" : { "type" : "list\\u003Cstring\\u003E" },
        "search_api_language" : { "type" : "string" },
        "search_api_url" : { "type" : "uri" },
        "status" : { "type" : "boolean" },
        "sticky" : { "type" : "boolean" },
        "title" : { "type" : "text" },
        "title_field" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" },
        "uuid" : { "type" : "text" },
        "vid" : { "type" : "integer" },
        "vuuid" : { "type" : "text" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_node_access" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_attachments_entityreference_alter_settings" : {
          "status" : 0,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_alter_language_control" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        },
        "search_api_attachments_alter_settings" : {
          "status" : 1,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_alter_add_hierarchy" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : {
              "source:field_parent_treaty" : "source:field_parent_treaty",
              "source:field_parent_decision" : "source:field_parent_decision"
            }
          }
        },
        "search_api_alter_add_url" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_metatag_alter_callback" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "uuid" : true,
              "vuuid" : true,
              "title_field" : true,
              "field_city" : true,
              "field_original_id" : true,
              "field_abstract" : true,
              "field_alternative_record_id" : true,
              "field_available_in" : true,
              "field_depositary" : true,
              "field_internet_reference" : true,
              "field_odata_identifier" : true,
              "field_official_name" : true,
              "field_place_of_adoption" : true,
              "field_related_website" : true,
              "field_title_abbreviation" : true,
              "field_official_publication" : true,
              "field_entry_into_force_notes" : true,
              "field_faolex_id" : true,
              "field_reference_number" : true,
              "field_isis_number" : true,
              "field_notes" : true,
              "field_serial_imprint" : true,
              "field_author" : true,
              "field_author_institution" : true,
              "field_collation" : true,
              "field_isbn" : true,
              "field_literature_call_number" : true,
              "field_literature_paper_title" : true,
              "field_literature_serial_title" : true,
              "field_organizations" : true,
              "field_publication_place" : true,
              "field_publisher" : true,
              "field_volume_no" : true,
              "field_court_name" : true,
              "field_justices" : true,
              "field_court_decision_subdivision" : true,
              "field_court_decision_raw" : true,
              "field_ecolex_treaty_raw" : true,
              "field_faolex_reference_raw" : true,
              "field_instance" : true,
              "field_ref_to_eu_legislation_raw" : true,
              "field_title_of_text_other" : true,
              "field_title_of_text_short" : true,
              "field_title_of_text_short_other" : true,
              "field_ref_to_nat_legislation_raw" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "vuuid" : true,
              "title_field" : true,
              "field_city" : true,
              "field_original_id" : true,
              "field_abstract" : true,
              "field_alternative_record_id" : true,
              "field_available_in" : true,
              "field_depositary" : true,
              "field_internet_reference" : true,
              "field_odata_identifier" : true,
              "field_official_name" : true,
              "field_place_of_adoption" : true,
              "field_related_website" : true,
              "field_title_abbreviation" : true,
              "field_official_publication" : true,
              "field_entry_into_force_notes" : true,
              "field_faolex_id" : true,
              "field_reference_number" : true,
              "field_isis_number" : true,
              "field_notes" : true,
              "field_serial_imprint" : true,
              "field_author" : true,
              "field_author_institution" : true,
              "field_collation" : true,
              "field_isbn" : true,
              "field_literature_call_number" : true,
              "field_literature_paper_title" : true,
              "field_literature_serial_title" : true,
              "field_organizations" : true,
              "field_publication_place" : true,
              "field_publisher" : true,
              "field_volume_no" : true,
              "field_court_name" : true,
              "field_justices" : true,
              "field_court_decision_subdivision" : true,
              "field_court_decision_raw" : true,
              "field_ecolex_treaty_raw" : true,
              "field_faolex_reference_raw" : true,
              "field_instance" : true,
              "field_ref_to_eu_legislation_raw" : true,
              "field_title_of_text_other" : true,
              "field_title_of_text_short" : true,
              "field_title_of_text_short_other" : true,
              "field_ref_to_nat_legislation_raw" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "vuuid" : true,
              "title_field" : true,
              "field_city" : true,
              "field_original_id" : true,
              "field_abstract" : true,
              "field_alternative_record_id" : true,
              "field_available_in" : true,
              "field_depositary" : true,
              "field_internet_reference" : true,
              "field_odata_identifier" : true,
              "field_official_name" : true,
              "field_place_of_adoption" : true,
              "field_related_website" : true,
              "field_title_abbreviation" : true,
              "field_official_publication" : true,
              "field_entry_into_force_notes" : true,
              "field_faolex_id" : true,
              "field_reference_number" : true,
              "field_isis_number" : true,
              "field_notes" : true,
              "field_serial_imprint" : true,
              "field_author" : true,
              "field_author_institution" : true,
              "field_collation" : true,
              "field_isbn" : true,
              "field_literature_call_number" : true,
              "field_literature_paper_title" : true,
              "field_literature_serial_title" : true,
              "field_organizations" : true,
              "field_publication_place" : true,
              "field_publisher" : true,
              "field_volume_no" : true,
              "field_court_name" : true,
              "field_justices" : true,
              "field_court_decision_subdivision" : true,
              "field_court_decision_raw" : true,
              "field_ecolex_treaty_raw" : true,
              "field_faolex_reference_raw" : true,
              "field_instance" : true,
              "field_ref_to_eu_legislation_raw" : true,
              "field_title_of_text_other" : true,
              "field_title_of_text_short" : true,
              "field_title_of_text_short_other" : true,
              "field_ref_to_nat_legislation_raw" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "vuuid" : true,
              "title_field" : true,
              "field_city" : true,
              "field_original_id" : true,
              "field_abstract" : true,
              "field_alternative_record_id" : true,
              "field_available_in" : true,
              "field_depositary" : true,
              "field_internet_reference" : true,
              "field_odata_identifier" : true,
              "field_official_name" : true,
              "field_place_of_adoption" : true,
              "field_related_website" : true,
              "field_title_abbreviation" : true,
              "field_official_publication" : true,
              "field_entry_into_force_notes" : true,
              "field_faolex_id" : true,
              "field_reference_number" : true,
              "field_isis_number" : true,
              "field_notes" : true,
              "field_serial_imprint" : true,
              "field_author" : true,
              "field_author_institution" : true,
              "field_collation" : true,
              "field_isbn" : true,
              "field_literature_call_number" : true,
              "field_literature_paper_title" : true,
              "field_literature_serial_title" : true,
              "field_organizations" : true,
              "field_publication_place" : true,
              "field_publisher" : true,
              "field_volume_no" : true,
              "field_court_name" : true,
              "field_justices" : true,
              "field_court_decision_subdivision" : true,
              "field_court_decision_raw" : true,
              "field_ecolex_treaty_raw" : true,
              "field_faolex_reference_raw" : true,
              "field_instance" : true,
              "field_ref_to_eu_legislation_raw" : true,
              "field_title_of_text_other" : true,
              "field_title_of_text_short" : true,
              "field_title_of_text_short_other" : true,
              "field_ref_to_nat_legislation_raw" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 1,
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
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : [],
    "tes" : { "enable" : false }
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function informea_search_default_search_api_server() {
  $items = array();
  $items['apache_solr_news_core'] = entity_import('search_api_server', '{
    "name" : "Apache Solr server",
    "machine_name" : "apache_solr_news_core",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "scheme" : "http",
      "host" : "localhost",
      "port" : 8983,
      "path" : "\\/solr\\/informea-news",
      "http" : { "http_user" : "", "http_pass" : null },
      "excerpt" : 1,
      "retrieve_data" : 1,
      "highlight_data" : 1,
      "skip_schema_check" : null,
      "solr_version" : "",
      "http_method" : "AUTO"
    },
    "enabled" : "1",
    "rdf_mapping" : [],
    "tes" : { "enable" : false }
  }');
  $items['law_and_literature'] = entity_import('search_api_server', '{
    "name" : "Law and literature",
    "machine_name" : "law_and_literature",
    "description" : "This core contains ECOLEX legislation, court decisions (UNEP and ECOLEX), literature and MEA publications",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids" : true,
      "site_hash" : true,
      "scheme" : "http",
      "host" : "localhost",
      "port" : "8983",
      "path" : "\\/solr\\/informea-literature",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 1,
      "retrieve_data" : 0,
      "highlight_data" : 0,
      "skip_schema_check" : 0,
      "solr_version" : "",
      "http_method" : "AUTO",
      "log_query" : 0,
      "log_response" : 0
    },
    "enabled" : "1",
    "rdf_mapping" : [],
    "tes" : { "enable" : false }
  }');
  $items['search_solr_server'] = entity_import('search_api_server', '{
    "name" : "Apache Solr server",
    "machine_name" : "search_solr_server",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "scheme" : "http",
      "host" : "localhost",
      "port" : 8983,
      "path" : "\\/solr\\/informea",
      "http" : { "http_user" : "", "http_pass" : null },
      "excerpt" : 1,
      "retrieve_data" : 1,
      "highlight_data" : 1,
      "skip_schema_check" : null,
      "solr_version" : "",
      "http_method" : "AUTO"
    },
    "enabled" : "1",
    "rdf_mapping" : [],
    "tes" : { "enable" : false }
  }');
  $items['solr_4_informea_documents'] = entity_import('search_api_server', '{
    "name" : "solr 4 informea-documents",
    "machine_name" : "solr_4_informea_documents",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids" : true,
      "site_hash" : true,
      "scheme" : "http",
      "host" : "localhost",
      "port" : "8983",
      "path" : "\\/solr\\/informea-documents",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 1,
      "retrieve_data" : 1,
      "highlight_data" : 1,
      "skip_schema_check" : 0,
      "solr_version" : "",
      "http_method" : "AUTO"
    },
    "enabled" : "1",
    "rdf_mapping" : [],
    "tes" : { "enable" : false }
  }');
  return $items;
}
