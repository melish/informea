<?php

class Glossary {

  public static function getSection($path = null) {
    if (empty($path)) {
      $path = current_path();
    }
    if (preg_match('/.*(taxonomy\/term\/\d*|terms\/.*)\/*(.*)/', $path, $matches)) {
      $allowed_sections = [
        'default', //treaties
        'bilateral-treaties',
        'court-decisions',
        'legislations',
        'publications',
      ];
      $section = end($matches) ?: 'default';
      if (in_array($section, $allowed_sections)) {
        return $section;
      }
    }
    return FALSE;
  }

}