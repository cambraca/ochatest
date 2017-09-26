<?php
/**
 * @file
 * ocha_config.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ocha_config_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-page-field_sections'.
  $field_instances['node-page-field_sections'] = array(
    'bundle' => 'page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_sections',
    'label' => 'Sections',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'global_filters' => -1,
        'kpis' => -1,
      ),
      'bundle_weights' => array(
        'global_filters' => 2,
        'kpis' => 3,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Paragraph',
      'title_multiple' => 'Paragraphs',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => -3,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-funding_charts-field_funding_charts'.
  $field_instances['paragraphs_item-funding_charts-field_funding_charts'] = array(
    'bundle' => 'funding_charts',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_funding_charts',
    'label' => 'Funding charts',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Funding charts');
  t('Sections');

  return $field_instances;
}
