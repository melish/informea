<?php
/**
 * Author: Cristian Romanescu <cristi _at_ eaudeweb dot ro>
 * Created: 201407171748
 */

require_once 'library.inc';

project_configure_solr();
project_change_field_size();
module_disable(array('overlay'));
project_fix_administrator_role();