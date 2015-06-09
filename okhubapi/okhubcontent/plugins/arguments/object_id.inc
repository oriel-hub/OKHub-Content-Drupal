<?php
/**
 * @file 
 */

$plugin = array(
  'title' => t("OKHUB Document"),
  'keyword' => "okhubcontent_context",
  'description' => t("Creates an OKHUB Document context from a string argument"),
  'context' => "okhubcontent_argument_context",
  'placeholder form' => array(
    '#type' => "textfield",
    '#description' => t("Enter the OKHUB API object ID")
  )
);

function okhubcontent_argument_context($arg = null, $conf = NULL, $empty = FALSE){
  if ($empty){
    return ctools_context_create_empty("okhubcontent_context");
  }
  $okhubWrapper = new OkhubApiWrapper();
  $dataset = variable_get('okhubapi_default_dataset', OKHUB_API_DEFAULT_DATASET);
  $apiKey = variable_get('okhubapi_api_key', '');
  $priorities = _okhubapi_get_priorities_arr();
  $item = $okhubWrapper->get("documents", $dataset, $apiKey, "full", $arg, $priorities);
  if (!empty($item) && !empty($item->results)){
    $document = $item->results[0];
  }
  else {
    return ctools_context_create_empty("okhubcontent_context");
  }

  return ctools_context_create("okhubcontent_context", $document);
}