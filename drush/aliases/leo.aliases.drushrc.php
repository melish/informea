<?php
$aliases['dev'] = array(
  'uri' => 'http://leo.edw.ro',
  'root' => '--fill-in-local-file--',
  'remote-host' => 'rom.edw.ro',
  'remote-user' => 'cristiroma',
  'command-specific' => array (
    'sql-sync' => array (
      'simulate' => '1',
    ),
    'rsync' => array (
      'simulate' => '0',
    ),
  ),
);

// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}
