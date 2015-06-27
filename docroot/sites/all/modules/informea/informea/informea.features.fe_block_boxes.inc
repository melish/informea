<?php
/**
 * @file
 * informea.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function informea_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Map Disclaimer';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'map_disclaimer';
  $fe_block_boxes->body = '<div class="alert alert-warning"><strong>Disclaimer</strong>:&nbsp;The designations employed and the presentation of material on this map do not imply the expression of any opinion whatsoever on the part of the United Nations concerning the legal status of any country, territory, city or area or of its authorities, or concerning the delimitation of its frontiers or boundaries.</div>';

  $export['map_disclaimer'] = $fe_block_boxes;

  return $export;
}
