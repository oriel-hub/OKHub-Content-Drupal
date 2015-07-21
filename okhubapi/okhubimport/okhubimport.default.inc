<?php
// $Id;

/**
 * @file
 *   OKHUB Import Module default parameters.
 */

//define('FEEDS_NODE_BATCH_SIZE', 50);

// TODO Query the database to see the available number. We now just set a large number in order not to limit results by this parameter.
define('OKHUB_IMPORT_GET_ALL_ITEMS', 1000000);

define('OKHUB_IMPORT_NUM_ASSETS', 20);
define('OKHUB_IMPORT_AGE_NEW_ASSETS', 0);

define('OKHUB_IMPORT_IMPORT_DATA', 'all');
define('OKHUB_IMPORT_CREATE_USER', TRUE);
define('OKHUB_IMPORT_USER', 'OKHUB');
define('OKHUB_IMPORT_USER_EMAIL','api@okhub.ac.uk');

define('OKHUB_IMPORT_EXPIRE_PERIOD_ASSETS', FEEDS_SCHEDULE_NEVER);
define('OKHUB_IMPORT_EXPIRE_PERIOD_CATEGORIES', FEEDS_SCHEDULE_NEVER);
define('OKHUB_IMPORT_IMPORT_PERIOD_ASSETS', FEEDS_SCHEDULE_NEVER);
define('OKHUB_IMPORT_IMPORT_PERIOD_CATEGORIES', FEEDS_SCHEDULE_NEVER);

define('OKHUB_IMPORT_IMPORT_CATEGORIES', TRUE);
/*define('OKHUB_IMPORT_LEVELS_CATEGORIES', '1|2');*/

define('OKHUB_IMPORT_IMPORTER_DOCUMENTS', 'okhub_documents_importer');
define('OKHUB_IMPORT_IMPORTER_ORGANISATIONS', 'okhub_organisations_importer');
define('OKHUB_IMPORT_IMPORTER_REGIONS', 'okhub_regions_importer');
define('OKHUB_IMPORT_IMPORTER_THEMES', 'okhub_themes_importer');
define('OKHUB_IMPORT_IMPORTER_SUBJECTS', 'okhub_subjects_importer');
define('OKHUB_IMPORT_IMPORTER_COUNTRIES', 'okhub_countries_importer');

define('OKHUB_IMPORT_DOCUMENTS_TYPE', 'okhub_document');
define('OKHUB_IMPORT_ORGANISATIONS_TYPE', 'okhub_organisation');
define('OKHUB_IMPORT_REGIONS_VOCABULARY', 'okhub_regions');
define('OKHUB_IMPORT_THEMES_VOCABULARY', 'okhub_themes');
define('OKHUB_IMPORT_SUBJECTS_VOCABULARY', 'okhub_subjects');
define('OKHUB_IMPORT_COUNTRIES_VOCABULARY', 'okhub_countries');

define('OKHUB_IMPORT_DOCUMENTS_FEED_TYPE', 'okhub_documents_feed');
define('OKHUB_IMPORT_ORGANISATIONS_FEED_TYPE', 'okhub_organisations_feed');
define('OKHUB_IMPORT_REGIONS_FEED_TYPE', 'okhub_regions_feed');
define('OKHUB_IMPORT_THEMES_FEED_TYPE', 'okhub_themes_feed');
define('OKHUB_IMPORT_SUBJECTS_FEED_TYPE', 'okhub_subjects_feed');
define('OKHUB_IMPORT_COUNTRIES_FEED_TYPE', 'okhub_countries_feed');






