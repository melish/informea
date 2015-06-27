<?php
$aliases['prod'] = array(
  'uri' => 'http://www.informea.org',
);

$aliases['dev'] = array(
  'uri' => 'http://informea.edw.ro',
  'root' => '/var/www/html/informea/informea.edw.ro/project/docroot',
  'remote-host' => 'php-prod1.edw.lan',
  'remote-user' => 'php',
);

// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}
