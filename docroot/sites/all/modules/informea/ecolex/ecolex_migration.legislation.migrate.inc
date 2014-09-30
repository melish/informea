<?php

class EcolexLegislationMigrate extends DynamicMigration {

    /**
     * {@inheritdoc}
     */
    public function __construct($arguments) {
        parent::__construct(MigrateGroup::getInstance('Ecolex'));
        $this->arguments = $arguments;
        $this->description = 'Import Ecolex legislation from XML web service (files)';
        $data_dir = $arguments['data_dir'];
        $this->source = new EcolexLegislationMigrateSource($data_dir, array(
                'skip_count' => TRUE,
            )
        );
        $this->map = new MigrateSQLMap($this->machineName,
            array(
                'id' => array(
                    'type' => 'varchar',
                    'length' => 255,
                    'not null' => TRUE,
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
        $this->addFieldMapping('field_entry_into_force', 'Entry_into_Force');
        // $this->addFieldMapping('', 'searchDate');
        $this->addFieldMapping('field_avaiable_web_site', 'Related_Web_Site');
        $this->addFieldMapping('field_url', 'link_to_full_text');
        // $this->addFieldMapping('', 'Internet_Reference');
        $this->addFieldMapping('field_type_of_text', 'Type_of_Text');
        // $this->addFieldMapping('', 'Sub_file_code');
        $this->addFieldMapping('body', 'Abstract');
        $this->addFieldMapping('field_abstract', 'Comment');

        $this->addFieldMapping('field_keywords', 'keyword');
        $this->addFieldMapping('field_keywords:create_term')->defaultValue(TRUE);

        // $this->addFieldMapping('', 'International_Organizations');
        // $this->addFieldMapping('', 'Record_Language');
        // $this->addFieldMapping('', 'Doc_Language');
        $this->addFieldMapping('field_repeals', 'Repealed');
        // $this->addFieldMapping('', 'Serial_Imprint');
        // $this->addFieldMapping('', 'Publication_reference');


        $this->addFieldMapping('field_ecolex_url', 'ecolex_url');

    }

    /**
     * {@inheritdoc}
     */
    protected function generateMachineName() {
        return 'EcolexLegislation';
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


class EcolexLegislationMigrateSource extends MigrateSource {

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
            'id' => '@todo',
            'ISIS_MFN' => 'ISIS number',
            'FaolexId' => 'FAOLEX Identifier',
            'Date_of_Entry' => '@todo',
            'Date_of_Modification' => '@todo',
            'country' => '@todo',
            'Territorial_Subdivision' => '@todo',
            'basin' => '@todo',
            'Title_of_Text' => '@todo',
            'title' => '@todo',
            'Date_of_Text' => '@todo',
            'Date_of_original_Text' => '@todo',
            'Date_of_Consolidation' => '@todo',
            'Entry_into_Force' => '@todo',
            'searchDate' => '@todo',
            'Related_Web_Site' => '@todo',
            'Internet_Reference' => '@todo',
            'link_to_full_text' => '@todo',
            'Type_of_Text' => '@todo',
            'Sub_file_code' => '@todo',
            'Abstract' => '@todo',
            'Comment' => '@todo',
            'keyword' => '@todo',
            'International_Organizations' => '@todo',
            'Record_Language' => '@todo',
            'Doc_Language' => '@todo',
            'Repealed' => '@todo',
            'Serial_Imprint' => '@todo',
            'Publication_reference' => '@todo',
            'ecolex_url' => '@todo',
        );
    }

    /**
     * Return the number of available source records.
     */
    public function computeCount() {
        return 0;
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
                try {
                    $docs = simplexml_load_file($file->uri);
                    foreach ($docs as $doc) {
                        $id = (string)$doc->id;

                        $ob = new stdClass();
                        $ob->language = 'en';
                        // Copy all attributes
                        $ob->id = (string)$doc->id;
                        $ob->ISIS_MFN = (string)$doc->ISIS_MFN;
                        $ob->FaolexId = (string)$doc->FaolexId;
                        $ob->Date_of_Entry = (string)$doc->Date_of_Entry;
                        $ob->Date_of_Modification = (string)$doc->Date_of_Modification;
                        $ob->country = (string)$doc->country;
                        $ob->Territorial_Subdivision = (string)$doc->Territorial_Subdivision;
                        $ob->basin = (string)$doc->basin;

                        $ob->Title_of_Text = (string)$doc->Title_of_Text;
                        $ob->title = (string)$doc->Title_of_Text;

                        $ob->Date_of_Text = (string)$doc->Date_of_Text;
                        $ob->Date_of_original_Text = (string)$doc->Date_of_original_Text;
                        $ob->Date_of_Consolidation = (string)$doc->Date_of_Consolidation;
                        $ob->Entry_into_Force = (string)$doc->Entry_into_Force;
                        $ob->searchDate = (string)$doc->searchDate;
                        $ob->Related_Web_Site = (string)$doc->Related_Web_Site;
                        $ob->Internet_Reference = (string)$doc->Internet_Reference;
                        $ob->link_to_full_text = (string)$doc->link_to_full_text;
                        $ob->Type_of_Text = (string)$doc->Type_of_Text;
                        $ob->Sub_file_code = (string)$doc->Sub_file_code;
                        $ob->Abstract = (string)$doc->Abstract;
                        $ob->Comment = (string)$doc->Comment;

                        foreach ($doc->keyword as $s) {
                            $ob->keyword[] = (string)$s;
                        }

                        $ob->International_Organizations = (string)$doc->International_Organizations;
                        $ob->Record_Language = (string)$doc->Record_Language;
                        $ob->Doc_Language = (string)$doc->Doc_Language;
                        $ob->Repealed = (string)$doc->Repealed;
                        $ob->Serial_Imprint = (string)$doc->Serial_Imprint;
                        $ob->Publication_reference = (string)$doc->Publication_reference;

                        if (empty($ob->title)) {
                            $this->setMessage('Skipping record with empty title:' . $ob->Recid);
                            continue;
                        }
                        $this->data[$id] = $ob;
                    }
                }
                catch(Exception $e) {
                    $this->setMessage('Error parsing ' . $e->getMessage());
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
