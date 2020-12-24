<?php

/**
 * @file
 * Drush configuration for Sample project.
 */

/**
 * List of tables whose *data* is skipped by the 'sql-dump' and 'sql-sync'
 * commands when the "--structure-tables-key=common" option is provided.
 */
$options['structure-tables']['common'] = array('cache', 'cache_*', 'history', 'search_*', 'sessions', 'watchdog');

/**
 * List of tables to be omitted entirely from SQL dumps made by the 'sql-dump'
 * and 'sql-sync' commands when the "--skip-tables-key=common" option is
 * provided on the command line.  This is useful if your database contains
 * non-Drupal tables used by some other application or during a migration for
 * example.  You may add new tables to the existing array or add a new element.
 */
$options['skip-tables']['common'] = array('migrate_*');

// Shell aliases.
$options['shell-aliases']['syncdb'] = '!drush --verbose --yes sql-sync @example.dev @self --create-db && drush devify';
$options['shell-aliases']['syncfiles'] = '--verbose --yes rsync @example.dev:%files/ @self:%files/';

/**
 * Command options for devify command.
 * @see build.drush.inc
 */
$command_specific['devify'] = array(
  'enable-modules' => array(
    'dblog',
    'devel',
    'field_ui',
    'reroute_email',
    'stage_file_proxy',
    'views_ui',
  ),
  'disable-modules' => array(
    'update',
    'purge',
  ),
  'reset-variables' => array(
    // File management settings.
    'file_temporary_path' => '/tmp/',
    // Cache settings.
    'cache' => FALSE,
    'block_cache' => FALSE,
    'preprocess_css' => FALSE,
    'preprocess_js' => FALSE,
    // Stage file proxy settings.
    'stage_file_proxy_origin' => 'http://dev.example.com',
    'stage_file_proxy_origin_dir' => 'sites/default/files',
    'stage_file_proxy_hotlink' => TRUE,
  ),
);
