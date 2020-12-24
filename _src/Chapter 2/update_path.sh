#!/bin/sh
#
# Run the update path in the current project.
#
# Usage:
# Change directory into a Drupal project and run:
#   sh /path-to-this-script/update_path.sh
#
# You may need to change permissions on this script with the following:
#   chmod u+x /path-to-this-script/update_path.sh

echo "Starting update path"

# 1. Registry Rebuild.
drush --verbose registry-rebuild --no-cache-clear
# 2. Run database updates.
drush --verbose --yes updatedb
# 3. Clear the Drush cache.
# Sometimes Features may need this due to a bug in Features module.
drush cache-clear drush
# 4. Revert all features.
drush --verbose --yes features-revert-all
# 5. Clear all caches.
drush --verbose cache-clear all

echo "Update path completed."
