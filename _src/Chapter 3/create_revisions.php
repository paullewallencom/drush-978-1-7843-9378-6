<?php
/**
 * @file
 * Script to create a bunch of nodes with revisions.
 *
 * Usage: drush php-script create_revisions.php
 */

$nodes_to_create = 10;
while ($nodes_to_create > 0) {
  // Minimum default values. We enable revisions with 'revision' => 1.
  $values = array(
    'type' => 'article',
    'uid' => 1,
    'status' => 1,
    'revision' => 1,
  );
  // Create the node entity and then use a wrapper to work with it.
  $entity = entity_create('node', $values);
  $node_wrapper = entity_metadata_wrapper('node', $entity);

  // Set a random title and save the node.
  $node_wrapper->title->set('Node title ' . rand(1, 100));
  $node_wrapper->save();

  // Create revisions for this node by simply re-saving the node a few times.
  $revisions = rand(20, 50);
  while ($revisions > 0) {
    $node_wrapper->save();
    $revisions--;
  }
  $nodes_to_create--;
}
