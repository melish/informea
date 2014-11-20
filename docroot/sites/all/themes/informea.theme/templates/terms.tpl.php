<?php
/**
 * @file
 * terms.tpl.php
 *
 * @ingroup themeable
 */
?>
<div class="row">
  <div class="col-md-6">
    <div class="section-header">
      <button type="button" class="btn btn-default pull-right" data-toggle="tree" data-target="#tree-substantive" aria-pressed="false"><?php print t('Show all'); ?></button>
      <h3><?php print t('Substantive terms'); ?></h3>
    </div><!-- .section-header -->
    <ul class="list-tree" id="tree-substantive">
      <li>
        <button class="btn btn-link btn-xs" data-toggle="tree-item" type="button">
          <span class="glyphicon glyphicon-plus-sign"></span>
        </button>
        <a href="#">Lorem ipsum dolor sit amet</a>
        <ul class="list-tree collapse">
          <li>
            <button class="btn btn-link btn-xs" data-toggle="tree-item" type="button">
              <span class="glyphicon glyphicon-plus-sign"></span>
            </button>
            <a href="#">Consectetur adipiscing elit</a>
            <ul class="list-tree collapse">
              <li>
                <a href="#">Integer molestie lorem at massa</a>
              </li>
              <li>
                <a href="#">Facilisis in pretium nisl aliquet</a>
              </li>
            </ul><!-- .list-tree -->
          </li>
          <li>
            <a href="#">Nulla volutpat aliquam velit </a>
          </li>
        </ul><!-- .list-tree -->
      </li>
    </ul><!-- .list-tree -->
  </div>
  <div class="col-md-6">
    <div class="section-header">
      <button class="btn btn-default pull-right" type="button"><?php print t('Show all'); ?></button>
      <h3><?php print t('Generic terms'); ?></h3>
    </div><!-- .section-header -->
    <ul class="list-tree" id="tree-generic">
      <li>todo</li>
    </ul><!-- .list-tree -->
  </div>
</div>
<p><?php print t('The InforMEA glossary was developed with the MEA Secretariats represented in the MEA Information and Knowledge Management (IKM) Initiative. Over the coming months, the InforMEA glossary will be upgraded to a Thesaurus on Environmental Law and Conventions in cooperation with partners such as FAO, IUCN, The European Environment Agency.'); ?></p>
