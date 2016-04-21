<?php

class EcolexLegislationMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->source = new EcolexLegislationMigrateSource($arguments['source_url_pattern']);
    $this->destination = new MigrateDestinationNode('legislation');


    // $this->addFieldMapping('field_data_source:source_type')->defaultValue('term');

    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');

    $this->addUnmigratedSources(array());
    $this->addUnmigratedDestinations(array());
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
    return $this->validateRow($row);
  }

  public function validateRow($row) {
    return !empty($row->title_english);
  }
}


class EcolexLegislationMigrateSource extends MigrateSource {

  public function __construct($source_url_pattern, $xml_encoding) {
    parent::__construct(array());
  }

  public function __toString() {
    return sprintf('Extract legislation from ECOLEX');
  }

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id'                          => 'Primary Key',
      'ISIS_MFN'                    => 'ISIS number',
      'FaolexId'                    => 'FAOLEX Identifier',
      'Date_of_Entry'               => 'Date of entry into the system',
      'Date_of_Modification'        => 'Date of last modification',
      'country'                     => 'Related country',
      'Territorial_Subdivision'     => 'Territory',
      'basin'                       => '@todo',
      'Title_of_Text'               => 'Title',
      'title'                       => 'Title in english',
      'Date_of_Text'                => 'Date of text',
      'Date_of_original_Text'       => 'Date of original text',
      'Date_of_Consolidation'       => 'Date of consolidation',
      'Entry_into_Force'            => 'Entry into force notes',
      'searchDate'                  => '@todo',
      'Related_Web_Site'            => 'Related web site',
      'Internet_Reference'          => 'Link to record',
      'link_to_full_text'           => 'Link to document',
      'Type_of_Text'                => 'Type of legislation text',
      'Abstract'                    => 'Abstract text',
      'Comment'                     => 'Comments / Notes',
      'Sub_file_code'               => 'Sub-file code (?)',
      'keyword'                     => 'FAOLEX numeric term IDs - see faolex_id_term_mapping.csv for mapping to ECOLEX',
      'International_Organizations' => '@todo',
      'Record_Language'             => '@todo',
      'Doc_Language'                => 'Document language',
      'Repealed'                    => 'Repealed (Y/N)',
      'Serial_Imprint'              => 'Serial imprint number',
      'Publication_reference'       => 'Reference to publication page/no.',
      'ecolex_url'                  => 'Link to ECOLEX',
      'faolex_url'                  => 'Link to FAOLEX',
      'region'                      => 'Automatically computed from country',
      'files'                       => 'Files attached to this treaty',
    );
  }

  function getFieldFilter($field_name) {
    $filters = array(
      'titleOfText' => 'filter_single_multilingual',
      'titleOfTextShort' => 'filter_single_multilingual',
      'country' => 'filter_multivalued',
      'abstract' => 'filter_multivalued_multilingual_concatenated',
      'subject' => 'filter_multivalued_multilingual',
      'keyword' => 'filter_multivalued_multilingual',
      'linkToFullText' => 'filter_single_multilingual',
      'internetReference' => 'filter_single_multilingual',
      'typeOfText' => 'filter_multivalued_multilingual',
      'referenceToNationalLegislation' => 'filter_multivalued',
      'referenceToEULegislation' => 'filter_multivalued',
      'referenceToCourtDecision' => 'filter_multivalued',
      'referenceToTreaties' => 'filter_multivalued',
      'justices' => 'filter_multivalued',
      'territorialSubdivision' => 'filter_multivalued_multilingual',
      'region' => 'filter_multivalued_multilingual',
      'referenceToFaolex' => 'filter_multivalued',
    );
    return !empty($filters[$field_name]) ? $filters[$field_name] : NULL;
  }

  function prepareItem($item) {
    $item->title_english = !empty($item->titleOfText[0]) ? $item->titleOfText[0] : NULL;
    $languages = array();
    if (!empty($item->titleOfText_languages)) {
      $languages += $item->titleOfText_languages;
    }
    if (!empty($item->linkToFullText_languages)) {
      $languages += $item->linkToFullText_languages;
    }
    $item->languages = array_unique($languages);
  }
}
