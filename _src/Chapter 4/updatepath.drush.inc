<?php
/**
 * @file
 * Drush implementation of the update path.
 */

/**
 * Implements hook_drush_command().
 */
function updatepath_drush_command() {
  $items = array();
  $items['updatepath'] = array(
    'description' => 'Runs the update path in the current site performing tasks such as database update, reverting features, etc.',
  );
  return $items;
}

/**
 * Implements drush_hook_pre_command().
 */
function drush_updatepath_pre_updatepath() {
  drush_log('Enabling maintenance mode and killing active sessions.', 'status');
  variable_set('maintenance_mode', 1);
  db_query('truncate table {sessions}');
}

/**
 * Implements drush_hook_command().
 */
function drush_updatepath() {
  drush_invoke_process('@self', 'registry-rebuild', array(), array(
    'no-cache-clear' => TRUE,
  ));
  drush_invoke_process('@self', 'updatedb', array(), array('yes' => true));
  drush_invoke_process('@self', 'cc', array('type' => 'drush'));
  drush_invoke_process('@self', 'features-revert-all', array(), array(
    'yes' => true,
  ));
  drush_invoke_process('@self', 'cc', array('type' => 'all'));
}

/**
 * Implements drush_hook_post_command().
 */
function drush_updatepath_post_updatepath() {
  drush_log('Disabling maintenance mode.', 'status');
  variable_del('maintenance_mode');
}

/**
 * Implements drush_hook_command_rollback().
 */
function drush_updatepath_rollback() {
  drush_log('Oh no! Something went wrong. Review the above log and disable maintenance mode when done.', 'error');
}

