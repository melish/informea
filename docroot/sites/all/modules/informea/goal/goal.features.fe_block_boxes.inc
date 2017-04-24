<?php
/**
 * @file
 * goal.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function goal_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Goals and principles disclaimer';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'goals_disclaimer';
  $fe_block_boxes->body = '<div class="alert alert-warning">Dear Visitor, this section is currently under development.</div><p>&nbsp;</p>';

  $export['goals_disclaimer'] = $fe_block_boxes;

  return $export;
}
