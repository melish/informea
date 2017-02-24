<?php

class Thesaurus {

  /**
   * @var int
   *  ID of 'Thesaurus - InforMEA' vocabulary.
   */
  public static $vid = 14;

  public static $sections = [
    'default', //treaties
    'bilateral-treaties',
    'court-decisions',
    'legislations', // @todo: replace with legislation (without 's')
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

  public static function generatePathAlias($term, $section = null) {
    $name = slugify($term->name);
    $alias = "terms/{$name}";
    if (!empty($section) && $section != 'default') {
      $alias .= "/{$section}";
    }
    return $alias;
  }

  /**
   * @param $term
   *  Taxonomy term object
   */
  public static function updatePathAliases() {
    $languages = language_list();
    $terms = taxonomy_get_tree(self::$vid);
    foreach ($terms as $term) {
      foreach (self::$sections as $section) {
        $alias = self::generatePathAlias($term, $section);
        foreach ($languages as $langKey => $language) {
          $source = "taxonomy/term/{$term->tid}";
          if ($section != 'default') {
            $source .= "/{$section}";
          }
          $path = path_load([
            'source' => $source,
            'language' => $langKey,
          ]);
          if (empty($path)) {
            // Path alias does not exist. Create a new one
            $path = [
              'source' => $source,
              'alias' => $alias,
              'language' => $langKey,
            ];
            path_save($path);

            if (function_exists('drush_log')) {
              drush_log("New alias for term '{$term->name}': {$alias}", "ok");
            }
          }
          elseif ($path['alias'] != $alias) {
            // The path alias exists, but it is incorrect.
            // Update the alias and redirect the old one.
            $redirect = new stdClass();
            redirect_object_prepare($redirect, [
              'source' => $path['alias'],
              'redirect' => $alias,
              'language' => $langKey,
            ]);

            $path['alias'] = $alias;
            path_save($path);

            redirect_save($redirect);

            if (function_exists('drush_log')) {
              drush_log("Redirect {$langKey}/{$path['alias']} to {$langKey}/{$alias}", "ok");
              drush_log("New alias for term '{$term->name}': {$alias}", "ok");
            }
          }
          
        } // end languages foreach
      } // end sections foreach
    } // end terms foreach
  }

}