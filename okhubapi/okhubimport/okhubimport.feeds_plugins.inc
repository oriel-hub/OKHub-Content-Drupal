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
			/* Joe McP -- commented out line below and moved to hook_feeds_after_save as when in batch process
			 * that is called after saving every item, but hook_feeds_after_import
			 * is only called on last batch run (so wasn't saving themes etc...)
			 */
			//okhubimport_imported_assets_categories($items);
		}
	}
}

function okhubimport_feeds_after_save(FeedsSource $source, $entity, $item, $entity_id){
	if(isset($entity->type)){
		if (($entity->type == 'ids_document') || ($entity->type == 'ids_organisation') || ($entity->type == 'ids_countries')) {
			$items = array();
			$items[] = $item;
			idsimport_imported_assets_categories($items);
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
    'name' => 'OKhub Assets Fetcher',
    'description' => 'Fetch OKhub assets.',
    'help' => 'Fetch OKhub assets.',
    'handler' => array(
      'parent' => 'FeedsFetcher',
      'class' => 'OkhubAssetsFetcher',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	$info['OkhubCategoriesFetcher'] = array(
    'name' => 'OKhub Categories Fetcher',
    'description' => 'Fetch OKhub categories.',
    'help' => 'Fetch OKhub categories.',
    'handler' => array(
      'parent' => 'FeedsFetcher',
      'class' => 'OkhubCategoriesFetcher',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	$info['OkhubAssetsParser'] = array(
    'name' => 'OKhub Assets Parser',
    'description' => 'Parse OKhub assets.',
    'help' => 'Parse OKhub assets.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubAssetsParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	$info['OkhubDocumentsParser'] = array(
    'name' => 'OKhub Documents Parser',
    'description' => 'Parse OKhub documents.',
    'help' => 'Parse OKhub documents.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubDocumentsParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	$info['OkhubOrganisationsParser'] = array(
    'name' => 'OKhub Organisations Parser',
    'description' => 'Parse OKhub organisations.',
    'help' => 'Parse OKhub organisations.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubOrganisationsParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	$info['OkhubCategoriesParser'] = array(
    'name' => 'OKhub Categories Parser',
    'description' => 'Parse OKhub regions, themes and subjects.',
    'help' => 'Parse OKhub regions, themes and subjects.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubCategoriesParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	$info['OkhubCountriesParser'] = array(
    'name' => 'OKhub Countries Parser',
    'description' => 'Parse OKhub countries.',
    'help' => 'Parse OKhub countries.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'OkhubCountriesParser',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	$info['OkhubAssetsProcessor'] = array(
    'name' => 'OKhub Assets Processor',
    'description' => 'Process OKhub assets.',
    'help' => 'Process OKhub assets.',
    'handler' => array(
      'parent' => 'FeedsNodeProcessor',
      'class' => 'OkhubAssetsProcessor',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	$info['OkhubCategoriesProcessor'] = array(
    'name' => 'OKhub Categories Processor',
    'description' => 'Process OKhub categories.',
    'help' => 'Process OKhub categories.',
    'handler' => array(
      'parent' => 'FeedsTermProcessor',
      'class' => 'OkhubCategoriesProcessor',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	$info['OkhubCountriesProcessor'] = array(
    'name' => 'OKhub Countries Processor',
    'description' => 'Process OKhub countries.',
    'help' => 'Process OKhub countries.',
    'handler' => array(
      'parent' => 'FeedsTermProcessor',
      'class' => 'OkhubCountriesProcessor',
      'file' => 'okhubimport.feeds.inc',
      'path' => drupal_get_path('module', 'okhubimport'),
	),
	);
	return $info;
}


