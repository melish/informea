<?php

/**
 * @file
 * Administration functionality for the Climate Tagger.
 */

/**
 * The Climate Tagger configuration form.
 */
function climate_tagger_admin_settings($form, &$form_state) {
  $config = climate_tagger_get_config();

  $form['#submit'] = array('climate_tagger_admin_settings_submit');

  // Define the container for the vertical tabs.
  $form['settings'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['server_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Server'),
    '#group' => 'settings',
  );

  // Display any unfulfilled module requirement.
  $requirement_errors = powertagging_check_requirements();
  if (!empty($requirement_errors)) {
    $requirement_errors_markup = '';
    foreach ($requirement_errors as $requirement_error) {
      $requirement_errors_markup .= '<div class="messages error">' . $requirement_error . '</div>';
    }
    $form['server_settings']['requirements'] = array(
      '#type' => 'item',
      '#markup' => $requirement_errors_markup,
    );
  }

  $form['server_settings']['climate_tagger_reegle_api_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Authentication token for the Climate Tagger API'),
    '#description' => t('A valid authentication token which has been generated in the Climate Tagger API dashboard.'),
    '#size' => 60,
    '#maxlength' => 60,
    '#default_value' => $config->token,
    '#required' => TRUE,
  );

  $form['server_settings']['health_check'] = array(
    '#type' => 'button',
    '#value' => t('Health check'),
    '#ajax' => array(
      'callback' => 'climate_tagger_health_check',
      'wrapper' => 'health_info',
      'method' => 'replace',
      'effect' => 'slide',
    ),
  );

  $form['server_settings']['health_info'] = array(
    '#type' => 'item',
    '#markup' => '<div id="health_info">Click to check if the server is available.</div>',
  );

  // Tab: Project settings.
  $form['project_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Project options'),
    '#group' => 'settings',
    '#tree' => TRUE,
  );

  // Project selection
  if (isset($config->powertagging_id)) {
    $projects = $config->connection->getApi('PPX')->getProjects();
    if (!empty($projects)) {
      $available_languages = array(
        LANGUAGE_NONE => (object) array(
          'language' => LANGUAGE_NONE,
          'name' => 'Language neutral',
          'enabled' => TRUE,
        ),
      );
      $available_languages = array_merge($available_languages, language_list());

      $project_options = array();
      foreach ($projects as $key => $project) {
        $project_options[$key] = $project->label;
      }
      $form['project_settings']['project'] = array(
        '#type'          => 'select',
        '#title'         => t('Select one of the Climate Thesauri'),
        '#description'   => t('Depending on the focus of your resources, you can now select a specific sector of the Climate Tagger or use all sectors by selecting "Full Climate Thesaurus (default)".<br />This new feature allows even more targeted tagging of your clean energy and climate resources.'),
        '#options'       => $project_options,
        '#default_value' => variable_get('climate_tagger_project_selected', CLIMATE_TAGGER_PROJECT_KEY),
      );

      foreach ($projects as $key => $project) {
        $form['project_settings']['projects'][$key] = array(
          '#type'        => 'fieldset',
          '#title'       => $project->label,
          '#description' => t('Please map the Climate Thesaurus languages to the Drupal languages:'),
          '#states'      => array(
            'visible' => array(
              '#edit-project-settings-project' => array('value' => $key),
            ),
          ),
        );

        $form['project_settings']['projects'][$key]['label'] = array(
          '#type'  => 'hidden',
          '#value' => $project->label,
        );

        // Language mapping.
        $project_language_options = array();
        foreach ($project->languages as $project_language) {
          $project_language_options[$project_language] = $project_language;
        }

        foreach ($available_languages as $lang) {
          if ($lang->enabled) {
            if (isset($config->config['projects'][$key]['languages'][$lang->language]) && !$config->config['projects'][$key]['no_language_selected']) {
              $default_language = $config->config['projects'][$key]['languages'][$lang->language];
            }
            else {
              $default_language = $project->defaultLanguage;
            }
            $form['project_settings']['projects'][$key]['languages'][$lang->language] = array(
              '#type'          => 'select',
              '#title'         => $lang->name,
              '#options'       => $project_language_options,
              '#default_value' => $default_language,
            );
          }
        }

        // Taxonomy selection.
        if (isset($config->config['projects']) && isset($config->config['projects'][$key]) && isset($config->config['projects'][$key]['taxonomy_name']) &&!empty($config->config['projects'][$key]['taxonomy_name'])) {
          $taxonomy_name = $config->config['projects'][$key]['taxonomy_name'];
        }
        else {
          $taxonomy_name = ($key == CLIMATE_TAGGER_PROJECT_KEY) ? t('Climate Thesaurus') : $project->label;
        }
        $form['project_settings']['projects'][$key]['taxonomy_name'] = array(
          '#type' => 'textfield',
          '#title' => t('Select or enter a new Drupal taxonomy'),
          '#description' => t('The name of the taxonomy where the extracted tags from the Climate Tagger API should be stored.</br >If the taxonomy does not exist, it will be created automatically.'),
          '#autocomplete_path' => 'powertagging/autocomplete_taxonomies',
          '#default_value' => $taxonomy_name,
          '#states' => array(
            'required' => array(
              '#edit-project-settings-project' => array('value' => $key),
            ),
          ),
        );
      }
    }
    else {
      $form['project_settings']['errors'] = array(
        '#type' => 'item',
        '#markup' => '<div class="messages warning">' . t('Either no connection can be established or there are no projects available for the given authentication token.') . '</div>',
      );
    }
  }
  else {
    $form['project_settings']['error'] = array(
      '#type' => 'item',
      '#markup' => '<div class="messages warning">' . t('The configuration needs to be saved before a Climate Tagger thesaurus can be selected.') . '</div>',
    );
  }

  // Tab: Global limits
  $form['climate_tagger_global_limits'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global limits'),
    '#group' => 'settings',
  );

  powertagging_global_limits_form($form['climate_tagger_global_limits'], $config->config['concepts_per_extraction'], $config->config['concepts_threshold'], $config->config['freeterms_per_extraction'], $config->config['freeterms_threshold']);
  $form['climate_tagger_global_limits']['freeterms']['freeterms_per_extraction']['#description'] .= '<br />(' . t('Please note these are not currently in the Climate Thesaurus and can cause some tagging inconsistencies') . ')';

  $field_instances = array();
  $content_type_options = array();
  if (isset($config->powertagging_id)) {
    $key = variable_get('climate_tagger_project_selected', CLIMATE_TAGGER_PROJECT_KEY);
    $field_instances = powertagging_get_tagging_field_instances($config->powertagging_id, $key);
    $content_type_options = climate_tagger_get_tagging_field_options_list($field_instances);

    // Search for all content types with the Climate Tagger field.
    if (!empty($field_instances)) {
      $form['climate_tagger_global_limits']['overwriting'] = array(
        '#type' => 'fieldset',
        '#title' => t('List of all content types with "Climate Tagger Tags" fields'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#description' => t('Select those content types which ones you want to overwrite the limits with the global limits defined above.'),
        '#tree' => FALSE,
      );
      if (count($field_instances) > 1) {
        $form['climate_tagger_global_limits']['overwriting']['select_all_content_types'] = array(
          '#type' => 'checkbox',
          '#title' => t('Select all'),
          '#attributes' => array(
            'onclick' => 'jQuery("#edit-overwrite-content-types").find("input").attr("checked", jQuery(this).attr("checked"));',
          ),
        );
      }
      $form['climate_tagger_global_limits']['overwriting']['overwrite_content_types'] = array(
        '#type' => 'checkboxes',
        '#options' => $content_type_options,
        '#validated' => TRUE,
      );
    }
  }

  // Tab: Batch Jobs.
  $form['batch_jobs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Batch jobs'),
    '#group' => 'settings',
    '#tree' => TRUE,
  );

  if (isset($config->powertagging_id)) {
    if (!empty($field_instances)) {
      $form['batch_jobs']['content_types'] = array(
        '#title' => t('Entity types to be included in the batch process.'),
        '#type' => 'checkboxes',
        '#options' => $content_type_options,
      );

      $form['batch_jobs']['skip_tagged_content'] = array(
        '#title' => t('Skip already tagged content'),
        '#type' => 'radios',
        '#options' => array(
          '1' => t('Yes'),
          '0' => t('No'),
        ),
        '#default_value' => TRUE,
      );

      $form['batch_jobs']['entities_per_request'] = array(
        '#type' => 'textfield',
        '#title' => t('Entities per request'),
        '#description' => t('The number of entities, that get processed during one HTTP request. (Allowed value range: 1 - 100)') . '<br />' . t('The higher this number is, the less HTTP requests have to be sent to the server until the batch finished tagging ALL your entities, what results in a shorter duration of the bulk tagging process.') . '<br />' . t('Numbers too high can result in a timeout, which will break the whole bulk tagging process.') . '<br />' . t('If entities are configured to get tagged with uploaded files, a value of 5 or below is recommended.'),
        '#required' => TRUE,
        '#default_value' => '10',
      );

      $form['batch_jobs']['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Index',
        '#validate' => array('climate_tagger_admin_settings_batch_validate'),
        '#submit' => array('climate_tagger_admin_settings_batch_submit'),
      );
    }
    else {
      $form['batch_jobs']['error'] = array(
        '#type' => 'item',
        '#markup' => '<div class="messages warning">' . t('No taggable content types found for the Climate Tagger API.') . '</div>',
      );
    }
  }
  else {
    $form['batch_jobs']['error'] = array(
      '#type' => 'item',
      '#markup' => '<div class="messages warning">' . t('The configuration needs to be saved before a batch process can be started.') . '</div>',
    );
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['cancel'] = array(
    '#type' => 'link',
    '#title' => t('Cancel'),
    '#href' => 'admin/config/services/climate-tagger',
  );

  return $form;
}

/**
 * Validate handler for the Climate Tagger configuration form.
 */
function climate_tagger_admin_settings_validate($form, &$form_state) {
  if (isset($form_state['values']['project_settings']['projects'])) {
    $key = $form_state['values']['project_settings']['project'];
    if (empty($form_state['values']['project_settings']['projects'][$key]['taxonomy_name'])) {
      form_set_error('projects][' . $key . '][taxonomy_name', t('"Select or enter a new Drupal taxonomy" field is required.'));
    }
  }
}

/**
 * Submit handler for the Climate Tagger configuration form.
 */
function climate_tagger_admin_settings_submit($form, &$form_state) {
  $powertagging_id = climate_tagger_get_powertagging_id();

  // Create a form-state, that can be used to create or update the powertagging
  // configuration for the Climate Tagger API.
  $new_form_state = array();
  form_load_include($new_form_state, 'inc', 'powertagging', 'includes/powertagging.admin');
  $new_form_state['values'] = array_merge($form_state['values'], array(
    'title' => 'Climate Tagger API',
    'server_title' => 'Climate Tagger API Server',
    'url' => CLIMATE_TAGGER_API_URL,
    'name' => '',
    'pass' => '',
  ));

  // A Powertagging-configuration needs to be created first.
  if ($powertagging_id == FALSE) {
    // Create a new powertagging configuration over Drupal's Form API.
    drupal_form_submit('powertagging_form', $new_form_state);

    $errors = form_get_errors();
    if (!empty($errors)) {
      foreach ($errors as $error) {
        $msg = 'Error: %error';
        $var = array('%error' => $error);
        watchdog('climate tagger', $msg, $var, WATCHDOG_ERROR);
      }
      return FALSE;
    }

    // Get the ID of the powertagging configuration we just created.
    $powertagging_id = climate_tagger_get_powertagging_id();

    // If powertagging-id is still false here, break everything (error).
    if ($powertagging_id == FALSE) {
      drupal_set_message(t('Could not create a Powertagging configuration for the Climate Tagger API'), 'error');
      return FALSE;
    }
  }

  // Update the powertagging-configuration.
  $powertagging_config = powertagging_config_load($powertagging_id);

  // Deselect the taxonomy for non selected projects.
  if (isset($form_state['values']['project_settings']['projects'])) {
    foreach ($form_state['values']['project_settings']['projects'] as $key => &$project) {
      if ($key == $form_state['values']['project_settings']['project']) {
        $project['no_language_selected'] = FALSE;
      }
      else {
        $project['taxonomy_name'] = '';
        $project['no_language_selected'] = TRUE;
      }
    }
    // Add Climate Tagger as a project.
    $new_form_state['values']['projects'] = $form_state['values']['project_settings']['projects'];
  }

  // Set the connection id.
  $new_form_state['values']['connection_id'] = $powertagging_config->connection_id;

  // Submit the powertagging form.
  $new_form_state['build_info']['args'] = array($powertagging_config);
  drupal_form_submit('powertagging_form', $new_form_state);

  // Clear the status-messages of the powertagging-config-creation.
  drupal_get_messages('status');

  $errors = form_get_errors();
  if (!empty($errors)) {
    foreach ($errors as $error) {
      $msg = 'Error: %error';
      $var = array('%error' => $error);
      watchdog('climate tagger', $msg, $var, WATCHDOG_ERROR);
    }
    return FALSE;
  }

  // Adapt the project key stored in all the climate tagger fields.
  $key = variable_get('climate_tagger_project_selected', CLIMATE_TAGGER_PROJECT_KEY);
  if (isset($form_state['values']['project_settings']['project']) && $key != $form_state['values']['project_settings']['project']) {
    $field_info = field_info_field_map();
    foreach ($field_info as $field_name => $fields) {
      if ($fields['type'] == 'powertagging') {
        foreach ($fields['bundles'] as $bundle_name => $entity_types) {
          foreach ($entity_types as $entity_type) {
            $instance = field_info_instance($bundle_name, $field_name, $entity_type);
            $instance['settings']['project_id'] = $form_state['values']['project_settings']['project'];
            field_update_instance(($instance));
          }
        }
      }
    }
    variable_set('climate_tagger_project_selected', $form_state['values']['project_settings']['project']);
  }

  // Overwrite content type limits with the global limits for
  // each selected content type.
  if (isset($form_state['values']['overwrite_content_types'])) {
    $overwrite_content_types = array_filter($form_state['values']['overwrite_content_types']);
    if (!empty($overwrite_content_types)) {
      foreach ($overwrite_content_types as $content_type) {
        list($entity_type, $bundle_name, $field_name) = explode(' ', $content_type);
        $instance = field_info_instance($entity_type, $field_name, $bundle_name);
        $limits = array(
          'concepts_per_extraction' => array('value' => $form_state['values']['concepts_per_extraction']['value']),
          'concepts_threshold' => array('value' => $form_state['values']['concepts_threshold']['value']),
          'freeterms_per_extraction' => array('value' => $form_state['values']['freeterms_per_extraction']['value']),
          'freeterms_threshold' => array('value' => $form_state['values']['freeterms_threshold']['value']),
        );
        $instance['settings'] = array_merge($instance['settings'], $limits);
        field_update_instance(($instance));
      }
    }
  }

  // Powertagging configuration is saved --> now go on with Climate Tagger API specific
  // variables.
  variable_set('climate_tagger_reegle_api_token', $form_state['values']['climate_tagger_reegle_api_token']);
  drupal_set_message(t('Successfully saved the configuration of Climate Tagger.'));
}

/**
 * Ajax callback function for checking the connection to the Climate Tagger API.
 */
function climate_tagger_health_check($form, $form_state) {
  $available = '<div id="health_info" class="available">' . t('The server is available.') . '</div>';
  $not_available = '<div id="health_info" class="not-available">' . t('The server is not available or the credentials are incorrect.') . '</div>';

  if (isset($form_state['values']['climate_tagger_reegle_api_token']) && !empty($form_state['values']['climate_tagger_reegle_api_token'])) {
    // Save the previous token.
    $previous_token = variable_get('climate_tagger_reegle_api_token', '');
    variable_set('climate_tagger_reegle_api_token', $form_state['values']['climate_tagger_reegle_api_token']);

    $connection = SemanticConnector::getConnection('pp_server');
    $connection->setUrl(CLIMATE_TAGGER_API_URL);
    $pp_api = $connection->getApi('PPX');
    $availability = $pp_api->available();

    // Restore the previous token.
    variable_set('climate_tagger_reegle_api_token', $previous_token);

    if (isset($availability['message']) && !empty($availability['message'])) {
      return '<div id="health_info" class="not-available">' . $availability['message'] . '</div>';
    }
    else {
      return $availability['success'] ? $available : $not_available;
    }
  }

  return $not_available;
}

/**
 * Validation-handler for the batch process in the Climate Tagger config form.
 */
function climate_tagger_admin_settings_batch_validate($form, &$form_state) {
  $valid_content_types = array();
  foreach ($form_state['values']['batch_jobs']['content_types'] as $content_type) {
    if ($content_type) {
      $valid_content_types[] = $content_type;
    }
  }

  if (empty($valid_content_types)) {
    form_set_error('batch_jobs][content_types', t('Select at least one content type to be included in the batch process.'));
  }

  $entities_per_request = $form_state['values']['batch_jobs']['entities_per_request'];
  if (empty($entities_per_request) || !ctype_digit($entities_per_request) || (int) $entities_per_request == 0 || (int) $entities_per_request > 100) {
    form_set_error('batch_jobs][entities_per_request', t('Only values in the range of 1 - 100 are allowed for field "Entities per request"'));
  }
}

/**
 * Submit-handler for the batch process in the Climate Tagger config form.
 */
function climate_tagger_admin_settings_batch_submit($form, &$form_state) {
  $content_types = array();
  foreach ($form_state['values']['batch_jobs']['content_types'] as $content_type) {
    if ($content_type) {
      $content_types[] = $content_type;
    }
  }

  $key = variable_get('climate_tagger_project_selected', CLIMATE_TAGGER_PROJECT_KEY);
  powertagging_indexProject(climate_tagger_get_config(), $key, array(
    'content_types' => $content_types,
    'skip_tagged_content' => $form_state['values']['batch_jobs']['skip_tagged_content'],
    'entities_per_request' => $form_state['values']['batch_jobs']['entities_per_request'],
  ), 'climate_tagger_batch_finished');
}
