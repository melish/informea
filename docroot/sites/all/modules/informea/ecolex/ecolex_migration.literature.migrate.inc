<?php

class EcolexLiteratureMigrate extends DynamicMigration {

    /**
     * {@inheritdoc}
     */
    public function __construct($arguments) {
        parent::__construct(MigrateGroup::getInstance('Ecolex'));
        $this->arguments = $arguments;
        $this->description = 'Import Ecolex literature from XML web service (files)';
        $data_dir = $arguments['data_dir'];
        $this->source = new EcolexLiteratureMigrateSource($data_dir, array());
        $this->map = new MigrateSQLMap($this->machineName,
            array(
                'Recid' => array(
                    'type' => 'varchar',
                    'length' => 255,
                    'not null' => TRUE,
                    'description' => 'RecId field remote primary key',
                ),
            ),
            MigrateDestinationNode::getKeySchema()
        );
        $this->destination = new MigrateDestinationNode('literature');

        $this->addFieldMapping('field_original_record_id', 'id');
        // $this->addFieldMapping('', 'dateOfEntry');
        // $this->addFieldMapping('', 'dateOfModification');
        $this->addFieldMapping('title', 'title');
        $this->addFieldMapping('title_field', 'titleOfText');

        $this->addFieldMapping('field_data_source')->defaultValue('Ecolex');
        $this->addFieldMapping('field_data_source:create_term')->defaultValue(TRUE);

        $this->addFieldMapping('field_type_of_text', 'typeOfText');
        $this->addFieldMapping('field_type_of_text:create_term')->defaultValue(TRUE);

        $this->addFieldMapping('field_jurisdiction', 'jurisdiction');
        $this->addFieldMapping('field_field_of_application', 'fieldOfApplication');

        $this->addFieldMapping('field_subjects', 'subject');
        $this->addFieldMapping('field_subjects:create_term')->defaultValue(TRUE);

        $this->addFieldMapping('field_keywords', 'keyword');
        $this->addFieldMapping('field_keywords:create_term')->defaultValue(TRUE);

        // $this->addFieldMapping('', 'languageOfDocument');
        $this->addFieldMapping('field_place_of_adoption', 'placeOfAdoption');
        $this->addFieldMapping('field_depositary', 'depository');
        $this->addFieldMapping('field_date_of_text', 'dateOfText');
        // $this->addFieldMapping('', 'searchDate');
        $this->addFieldMapping('field_entry_into_force', 'entryIntoForceDate');
        // $this->addFieldMapping('', 'obsolete');
        // $this->addFieldMapping('', 'officialPublication');
        $this->addFieldMapping('field_available_in', 'availableIn');
        $this->addFieldMapping('field_treaty_text_url', 'linkToFullText');
        $this->addFieldMapping('field_treaty_website_url', 'internetReference');
        $this->addFieldMapping('body', 'abstract');
        // $this->addFieldMapping('', 'amendsTreaty');
        // $this->addFieldMapping('', 'relatedWebSite');
        // $this->addFieldMapping('', 'citesTreaty');

        $this->addFieldMapping('field_region', 'region');
        $this->addFieldMapping('field_region:create_term')->defaultValue(TRUE);

        $this->addFieldMapping('field_ecolex_url', 'ecolex_url');
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
        $migration = Migration::currentMigration();
        $languages = array_keys(language_list());
        $entity_type = $migration->getDestination()->getEntityType();

        $row->field_ecolex_url['en'][0]['url'] = 'http://www.ecolex.org/ecolex/ledge/view/RecordDetails?index=treaties&id=' . $row->Recid;

        $translation_handler = entity_translation_get_handler($entity_type, $entity);
        $entity->translations = $translation_handler->getTranslations();
        $entity->language = 'en';
        foreach ($languages as $language) {
            $has_translation = FALSE;

            if (!empty($row->abstract[$language])) {
                $entity->body[$language][0]['value'] = $row->abstract[$language];
                $entity->body[$language][0]['format'] = 'full_html';
                $has_translation = TRUE;
            }
            if (!empty($row->titleOfText[$language])) {
                $entity->title_field[$language][0]['value'] = $row->titleOfText[$language];
                $has_translation = TRUE;
            }
            if ($has_translation) {
                MigrationUtil::setTranslation($translation_handler, $entity, $row, $language);
            }
        }
    }
}


class EcolexLiteratureMigrateSource extends MigrateSource {

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
            'Recid' => 'Ecolex unique ID',
            'dateOfEntry' => '@todo: dateOfEntry',
            'dateOfModification' => '@todo: dateOfModification',
            'titleOfText' => 'Page title multilingual',
            'typeOfText' => '@todo: typeOfText',
            'jurisdiction' => '@todo: jurisdiction',
            'fieldOfApplication' => '@todo: fieldOfApplication',
            'subject' => '@todo: subject',
            'languageOfDocument' => '@todo: languageOfDocument',

            'placeOfAdoption' => '@todo: placeOfAdoption',
            'depository' => '@todo: depository',
            'dateOfText' => '@todo: dateOfText',
            'searchDate' => '@todo: searchDate',
            'entryIntoForceDate' => '@todo: entryIntoForceDate',
            'obsolete' => '@todo: obsolete',
            'officialPublication' => '@todo: officialPublication',
            'availableIn' => '@todo: availableIn',
            'linkToFullText' => '@todo: linkToFullText',
            'internetReference' => '@todo: internetReference',
            'amendsTreaty' => '@todo: amendsTreaty',
            'relatedWebSite' => '@todo: relatedWebSite',
            'abstract' => '@todo: abstract',
            'citesTreaty' => '@todo: citesTreaty',
            'keyword' => '@todo: keyword',
            'region' => '@todo: region',
            'ecolex_url' => 'Web page on Ecolex website',
        );
    }

    /**
     * Return the number of available source records.
     */
    public function computeCount() {
      $files = file_scan_directory($this->data_dir, '/.*/');
      $ret = 0;
      foreach ($files as $i => $file) {
        try {
          $docs = @simplexml_load_file($file->uri);
          if(!$docs) {
            continue;
          }
          foreach ($docs as $doc) {
            $ret++;
          }
        }
        catch (Exception $e) {
          // Swallow
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
        if(count($this->data)) {
            $item = current($this->data);
            next($this->data);
        }
        return $item;
    }

    /**
     * Query the remote source and pull the data.
     */
    protected function readData() {
        if (!$this->parsed) {
            $this->data = array();
            $this->parsed = TRUE;
            $files = file_scan_directory($this->data_dir, '/.*/');
            foreach($files as $file) {
                $docs = simplexml_load_file($file->uri);
                foreach($docs as $doc) {
                    $id = (string) $doc->id;

                    $ob = new stdClass();
                    // Copy all attributes
                    $ob->id = $id;
                    $ob->id2 = (string) $doc->id2;
                    $ob->isisMfn = (string) $doc->isisMfn;
                    $ob->dateOfEntry = (string)$doc->dateOfEntry;
                    $ob->dateOfModification = (string)$doc->dateOfModification;

                    foreach($doc->authorM as $s) { $ob->author[] = (string)$s; }
                    foreach($doc->corpAuthorM as $s) { $ob->author_institution[] = (string)$s; }

                    $ob->title = (string)$doc->titleOfText;
                    $ob->titleOfText = (string)$doc->titleOfText;

                    $ob->paperTitleOfText = (string)$doc->paperTitleOfText;

                    foreach($doc->languageOfDocument as $s) { $ob->languageOfDocument[] = (string)$s; }
                    $ob->callNo = (string)$doc->callNo;
                    $ob->isbn = (string)$doc->isbn;
                    $ob->publisher = (string)$doc->publisher;
                    $ob->publPlace = (string)$doc->publPlace;
                    $ob->dateOfText = (string)$doc->dateOfText;
                    $ob->serialTitle = (string)$doc->serialTitle;
                    $ob->volumeNo = (string)$doc->volumeNo;
                    $ob->collation = (string)$doc->collation;
                    $ob->typeOfText = (string)$doc->typeOfText;
                    foreach($doc->subject as $s) { $ob->subject[] = (string)$s; }
                    foreach($doc->intOrg as $s) { $ob->intOrg[] = (string)$s; }
                    foreach($doc->country as $s) { $ob->country[] = (string)$s; }
                    $ob->scope = (string)$doc->scope;
                    foreach($doc->region as $s) { $ob->region[] = (string)$s; }
                    $ob->linkToFullText = (string)$doc->linkToFullText;
                    foreach($doc->keyword as $s) { $ob->keyword[] = (string)$s; }
                    foreach($doc->referenceToLiterature as $s) { $ob->referenceToLiterature[] = (string)$s; }
                    foreach($doc->referenceToTreaties as $s) { $ob->referenceToTreaties[] = (string)$s; }
                    $ob->abstract = (string)$doc->abstract;
                    foreach($doc->territorialSubdivision as $s) { $ob->territorialSubdivision[] = (string)$s; }

                    if(empty($ob->title)) {
                        $this->setMessage('Skipping record with empty title:' . $ob->id);
                        continue;
                    }
                    $this->data[$id] = $ob;
                }
            }
        }
    }

    /**
     * Add messages during data retrieval for debugging.
     *
     * @param string $msg
     *   Message string
     * @param int $severity
     *   Migration message level
     */
    protected function setMessage($msg, $severity = MigrationBase::MESSAGE_WARNING) {
        if(function_exists('drush_log')) {
            drush_log($msg, 'warning');
        }
        drupal_set_message($msg);
        $this->activeMigration->queueMessage($msg, $severity);
    }
}
