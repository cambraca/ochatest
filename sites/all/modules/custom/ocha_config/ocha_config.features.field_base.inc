<?php
/**
 * @file
 * ocha_config.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ocha_config_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_funding_charts'.
  $field_bases['field_funding_charts'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_funding_charts',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'by_year_window' => 'By year and window',
        'by_emergency_window' => 'By emergency and window',
        'by_agency_window' => 'By agency and window',
        'by_sector_window' => 'By sector and window',
        'by_country_year' => 'By country and year (wide)',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_sections'.
  $field_bases['field_sections'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_sections',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'paragraphs',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'paragraphs',
  );

  return $field_bases;
}
