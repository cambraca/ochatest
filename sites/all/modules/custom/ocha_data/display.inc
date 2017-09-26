<?php

/**
 * Utility function to create a chart for a paragraph.
 *
 * @param array $variables
 * @param array $data
 * @param string $js
 */
function _ocha_data_include_chart(&$variables, $data, $js = NULL) {
  $variables['content']['#attached']['js'][] = [
    'type' => 'external',
    'data' => '//cdn.plot.ly/plotly-1.5.0.min.js',
  ];

  if ($js)
    $variables['content']['#attached']['js'][] = drupal_get_path('module', 'ocha_data') . '/js/' . $js;

  $html_id = drupal_html_id('chart');

  $variables['content']['chart'] = [
    '#type' => 'container',
    '#attributes' => ['class' => ['ocha_cerf_map'], 'id' => $html_id],
  ];

  $variables['content']['#attached']['js'][] = [
    'type' => 'setting',
    'data' => [
      'ocha_data' => [
        $html_id => $data,
      ],
    ],
  ];
}

/**
 * Implements hook_preprocess_entity().
 */
function ocha_data_preprocess_entity(&$variables) {
  if ($variables['entity_type'] !== 'paragraphs_item')
    return;

  /** @var \ParagraphsItemEntity $p */
  $p = $variables['paragraphs_item'];

  switch ($p->bundle()) {
    case 'kpis':
      $all = ocha_get_data(OCHA_DATASET_ALL_PROJECTS);

      $values = [
        'Allocated' => [
          'value' => 0,
          'format' => 'currency_millions',
        ],
        'Underfunded Emergencies' => [
          'value' => 0,
          'format' => 'currency',
        ],
        'Rapid Response' => [
          'value' => 0,
          'format' => 'currency',
        ],
        'Countries Assisted' => [
          'value' => 0,
          'list' => [],
        ],
        'Projects Approved' => [
          'value' => 0,
        ],
      ];

      foreach ($all['project'] as $project) {
        $amount = floatval($project['TotalAmountApproved']);

        $values['Allocated']['value'] += $amount;

        if ($project['WindowID'] == 2)
          $values['Underfunded Emergencies']['value'] += $amount;

        if ($project['WindowID'] == 3)
          $values['Rapid Response']['value'] += $amount;

        $values['Countries Assisted']['list'][$project['CountryCode']] = TRUE;

        if ($project['ProjectStatus'] === 'Approved')
          $values['Projects Approved']['value']++;
      }

      $values['Countries Assisted']['value'] = count($values['Countries Assisted']['list']);

      $variables['content']['values'] = $values;
      break;

    case 'global_filters':

      break;

    case 'cerf_map':
      $all = ocha_get_data(OCHA_DATASET_ALL_PROJECTS);

      $data = [];
      foreach ($all['project'] as $project) {
        if (!array_key_exists($project['CountryCode'], $data))
          $data[$project['CountryCode']] = [
            'label' => $project['CountryName'],
            'value' => 0,
          ];

        $data[$project['CountryCode']]['value'] += floatval($project['TotalAmountApproved']);
      }

      $processed = [
        'countries' => [],
        'labels' => [],
        'values' => [],
      ];
      foreach ($data as $code => $datum) {
        $processed['countries'][] = $code;
        $processed['labels'][] = $datum['label'];
        $processed['values'][] = $datum['value'];
      }

      _ocha_data_include_chart($variables, $processed, 'cerf_map.js');
      break;
  }
}
