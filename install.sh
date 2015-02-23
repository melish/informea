#!/bin/sh

# Setup a clean site in docroot/
cd docroot/
drush site-install -y
drush en -y leo_theme

# Save configuration to database for later usage
drush php-script ../scripts/drupal_pre_install.php

drush init
drush build

drush migrate-auto-register

drush php-script ../scripts/drupal_post_install.php

if [ "$1" == "--migrate" ]; then

	echo "Running migrations ..."
	drush mi Treaties
	drush mi Meetings
	drush mi Thesaurus

	drush mi ActionPlans
	drush mi NationalFocalPoints
	drush mi NationalReports
	drush mi Sites
	drush mi Decisions

fi

drush informea-country-import

drush cc all
