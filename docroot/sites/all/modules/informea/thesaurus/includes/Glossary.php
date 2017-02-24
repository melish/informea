<?php

class Glossary {

  public static $sections = [
    'default', //treaties
    'bilateral-treaties',
    'court-decisions',
    'legislations',
    'publications',
  ];

  public static function getSection($path = null) {
    if (empty($path)) {
      $path = current_path();
    }
    if (preg_match('/.*(taxonomy\/term\/\d*|terms\/.*)\/*(.*)/', $path, $matches)) {
      $section = end($matches) ?: 'default';
      if (in_array($section, self::$sections)) {
        return $section;
      }
    }
    return FALSE;
  }

}