<?php


function taxonomy_external_sync_taxonomy_form_element($form, $form_state) {
  $ret = array();
  $vocabulary = $form['#vocabulary'];
  $ret['tes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Synchronise with external data source'),
    '#prefix' => '<div id="wrapper-taxonomy-external-sync-plugins">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  $ret['tes']['enable'] = array(
    '#type' => 'checkbox',
    '#default_value' => !empty($vocabulary->tes),
    '#title' => 'Enable',
    '#ajax' => array(
      'callback' => 'taxonomy_external_sync_taxonomy_form_element_plugins_ajax_callback',
      'wrapper' => 'wrapper-taxonomy-external-sync-plugins',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  if (!empty($form_state['values']['tes']['enable']) || !empty($vocabulary->tes)) {
    $options = array();
    $plugins = taxonomy_external_sync_source_plugins();
    /**
     * @var string $machine_name
     * @var \Drupal\taxonomy_external_sync\plugin\source\DefaultSource $ob
     */
    foreach ($plugins as $machine_name => $ob) {
      $options[$machine_name] = $ob->getName();
    }
    $selected = !empty($vocabulary->tes['plugin']) ? $vocabulary->tes['plugin'] : NULL;
    if (!empty($form_state['values']['tes']['plugin'])) {
      $selected = $form_state['values']['tes']['plugin'];
    }
    $ret['tes']['plugin'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#title' => t('Source'),
      '#required' => TRUE,
      '#visible' => FALSE,
      '#default_value' => $selected,
      '#ajax' => array(
        'callback' => 'taxonomy_external_sync_taxonomy_form_element_plugins_ajax_callback',
        'wrapper' => 'wrapper-taxonomy-external-sync-plugins',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    );
    /** @var \Drupal\taxonomy_external_sync\plugin\source\DefaultSource $plugin */
    if ($selected && $plugin = $plugins[$selected]) {
      $ret['tes']['plugin_config'] = array(
        '#type' => 'fieldset',
        '#title' => t('Configuration'),
        '#tree' => TRUE,
      );
      $ret['tes']['plugin_config']['description'] = array(
        '#type' => 'item',
        '#markup' => '<div>' . $plugin->getDescription() . '</div>',
      );
      if ($plugin_form = $plugin->getConfigurationForm($vocabulary, $form_state)) {
        foreach ($plugin_form as $key => $element) {
          $ret['tes']['plugin_config'][$key] = $element;
        }
      }
      // Mappings
      $destination_fields = taxonomy_external_sync_get_taxonomy_fields($vocabulary->machine_name);
      $ret['tes']['mappings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Mappings'),
        '#tree' => TRUE,
      );
      foreach ($destination_fields as $field_name => $label) {
        $options = array('' => t('-- Not mapped --'));
        if ($source_fields = $plugin->getFieldNames()) {
          $options += $source_fields;
        }
        $selected = !empty($vocabulary->tes['mappings'][$field_name]) ? $vocabulary->tes['mappings'][$field_name] : NULL;
        $ret['tes']['mappings'][$field_name] = array(
          '#type' => 'select',
          '#options' => $options,
          '#default_value' => $selected,
          '#title' => $label,
          '#attributes' => array('class' => array('select2-excluded')),
        );
      }
    }
  }
  return $ret;
}

function taxonomy_external_sync_taxonomy_form_element_plugins_ajax_callback($form, $form_state) {
  return $form['tes'];
}
