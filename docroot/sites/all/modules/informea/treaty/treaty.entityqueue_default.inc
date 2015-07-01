<?php
/**
 * @file
 * treaty.entityqueue_default.inc
 */

/**
 * Implements hook_entityqueue_default_queues().
 */
function treaty_entityqueue_default_queues() {
  $export = array();

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'regional_treaties_ordering';
  $queue->label = 'Regional treaties ordering';
  $queue->language = 'en';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'treaty' => 'treaty',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 1,
  );
  $export['regional_treaties_ordering'] = $queue;

  return $export;
}
