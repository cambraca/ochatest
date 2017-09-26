<?php
/**
 * @file
 * ocha_config.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function ocha_config_paragraphs_info() {
  $items = array(
    'cerf_map' => array(
      'name' => 'CERF Map',
      'bundle' => 'cerf_map',
      'locked' => '1',
    ),
    'funding_charts' => array(
      'name' => 'Funding charts',
      'bundle' => 'funding_charts',
      'locked' => '1',
    ),
    'global_filters' => array(
      'name' => 'Global filters',
      'bundle' => 'global_filters',
      'locked' => '1',
    ),
    'kpis' => array(
      'name' => 'KPIs',
      'bundle' => 'kpis',
      'locked' => '1',
    ),
  );
  return $items;
}
