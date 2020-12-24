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

// Shell aliases.
$options['shell-aliases']['syncdb'] = '--verbose --yes sql-sync @example.dev @self --create-db';
$options['shell-aliases']['syncfiles'] = '--verbose --yes core-rsync @example.dev:%files/ @self:%files/';
