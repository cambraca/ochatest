<?php

/**
 * Utility function to create a chart for a paragraph.
 *
 * @param array $variables
 * @param string $type
 * @param array $data
 * @param array|string $extra_classes
 */
function _ocha_data_include_chart(&$variables, $type, $data, $extra_classes = []) {
  $variables['#attached']['js'][] = [
    'type' => 'external',
    'data' => '//cdn.plot.ly/plotly-1.5.0.min.js',
  ];

  $variables['#attached']['js'][] = drupal_get_path('module', 'ocha_data') . '/js/common.js';
  $variables['#attached']['js'][] = drupal_get_path('module', 'ocha_data') . '/js/' . $type . '.js';

  $html_id = drupal_html_id('chart');

  $variables['chart'] = [
    '#type' => 'container',
    '#attributes' => ['class' => array_merge([$type], (array) $extra_classes), 'id' => $html_id],
  ];

  $variables['#attached']['js'][] = [
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
      $projects = ocha_get_data(OCHA_DATASET_ALL_PROJECTS);

      $values = [
        'Allocated' => [
          'value' => 0,
          'format' => 'currency_millions',
        ],
        'Underfunded Emergencies' => [
          'value' => 0,
          'format' => 'currency_millions',
        ],
        'Rapid Response' => [
          'value' => 0,
          'format' => 'currency_millions',
        ],
        'Countries Assisted' => [
          'value' => 0,
          'list' => [],
        ],
        'Projects Approved' => [
          'value' => 0,
        ],
      ];

      foreach ($projects as $project) {
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
      $projects = ocha_get_data(OCHA_DATASET_ALL_PROJECTS);

      $data = [];
      foreach ($projects as $project) {
        if (!array_key_exists($project['CountryCode'], $data))
          $data[$project['CountryCode']] = [
            'label' => $project['CountryName'],
            'value' => 0,
          ];

        $data[$project['CountryCode']]['value'] += floatval($project['TotalAmountApproved']);
      }

      $processed_data = [
        'countries' => [],
        'labels' => [],
        'values' => [],
        'title' => t('Funding by country (in US$ million)'),
      ];
      foreach ($data as $code => $datum) {
        $processed_data['countries'][] = $code;
        $processed_data['labels'][] = $datum['label'];
        $processed_data['values'][] = $datum['value'];
      }

      _ocha_data_include_chart($variables['content'], 'ocha_cerf_map', $processed_data);
      break;

    case 'funding_charts':
      $variables['content']['field_funding_charts']['#access'] = FALSE;

      $projects = ocha_get_data(OCHA_DATASET_ALL_PROJECTS);
      $agencies = ocha_get_data(OCHA_DATASET_ALL_AGENCIES);

      $data = [
        'by_year_window' => [],
        'by_emergency_window' => [],
        'by_agency_window' => [],
        'by_sector_window' => [],
        'by_country_year' => [],
      ];
      foreach ($projects as $project) {
        if (!floatval($project['TotalAmountApproved']))
          continue;


        _ocha_data_deep_array_add(floatval($project['TotalAmountApproved']), $data, 'by_year_window', $project['Year'], $project['WindowFullName']);

        _ocha_data_deep_array_add(floatval($project['TotalAmountApproved']), $data, 'by_emergency_window', $project['EmergencyGroupName'], $project['WindowFullName']);

        _ocha_data_deep_array_add(floatval($project['TotalAmountApproved']), $data, 'by_agency_window', $agencies[$project['AgencyID']]['AgencyShortName'], $project['WindowFullName']);

        foreach ($project['projectsectors'] as $projectsector) {
          if (!array_key_exists('SectorAmount', $projectsector))
            continue;
          $sector_name = array_key_exists('SectorName', $projectsector) ? $projectsector['SectorName'] : '(none)';
          _ocha_data_deep_array_add(floatval($projectsector['SectorAmount']), $data, 'by_sector_window', $sector_name, $project['WindowFullName']);
        }

        _ocha_data_deep_array_add(floatval($project['TotalAmountApproved']), $data, 'by_country_year', $project['CountryName'], $project['WindowFullName']);
      }

      $initial_data = [
        'by_year_window' => [
          'title' => t('Funding by year'),
        ],
        'by_emergency_window' => [
          'title' => t('Funding by emergency'),
        ],
        'by_agency_window' => [
          'title' => t('Funding by agency'),
        ],
        'by_sector_window' => [
          'title' => t('Funding by sector'),
        ],
        'by_country_year' => [
          'title' => t('Funding by country/year'),
        ],
      ];

      foreach ($variables['content']['field_funding_charts']['#items'] as $item) {
        $key = $item['value'];
        if (!isset($data[$key]))
          continue;

        ksort($data[$key]);

        $processed_data = $initial_data[$key];
        $processed_data['sets'] = [];

        foreach ($data[$key] as $category => $category_data) {
          ksort($category_data);

          foreach ($category_data as $set => $amount) {
            if (!array_key_exists($set, $processed_data['sets']))
              $processed_data['sets'][$set] = [
                'name' => $set,
                'type' => 'bar',
                'x' => [],
                'y' => [],
              ];

            $processed_data['sets'][$set]['x'][] = $category;
            $processed_data['sets'][$set]['y'][] = $amount;
          }
        }
        $processed_data['sets'] = array_values($processed_data['sets']);

        $variables['content'][$key] = [];
        _ocha_data_include_chart($variables['content'][$key], 'ocha_stackedbar', $processed_data, $key);
      }

      break;
  }
}

/**
 * Adds the value to the given path in the array. E.g.
 *   $array = ['a' => ['b' => ['c' => 4]]];
 *   _add(1, $array, 'a', 'b', 'c');
 *   //now $array is ['a' => ['b' => ['c' => 5]]];
 *   _add(2, $array, 'd', 'e');
 *   //now $array is ['a' => ['b' => ['c' => 5]], 'd' => ['e' => 2]];
 *
 * @param float $value
 * @param array $array
 * @param string $key1
 * @param string $key2
 * @param string ...
 */
function _ocha_data_deep_array_add($value, &$array) {
  $path = func_get_args();
  array_shift($path);
  array_shift($path);

  $first_part = array_shift($path);
  if (!array_key_exists($first_part, $array))
    $array[$first_part] = $path ? [] : 0;

  if (!$path) {
    $array[$first_part] += $value;
    return;
  }

  call_user_func_array(__FUNCTION__, array_merge([$value, &$array[$first_part]], $path));
}
