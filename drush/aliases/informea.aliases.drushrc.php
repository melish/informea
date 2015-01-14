<?php
$aliases['dev'] = array(
  'uri' => 'http://informea.edw.ro',
  'root' => '--fill-in-local-file--',
  'remote-host' => 'rom.edw.ro',
  'remote-user' => 'cristiroma',
);

// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}
