<?php

function project_get_config() {
  static $json = NULL;
  if(empty($json)) {
    $config_file = sprintf('%s/../conf/config.json', dirname(__FILE__));
    if(!is_readable($config_file)) {
      die("Cannot read config file! ($config_file). Please configure your project correctly");
    }
    $json = json_decode(file_get_contents($config_file), TRUE);
  }
  return $json;
}


function project_pre_install_set_config_variables() {
  $json = project_get_config();
  if(!empty($json['variables']) && is_array($json['variables'])) {
    foreach($json['variables'] as $k => $v) {
      variable_set($k, $v);
    }
  }
}

