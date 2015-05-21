<?php

/* -------------------- Implementation of hooks used with Feeds ------------------- */

/**
 * Tasks to be done after items are imported, such as rebuilding the taxonomies or
 * creating new vocabulary terms for imported assets' categories.
 */
function okhubimport_feeds_after_import($source) {
  $processor = $source->importer->processor;
  $parser = $source->importer->parser;
  if ($parser instanceOf OkhubCategoriesParser) {
    if ($vocabulary = $processor->vocabulary()) {
      okhubimport_build_category_tree($vocabulary->vid);
      drupal_set_message(t('Rebuilt category hierarchy.'));
    }
  }
  elseif (($parser instanceOf OkhubDocumentsParser) || ($parser instanceOf OkhubOrganisationsParser) || ($parser instanceOf OkhubCountriesParser)) {
    if ($items = $processor->parsed_items) {
      okhubimport_imported_assets_categories($items);
    }
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function okhubimport_ctools_plugin_api() {
  cache_clear_all('plugins:feeds:plugins', 'cache');
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}

/**
 * Implements Feeds' hook_feeds_plugins().
 * Declares available Fetcher, Parser and Processor.
 */
function okhubimport_feeds_plugins() {
  cache_clear_all('plugins:feeds:plugins', 'cache');
  module_load_include('inc', 'okhubimport', 'feeds');
  $info = array();
  $info['OkhubAssetsFetcher'] = array(
    'name' => 'OKHUB Assets Fetcher',
    'description' => 'Fetch OKHUB assets.',
    'help' => 'Fetch OKHUB assets.',
    'handler' => array(
      'parent' => 'FeedsFetcher',
      'class' => 'OkhubAssetsFetcher',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
  $info['OkhubCategoriesFetcher'] = array(
    'name' => 'OKHUB Categories Fetcher',
    'description' => 'Fetch OKHUB categories.',
    'help' => 'Fetch OKHUB categories.',
    'handler' => array(
      'parent' => 'FeedsFetcher',
      'class' => 'OkhubCategoriesFetcher',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
  $info['OkhubAssetsParser'] = array(
    'name' => 'OKHUB Assets Parser',
    'description' => 'Parse OKHUB assets.',
    'help' => 'Parse OKHUB assets.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubAssetsParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
    $info['OkhubDocumentsParser'] = array(
    'name' => 'OKHUB Documents Parser',
    'description' => 'Parse OKHUB documents.',
    'help' => 'Parse OKHUB documents.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubDocumentsParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
    $info['OkhubOrganisationsParser'] = array(
    'name' => 'OKHUB Organisations Parser',
    'description' => 'Parse OKHUB organisations.',
    'help' => 'Parse OKHUB organisations.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubOrganisationsParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
  $info['OkhubCategoriesParser'] = array(
    'name' => 'OKHUB Categories Parser',
    'description' => 'Parse OKHUB regions, themes and subjects.',
    'help' => 'Parse OKHUB regions, themes and subjects.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubCategoriesParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
  $info['OkhubCountriesParser'] = array(
    'name' => 'OKHUB Countries Parser',
    'description' => 'Parse OKHUB countries.',
    'help' => 'Parse OKHUB countries.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubCountriesParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
  $info['OkhubAssetsProcessor'] = array(
    'name' => 'OKHUB Assets Processor',
    'description' => 'Process OKHUB assets.',
    'help' => 'Process OKHUB assets.',
    'handler' => array(
      'parent' => 'FeedsNodeProcessor',
      'class' => 'OkhubAssetsProcessor',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
  $info['OkhubCategoriesProcessor'] = array(
    'name' => 'OKHUB Categories Processor',
    'description' => 'Process OKHUB categories.',
    'help' => 'Process OKHUB categories.',
    'handler' => array(
      'parent' => 'FeedsTermProcessor',
      'class' => 'OkhubCategoriesProcessor',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
  $info['OkhubCountriesProcessor'] = array(
    'name' => 'OKHUB Countries Processor',
    'description' => 'Process OKHUB countries.',
    'help' => 'Process OKHUB countries.',
    'handler' => array(
      'parent' => 'FeedsTermProcessor',
      'class' => 'OkhubCountriesProcessor',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
    ),
  );
  return $info;
}


