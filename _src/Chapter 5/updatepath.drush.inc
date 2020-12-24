<?php
/**
 * @file
 * Runs a set of steps to update a database to be in line with code.
 */

/**
 * Implements hook_drush_command().
 */
function updatepath_drush_command() {
  $items = array();
  $items['updatepath'] = array(
    'description' => 'Runs the update path in the bootstrapped site performing tasks such as database updates, reverting features, etc.',
    'drush dependencies' => array('registry_rebuild', 'features'),
    'examples' => array(
      'drush updatepath' => 'Runs the updatepath in the current Drupal project.',
      'drush @example.dev updatepath' => 'Runs the updatepath in the Drupal project referenced by @example.dev.',
    ),
  );
  return $items;
}

/**
 * Implements drush_hook_pre_command().
 */
function drush_updatepath_pre_updatepath() {
  drush_log('Enabling maintenance mode and killing active sessions.', 'status');
  $return = drush_invoke_process('@self', 'variable-set', array('maintenance_mode', 1), array(
    'yes' => TRUE,
    'always-set' => TRUE,
  ));
  if ($return['error_status']) {
    return drush_set_error('UPDATEPATH_PRE_MAINTENANCE', 'Could not enable maintenance mode.');
  }
  $return = drush_invoke_process('@self', 'sql-query', array('truncate table sessions'));
  if ($return['error_status']) {
    return drush_set_error('UPDATEPATH_PRE_SESSIONS', 'Could not truncate user sessions.');
  }
}

/**
 * Implements drush_hook_command().
 */
function drush_updatepath() {
  // Registry rebuild.
  $return = drush_invoke_process('@self', 'registry-rebuild', array(), array('no-cache-clear' => TRUE));
  if ($return['error_status']) {
    return drush_set_error('UPDATEPATH_RR', 'registry-rebuild failed.');
  }

  // Database updates.
  $return = drush_invoke_process('@self', 'updatedb', array(), array('yes' => true));
  if ($return['error_status']) {
    return drush_set_error('UPDATEPATH_UPDB', 'updatedb failed.');
  }

  // Clear Drush cache (sometimes needed before reverting Features components).
  $return = drush_invoke_process('@self', 'cache-clear', array('type' => 'drush'));
  if ($return['error_status']) {
    return drush_set_error('UPDATEPATH_CC_DRUSH', 'cache-clear failed.');
  }

  // Revert all Features components.
  $return = drush_invoke_process('@self', 'features-revert-all', array(), array(
    'yes' => TRUE,
  ));
  if ($return['error_status']) {
    return drush_set_error('UPDATEPATH_FRA', 'features-revert-all failed.');
  }

  // Clear all caches.
  $return = drush_invoke_process('@self', 'cache-clear', array('type' => 'all'));
  if ($return['error_status']) {
    return drush_set_error('UPDATEPATH_CC_ALL', 'cache-clear failed.');
  }
}

/**
 * Implements drush_hook_post_command().
 */
function drush_updatepath_post_updatepath() {
  drush_log('Disabling maintenance mode.', 'success');
  $return = drush_invoke_process('@self', 'variable-delete', array('maintenance_mode'), array(
   'yes' => TRUE,
   'exact' => TRUE,
  ));
  if ($return['error_status']) {
    return drush_set_error('UPDATEPATH_POST_MAINTENANCE', 'Could not disable maintenance mode.');
  }
}

/**
 * Implements drush_hook_command_rollback().
 */
function drush_updatepath_rollback() {
  drush_log('Oh no! Something went wrong. Review the above log and disable maintenance mode when done.', 'error');
  drush_set_context('UPDATEPATH_ROLLBACK', TRUE);
}

/**
 * Implements drush_hook_pre_command_rollback().
 */
function drush_updatepath_pre_updatepath_rollback() {
  if (!drush_get_context('UPDATEPATH_ROLLBACK')) {
    drush_log('Oh no! Something went wrong prior to start the update path. Check the status of the maintenance mode and the sessions table.', 'error');
  }
}

