#!/bin/bash

if [ -z $1 ]; then
  echo "Usage: test.sh <script>"
  echo "    example: test.sh sites/all/modules/informea/ws_consumer_odata/tests/Contacts.php"
  exit -1;
fi

cd docroot/
drush -v scr $1
