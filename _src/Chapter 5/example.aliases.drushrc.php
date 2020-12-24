<?php
/**
 * @file
 *
 * Site alias definitions for Example project.
 */

// Development environment.
$aliases['dev'] = array(
  'root' => '/var/www/drupal-dev',
  'uri' => 'http://dev.example.com/docroot',
  'remote-user' => 'exampledev',
  'remote-host' => 'dev.example.com',
  'command-specific' => array(
    'sql-dump' => array(
      'structure-tables-key' => 'common',
    ),
  ),
);

// Production environment.
$aliases['prod'] = array(
  'root' => '/var/www/exampleprod/docroot',
  'uri' => 'http://www.example.com',
  'remote-host' => 'www.example.com',
  'remote-user' => 'exampleprod',
);
