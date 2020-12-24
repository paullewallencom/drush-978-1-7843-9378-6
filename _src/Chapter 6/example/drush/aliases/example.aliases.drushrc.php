<?php
/**
 * @file
 *
 * Site alias definitions for Example project.
 */

// Development environment.
$aliases['dev'] = array(
  'root' => '/var/www/exampledev/docroot',
  'uri' => 'http://dev.example.com',
  'remote-host' => 'dev.example.com',
  'remote-user' => 'exampledev',
  'command-specific' => array (
    'sql-dump' => array (
      'structure-tables-key' => 'common',
      'skip-tables-key' => 'common',
    ),
  ),
);

// Production environment.
$aliases['prod'] = array(
  'root' => '/var/www/exampleprod/docroot',
  'uri' => 'http://www.example.com',
  'remote-host' => 'prod.example.com',
  'remote-user' => 'exampleprod',
  'command-specific' => array (
    'sql-dump' => array (
      'structure-tables-key' => 'common',
    ),
  ),
);
