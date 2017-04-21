<?php


/**
 * Created by PhpStorm.
 * User: cristiroma
 * Date: 4/20/17
 * Time: 2:05 PM
 */
class ThesaurusMapping {

  const THESAURUS_ECOLEX_VID = 10;

  /**
   * Find the mapping between ECOLEX and LEO corresponding terms
   * @param string $ecolex_name_en ECOLEX term in english
   * @param string $ecolex_vid ECOLEX vocabulary ID
   *
   * @return array
   *   Array of LEO tids corresponding in accordance to mapping, ex. [ 1, 2, 3 ]
   * <pre>
   * SELECT
   *   a.name as ecolex_term_en,
   *   c.entity_id as leo_tid
   * FROM taxonomy_term_data a
   *   INNER JOIN field_data_field_taxonomy_term_uri b ON a.tid = b.entity_id
   *   INNER JOIN field_data_field_term_reference_url c ON b.field_taxonomy_term_uri_url = c.field_term_reference_url_value
   *   WHERE a.vid = 10
   * ORDER BY a.name;
   * </pre>
   */
  public static function mapEcolexTermToLEO($ecolex_name_en, $ecolex_vid = 10) {
    static $mappings = null;
    if (!$mappings) {
      $query = db_select('taxonomy_term_data', 'a');
      $query->fields('a', array('name'));
      $query->fields('c', array('entity_id'));
      $query->innerJoin('field_data_field_taxonomy_term_uri', 'b', 'a.tid = b.entity_id');
      $query->innerJoin('field_data_field_term_reference_url', 'c', 'b.field_taxonomy_term_uri_url = c.field_term_reference_url_value');
      $query->condition('a.vid', $ecolex_vid);
      $query->orderBy('a.name');
      $rows = $query->execute()->fetchAll();
      foreach($rows as $row) {
        if (!empty($mappings[$row->name])) {
          $mappings[$row->name][] = $row->entity_id;
        }
        else {
          $mappings[$row->name] = array($row->entity_id);
        }
      }
    }
    return !empty($mappings[$ecolex_name_en]) ? $mappings[$ecolex_name_en] : array();
  }

  /**
   * Map multiple terms to LEO at once.
   *
   * @see self::mapEcolexTermToLEO
   *
   * @param array $ecolex_names_en Array of english ECOLEX terms
   * @param int $ecolex_vid
   *
   * @return array
   *   Array of unique tids
   */
  public static function mapEcolexTermToLEOMultiple($ecolex_names_en, $ecolex_vid = 10) {
    if (empty($ecolex_names_en)) {
      return array();
    }
    $ret = array();
    if (is_array($ecolex_names_en)) {
      foreach($ecolex_names_en as $ecolex_name_en) {
        $ret = array_merge($ret, self::mapEcolexTermToLEO($ecolex_name_en, $ecolex_vid));
      }
    }
    else {
      $ret = self::mapEcolexTermToLEO($ecolex_names_en, $ecolex_vid);
    }
    return array_unique($ret);
  }
}
