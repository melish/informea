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
  $queue->name = 'treaty_global';
  $queue->label = 'Global treaties and conventions';
  $queue->language = 'en';
  $queue->handler = 'multiple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'treaty' => 'treaty',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 0,
  );
  $export['treaty_global'] = $queue;

  return $export;
}
