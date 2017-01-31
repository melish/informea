<?php
$aliases['prod'] = array(
  'uri' => 'http://www.informea.org',
);

$aliases['test'] = array(
  'uri' => 'http://test.informea.org',
  'root' => '/var/www/html/informea/docroot',
  'remote-host' => '5.9.54.24',
  'remote-user' => 'php',
);


// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}
