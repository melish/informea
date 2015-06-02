<?php

class InforMEAThesaurusExportXLS {

  public static function toXLS() {
    // Start building up a RDF graph
    $voc = taxonomy_vocabulary_machine_name_load('thesaurus_informea');
    $all_terms = taxonomy_get_tree($voc->vid);

    $xls = new PHPExcel();
    $xls->getProperties()->setCreator('www.informea.org');
    $xls->getProperties()->setTitle('InforMEA Glossary');
    $xls->setActiveSheetIndex(0);

    $xls->getActiveSheet()->SetCellValue('A1', 'Term');
    $xls->getActiveSheet()->getStyle('A1')->getFont()->setBold(true);
    $xls->getActiveSheet()->SetCellValue('B1', 'Definition');
    $xls->getActiveSheet()->getStyle('B1')->getFont()->setBold(true);

    $i = 2;
    $unique = array();
    foreach($all_terms as $term_sk) {
      if (in_array($term_sk->tid, $unique)) {
        continue;
      }
      $definition = '';
      $tid = $term_sk->tid;
      $term_ob = taxonomy_term_load($tid);
      $cell_name = 'A' . $i;
      if (!empty($term_ob->description_field['en'][0]['value'])) {
        $definition = $term_ob->description_field['en'][0]['value'];
      }
      $xls->getActiveSheet()->fromArray(array(
        $term_ob->name_original,
        $definition
      ), NULL, $cell_name);
      $i++;
    }
    $xls_writer = PHPExcel_IOFactory::createWriter($xls, 'Excel5');
    $xls_writer->save('php://output');
  }
}
