<div class="related-national-reports-container">
  <?php if (!empty($items)): ?>
    <h3><?php print t('Related national reports'); ?></h3>
    <div class="accordion panel-group tagged-content" role="tablist" aria-multiselectable="true">
      <?php foreach ($items as $treaty) : ?>
        <?php $treaty_w = entity_metadata_wrapper('node', $treaty); ?>
        <div class="panel panel-default">
          <div class="panel-heading collapsed" role="tab" id="heading-<?php print $treaty->nid; ?>" data-target="#content-<?php print $treaty->nid; ?>" data-toggle="collapse" aria-expanded="false">
            <i class="glyphicon glyphicon-plus-sign"></i>
            <h4 class="panel-title">
              <?php print treaty_url_logo($treaty); ?>
              <?php print $treaty_w->label(); ?>
            </h4><!-- .panel-title -->
          </div>
          <div class="accordion panel-group panel-collapse collapse" id="content-<?php print $treaty->nid; ?>" role="tabpanel">
            <div class="national-reports">
              <?php foreach($treaty->children as $national_report): ?>
                <?php $national_report_w = entity_metadata_wrapper('node', $national_report); ?>
                <div class="accordion panel-group tagged-content" role="tablist" aria-multiselectable="true">
                  <div class="panel panel-default">
                    <div class="panel-heading collapsed" role="tab" id="heading-<?php print $national_report->nid; ?>" data-target="#content-<?php print $national_report->nid; ?>" data-toggle="collapse" aria-expanded="false">
                      <i class="glyphicon glyphicon-plus-sign"></i>
                      <h4 class="panel-title">
                        <?php print $national_report_w->label(); ?>
                      </h4><!-- .panel-title -->
                    </div>
                    <div class="accordion panel-group panel-collapse collapse" id="content-<?php print $national_report->nid; ?>" role="tabpanel">
                      <div class="national-report-paragraphs">
                        <?php foreach($national_report->children as $national_report_paragraph): ?>
                          <?php $national_report_paragraph_w = entity_metadata_wrapper('node', $national_report_paragraph); ?>
                          <div class="item" id="content-<?php print $national_report->nid; ?>">
                            <p>
                              <h4><?php print $national_report_paragraph_w->label(); ?></h4>
                              <?php if($national_report_paragraph_w->body->value()): ?>
                                <?php print($national_report_paragraph_w->body->value->value(array('decode' => FALSE))); ?>
                              <?php endif; ?>
                            </p>
                          </div>
                        <?php endforeach; ?>
                      </div>
                    </div>
                </div>
              <?php endforeach; ?>
            </div>
          </div>
        </div>
      <?php endforeach; ?>
    </div><!-- .panel-group -->
  <?php endif; ?>
</div>