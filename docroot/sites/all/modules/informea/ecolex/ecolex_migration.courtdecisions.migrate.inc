<?php

class EcolexCourtDecisionsMigrate extends DynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct(MigrateGroup::getInstance('Ecolex'));
    $this->arguments   = $arguments;
    $this->description = 'Import Ecolex court decisions from XML web service (files)';
    $data_dir          = $arguments['data_dir'];
    $this->source      = new EcolexCourtDecisionsMigrateSource($data_dir, array());
    $this->map         = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type'        => 'varchar',
          'length'      => 255,
          'not null'    => TRUE,
          'description' => 'RecId field remote primary key',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('court_decisions');

    $this->addFieldMapping('field_isis_number', 'isisMfn');
    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('field_alternative_record_id', 'id2');
    $this->addFieldMapping('field_date_of_entry', 'dateOfEntry');
    $this->addFieldMapping('field_date_of_modification', 'dateOfModification');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('title_field', 'titleOfText');

    $this->addFieldMapping('field_type_of_text', 'typeOfText');
    $this->addFieldMapping('field_type_of_text:create_term')->defaultValue(TRUE);

    $this->addFieldMapping('field_country', 'country');

    $this->addFieldMapping('field_ecolex_tags', 'subject');
    $this->addFieldMapping('field_ecolex_tags:create_term')->defaultValue(TRUE);

    $this->addFieldMapping('field_language_of_document', 'languageOfDocument');
    $this->addFieldMapping('field_court_name', 'courtName');
    $this->addFieldMapping('field_court_decision_subdivision', 'subdivision');
    $this->addFieldMapping('field_justices', 'justices');
    $this->addFieldMapping('field_date_of_text', 'dateOfText');
    $this->addFieldMapping('field_reference_number', 'referenceNumber');
    $this->addFieldMapping('field_number_of_pages', 'numberOfPages');

    $this->addFieldMapping('field_keywords', 'keyword');
    $this->addFieldMapping('field_keywords:create_term')->defaultValue(TRUE);

    $this->addFieldMapping('field_related_url', 'relatedWebSite');

    $this->addFieldMapping('field_territorial_subdivision', 'territorialSubdivision');
    $this->addFieldMapping('field_territorial_subdivision:create_term')->defaultValue(TRUE);

    $this->addFieldMapping('field_internet_reference_url', 'internetReference');
    $this->addFieldMapping('field_url', 'linkToFullText');

    // @todo: decode entities and make migration dependent on legislation.
    //$this->addFieldMapping('field_reference_to_legislation', 'referenceToNationalLegislation');
    $this->addFieldMapping('field_abstract', 'abstract');
    $this->addFieldMapping('field_faolex_url', 'urlToFaolexDocument');
    $this->addFieldMapping('field_ecolex_url', 'urlToEcolexRecord');

    $this->addFieldMapping('field_ecolex_decision_status', 'statusOfDecision');
    $this->addFieldMapping('field_ecolex_decision_status:create_term')->defaultValue(TRUE);
  }

  /**
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return 'EcolexCourtDecisions';
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    return TRUE;
  }

  /**
   * Called by destination right before saving.
   *
   * @param object $entity
   *   Entity to save
   * @param object $row
   *   Source row
   */
  public function prepare($entity, $row) {
    $migration   = Migration::currentMigration();
    $languages   = array_keys(language_list());
    $entity_type = $migration->getDestination()->getEntityType();

    $translation_handler  = entity_translation_get_handler($entity_type, $entity);
    $entity->translations = $translation_handler->getTranslations();
    $entity->language     = 'en';
    foreach ($languages as $language) {
      $has_translation = FALSE;

      if ($has_translation) {
        MigrationUtil::setTranslation($translation_handler, $entity, $row, $language);
      }
    }
  }
}


class EcolexCourtDecisionsMigrateSource extends EcolexMigrateSource {

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
      'isisMfn'                     => 'ISIS number',
      'id'                          => 'Primary Key',
      'id2'                         => 'Alternative identifier',
      'dateOfEntry'                 => 'Date of entry into the system',
      'dateOfModification'          => 'Date of last modification',
      'title'                       => 'English record title',
      'titleOfText'                 => 'Record title',
      'typeOfText'                  => 'Type of court decision document',
      'country'                     => 'Country associated with this record',
      'subject'                     => 'Ecolex vocabulary tags',
      'languageOfDocument'          => 'Language for attached document',
      'courtName'                   => 'Court name for the decision',
      'subdivision'                 => 'Court subdivision (?)',
      'justices'                    => 'Justices',
      'dateOfText'                  => 'Record date',
      'referenceNumber'             => 'Document reference number',
      'numberOfPages'               => 'Document number of pages',
      'keyword'                     => 'Ecolex keywords',
      'relatedWebSite'              => 'Related website',
      'territorialSubdivision'      => 'Territory',
      'basin'                       => 'Geographical basin',
      'internetReference'           => 'URL',
      'linkToFullText'              => 'Link to Ecolex document',
      'statusOfDecision'            => 'Court decision status',
      'referenceToNationalLegislation' => 'Reference to national legislation record',
      'abstract'                    => 'Document abstract',
      'urlToFaolexDocument'         => 'Link to FAOLEX',
      'urlToEcolexRecord'           => 'Link to Ecolex',
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
      $processed    = 0;
      foreach ($files as $i => $file) {
        try {
          $docs = @simplexml_load_file($file->uri);
          if ( ! $docs) {
            continue;
          }
          foreach ($docs as $doc) {
            $processed++;
            if ($processed % 5000 == 0) {
              $this->setMessage("Processed $processed records");
            }
            $id = (string) $doc->id;

            $ob = new stdClass();
            // Copy all attributes
            $ob->id                 = $id;
            $ob->isisMfn            = (string) $doc->isisMfn;
            $ob->id2                = (string) $doc->id2;
            $ob->dateOfEntry        = (string) $doc->dateOfEntry;
            $ob->dateOfModification = (string) $doc->dateOfModification;

            $ob->titleOfText['en'] = (string) $doc->titleOfText;
            $ob->titleOfText['fr'] = (string) $doc->titleOfTextFr;
            $ob->titleOfText['es'] = (string) $doc->titleOfTextSp;
            $ob->titleOfText['de'] = (string) $doc->titleOfTextOther;
            foreach ($ob->titleOfText as $title) {
              if ( ! empty( $title )) {
                $ob->title = $title;
                break;
              }
            }

            $country_name = (string) $doc->country;
            if ( ! empty( $country_name )) {
              $ob->country = wp_migration_get_country_id_from_name($country_name);
              if (empty( $ob->country )) {
                $this->setMessage("Cannot match country: " . $country_name);
              }
            }

            foreach ($doc->subject as $s) {
              $ob->subject[] = MigrationUtil::decodeHTMLText((string) $s);
            }
            $ob->languageOfDocument = (string) $doc->languageOfDocument;
            $ob->courtName          = (string) $doc->courtName;
            $ob->subdivision = (string) $doc->subdivision;
            foreach ($doc->justices as $s) {
              $ob->justices[] = MigrationUtil::decodeHTMLText((string) $s);
            }
            $ob->dateOfText      = (string) $doc->dateOfText;
            $ob->referenceNumber = (string) $doc->referenceNumber;
            $ob->numberOfPages   = (string) $doc->numberOfPages;
            foreach ($doc->keyword as $s) {
              $ob->keyword[] = (string) $s;
            }
            $ob->relatedWebSite       = (string) $doc->relatedWebSite;
            $ob->territorialSubdivision = (string) $doc->territorialSubdivision;
            $ob->basin = (string) $doc->basin;

            $ob->internetReference['en'] = (string) $doc->internetReference;
            $ob->internetReference['es'] = (string) $doc->internetReferenceSp;

            $ob->linkToFullText  = (string) $doc->linkToFullText;

            $ob->statusOfDecision  = (string) $doc->statusOfDecision;

            foreach ($doc->referenceToNationalLegislation as $s) {
              $ob->referenceToNationalLegislation[] = (string) $s;
            }

            $ob->abstract['en'] = '';
            foreach ($doc->abstract as $s) {
              $ob->abstract['en'] .= (string) $s . "\n";
            }
            $ob->abstract['fr'] = (string) $doc->abstractFr;
            $ob->abstract['es'] = (string) $doc->abstractSp;
            $ob->urlToFaolexDocument = sprintf(
              'http://faolex.fao.org/cgi-bin/faolex.exe?database=faolex&search_type=link&table=result&lang=eng&format_name=@ERALL&rec_id=%s',
              $ob->isisMfn
            );
            $ob->urlToEcolexRecord = sprintf(
              'http://www.ecolex.org/ecolex/ledge/view/RecordDetails?index=documents&id=%s',
              $ob->id
            );


            if (empty( $ob->title )) {
              $this->setMessage('Skipping record with empty title:' . $ob->Recid);
              continue;
            }
            $this->data[$id] = $ob;
          }
        }
        catch ( Exception $e ) {
          $this->setMessage('Error parsing ' . $e->getMessage());
        }
      }
    }
  }
}
