#!/usr/bin/env bash

# Jenkins script to sync database and files from Production to Development.
cd /var/www/drupal-dev/docroot

# Sync database and files.
drush --verbose --yes sql-sync @example.prod @self --create-db --sanitize
drush --verbose --yes core-rsync @example.prod:%files @self:%files

# Disable email submission.
drush --verbose --yes pm-enable reroute_email
drush --verbose --yes variable-set reroute_email_enable 1
drush --verbose --yes variable-set reroute_email_address 'dummy@example.com'
drush --verbose --yes variable-set reroute_email_enable_message 1
