<?php
// $Id;

/**
 * @file
 *   OKHUB Import Module global settings form.
 *
 * Display and allows to change global settings for the module.
 * Includes a button to import content and categories.
 *
 * Note: The author of the imported assets is a required field. It's set globally and overrides the importers'. 
 */
function okhubimport_settings_form() {
  drupal_add_css(drupal_get_path('module', 'okhubapi') . '/lib/tokenize/jquery.tokenize.css');
  drupal_add_js(drupal_get_path('module', 'okhubapi') . '/lib/tokenize/jquery.tokenize.js');
  drupal_add_css(drupal_get_path('module', 'okhubimport') . '/css/okhubimport-admin.css');
  drupal_add_js(drupal_get_path('module', 'okhubimport') . '/js/okhubimport-admin.js');
  $okhubwrapper = new OkhubApiWrapper();
  $form = array();
  $additional_fields = variable_get('okhubapi_additional_fields', FALSE);
  $list_categories = 'regions, countries, themes';
  if ($additional_fields) {
    $list_categories .= ', subjects';
  }

  if(variable_get('okhubapi_api_key', '')){  
  
	  $form['#submit'][] = 'okhubimport_settings_form_submit';
	
	  $form['global'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('OKHUB API Module settings'),
	    '#prefix' => '<div class="okhubimport-form-general">',
	    '#suffix' => '</div>',
	    '#collapsible' => TRUE,
	    '#collapsed' => FALSE,
	  );
	
	  /* this is left over from IDS API Module was Eddis or Brigde now always hub */
	  $form['global']['okhubimport_default_dataset'] = array(
	    '#title' => t('Default dataset'),
	    '#type' => 'hidden',
	    '#required' => TRUE,
	    '#default_value' => variable_get('okhubimport_default_dataset', OKHUB_API_DEFAULT_DATASET),
	    '#description' => t('OKHUB dataset to be used by default.'),
	  );
	 
  	$api_key = variable_get('okhubapi_api_key', '');
	  $sources_options = $okhubwrapper->okhubapi_get_sources_options($api_key);
	
	  
	$form['global']['info'] = array(
	    '#title' => t('general settings information'),
	    '#type' => 'markup',
		'#markup' => _okhubapi_global_settings_display() . _okhubapi_global_settings_link(),
	  );   
	  
	  $form['general'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('General importing settings'),
	    '#description' => t('These settings apply both to manual and periodic automatic imports of <b>documents</b> and <b>organisations</b>.<br>Please note that no partial importing is available for categories (' . $list_categories . '):<br> if chosen, all of the items in the categories sets are imported in order to preserve the internal coherence of the data.'),
	    '#prefix' => '<div class="okhubimport-form-general">',
	    '#suffix' => '</div>',
	    '#collapsible' => TRUE,
	    '#collapsed' => TRUE,
	  );
	
	  $form['general']['okhubimport_number_assets'] = array(
	    '#title' => t('Number of documents and/or organisations to import'),
	    '#type' => 'textfield',
	    '#size' => 10,
	    '#maxlength' => 10,
	    '#required' => FALSE,
	    '#default_value' => variable_get('okhubimport_number_assets', OKHUB_IMPORT_NUM_ASSETS),
	    '#description' => t('Number of documents and/or organisations to retrieve in each call to the OKHUB API. Leave blank if you do not want to limit it, and import all available items.'),
	  );
	  
	  $form['general']['okhubimport_new_user'] = array(
	    '#title' => t('Author'),
	    '#type' => 'textfield',
	    '#size' => 10,
	    '#maxlength' => 10,
	    '#required' => TRUE,
	    '#default_value' => variable_get('okhubimport_new_user', OKHUB_IMPORT_USER),
	    '#description' => t('Imported OKHUB content will be assigned to this user. If the user does not exist, it will be created.'),
	    '#autocomplete_path' => 'user/autocomplete',
	  );
	  
	   $form['filters'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('Filter importing settings'),
	    '#description' => t('Use these settings to filter the the imported items.'),
	    '#prefix' => '<div class="okhubimport-form-general">',
	    '#suffix' => '</div>',
	    '#collapsible' => TRUE,
	    '#collapsed' => TRUE,
	  ); 
	  
	  $form['filters']['okhubimport_age_new_assets'] = array(
	    '#title' => t('Age of new content'),
	    '#type' => 'select',
	    '#options' => array(
	      '0' => t('Do not filter by age'),
	      '7' => t('One week'),
	      '30' => t('One month'),
	      '180' => t('Six months'),
	      '365' => t('One year'),
	    ),
	    '#required' => FALSE,
	    '#default_value' => variable_get('okhubimport_age_new_assets', OKHUB_IMPORT_AGE_NEW_ASSETS),
	    '#description' => t('Import documents and/or organisations posted within the indicated period.'),
	  );
	  
	  $sources_options = _okhubapi_get_sources_with_themes_options();
	  
	  $form['filters']['okhubimport_themes_datasources'] = array(
	    '#title' => t('Data sources to provide themes'),
	    '#type' => 'checkboxes',
	    '#options' => $sources_options,
	  	'#default_value' => variable_get('okhubimport_themes_datasources', ''),
	    '#description' => t('OKHUB data sources to be used to provide the themes. If none selected then ALL sources used. Note only data sources that make their themes available are listed.'),
	  );
	  
	  $form['filters'][] = array(
	    '#type' => 'submit',
	    '#value' => t('Save configuration'),
	    '#submit' => array('okhubimport_settings_form_submit'),
	  );
	  
	  $theme_arr = _okhubapi_get_themes_arr(TRUE);
	  
	  $theme_options = _okhubapi_get_themes_options($theme_arr);
	  
	  $language_options_for_themes = _okhubapi_get_language_options_from_themes($theme_arr);
	  
	  $form['filters']['okhubimport_default_lang_themes'] = array(
	    '#title' => t('Language selection for Themes'),
	    '#type' => 'select',
	    '#options' => $language_options_for_themes,
	  	'#default_value' => variable_get('okhubimport_default_lang_themes', ''),
	    '#description' => t('Languages to be used to filter Themes.'),
	  );
	  
	  $form['filters']['okhubimport_default_themes'] = array(
	    '#title' => t('Themes'),
	    '#type' => 'select',
	    '#multiple' => 'true',
	    '#options' => $theme_options,
	  	'#default_value' => variable_get('okhubimport_default_themes', ''),
	    '#description' => t('Themes to be used to filter results. If none selected then ALL themes used.'),
	  );
	
	  $form['filters']['okhubimport_query_string'] = array(
	    '#title' => t('Query string'),
	    '#type' => 'textfield',
	    '#size' => 40,
	    '#required' => FALSE,
	    '#default_value' => variable_get('okhubimport_query_string'),
	    '#description' => t('Query string to be appended to the OKHUB API URLs used when importing <b>documents and/or organisations</b>.<br>Use comma-separated pairs of unencoded query fields and values (example: <i>country=Argentina,keyword=climate change,language_name=Spanish</i>).<br>Please check the <a href="@okhubapidoc">OKHUB API documentation</a> for a list of query fields available.', array('@okhubapidoc' => 'http://developer.okhub.org/hub-api-documentation/api-explorer/')),
	  );
	
	  $form['enable'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('Periodic import'),
	    '#prefix' => '<div class="okhubimport-form-enable">',
	    '#suffix' => '</div>',
	    '#collapsible' => TRUE,
	    '#collapsed' => TRUE,
	  );
	
	  $form['enable']['okhubimport_check_enable_assets'] = array(
	    '#type' => 'checkbox',
	    '#title' => t('Enable periodic importing of OKHUB documents and/or organisations.'),
	    '#default_value' => variable_get('okhubimport_check_enable_assets', FALSE),
	  );
	  
	  $form['enable']['okhubimport_check_enable_categories'] = array(
	    '#type' => 'checkbox',
	    '#title' => t('Enable periodic importing of OKHUB categories (' . $list_categories .').'),
	    '#default_value' => variable_get('okhubimport_check_enable_categories', FALSE),
	  );
	
	  $form['enable']['assets'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('Periodic import settings for documents and/or organisations'),
	    '#prefix' => '<div class="okhubimport-form-enable-assets">',
	    '#suffix' => '</div>',
	    '#states' => array(
	      'visible' => array(
	        ':input[name="okhubimport_check_enable_assets"]' => array('checked' => TRUE),
	      ),
	    ),
	  );
	
	  $form['enable']['assets']['okhubimport_enable_assets'] = array(
	    '#title' => t('Type of content to import periodically'),
	    '#type' => 'checkboxes',
	    '#multiple' => TRUE,
	    '#options' => array(
	      OKHUB_IMPORT_IMPORTER_DOCUMENTS => t('Documents'),
	      OKHUB_IMPORT_IMPORTER_ORGANISATIONS => t('Organisations'),
	     ),
	    '#states' => array(
	      'visible' => array(
	        ':input[name="okhubimport_check_enable_assets"]' => array('checked' => TRUE),
	      ),
	    ),
	    '#default_value' => (array) variable_get('okhubimport_enable_assets'),
	    '#description' => t('Please indicate the content that you want to import automatically.<br>If the categories attached to the imported documents/organisations have not been imported and do not exist as taxonomy terms in Drupal they will be created with basic information.'),
	  );
	
	  $form['enable']['assets']['okhubimport_import_period_assets'] = array(
	    '#title' => t('Frequency to import documents/organisations'),
	    '#type' => 'select',
	    '#options' => array(
	      FEEDS_SCHEDULE_NEVER => t('Off'),
	      0 => t('As often as possible'),
	      900 => t('Every 15 min'),
	      1800 => t('Every 30 min'),
	      3600 => t('Every 1 hour'),
	      10800 => t('Every 3 hours'),
	      21600 => t('Every 6 hours'),
	      43200 => t('Every 12 hours'),
	      86400 => t('Every 1 day'),
	      259200 => t('Every 3 days'),
	      604800 => t('Every 1 week'),
	      2419200 => t('Every 4 weeks'),
	     ),
	    '#required' => FALSE,
	    '#default_value' => variable_get('okhubimport_import_period_assets', OKHUB_IMPORT_IMPORT_PERIOD_ASSETS),
	    '#states' => array(
	      'visible' => array(
	        ':input[name="okhubimport_check_enable_assets"]' => array('checked' => TRUE),
	      ),
	    ),
	    '#description' => t('Choose how often OKHUB documents and/or organisations should be imported (<a href="@cronurl">requires cron to be configured</a>).', array('@cronurl' => url('admin/config/system/cron'))),
	  );
	
	  $form['enable']['assets']['okhubimport_expire_period_assets'] = array(
	    '#title' => t('Default time to expire imported content'),
	    '#type' => 'select',
	    '#options' => array(
	      '-1' => t('Never'),
	      '3600' => t('After one hour'),
	      '10800' => t('After three hours'),
	      '21600' => t('After six hours'),
	      '43200' => t('After twelve hours'),
	      '86400' => t('After one day'),
	      '259200' => t('After three days'),
	      '604800' => t('After one week'),
	      '2592000' => t('After one month'),
	      '7776000' => t('After three months'),
	      '15552000' => t('After six months'),
	      '31536000' => t('After one year'),
	     ),
	    '#required' => FALSE,
	    '#default_value' => variable_get('okhubimport_expire_period_assets', OKHUB_IMPORT_EXPIRE_PERIOD_ASSETS),
	    '#description' => t('Select after how much time imported OKHUB content should expire and be deleted from the database.<br><small>This can be overriden in the importers processors settings, so different expiration times can be used for different sets of imported items.<br>To change these settings for current importers, please go to the <a href="@feedsadmin">Feeds importers administration page</a> and edit the importer that you would like to change.</small>', array('@feedsadmin' => url('admin/structure/feeds'))),
	  );
	
	  $form['enable']['categories'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('Categories periodic import settings'),
	    '#prefix' => '<div class="okhubimport-form-enable-categories">',
	    '#suffix' => '</div>',
	    '#states' => array(
	      'visible' => array(
	        ':input[name="okhubimport_check_enable_categories"]' => array('checked' => TRUE),
	      ),
	    ), 
	  );
	
	  $options_enable_categories = array(
	      OKHUB_IMPORT_IMPORTER_REGIONS => t('Regions'),
	      OKHUB_IMPORT_IMPORTER_THEMES => t('Themes'),
	      OKHUB_IMPORT_IMPORTER_COUNTRIES => t('Countries'),
	  );
	  if ($additional_fields) {
	      $options_enable_categories[OKHUB_IMPORT_IMPORTER_SUBJECTS] = t('Subjects');
	  }
	  $form['enable']['categories']['okhubimport_enable_categories'] = array(
	    '#title' => t('Categories to import periodically'),
	    '#type' => 'checkboxes',
	    '#multiple' => TRUE,
	    '#options' => $options_enable_categories,
	    '#states' => array(
	      'visible' => array(
	        ':input[name="okhubimport_check_enable_categories"]' => array('checked' => TRUE),
	      ),
	    ),    
	    '#default_value' => (array) variable_get('okhubimport_enable_categories'),
	    '#description' => t('Please indicate the categories that you want to import automatically.'),
	  );
	
	  $form['enable']['categories']['okhubimport_import_period_categories'] = array(
	    '#title' => t('Frequency to import categories'),
	    '#type' => 'select',
	    '#options' => array(
	      FEEDS_SCHEDULE_NEVER => t('Off'),
	      0 => t('As often as possible'),
	      900 => t('Every 15 min'),
	      1800 => t('Every 30 min'),
	      3600 => t('Every 1 hour'),
	      10800 => t('Every 3 hours'),
	      21600 => t('Every 6 hours'),
	      43200 => t('Every 12 hours'),
	      86400 => t('Every 1 day'),
	      259200 => t('Every 3 days'),
	      604800 => t('Every 1 week'),
	      2419200 => t('Every 4 weeks'),
	     ),
	    '#required' => FALSE,
	    '#default_value' => variable_get('okhubimport_import_period_categories', OKHUB_IMPORT_IMPORT_PERIOD_CATEGORIES),
	    '#states' => array(
	      'visible' => array(
	        ':input[name="okhubimport_check_enable_categories"]' => array('checked' => TRUE),
	      ),
	    ),
	    '#description' => t('Choose how often OKHUB categories (' . $list_categories . ') should be imported (<a href="@cronurl">requires cron to be configured</a>).', array('@cronurl' => url('admin/config/system/cron'))),
	  );
	
	  $form['enable'][] = array(
	    '#type' => 'submit',
	    '#value' => t('Save configuration'),
	    '#submit' => array('okhubimport_settings_form_submit'),
	  );
	
	  $form['import'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('Manual import'),
	    '#prefix' => '<div class="okhubimport-form-import">',
	    '#suffix' => '</div>',
	    '#collapsible' => TRUE,
	    '#collapsed' => TRUE,
	  );
	
	  $form['import']['okhubimport_check_import'] = array(
	    '#type' => 'checkbox',
	    '#title' => t('Import OKHUB content now.'),
	    '#default_value' => variable_get('okhubimport_check_import', FALSE),
	  );
	
	  $options_categories_import = array(
	      OKHUB_IMPORT_IMPORTER_DOCUMENTS => t('Documents'),
	      OKHUB_IMPORT_IMPORTER_ORGANISATIONS => t('Organisations'),
	      OKHUB_IMPORT_IMPORTER_REGIONS => t('Regions'),
	      OKHUB_IMPORT_IMPORTER_COUNTRIES => t('Countries'),
	      OKHUB_IMPORT_IMPORTER_THEMES => t('Themes'),
	  );
	  if ($additional_fields) {
	      $options_categories_import[OKHUB_IMPORT_IMPORTER_SUBJECTS] = t('Subjects');
	  }
	  $form['import']['okhubimport_import'] = array(
	    '#title' => t('Items to import'),
	    '#type' => 'checkboxes',
	    '#multiple' => TRUE,
	    '#options' => $options_categories_import,
	    '#states' => array(
	      'visible' => array(
	        ':input[name="okhubimport_check_import"]' => array('checked' => TRUE),
	      ),
	    ),    
	    '#description' => t('Please indicate the content that you want to import.<br><small>Please note that due to the large number of <b>themes</b> in the OKHUB collection, <u>importing themes can take some minutes</u></small>.'),
	  );
	
	  $form['import']['okhubimport_import_now'] = array(
	    '#type' => 'submit',
	    '#value' => t('Save configuration and import OKHUB content'),
	    '#states' => array(
	      'visible' => array(
	        ':input[name="okhubimport_check_import"]' => array('checked' => TRUE),
	      ),
	    ),
	    '#submit' => array('okhubimport_settings_form_submit','okhubimport_import_now'),
	  );
	
	  $form['delete'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('Delete OKHUB content'),
	    '#prefix' => '<div class="okhubimport-form-advanced">',
	    '#suffix' => '</div>',
	    '#collapsible' => TRUE,
	    '#collapsed' => TRUE,
	  );
	
	
	  $options_delete_types = array(
	      OKHUB_IMPORT_DOCUMENTS_TYPE => t('Documents'),
	      OKHUB_IMPORT_ORGANISATIONS_TYPE => t('Organisations'),
	      OKHUB_IMPORT_REGIONS_VOCABULARY => t('Regions'),
	      OKHUB_IMPORT_COUNTRIES_VOCABULARY => t('Countries'),
	      OKHUB_IMPORT_THEMES_VOCABULARY => t('Themes'),
	  );
	  if ($additional_fields) {
	    $options_delete_types[OKHUB_IMPORT_SUBJECTS_VOCABULARY] = t('Subjects');
	  }
	  $form['delete']['okhubimport_delete_types'] = array(
	    '#title' => t('Delete items imported from the OKHUB collection'),
	    '#type' => 'checkboxes',
	    '#multiple' => TRUE,
	    '#options' => $options_delete_types,
	    '#required' => FALSE,
	    '#states' => array(
	      'visible' => array(
	        ':input[name="show_advanced"]' => array('checked' => TRUE),
	      ),
	    ),
	    '#description' => t('Please indicate the content that you want to delete.'),
	  );
	
	  $form['delete']['okhubimport_delete'] = array(
	    '#type' => 'submit',
	    '#value' => t('Delete selected items'),
	    '#description' => t('Delete selected items from the OKHUB collection.'),
	    '#submit' => array('okhubimport_delete'),
	    '#attributes' => array('onclick' => 'if(!confirm("Are you sure that you want to delete these items?")){return false;}'),
	    '#states' => array(
	      'visible' => array(
	        ':input[name="show_advanced"]' => array('checked' => TRUE),
	      ),
	    ),
	  );
	
	  $form['rebuild'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('Rebuild OKHUB categories'),
	    '#description' => t('This will run a process to make the Drupal taxonomies match the OKHUB categories trees.<br>If the Drupal taxonomies corresponding to OKHUB categories have been manually changed, these changes will be undone.<br>This process is executed automatically after categories are imported.<br>'),
	    '#prefix' => '<div class="okhubimport-form-advanced-delete">',
	    '#suffix' => '</div>',
	    '#collapsible' => TRUE,
	    '#collapsed' => TRUE,
	  );
	
	  $form['rebuild']['okhubimport_rebuild_taxonomies'] = array(
	    '#title' => t('Rebuild OKHUB categories'),
	    '#type' => 'submit',
	    '#value' => t('Rebuild OKHUB taxonomies'),
	    '#description' => t('Rebuild the OKHUB categories trees.'),
	    '#submit' => array('okhubimport_rebuild_taxonomies'),
	    '#states' => array(
	      'visible' => array(
	        ':input[name="show_advanced"]' => array('checked' => TRUE),
	      ),
	    ),
	  );
	
	  $form['caching'] = array (
	    '#type' => 'fieldset',
	    '#title' => t('Clear Feeds cache'),
	    '#description' => t('If you deleted imported items manually, you might need to clear the cache in order to re-import them.<br>'),
	    '#prefix' => '<div class="okhubimport-form-advanced-delete">',
	    '#suffix' => '</div>',
	    '#collapsible' => TRUE,
	    '#collapsed' => TRUE,
	  );
	
	  $form['caching']['okhubimport_cache_clear'] = array(
	    '#title' => t('Clear Feeds cache'),
	    '#type' => 'submit',
	    '#value' => t('Clear Feeds cache'),
	    '#submit' => array('okhubimport_cache_clear'),
	    '#states' => array(
	      'visible' => array(
	        ':input[name="show_advanced"]' => array('checked' => TRUE),
	      ),
	    ),
	  );
  
  } else {
	$form['general']['info'] = array(
	    '#title' => t('general settings information'),
	    '#type' => 'markup',
		'#markup' => _okhubapi_global_settings_link(),
	  ); 
  }
  return system_settings_form($form);
}

/* --------------------------------- Submit handlers --------------------------- */

/**
 * Validates the form settings input.
 */
function okhubimport_settings_form_validate($form, &$form_state) {
  $api_key = variable_get('okhubapi_api_key', '');
  $reg = '/^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$/';
  if (!preg_match($reg, $api_key)) {
    form_set_error('okhubimport_import_now', t('Please enter a valid API key in the <a href="@okhubconfig">OKHUB API Module configuration page</a>.', array('@okhubconfig' => url('admin/config/services/okhubapi'))));
  }
  $num_items = $form_state['values']['okhubimport_number_assets'];
  if ($form_state['values']['okhubimport_check_enable_assets']) {
    if (isset($num_items) && !is_numeric($num_items)) {
      form_set_error('okhubimport_number_assets', t('Please enter a number.'));
    }
    if (isset($num_items) && ($num_items < 1)) {
      form_set_error('okhubimport_number_assets', t('Please enter a greater number.'));
    }
  }
  $import_assets = $form_state['values']['okhubimport_check_enable_assets'];
  $import_categories = $form_state['values']['okhubimport_check_enable_categories'];
  $assets_checked = FALSE;
  foreach ($form_state['values']['okhubimport_enable_assets'] as $import_asset) {
    $assets_checked = $assets_checked || $import_asset;
  }
  if (($import_assets) && ($form_state['values']['okhubimport_import_period_assets'] !== FEEDS_SCHEDULE_NEVER) && (!$assets_checked)) {
    form_set_error('okhubimport_enable_assets', t('Please indicate the type(s) of documents and/or organisations that you want to import periodically.'));
  }
  $categories_checked = FALSE;
  foreach ($form_state['values']['okhubimport_enable_categories'] as $import_category) {
    $categories_checked = $categories_checked || $import_category;
  }
  if (($import_categories) && ($form_state['values']['okhubimport_import_period_categories'] !== FEEDS_SCHEDULE_NEVER) && (!$categories_checked)) {
    form_set_error('okhubimport_enable_categories', t('Please indicate the type(s) of categories that you want to import periodically.'));
  }
}

/*
 * Implements hook_form_submit().
 */
function okhubimport_settings_form_submit($form, &$form_state) {
  system_settings_form($form, $form_state);
  $values = $form_state['values'];
  $import_assets = $values['okhubimport_check_enable_assets'];
  $import_categories = $values['okhubimport_check_enable_categories'];
  $assets_to_import = $values['okhubimport_enable_assets'];
  $categories_to_import = $values['okhubimport_enable_categories'];
  $import_period_assets = $values['okhubimport_import_period_assets'];
  $import_period_categories = $values['okhubimport_import_period_categories'];
  $expire_period_assets = $values['okhubimport_expire_period_assets'];
  $current_user_id = variable_get('okhubimport_new_user_id', 0);
  $new_user = check_plain($values['okhubimport_new_user']);

  if ($new_user) {
    $new_user_id = okhubimport_new_user($new_user);
    variable_set('okhubimport_new_user_id', $new_user_id);
  }
  foreach (okhubimport_get_all_importers() as $importer) {
	if (is_a($importer->fetcher, 'OkhubAssetsFetcher')) {
		if ($new_user_id) {
			$importer->processor->setAuthor($new_user_id);
		}
	}
	$importer_settings = array();
	if (($import_assets) && (array_key_exists($importer->id, $assets_to_import))) {
      if ($assets_to_import[$importer->id]) {
        $importer_settings['import_period'] = $import_period_assets;
        $importer->processor->setExpirePeriod($expire_period_assets);
      }
    }
    elseif (($import_categories) && (array_key_exists($importer->id, $categories_to_import))) {
      if ($categories_to_import[$importer->id]) {
        $importer_settings['import_period'] = $import_period_categories;
      }
    }
    else {
      $importer_settings['import_period'] = FEEDS_SCHEDULE_NEVER;
    }
    feeds_reschedule($importer->id);
    $importer->addConfig($importer_settings);
    $importer->schedule();
    $importer->save();
    $nodes_importer = okhubimport_get_nodes_importer($importer);
    foreach ($nodes_importer as $node_importer) {
      $feed_nid = $node_importer->nid;
      $source = feeds_source($importer->id, $feed_nid);
      $source->scheduleImport();
    }
  }
  feeds_cache_clear(FALSE);
}

/**
 * Invoke importers.
 */
function okhubimport_import_now($form, &$form_state) {
  system_settings_form_submit($form, $form_state);
  $values = $form_state['values'];
  $import_now = $values['okhubimport_check_import'];
  $importers = $values['okhubimport_import'];
  if ($import_now) {
    $importers_to_invoke = array();
    foreach ($importers as $importer_id => $delete) {
      if ($delete) {
        $importers_to_invoke[] = $importer_id;
      }
    }
    if ($importers_to_invoke) {
      foreach(okhubimport_get_importers_by_id($importers_to_invoke) as $importer) {
        foreach (okhubimport_get_nodes_importer($importer) as $feed) {
          $source = feeds_source($importer->id, $feed->nid);
          $source->startImport();
        }
      }
    }
  }
}

/**
 * Delete all imported items.
 */
function okhubimport_delete($form, &$form_state) {
  $values = $form_state['values'];
  $types = $values['okhubimport_delete_types'];
  $types_to_delete = array();
  foreach ($types as $type => $delete) {
    if ($delete) {
      $types_to_delete[] = $type;
    }
  }
  okhubimport_delete_items_type($types_to_delete);
  feeds_cache_clear();
  drupal_set_message(t('The imported items have been deleted.'));
}

/**
 * Check and rebuild all the imported taxonomies.
 */
function okhubimport_rebuild_taxonomies(&$form) {
  okhubimport_build_all_category_trees();
  drupal_set_message(t('The imported categories have been rebuilt.'));
}

/**
 * Clear the request cache.
 */
function okhubimport_cache_clear(&$form) {
  feeds_cache_clear();
  drupal_set_message(t('The Feeds cache has been cleared.'));
}




