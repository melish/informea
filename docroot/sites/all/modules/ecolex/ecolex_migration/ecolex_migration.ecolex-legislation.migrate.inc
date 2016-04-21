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

  private $url_pattern = NULL;

  public function __construct($source_url_pattern) {
    parent::__construct(array());
    $this->url_pattern = 'http://ecolex-frontend.edw.ro:8983/solr/ecolex/select?q=type%3Alegislation&wt=json';
  }

  public function __toString() {
    return sprintf('Extract legislation from ECOLEX Solr');
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


  /**
   * Return the number of available source records.
   */
  public function computeCount() {
    $ret = 0;
    if ($str = elis_consumer_http_request($this->url_pattern . '&rows=0', array('Accept' => 'application/json'))) {
      if ($json = json_decode($str)) {
        $ret = $json->response->numFound;
      }
    }
    return $ret;
  }

  /**
   * Do whatever needs to be done to start a fresh traversal of the source data.
   *
   * This is always called at the start of an import, so tasks such as opening
   * file handles, running queries, and so on should be performed here.
   */
  public function performRewind() {
    reset($this->data);
  }

  /**
   * Fetch the next row of data, returning it as an object.
   *
   * @return object
   *   FALSE data as stdClass, FALSE when there is no more data available.
   */
  public function getNextRow() {
    if (empty($this->data)) {
      $this->readData();
    }
    $item = NULL;
    if (count($this->data)) {
      $item = current($this->data);
      next($this->data);
    }
    return $item;
  }
}
