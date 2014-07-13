#!/bin/sh

# Setup a clean site in docroot/
cd docroot/
drush site-install -y

# Save configuration to database for later usage
drush php-script ../scripts/drupal_pre_install.php

drush init
drush build

drush php-script ../scripts/drupal_post_install.php

drush cc all
