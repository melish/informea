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
    <div class="panel panel-default">
      <div class="panel-body">
        <form class="form-horizontal" role="form">
          <h3><?php print t('Find legislation'); ?></h3>
          <hr>
          <div class="form-group">
            <label for="inputSearch" class="col-sm-2 control-label"><?php print t('Search for'); ?></label>
            <div class="col-sm-10">
              <input type="text" class="form-control" id="inputSearch">
            </div><!-- .col-sm-10 -->
          </div><!-- .form-group -->
          <div class="form-group">
            <div class="col-sm-offset-2 col-sm-10">
              <label class="radio-inline">
                <input type="radio" name="inlineRadioOptions" id="inlineRadio1" value="option1">
                <?php print t('Any of these words'); ?>
              </label><!-- .radio-inline -->
              <label class="radio-inline">
                <input type="radio" name="inlineRadioOptions" id="inlineRadio2" value="option2">
                <?php print t('All of these words'); ?>
              </label><!-- .radio-inline -->
              <label class="radio-inline">
                <input type="radio" name="inlineRadioOptions" id="inlineRadio3" value="option3">
                <?php print t('Exact match'); ?>
              </label><!-- .radio-inline -->
            </div><!-- .col-sm-offset-2 .col-sm-10 -->
          </div><!-- .form-group -->
          <div class="form-group">
            <div class="col-sm-offset-2 col-sm-10">
              <input type="text" class="form-control" id="inputExclude" aria-describedby="helpBlockExclude">
              <p id="helpBlockExclude" class="help-block"><?php print t('None of these'); ?></p>
            </div><!-- .col-sm-offset-2 .col-sm-10 -->
          </div><!-- .form-group -->
          <hr>
          <div class="form-group">
            <label for="inputYearsAfter" class="col-sm-2 control-label"><?php print t('Years'); ?></label>
            <div class="col-sm-5">
              <input type="text" class="form-control" id="inputYearsAfter" aria-describedby="helpBlockYearsAfter">
              <p id="helpBlockYearsAfter" class="help-block"><?php print t('After'); ?></p>
            </div><!-- .col-sm-5 -->
            <div class="col-sm-5">
              <input type="text" class="form-control" id="inputYearsBefore" aria-describedby="helpBlockYearsBefore">
              <p id="helpBlockYearsBefore" class="help-block"><?php print t('Before'); ?></p>
            </div><!-- .col-sm-5 -->
          </div><!-- .form-group -->
          <hr>
          <div class="form-group">
            <label for="selectCountry" class="col-sm-2 control-label"><?php print t('Country'); ?></label>
            <div class="col-sm-10">
              <select class="form-control" id="selectCountry">
                <option><?php print t('France'); ?></option>
                <option><?php print t('Germany'); ?></option>
                <option><?php print t('Poland'); ?></option>
                <option><?php print t('Ukraine'); ?></option>
                <option><?php print t('Romania'); ?></option>
              </select><!-- .form-control -->
            </div><!-- .col-sm-10 -->
          </div><!-- .form-group -->
          <hr>
          <div class="form-group">
            <label class="col-sm-2 control-label"><?php print t('Type of document'); ?></label>
            <div class="col-sm-10">
              <div class="checkbox">
                <label>
                  <input type="checkbox" value="">
                  <?php print t('Judical decision'); ?>
                </label>
              </div><!-- .checkbox -->
              <div class="checkbox">
                <label>
                  <input type="checkbox" value="">
                  <?php print t('Judical decision of a inferior court'); ?>
                </label>
              </div><!-- .checkbox -->
              <div class="checkbox">
                <label>
                  <input type="checkbox" value="">
                  <?php print t('Preliminary decision'); ?>
                </label>
              </div><!-- .checkbox -->
              <div class="checkbox">
                <label>
                  <input type="checkbox" value="">
                  <?php print t('Judical notice'); ?>
                </label>
              </div><!-- .checkbox -->
              <div class="checkbox">
                <label>
                  <input type="checkbox" value="">
                  <?php print t('Judical decision of a superior court'); ?>
                </label>
              </div><!-- .checkbox -->
              <div class="checkbox">
                <label>
                  <input type="checkbox" value="">
                  <?php print t('Other'); ?>
                </label>
              </div><!-- .checkbox -->
            </div><!-- .col-sm-10 -->
          </div><!-- .form-group -->
          <hr>
          <div class="form-group">
            <div class="col-sm-offset-2 col-sm-10">
              <button type="submit" class="btn btn-success btn-lg"><?php print t('Show results'); ?></button>
            </div><!-- .col-sm-offset-2 .col-sm-10 -->
          </div><!-- .form-group -->
        </form><!-- .form-horizontal -->
      </div><!-- .panel-body -->
    </div><!-- .panel .panel-default -->
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
