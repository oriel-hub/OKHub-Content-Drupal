<?php

class okhubviews_handler_filter_datasource extends views_handler_filter {

  function option_definition() {
    $options = parent::option_definition();
    $sources_options = _okhubapi_get_sources_options();
    $options['filter_datasource'] = $sources_options;
    return $options;
  }

  function options_form(&$form, &$form_state) {   
    parent::options_form($form, $form_state);
    $sources_options = _okhubapi_get_sources_options();
    $form['filter_datasource'] = array(
      '#type' => 'select',
      '#title'  => t('Data Source'),
      '#options'  => $sources_options,
      '#default_value'  => $this->options['filter_datasource'],
      '#multiple' => TRUE,
    );
  }
  
  function admin_summary() {
    $output = '';
    foreach($this->options['filter_datasource'] as $datasource){
    	if($output){
    		$output .= ', ';
    	}
    	$output .= $datasource;
    }
    return $output;
  }

  function can_expose() {
    return FALSE;
  }

  function query() {
  	$selected_datasources = $this->options['filter_datasource'];
  	$datasources_param = _okhubapi_array_to_url_param($selected_datasources);
    $this->view->query->add_datasource($datasources_param);
  }
}
