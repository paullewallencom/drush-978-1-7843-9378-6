<?php

/**
 * Custom callback to log messages.
 */
function mycustom_log($entry) {
  $message =  '[' . $entry['type'] . '] ' . $entry['message'];
  return drush_print($message, 0, STDOUT);
}

/**
 * Implements hook_drush_init().
 *
 * Overrides Drush's callback to write log messages.
 */
function customlog_drush_init() {
  drush_set_context('DRUSH_LOG_CALLBACK', 'mycustom_log');
}
