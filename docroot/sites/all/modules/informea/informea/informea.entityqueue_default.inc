<?php
/**
 * @file
 * informea.entityqueue_default.inc
 */

/**
 * Implements hook_entityqueue_default_queues().
 */
function informea_entityqueue_default_queues() {
  $export = array();

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'front_page_slider';
  $queue->label = 'Front page slider';
  $queue->language = 'en';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'article' => 'article',
      'feed_item' => 'feed_item',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 0,
  );
  $export['front_page_slider'] = $queue;

  return $export;
}
