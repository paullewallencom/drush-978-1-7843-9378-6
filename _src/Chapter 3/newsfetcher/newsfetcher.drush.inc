<?php

/**
 * @file
 * Drush command to fetch news from BBC's RSS feed.
 */

/**
 * Implements hook_drush_command().
 *
 * Defines the command to fetch news.
 */
function newsfetcher_drush_command() {
  $items = array();

  $items['news-fetch'] = array(
    'description' => "Fetches latest news from BBC's RSS feed.",
  );

  return $items;
}

/**
 * Implements drush_hook_COMMAND().
 *
 * Callback for news-fetch Drush command.
 */
function drush_newsfetcher_news_fetch() {
  // Define the id (machine name) of the importer you want to use.
  $importer_id = 'bbc_world_news';
  $source = feeds_source($importer_id);

  // Override to work with Drush.
  $config = array(
    'process_in_background' => TRUE,
  );
  $source->importer->addConfig($config);

  // Set the import URL.
  $fetcher_config = $source->getConfigFor($source->importer->fetcher);
  $fetcher_config['source'] = 'http://feeds.bbci.co.uk/news/world/rss.xml';
  $source->setConfigFor($source->importer->fetcher, $fetcher_config);
  $source->save();

  // Execute the import.
  $source->startImport();
}
