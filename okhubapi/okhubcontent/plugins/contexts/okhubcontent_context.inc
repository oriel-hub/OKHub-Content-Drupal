<?php
/**
 * @file 
 */

$plugin = array(
  'title' => t("OKHUB Document"),
  'description' => t("A document from the OKHUB API"),
  'context' => "okhubcontent_context_create",
  'edit form' => "okhubcontent_context_settings_form",
  'keyword' => "okhubcontent_context",
  'context name' => "okhubcontent_context",
  "convert list" => "okhubcontent_context_convert_list",
  'convert' => "okhubcontent_context_convert",
  'placeholder form' => array(
    '#type' => "textfield",
    '#description' => t("Enter the ID of the OKHUB API object")
  )
);

function okhubcontent_context_create($empty, $data = NULL, $conf = FALSE){
  $context = new ctools_context("okhubcontent");
  $context->plugin = "okhubcontent";
  if ($empty){
    return $context;
  }
  if ($conf){
    $okhubWrapper = new OkhubApiWrapper();
    $dataset = variable_get('okhubapi_default_dataset', OKHUB_API_DEFAULT_DATASET);
    $apiKey = variable_get('okhubapi_api_key', '');
    $results = $okhubWrapper->get("documents", $dataset, $apiKey, "full", $data['okhubcontent']);
    if (!empty($results) && !empty($results->result)){
      $data = $results->result[0];
    }
    else {
      $data = false;
    }
  }
  if (!empty($data)){
    $context->data = $data;
    $context->argument = check_plain($data->object_id);
    $context->title = check_plain($data->title);
    return $context;
  }
  return false;
}

function okhubcontent_context_settings_form($form, &$form_state){
  $conf = $form_state['conf'];
  $form['okhubcontent'] = array(
    '#title' => t("OKHUB Item ID"),
    '#description' => t("Enter a OKHUB Item ID"),
    '#default_value' => $conf['okhubcontent'],
    '#type' => "textfield"
  );
  return $form;
}

function okhubcontent_context_settings_form_submit($form, &$form_state){
  $form_state['conf']['okhubcontent'] = $form_state['values']['okhubcontent'];
}

/**
 * Provides a list of text conversions to be used in the pane.
 *
 * @return array
 */
function okhubcontent_context_convert_list(){
  return array(
    "title" => t("Title"),
    "description" => t("Description"),
    'object_id' => t("Item ID")
  );
}

/**
 * Resolves a keyword into some data.
 *
 * @param $context
 * @param $type
 *
 * @return mixed
 */
function okhubcontent_context_convert($context, $type){
  return $context->data->{$type};
}