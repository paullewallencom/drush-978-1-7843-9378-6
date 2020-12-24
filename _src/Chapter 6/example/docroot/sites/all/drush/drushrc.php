<?php

/**
 * @file
 * Drush configuration for Example project.
 *
 * Loads configuration files located out of the document root.
 */

// Safety check. Only run in the command line.
if (php_sapi_name() != 'cli') {
  return;
}

// Load Drush configuration, commands and site alias files from docroot/../drush.
$drupal_dir = drush_get_context('DRUSH_SELECTED_DRUPAL_ROOT');
if ($drupal_dir) {
  include_once $drupal_dir . '/../drush/drushrc.php';
  $options['include'][] = $drupal_dir . '/../drush/commands';
  $options['alias-path'][] = $drupal_dir . '/../drush/aliases';
}
