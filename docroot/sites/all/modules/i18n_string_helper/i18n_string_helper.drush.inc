<?php

function i18n_string_helper_drush_command() {
  return array(
    'i18n-string-helper-refresh' => array(
      'description' => 'Register website custom website strings with the locale system',
      'alias' => 'i18n-shr',
    )
  );
}

function drush_i18n_string_helper_refresh() {
  $strings = module_invoke_all('i18n_string_helper_strings');
  foreach ($strings as $string) {
    locale($string);
  }
  drush_log(sprintf('Registered %d strings ...', count($strings)), 'success');
}
