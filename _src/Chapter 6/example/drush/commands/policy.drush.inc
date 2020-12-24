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

/**
 * Implements hook_drush_sql_sync_sanitize().
 *
 * Custom sql-sync sanitization to alter user's full name.
 *
 * @see sql_drush_sql_sync_sanitize().
 */
function policy_drush_sql_sync_sanitize($source) {
  drush_sql_register_post_sync_op('policy-sanitize-full-name', dt('Reset the full name of all users.'),
    "UPDATE field_data_field_full_name
     SET field_full_name_value = CONCAT('user+', entity_id);");
  drush_sql_register_post_sync_op('policy-sanitize-full-name-revisions', dt('Reset the full name revisions of all users.'),
    "UPDATE field_revision_field_full_name
     SET field_full_name_value = CONCAT('user+', entity_id);");
}
