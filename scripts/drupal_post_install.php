<?php
/**
 * Author: Cristian Romanescu <cristi _at_ eaudeweb dot ro>
 * Created: 201407171748
 */

require_once 'library.inc';

project_change_field_size();
project_fix_administrator_role();

ecolex_create_default_thesaurus_terms();
ecolex_create_default_keywords_terms();

informea_fix_title_field();