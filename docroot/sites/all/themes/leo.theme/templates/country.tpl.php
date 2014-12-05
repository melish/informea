<?php
/**
 * @file
 * country.tpl.php
 *
 * @ingroup themeable
 */
?>
<div class="row">
  <div class="col-sm-9">
    <div class="well">
      <div id="chart-bar"></div>
    </div><!-- .well -->
  </div><!-- .col-sm-9 -->
  <div class="col-sm-3">
    <div class="list-group">
      <a href="#" class="list-group-item"><?php print t('Map'); ?></a>
      <a href="#" class="list-group-item">
        <span class="badge">56</span>
        <?php print t('Membership'); ?>
      </a><!-- .list-group-item -->
      <a href="#" class="list-group-item active">
        <span class="badge">560</span>
        <?php print t('Legislation'); ?>
      </a><!-- .list-group-item .active -->
      <a href="#" class="list-group-item">
        <span class="badge">32</span>
        <?php print t('Decisions'); ?>
      </a><!-- .list-group-item -->
      <a href="#" class="list-group-item">
        <span class="badge">320</span>
        <?php print t('Terms'); ?>
      </a><!-- .list-group-item -->
      <a href="#" class="list-group-item">
        <span class="badge">10</span>
        <?php print t('Goals'); ?>
      </a><!-- .list-group-item -->
      <a href="#" class="list-group-item">
        <span class="badge">14</span>
        <?php print t('Publications'); ?>
      </a><!-- .list-group-item -->
    </div><!-- .list-group -->
    <h4><?php print t('Keywords'); ?></h4>
    <p class="keywords">
      <a href="#" class="label label-default"><?php print t('basic legislation'); ?></a>
      <a href="#" class="label label-default"><?php print t('biological diversity'); ?></a>
      <a href="#" class="label label-default"><?php print t('international agreeme&hellip;'); ?></a>
      <a href="#" class="label label-default"><?php print t('biotechnology'); ?></a>
      <a href="#" class="label label-default"><?php print t('education'); ?></a>
      <a href="#" class="label label-default"><?php print t('classification/declassif&hellip;'); ?></a>
      <a href="#" class="label label-default"><?php print t('data collection/report&hellip;'); ?></a>
      <a href="#" class="label label-default"><?php print t('ecosystem preservation&hellip;'); ?></a>
    </p><!-- .keywords -->
    <p><a href="#"><?php print t('See all @count keywords', array('@count' => 25)); ?></a></p>
  </div><!-- .col-sm-3 -->
</div><!-- .row -->
