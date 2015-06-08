<?php
/**
 * @file
 * informea.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function informea_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function informea_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function informea_image_default_styles() {
  $styles = array();

  // Exported image style: logo.
  $styles['logo'] = array(
    'label' => 'logo',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 40,
          'height' => 40,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function informea_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Article'),
      'base' => 'node_content',
      'description' => t('Use <em>articles</em> for time-sensitive content like news, press releases or blog posts.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_default_search_api_index().
 */
function informea_default_search_api_index() {
  $items = array();
  $items['news_search_index'] = entity_import('search_api_index', '{
    "name" : "News search index",
    "machine_name" : "news_search_index",
    "description" : "Search RSS news",
    "server" : "database_server",
    "item_type" : "node",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "author" : { "type" : "integer", "entity_type" : "user" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "feed_nid" : { "type" : "integer" },
        "field_feed_item_description:summary" : { "type" : "text" },
        "field_feed_item_description:value" : { "type" : "text" },
        "field_informea_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_mea_topic" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "language" : { "type" : "string" },
        "nid" : { "type" : "integer" },
        "promote" : { "type" : "boolean" },
        "search_api_language" : { "type" : "string" },
        "search_api_viewed" : { "type" : "text" },
        "status" : { "type" : "integer" },
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
          "status" : 1,
          "weight" : "-10",
          "settings" : { "default" : "0", "bundles" : { "feed_item" : "feed_item" } }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
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
              "vuuid" : true,
              "title_field" : true,
              "field_feed_item_description:value" : true,
              "field_feed_item_description:summary" : true
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
              "vuuid" : true,
              "title_field" : true,
              "field_feed_item_description:value" : true,
              "field_feed_item_description:summary" : true
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
              "vuuid" : true,
              "title_field" : true,
              "field_feed_item_description:value" : true,
              "field_feed_item_description:summary" : true
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
              "field_feed_item_description:value" : true,
              "field_feed_item_description:summary" : true
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
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function informea_default_search_api_server() {
  $items = array();
  $items['database_server'] = entity_import('search_api_server', '{
    "name" : "Database server",
    "machine_name" : "database_server",
    "description" : "",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "2",
      "partial_matches" : 0,
      "indexes" : { "news_search_index" : {
          "nid" : {
            "table" : "search_api_db_news_search_index",
            "column" : "nid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "vid" : {
            "table" : "search_api_db_news_search_index",
            "column" : "vid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "type" : {
            "table" : "search_api_db_news_search_index",
            "column" : "type",
            "type" : "string",
            "boost" : "1.0"
          },
          "title" : {
            "table" : "search_api_db_news_search_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "language" : {
            "table" : "search_api_db_news_search_index",
            "column" : "language",
            "type" : "string",
            "boost" : "1.0"
          },
          "url" : {
            "table" : "search_api_db_news_search_index",
            "column" : "url",
            "type" : "uri",
            "boost" : "1.0"
          },
          "status" : {
            "table" : "search_api_db_news_search_index",
            "column" : "status",
            "type" : "integer",
            "boost" : "1.0"
          },
          "promote" : {
            "table" : "search_api_db_news_search_index",
            "column" : "promote",
            "type" : "boolean",
            "boost" : "1.0"
          },
          "feed_nid" : {
            "table" : "search_api_db_news_search_index",
            "column" : "feed_nid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "uuid" : {
            "table" : "search_api_db_news_search_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "vuuid" : {
            "table" : "search_api_db_news_search_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "title_field" : {
            "table" : "search_api_db_news_search_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_tags" : {
            "table" : "search_api_db_news_search_index_field_tags",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_informea_tags" : {
            "table" : "search_api_db_news_search_index_field_informea_tags",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_news_search_index",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "field_feed_item_description:value" : {
            "table" : "search_api_db_news_search_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_feed_item_description:summary" : {
            "table" : "search_api_db_news_search_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "search_api_viewed" : {
            "table" : "search_api_db_news_search_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "created" : {
            "table" : "search_api_db_news_search_index",
            "column" : "created",
            "type" : "date",
            "boost" : "1.0"
          },
          "changed" : {
            "table" : "search_api_db_news_search_index",
            "column" : "changed",
            "type" : "date",
            "boost" : "1.0"
          },
          "author" : {
            "table" : "search_api_db_news_search_index",
            "column" : "author",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_mea_topic" : {
            "table" : "search_api_db_news_search_index",
            "column" : "field_mea_topic",
            "type" : "integer",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  return $items;
}
