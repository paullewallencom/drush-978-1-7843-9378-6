<?php

/**
 * @file
 * Policy rules for Example project.
 */

/**
 * Implements drush_hook_COMMAND_validate().
 *
 * Prevent overriding Production's database.
 */
function drush_policy_sql_sync_validate($source = NULL, $destination = NULL) {
  if ($destination == '@example.prod') {
    return drush_set_error('POLICY_DENY_SQL', dt('Oops, you almost copied your database onto Production. Please use drush syncdb instead.'));
  }
}

/**
 * Implements drush_hook_COMMAND_validate().
 *
 * Prevent modifying Production's files directory.
 */
function drush_policy_core_rsync_validate($source = NULL, $destination = NULL) {
  if (strpos($destination, '@example.prod') === 0) {
    return drush_set_error('POLICY_DENY_RSYNC', dt('Oops, you almost copied files onto Production. Please use drush syncfiles instead.'));
  }
}
