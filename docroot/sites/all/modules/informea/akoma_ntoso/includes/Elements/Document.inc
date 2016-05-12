<?php

namespace Drupal\akoma_ntoso\Elements;

class Documents extends Element {

  static $acceptedDocumentTypes = [
    'act',
    'bill',
    'judgement',
    'debateReport',
    'debate',
    'amendmentList',
    'officialGazette',
    'documentCollection',
    'amendment',
    'doc',
  ];

  protected $documentType;

  public function __construct($type = 'doc') {
    if (!in_array($type, self::$acceptedDocumentTypes)) {
      throw new \Exception('Document type not found.');
    }
    $this->documentType = $type;
  }
}