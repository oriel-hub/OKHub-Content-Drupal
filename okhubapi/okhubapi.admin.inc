<?php
// $Id;

/**
 * @file
 *   OKHUB API Module global settings form.
 *
 * Display and allows to change global settings for the module.
 *
 */

function okhubapi_settings_form() {
  $form = array();

  $form['okhubapi_api_key'] = array(
    '#title' => t('API Key'),
    '#type' => 'textfield',
    '#size' => 36,
    '#maxlength' => 36,
    '#required' => TRUE,
    '#default_value' => variable_get('okhubapi_api_key', ''),
    '#description' => t('Your OKHUB API key. ') . l(t('If you do not have an API key, request one here.'), OKHUB_API_KEY_URL),
  );

  $form['okhubapi_default_dataset'] = array(
    '#title' => t('Default dataset'),
    '#type' => 'hidden',
/*  '#type' => 'select',
    '#options' => array(
      'hub' => 'OKhub'
    ),*/
    '#required' => FALSE,
    '#default_value' => variable_get('okhubapi_default_dataset', OKHUB_API_DEFAULT_DATASET),
    '#description' => t('OKHUB dataset to be used by default.'),
  );
  
  $form['general']['okhubimport_default_datasources'] = array(
    '#title' => t('Default data sources'),
    '#type' => 'checkboxes',
    '#options' => _okhubapi_get_sources_options(),
  	'#default_value' => variable_get('okhubimport_default_datasources', ''),
    '#description' => t('OKHUB data sources to be used by default. If none selected then ALL sources used.'),
  );
  
  $form['okhubapi_number_items'] = array(
    '#title' => t('Default number of items'),
    '#type' => 'textfield',
    '#size' => 10,
    '#maxlength' => 10,
    '#required' => FALSE,
    '#default_value' => variable_get('okhubapi_number_items', OKHUB_API_NUM_ITEMS),
    '#description' => t('Max. number of items to retrieve in each call to the OKHUB API.'),
  );

  $form['okhubapi_cache_time'] = array(
    '#title' => t('Cache lifetime'),
    '#type' => 'select',
    '#options' => array(
      '86400' => t('One day'),
      '172800' => t('Two days'),
      '604800' => t('One week'),
      '1209600' => t('Two weeks'),
      '0' => t('Permanent'),
    ),
    '#required' => FALSE,
    '#default_value' => variable_get('okhubapi_cache_time', OKHUB_API_DEFAULT_CACHE_TIME),
    '#description' => t('How long cached values from the API should be considered valid.'),
  );
  
  $form['advanced']['show_advanced'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show advanced options.'),
  );
    
  $form['advanced']['okhubapi_cache_clear'] = array(
    '#type' => 'submit',
    '#value' => t('Clear all the content in the cache'),
    '#submit' => array('okhubapi_cache_clear'),
    '#states' => array(
      'visible' => array(
        ':input[name="show_advanced"]' => array('checked' => TRUE),
      ),
    ),    
  );

  return system_settings_form($form);
}


/**
 * Clear the request cache.
 */
function okhubapi_cache_clear(&$form) {
  drupal_set_message(t('The OKHUB API cache has been cleared.'));
  cache_clear_all('*', 'okhubapi_cache', TRUE);
}

/**
 * Validates the form settings input.
 */
function okhubapi_settings_form_validate($form, &$form_state) {
  if (!class_exists("OkhubApiWrapper")){
    require OKHUB_API_LIBRARY_PATH . 'okhubwrapper.wrapper.inc';
  }
  $okhubwrapper = new OkhubApiWrapper();
  $reg = '/^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$/';
  if (!preg_match($reg, $form_state['values']['okhubapi_api_key'])) {
    form_set_error('okhubapi_api_key', t('The API key has an invalid format.'));
  }
  else {
    if (!$okhubwrapper->validateKey($form_state['values']['okhubapi_api_key'])) {
      form_set_error('okhubapi_api_key', t('The API key could not be verified. Please check that you have entered a valid API key.'));
    }
    else {
      variable_set('okhubapi_additional_fields', $okhubwrapper->additionalFieldsAvailable($form_state['values']['okhubapi_api_key']));
      // We have to rebuild forms and menus in order to show/hide additional fields (such as subjects) in the admin area.
      module_invoke_all('okhub_api_key');
    }
  }
  $num_items = $form_state['values']['okhubapi_number_items'];
  if (isset($num_items) && !is_numeric($num_items)) {

  }
  if (isset($num_items) && ($num_items < 1)) {
    form_set_error('okhubapi_number_items', t('Please enter a greater number.'));
  }
}








