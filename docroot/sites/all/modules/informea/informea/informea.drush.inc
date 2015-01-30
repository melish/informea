<?php


function informea_drush_command() {
  return array(
    'informea-taxonomy-mappings' => array(
      'description' => 'Map taxonomies from Ecolex keywords and GEG into InforMEA',
      'aliases' => array('imea-tm'),
      'options' => array(
        'test' => 'Validate the terms from CSV. Errors are printed in console',
      )
    ),
  );
}

function drush_informea_taxonomy_mappings() {
  $test = drush_get_option('test', FALSE);
  ini_set('auto_detect_line_endings', '1');

  $error = FALSE;
  $terms = array();
  if($file = fopen(drupal_get_path('module', 'informea') . '/informea_ecolex_geg_mappings.csv', 'r')) {
    $i = 0;
    while ($row = fgetcsv($file, 0, ';')) {
      if ($i > 0) {
        $informea = $row[0];
        if (taxonomy_get_term_by_name($informea, 'thesaurus_informea')) {
          if (!array_key_exists($informea, $terms)) {
            $terms[$informea] = array(
              'ecolex' => array(),
              'geg' => array(),
            );
          }
          $mapping =& $terms[$informea];

          // Ecolex mappings
          $ecolex = $row[1];
          if (!empty($ecolex)) {
            if ($ecolex_term = taxonomy_get_term_by_name($ecolex, 'keywords')) {
              if(!in_array($ecolex, $mapping['ecolex'])) {
                $mapping['ecolex'][] = $ecolex;
              }
            }
            else {
              $error = TRUE;
              drupal_set_message("Cannot match ecolex keyword: $ecolex");
            }
          }
          // GEG mappings
          $geg = $row[2];
          if (!empty($geg)) {
            if ($geg_term = taxonomy_get_term_by_name($geg, 'thesaurus_geg')) {
              if(!in_array($geg, $mapping['geg'])) {
                $mapping['geg'][] = $geg;
              }
            }
            else {
              $error = TRUE;
              drupal_set_message("Cannot match geg term: $geg");
            }
          }
        }
        else {
          $error = TRUE;
          drupal_set_message("Cannot match informea term: $informea");
        }
      }
      $i++;
    }
    fclose($file);
  }
  if ($error) {
    drupal_set_message('Errors were encountered while validating all terms', 'error');
  }

  // Update mappings
  foreach ($terms as $term => $mappings) {
    $informea = taxonomy_get_term_by_name($term, 'thesaurus_informea');
    $informea = current($informea);
    $ecolex_terms = $mappings['ecolex'];

    foreach ($ecolex_terms as $i => $t) {
      $ecolex_term = taxonomy_get_term_by_name($t, 'keywords');
      $ecolex_term = current($ecolex_term);
      $informea->field_keywords[LANGUAGE_NONE][$i]['tid'] = $ecolex_term->tid;
    }

    $geg_terms = $mappings['geg'];
    foreach ($geg_terms as $i => $t) {
      $geg_term = taxonomy_get_term_by_name($t, 'thesaurus_geg');
      $geg_term = current($geg_term);
      $informea->field_thesaurus_map_geg[LANGUAGE_NONE][$i]['tid'] = $geg_term->tid;
    }
    if (!$test) {
      taxonomy_term_save($informea);
    }
  }
}
