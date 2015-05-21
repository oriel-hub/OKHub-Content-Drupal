<?php
// $Id;

/**
 * @file
 *   OKHUB API Module default parameters.
 *   See okhubwrapper/okhubwrapper.default.inc for additional settings.
 *
 */

// Environment in which we are using the API wrapper. Possible values: 'generic', 'wordpress', 'drupal'. Default is 'generic'.
if (!defined('OKHUB_API_LIBRARY_PATH')) define('OKHUB_API_LIBRARY_PATH', dirname(__FILE__) . '/okhubwrapper/');
if (!defined('OKHUB_API_ENVIRONMENT')) define('OKHUB_API_ENVIRONMENT', 'drupal');







