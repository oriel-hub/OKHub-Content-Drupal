<?php
/**
 * @file
 * okhubimport.content_types.inc
 */

/**
 * Creates content-type definitions for OKhub assets (documents, organisations) and importers.
 */
function okhubimport_content_types() {
  $types[OKHUB_IMPORT_DOCUMENTS_TYPE] = array(
      'type' => OKHUB_IMPORT_DOCUMENTS_TYPE,
      'name' => 'OKhub Document',
      'base' => 'node_content',
      'module' => 'okhubimport',
      'description' => 'Documents imported via the OKhub API.',
      'help' => '',
      'has_title' => '1',
      'title_label' => 'Title',
      'custom' => '1',
      'modified' => '1',
      'locked' => '1',
      'disabled' => FALSE,
      'orig_type' => 'OKHUB_IMPORT_DOCUMENTS_TYPE',
      'disabled_changed' => FALSE,
      'bc_entity_type' => 'node',
    );
  $types[OKHUB_IMPORT_ORGANISATIONS_TYPE] = array(
      'type' => OKHUB_IMPORT_ORGANISATIONS_TYPE,
      'name' => 'OKhub Organisation',
      'base' => 'node_content',
      'module' => 'okhubimport',
      'description' => 'Organisations imported via the OKhub API.',
      'help' => '',
      'has_title' => '1',
      'title_label' => 'Title',
      'custom' => '1',
      'modified' => '1',
      'locked' => '1',
      'disabled' => FALSE,
      'orig_type' => OKHUB_IMPORT_ORGANISATIONS_TYPE,
      'disabled_changed' => FALSE,
      'bc_entity_type' => 'node',
    );
    $types[OKHUB_IMPORT_DOCUMENTS_FEED_TYPE] = array(
      'type' => OKHUB_IMPORT_DOCUMENTS_FEED_TYPE,    
      'name' => 'OKhub Documents Feed',
      'base' => 'node_content',
      'description' => 'Feeds for documents imported via the OKHUB API.',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
      'custom' => 1,
      'modified' => 1,
      'locked' => '1',
      'disabled' => FALSE,
      'module' => 'okhubimport',
      'orig_type' => OKHUB_IMPORT_DOCUMENTS_FEED_TYPE,
      'disabled_changed' => FALSE,
      'bc_entity_type' => 'node',
    );
    $types[OKHUB_IMPORT_ORGANISATIONS_FEED_TYPE] = array(
      'type' => OKHUB_IMPORT_ORGANISATIONS_FEED_TYPE,        
      'name' => 'OKhub Organisations Feed',
      'base' => 'node_content',
      'description' => 'Feeds for organisations imported via the OKhub API.',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
      'custom' => 1,
      'modified' => 1,
      'locked' => '1',
      'disabled' => FALSE,
      'module' => 'okhubimport',
      'orig_type' => OKHUB_IMPORT_ORGANISATIONS_FEED_TYPE,
      'disabled_changed' => FALSE,
      'bc_entity_type' => 'node',
    );
    $types[OKHUB_IMPORT_THEMES_FEED_TYPE] = array(   
      'type' => OKHUB_IMPORT_THEMES_FEED_TYPE,
      'name' => 'OKhub Themes Feed',
      'base' => 'node_content',
      'module' => 'node',
      'description' => 'Feeds for themes imported via the OKhub API.',
      'help' => '',
      'has_title' => '1',
      'title_label' => 'Title',
      'custom' => '1',
      'modified' => '1',
      'locked' => '1',
      'disabled' => FALSE,
      'orig_type' => OKHUB_IMPORT_THEMES_FEED_TYPE,
      'disabled_changed' => FALSE,
      'bc_entity_type' => 'node',
    );
    $types[OKHUB_IMPORT_SUBJECTS_FEED_TYPE] = array(   
      'type' => OKHUB_IMPORT_SUBJECTS_FEED_TYPE,
      'name' => 'OKhub Subjects Feed',
      'base' => 'node_content',
      'module' => 'node',
      'description' => 'Feeds for subjects imported via the OKHUB API.',
      'help' => '',
      'has_title' => '1',
      'title_label' => 'Title',
      'custom' => '1',
      'modified' => '1',
      'locked' => '1',
      'disabled' => FALSE,
      'orig_type' => OKHUB_IMPORT_SUBJECTS_FEED_TYPE,
      'disabled_changed' => FALSE,
      'bc_entity_type' => 'node',
    );
    $types[OKHUB_IMPORT_REGIONS_FEED_TYPE] = array(   
      'type' => OKHUB_IMPORT_REGIONS_FEED_TYPE,
      'name' => 'OKHUB Regions Feed',
      'base' => 'node_content',
      'module' => 'node',
      'description' => 'Feeds for regions imported via the OKhub API.',
      'help' => '',
      'has_title' => '1',
      'title_label' => 'Title',
      'custom' => '1',
      'modified' => '1',
      'locked' => '1',
      'disabled' => FALSE,
      'orig_type' => OKHUB_IMPORT_REGIONS_FEED_TYPE,
      'disabled_changed' => FALSE,
      'bc_entity_type' => 'node',
    );
    $types[OKHUB_IMPORT_COUNTRIES_FEED_TYPE] = array(   
      'type' => OKHUB_IMPORT_COUNTRIES_FEED_TYPE,
      'name' => 'OKhub Countries Feed',
      'base' => 'node_content',
      'module' => 'node',
      'description' => 'Feeds for countries imported via the OKhub API.',
      'help' => '',
      'has_title' => '1',
      'title_label' => 'Title',
      'custom' => '1',
      'modified' => '1',
      'locked' => '1',
      'disabled' => FALSE,
      'orig_type' => OKHUB_IMPORT_COUNTRIES_FEED_TYPE,
      'disabled_changed' => FALSE,
      'bc_entity_type' => 'node',
    );

  return $types;
}








