<?php

class EcolexLegislationMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'legId' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Entity original ID from the Ecolex',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->source = new EcolexLegislationMigrateSource($arguments['source_url_pattern']);
    $this->destination = new MigrateDestinationNode('legislation');


    // $this->addFieldMapping('field_data_source:source_type')->defaultValue('term');

    $this->addFieldMapping('title', 'legTitle');
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
//    return $this->validateRow($row);
  }

  public function validateRow($row) {
//    return !empty($row->title_english);
  }
}


class EcolexLegislationMigrateSource extends MigrateSource {

  private $url_pattern = NULL;

  public $totalCount = 0;
  public $currentCount = 0;
  public $currentPage = 0;
  public $pagination = 100;
  protected $data = array();

  public function __construct($source_url_pattern) {
    parent::__construct(array());
    $this->url_pattern = 'http://ecolex-frontend.edw.ro:8983/solr/ecolex/select?q=type%3Alegislation&wt=json';
    $this->computeCount();
  }

  public function __toString() {
    return sprintf('Extract legislation from ECOLEX Solr');
  }

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id'                       => 'Primary Key',
      'legId'                    => 'FAOLEX Identifier',
      'legYear'                  => 'Date of text',
      'legOriginalYear'          => 'Consolidation date',
      'legType'                  => 'Type of document (Legisation, Regulation, Miscellaneous)',
      'legTitle'                 => 'Short title',
      'legLongTitle'             => 'Full title',
      'legAbstract'              => 'Abstract',
      'legCountry_iso'           => 'Country ISO code',
      'legEntryIntoForce'        => 'Notes about enter into force',
      'legGeoArea_en'            => 'Geographical area, multivalued',
      'legBasin'                 => 'Basin geographical area',
      'legLanguage_en'           => 'Document language',
      'legLinkToFullText'        => 'Link to document file',
      'legModificationDate'      => 'Modification date',
      'legRelatedWebSite'        => 'Related website',
      'legSource'                => 'Source of the data input (ie. scanned copy)',
      'legStatus'                => 'Status (i.e. in force)',
      'legSubject'               => 'ECOLEX subject',
      'legTerritorialSubdivision' => 'Territorial subdivision',
      'legAmends'                => 'IDs of the amended legislation',
      'legImplement'             => 'IDs of the implemented legislation',
      'legRepeals'               => 'IDs of the repealed legislation',
      'legKeyword_en'            => 'Tagging keywords',
      'ecolex_url'                  => 'Link to ECOLEX',
      'faolex_url'                  => 'Link to FAOLEX',
      // 'legEntryDate'             => 'Date when record entered into the system',
      // 'legTypeCode'              => 'Codification for type of document',
      // 'legSearchDate'            => '',
    );
  }


  /**
   * Return the number of available source records.
   */
  public function computeCount() {
    if ($str = elis_consumer_http_request($this->url_pattern . '&rows=0', array('Accept' => 'application/json'))) {
      if ($json = json_decode($str)) {
        $this->totalCount = $json->response->numFound;
      }
    }
    return $this->totalCount;
  }

  /**
   * Do whatever needs to be done to start a fresh traversal of the source data.
   *
   * This is always called at the start of an import, so tasks such as opening
   * file handles, running queries, and so on should be performed here.
   */
  public function performRewind() {
    $this->data = array();
    $this->currentPage = 0;
    $this->currentCount = 0;
  }

  /**
   * Fetch the next row of data, returning it as an object.
   *
   * @return object
   *   FALSE data as stdClass, FALSE when there is no more data available.
   */
  public function getNextRow() {
    $next_call_count = $this->currentPage * $this->pagination;
    if ($this->currentCount == $this->totalCount) {
      return NULL;
    }
    if ($this->currentCount == $next_call_count && $next_call_count < $this->totalCount) {
      $start = $this->currentPage * $this->pagination;
      if ($str = elis_consumer_http_request($this->url_pattern . '&rows=' . $this->pagination . '&start=' . $start, array('Accept' => 'application/json'))) {
        if ($json = json_decode($str)) {
          $this->data = $json->response->docs;
          $this->currentPage++;
        }
      }
    }
    // TODO Messages in case of empty data / failed call etc.
    $item = NULL;
    if (count($this->data)) {
      $item = current($this->data);
      next($this->data);
      $this->currentCount++;
    }
    return $item;
  }
}
