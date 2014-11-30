<?php

class EcolexLiteratureMigrate extends DynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct(MigrateGroup::getInstance('Ecolex'));
    $this->dependencies = array('EcolexTreaties');
    $this->arguments   = $arguments;
    $this->description = 'Import Ecolex literature from XML web service (files)';
    $data_dir          = $arguments['data_dir'];
    $this->source      = new EcolexLiteratureMigrateSource($data_dir, array());
    $this->map         = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type'        => 'varchar',
          'length'      => 255,
          'not null'    => TRUE,
          'description' => 'ID field remote primary key',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('literature');

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('field_alternative_record_id', 'id2');
    $this->addFieldMapping('field_isis_number', 'isisMfn');
    $this->addFieldMapping('field_date_of_entry', 'dateOfEntry');
    $this->addFieldMapping('field_date_of_modification', 'dateOfModification');
    $this->addFieldMapping('field_author', 'authorM');
    $this->addFieldMapping('field_author_institution', 'corpAuthorM');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('title_field', 'titleOfText');
    $this->addFieldMapping('field_literature_paper_title', 'paperTitleOfText');
    // $this->addFieldMapping('', 'languageOfDocument');
    $this->addFieldMapping('field_literature_call_number', 'callNo');
    $this->addFieldMapping('field_isbn', 'isbn');
    $this->addFieldMapping('field_publisher', 'publisher');
    $this->addFieldMapping('field_publication_place', 'publPlace');
    $this->addFieldMapping('field_date_of_text', 'dateOfText');
    $this->addFieldMapping('field_literature_serial_title', 'serialTitle');
    $this->addFieldMapping('field_volume_no', 'volumeNo');
    $this->addFieldMapping('field_collation', 'collation');
    $this->addFieldMapping('field_literature_type', 'typeOfText');
    $this->addFieldMapping('field_ecolex_tags', 'subject');
    $this->addFieldMapping('field_organizations', 'intOrg');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_geographical_scope', 'scope');

    $this->addFieldMapping('field_region', 'region');
    $this->addFieldMapping('field_region:create_term')->defaultValue(TRUE);

    $this->addFieldMapping('field_url', 'linkToFullText');

    $this->addFieldMapping('field_keywords', 'keyword');
    $this->addFieldMapping('field_keywords:create_term')->defaultValue(TRUE);

    // $this->addFieldMapping('field_related_literature', 'referenceToLiterature');
    $this->addFieldMapping('field_treaty', 'referenceToTreaties');

    $this->addFieldMapping('body', 'abstract');
    $this->addFieldMapping('field_territorial_subdivision', 'territorialSubdivision');

    $this->addFieldMapping('uid')->defaultValue(1);
  }

  /**
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return 'EcolexLiterature';
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow($row) {

    /*
    @todo
    foreach($row->referenceToLiteratureIds as $lid) {
      $id = $this->findRelatedLiterature($lid);
      if (empty( $id )) {
        $id = $this->handleSourceMigration($this->generateMachineName(), $lid);
      }
      $row->referenceToLiterature[] = $id;
    }
    */

    if(!empty($row->referenceToTreatiesIds)) {
      foreach ($row->referenceToTreatiesIds as $tid) {
        $id = $this->findRelatedTreaty($tid);
        if ( ! empty( $id )) {
          $row->referenceToTreaties[] = $id;
        }
      }
    }

    return TRUE;
  }

  public static function findRelatedLiterature($id) {
    $query = new EntityFieldQuery();
    try {
      $result = $query
        ->entityCondition('entity_type', 'literature')
        ->fieldCondition('field_original_id', 'value', $id, '=');
      $result = $query->execute();
    }
    catch(Exception $e) {
      drupal_set_message(
        sprintf('Cannot find literature due to error: %s', $e->getMessage()),
        'warning'
      );
    }
    return !empty($result['node']) ? current(array_keys($result['node'])) : NULL;
  }

  public static function findRelatedTreaty($id) {
    $query = new EntityFieldQuery();
    try {
      $result = $query
        ->entityCondition('entity_type', 'treaty')
        ->fieldCondition('field_original_id', 'value', $id, '=');
      $result = $query->execute();
    }
    catch(Exception $e) {
      drupal_set_message(
        sprintf('Cannot find related treaty due to error: %s', $e->getMessage()),
        'warning'
      );
    }
    return !empty($result['node']) ? current(array_keys($result['node'])) : NULL;
  }
}


class EcolexLiteratureMigrateSource extends EcolexMigrateSource {

  protected $data_dir;
  protected $parsed = FALSE;
  protected $data = array();
  protected $newestItemDate = NULL;

  /**
   * {@inheritdoc}
   */
  public function __construct($data_dir, array $options = array()) {
    parent::__construct($options);
    $this->data_dir = $data_dir;
    //$this->newestItemDate = $this->getNewestItemDate();
  }

  /**
   * Return a string representing the source, for display in the UI.
   */
  public function __toString() {
    return "Extract treaties from Ecolex XML in {$this->data_dir}";
  }

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id'                     => 'Ecolex unique ID',
      'id2'                    => 'Alternative ID',
      'isisMfn'                => 'ISIS Number',
      'dateOfEntry'            => 'Date of entery in the system',
      'dateOfModification'     => 'Date of modification',
      'authorM'                => 'Author(s)',
      'corpAuthorM'            => 'Institution Author(s)',
      'title'                  => 'Synonym for titleOfText',
      'titleOfText'            => 'Page title multilingual',
      'paperTitleOfText'       => 'Paper title',
      'languageOfDocument'     => 'Language(s) for the attached document',
      'callNo'                 => '//@TODO',
      'isbn'                   => 'Publication ISBN number',
      'publisher'              => 'Publisher',
      'publPlace'              => 'Place of publication',
      'dateOfText'             => 'Date of publication (?)',
      'serialTitle'            => '//@TODO',
      'volumeNo'               => 'Volume number',
      'collation'              => 'Info about pages etc.',
      'typeOfText'             => 'Enumerated type of text',
      'subject'                => 'Ecolex subjects',
      'intOrg'                 => 'Organization international (?)',
      'country'                => 'Related countries',
      'scope'                  => 'Geographical scope',
      'region'                 => 'Related regions',
      'linkToFullText'         => 'Link to document',
      'keyword'                => 'Ecolex keywords',
      'referenceToLiterature'  => 'Related literature entities',
      'referenceToTreaties'    => 'Related treaties entities',
      'abstract'               => 'Short description',
      'territorialSubdivision' => 'Geographical territories',
    );
  }

  /**
   * Query the remote source and pull the data.
   */
  protected function readData() {
    if ( ! $this->parsed) {
      $this->data   = array();
      $this->parsed = TRUE;
      $files        = file_scan_directory($this->data_dir, '/.*/');
      $missing = array();
      foreach ($files as $file) {
        $docs = simplexml_load_file($file->uri);
        foreach ($docs as $doc) {
          $id = (string) $doc->id;

          $ob = new stdClass();
          // Copy all attributes
          $ob->id                 = $id;
          $ob->id2                = (string) $doc->id2;
          $ob->isisMfn            = (string) $doc->isisMfn;
          $ob->dateOfEntry        = (string) $doc->dateOfEntry;
          $ob->dateOfModification = (string) $doc->dateOfModification;

          foreach ($doc->authorM as $s) {
            $ob->author[] = (string) $s;
          }
          foreach ($doc->corpAuthorM as $s) {
            $ob->author_institution[] = (string) $s;
          }

          // Compute the title
          $title = (string) $doc->titleOfText;
          if(empty($title)) {
            $title = (string) $doc->paperTitleOfText;
          }
          if(empty($title)) {
            $title = (string) $doc->titleOfTextSp;
          }
          if(empty($title)) {
            $title = (string) $doc->titleOfTextFr;
          }
          if(empty($title)) {
            $title = (string) $doc->titleOfTextOther;
          }
          if(empty($title)) {
            $title = (string) $doc->paperTitleOfTextOther;
          }
          if(empty($title)) {
            $title = (string) $doc->paperTitleOfTextFr;
          }
          if(empty($title)) {
            $title = (string) $doc->paperTitleOfTextEs;
          }
          if(empty($title)) {
            $title = (string) $doc->serialTitle;
          }
          if(empty($title)) {
            $title = $id;
          }

          $ob->title       = $title;
          $ob->titleOfText = (string) $doc->titleOfText;
          $ob->paperTitleOfText = (string) $doc->paperTitleOfText;
          foreach ($doc->languageOfDocument as $s) {
            $ob->languageOfDocument[] = (string) $s;
          }
          $ob->callNo      = (string) $doc->callNo;
          $ob->isbn        = (string) $doc->isbn;
          $ob->publisher   = (string) $doc->publisher;
          $ob->publPlace   = (string) $doc->publPlace;
          $ob->dateOfText  = (string) $doc->dateOfText;
          $ob->serialTitle = (string) $doc->serialTitle;
          $ob->volumeNo    = (string) $doc->volumeNo;
          $ob->collation   = (string) $doc->collation;
          $ob->typeOfText  = (string) $doc->typeOfText;
          foreach ($doc->subject as $s) {
            $ob->subject[] = (string) $s;
          }
          foreach ($doc->intOrg as $s) {
            $ob->intOrg[] = (string) $s;
          }
          foreach ($doc->country as $s) {
            $cid = wp_migration_get_country_id_from_name((string)$s);
            if (empty($cid)) {
              $missing[] = (string)$s;
              $this->setMessage("Cannot match country: " . $s);
            } else {
              $ob->country[] = $cid;
            }
          }

          $ob->scope = (string) $doc->scope;
          foreach ($doc->region as $s) {
            $ob->region[] = (string) $s;
          }
          $ob->linkToFullText = (string) $doc->linkToFullText;
          foreach ($doc->keyword as $s) {
            $ob->keyword[] = (string) $s;
          }
          foreach ($doc->referenceToLiterature as $s) {
            $ob->referenceToLiteratureIds[] = (string) $s;
          }
          foreach ($doc->referenceToTreaties as $s) {
            $ob->referenceToTreatiesIds[] = (string) $s;
          }
          $ob->abstract = (string) $doc->abstract;
          foreach ($doc->territorialSubdivision as $s) {
            $ob->territorialSubdivision[] = (string) $s;
          }

          if (empty( $ob->title )) {
            $this->setMessage('Skipping record with empty title:' . $ob->id);
            continue;
          }
          $this->data[$id] = $ob;
        }
      }
    }
  }
}
