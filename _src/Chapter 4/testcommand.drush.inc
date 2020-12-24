<?php 
/**
 * Implements hook_drush_command().
 */
function testcommand_drush_command() {
  $items = array();

  $items['testcommand'] = array(
    'description' => 'Tests Drush command arguments',
    'arguments' => array(
      'argument_1' => 'This is a sample argument.',
      'argument_2' => 'This is a sample argument.',
      'argument_3' => 'This is a sample argument.',
    ),
    'required-arguments' => 2,
  );

  return $items;
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_testcommand($argument_1, $argument_2, $argument_3 = NULL) {
  var_dump(array($argument_1, $argument_2, $argument_3));
}
