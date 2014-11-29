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
    $this->destination = new MigrateDestinationNode('legislation');

    $this->addFieldMapping('field_original_id', 'id');
    // $this->addFieldMapping('', 'ISIS_MFN');
    $this->addFieldMapping('field_faolex_id', 'FaolexId');
    // $this->addFieldMapping('', 'Date_of_Entry');
    // $this->addFieldMapping('', 'Date_of_Modification');

    $this->addFieldMapping('field_country', 'country');
    // $this->addFieldMapping('', 'Territorial_Subdivision');
    // $this->addFieldMapping('', 'basin');

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('title_field', 'Title_of_Text');

    $this->addFieldMapping('field_date_of_text', 'Date_of_Text');
    $this->addFieldMapping('field_date_of_original_text', 'Date_of_original_Text');
    $this->addFieldMapping('field_date_of_consolidation', 'Date_of_Consolidation');
    // $this->addFieldMapping('field_entry_into_force', 'Entry_into_Force');
    // $this->addFieldMapping('', 'searchDate');
    $this->addFieldMapping('field_avaiable_web_site', 'Related_Web_Site');
    $this->addFieldMapping('field_url', 'link_to_full_text');
    // $this->addFieldMapping('', 'Internet_Reference');
    $this->addFieldMapping('field_type_of_text', 'Type_of_Text');
    $this->addFieldMapping('field_type_of_text:create_term')
         ->defaultValue(TRUE);
    // $this->addFieldMapping('', 'Sub_file_code');
    $this->addFieldMapping('body', 'Abstract');
    $this->addFieldMapping('field_abstract', 'Comment');

    //@todo: Integers instead of real terms.
    #$this->addFieldMapping('field_keywords', 'keyword');
    #$this->addFieldMapping('field_keywords:create_term')->defaultValue(TRUE);

    // $this->addFieldMapping('', 'International_Organizations');
    // $this->addFieldMapping('', 'Record_Language');
    // $this->addFieldMapping('', 'Doc_Language');
    // $this->addFieldMapping('field_repeals', 'Repealed');
    // $this->addFieldMapping('', 'Serial_Imprint');
    // $this->addFieldMapping('', 'Publication_reference');


    // see prepare() $this->addFieldMapping('field_ecolex_url', 'ecolex_url');
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

    $entity->field_ecolex_url['en'][0]['url'] = 'http://www.ecolex.org/ecolex/ledge/view/RecordDetails?index=documents&id=' . $row->id;
    $entity->field_faolex_url['en'][0]['url'] = 'http://faolex.fao.org/cgi-bin/faolex.exe?database=faolex&search_type=link&table=result&lang=eng&format_name=@ERALL&rec_id=' . $row->ISIS_MFN;

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
      'id'                          => '@todo',
      'ISIS_MFN'                    => 'ISIS number',
      'FaolexId'                    => 'FAOLEX Identifier',
      'Date_of_Entry'               => '@todo',
      'Date_of_Modification'        => '@todo',
      'country'                     => '@todo',
      'Territorial_Subdivision'     => '@todo',
      'basin'                       => '@todo',
      'Title_of_Text'               => '@todo',
      'title'                       => '@todo',
      'Date_of_Text'                => '@todo',
      'Date_of_original_Text'       => '@todo',
      'Date_of_Consolidation'       => '@todo',
      'Entry_into_Force'            => '@todo',
      'searchDate'                  => '@todo',
      'Related_Web_Site'            => '@todo',
      'Internet_Reference'          => '@todo',
      'link_to_full_text'           => '@todo',
      'Type_of_Text'                => '@todo',
      'Sub_file_code'               => '@todo',
      'Abstract'                    => '@todo',
      'Comment'                     => '@todo',
      'keyword'                     => '@todo',
      'International_Organizations' => '@todo',
      'Record_Language'             => '@todo',
      'Doc_Language'                => '@todo',
      'Repealed'                    => '@todo',
      'Serial_Imprint'              => '@todo',
      'Publication_reference'       => '@todo',
      'ecolex_url'                  => '@todo',
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

            foreach ($doc->justices as $s) {
              $ob->justices[] = MigrationUtil::decodeHTMLText((string) $s);
            }

            $ob->dateOfText      = (string) $doc->dateOfText;
            $ob->referenceNumber = (string) $doc->referenceNumber;
            $ob->numberOfPages   = (string) $doc->numberOfPages;
            $ob->linkToFullText  = (string) $doc->linkToFullText;
            foreach ($doc->keyword as $s) {
              $ob->keyword[] = (string) $s;
            }

            $ob->abstract['en'] = (string) $doc->abstract;
            $ob->abstract['fr'] = (string) $doc->abstractFr;
            $ob->abstract['es'] = (string) $doc->abstractSp;

            $ob->internetReference['es'] = (string) $doc->internetReferenceSp;


            $filename = (string) $doc->link_to_full_text;
            if (strpos($filename, '.pdf')) {
              $ob->link_to_full_text = 'http://faolex.fao.org/docs/pdf/' . $filename;
            }
            else {
              if (strpos($filename, '.doc')) {
                $ob->link_to_full_text = 'http://faolex.fao.org/docs/texts/' . $filename;
              }
              else {
                if (strpos($filename, '.html')) {
                  $ob->link_to_full_text = 'http://faolex.fao.org/html/' . $filename;
                }
                else {
                  $ob->link_to_full_text = $filename;
                }
              }
            }

            $ob->Type_of_Text  = (string) $doc->Type_of_Text;
            $ob->Sub_file_code = (string) $doc->Sub_file_code;
            $ob->Abstract      = (string) $doc->Abstract;
            $ob->Comment       = (string) $doc->Comment;


            $ob->International_Organizations = (string) $doc->International_Organizations;
            $ob->Record_Language             = (string) $doc->Record_Language;
            $ob->Doc_Language                = (string) $doc->Doc_Language;
            $ob->Repealed                    = (string) $doc->Repealed;
            $ob->Serial_Imprint              = (string) $doc->Serial_Imprint;
            $ob->Publication_reference       = (string) $doc->Publication_reference;

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
