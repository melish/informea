<?php
/**
 * @file
 * footer.tpl.php
 */
?>
<footer class="footer">
  <div class="container">
    <div class="panel panel-default" id="footer-panel">
      <div class="panel-heading">
        <h3 class="panel-title">
          <a aria-controls="footer-index" aria-expanded="false" href="#footer-index" data-toggle="collapse">
            <?php print t('A&ndash;Z of UNEP'); ?>
          </a>
        </h3><!-- .panel-title -->
      </div><!-- .panel-heading -->
      <div class="panel-collapse collapse" id="footer-index">
        <div class="panel-body">
          <div class="well well-sm">
            <div class="row">
              <div class="col-sm-3">
                <ul class="list-unstyled">
                  <li><?php print l(t('Access to Finance'), NULL); ?></li>
                  <li><?php print l(t('Annual Report'), NULL); ?></li>
                  <li><?php print l(t('Biosafety'), NULL); ?></li>
                  <li><?php print l(t('Champions of the Earth'), NULL); ?></li>
                  <li><?php print l(t('Children and Youth/Tunza'), NULL); ?></li>
                  <li><?php print l(t('Cities and Buildings'), NULL); ?></li>
                  <li><?php print l(t('Climate and Clean Air Coalition'), NULL); ?></li>
                  <li><?php print l(t('Climate Change'), NULL); ?></li>
                  <li><?php print l(t('Climate Technology Centre &amp; Network'), NULL, array('html' => TRUE)); ?></li>
                  <li><?php print l(t('Disasters &amp; Conflicts'), NULL, array('html' => TRUE)); ?></li>
                  <li><?php print l(t('Ecosystem Management'), NULL); ?></li>
                  <li><?php print l(t('Education and Training'), NULL); ?></li>
                  <li><?php print l(t('Employment'), NULL); ?></li>
                  <li><?php print l(t('Energy'), NULL); ?></li>
                  <li><?php print l(t('Environment Management Group'), NULL); ?></li>
                </ul><!-- .list-unstyled -->
              </div><!-- .col-sm-3 -->
              <div class="col-sm-3">
                <ul class="list-unstyled">
                  <li><?php print l(t('Environmental Governance'), NULL); ?></li>
                  <li><?php print l(t('Evaluation'), NULL); ?></li>
                  <li><?php print l(t('Forests'), NULL); ?></li>
                  <li><?php print l(t('Funding for UNEP'), NULL); ?></li>
                  <li><?php print l(t('GEAS'), NULL); ?></li>
                  <li><?php print l(t('Gender'), NULL); ?></li>
                  <li><?php print l(t('Global Environment Outlook'), NULL); ?></li>
                  <li><?php print l(t('Governments/SGB'), NULL); ?></li>
                  <li><?php print l(t('Green Economy'), NULL); ?></li>
                  <li><?php print l(t('Greening the Blue'), NULL); ?></li>
                  <li><?php print l(t('Harmful Substances'), NULL); ?></li>
                  <li><?php print l(t('InforMEA'), NULL); ?></li>
                  <li><?php print l(t('IYSEA'), NULL); ?></li>
                  <li><?php print l(t('Major Groups and Stakeholders'), NULL); ?></li>
                  <li><?php print l(t('OARE'), NULL); ?></li>
                </ul><!-- .list-unstyled -->
              </div><!-- .col-sm-3 -->
              <div class="col-sm-3">
                <ul class="list-unstyled">
                  <li><?php print l(t('Our Planet'), NULL); ?></li>
                  <li><?php print l(t('PROVIA - Science for Adaptation Policy'), NULL); ?></li>
                  <li><?php print l(t('Resource Efficiency'), NULL); ?></li>
                  <li><?php print l(t('Sasakawa'), NULL); ?></li>
                  <li><?php print l(t('Science'), NULL); ?></li>
                  <li><?php print l(t('South South Co-operation'), NULL); ?></li>
                  <li><?php print l(t('Sports &amp; Environment'), NULL, array('html' => TRUE)); ?></li>
                  <li><?php print l(t('Sustainable Consumption &amp; Production'), NULL, array('html' => TRUE)); ?></li>
                  <li><?php print l(t('Tourism'), NULL); ?></li>
                  <li><?php print l(t('Transport'), NULL); ?></li>
                  <li><?php print l(t('UN Environment Assembly'), NULL); ?></li>
                  <li><?php print l(t('UN REDD'), NULL); ?></li>
                  <li><?php print l(t('UNDP-UNEP Poverty &amp; Environment'), NULL, array('html' => TRUE)); ?></li>
                  <li><?php print l(t('UNEP 40th Anniversary'), NULL); ?></li>
                  <li><?php print l(t('UNEP Finance Initiative'), NULL); ?></li>
                </ul><!-- .list-unstyled -->
              </div><!-- .col-sm-3 -->
              <div class="col-sm-3">
                <ul class="list-unstyled">
                  <li><?php print l(t('UNEP Governing Council'), NULL); ?></li>
                  <li><?php print l(t('UNEP Planning and Monitoring'), NULL); ?></li>
                  <li><?php print l(t('UNEP Resource Kit'), NULL); ?></li>
                  <li><?php print l(t('UNEP Sustainability'), NULL); ?></li>
                  <li><?php print l(t('UNEP Year Book'), NULL); ?></li>
                  <li><?php print l(t('Virtual Library'), NULL); ?></li>
                  <li><?php print l(t('World Environment Day'), NULL); ?></li>
                  <li><?php print l(t('10YFP'), NULL); ?></li>
                  <li><?php print t('Regional Offices'); ?></li>
                  <li><?php print l(t('Africa'), NULL); ?></li>
                  <li><?php print l(t('Asia Pacific'), NULL); ?></li>
                  <li><?php print l(t('Europe'), NULL); ?></li>
                  <li><?php print l(t('Latin America and the Caribbean'), NULL); ?></li>
                  <li><?php print l(t('North America'), NULL); ?></li>
                  <li><?php print l(t('West Asia'), NULL); ?></li>
                </ul><!-- .list-unstyled -->
              </div><!-- .col-sm-3 -->
            </div><!-- .row -->
          </div><!-- .well .well-sm -->
        </div><!-- .panel-body -->
      </div><!-- .panel-collapse .collapse #footer-index -->
    </div><!-- .panel .panel-default #footer-panel -->
    <ul class="list-inline" id="footer-list">
      <li><a href="<?php print url('<front>'); ?>"><?php print theme('image', array('path' => $directory . '/img/logo-footer.jpg')); ?></a></li>
      <li class="hidden-xs hidden-sm">
        <?php print t('Copyright &copy; United Nations Environment Programme'); ?>
        |
        <?php print l(t('Privacy'), NULL); ?>
        |
        <?php print l(t('Terms and Conditions'), NULL); ?>
      </li><!-- .hidden-xs .hidden-sm -->
      <li class="hidden-xs hidden-sm">
        <?php print l(t('Contacts'), NULL); ?>
        |
        <?php print l(t('Site Locator'), NULL); ?>
        |
        <?php print l(t('UNEP Intranet'), NULL); ?>
      </li><!-- .hidden-xs .hidden-sm -->
      <li id="footer-social-media">
        <?php print t('Follow UNEP:'); ?>
        <a href="<?php print url('http://www.facebook.com/pages/UNEP/287683225711'); ?>" target="_blank"><?php print theme('image', array('path' => $directory . '/img/icon-facebook.gif')); ?></a>
        <a href="<?php print url('http://twitter.com/unep'); ?>" target="_blank"><?php print theme('image', array('path' => $directory . '/img/icon-twitter.gif')); ?></a>
        <a href="<?php print url('rss'); ?>"><?php print theme('image', array('path' => $directory . '/img/icon-rss.gif')); ?></a>
      </li><!-- #footer-social-media -->
    </ul><!-- .list-inline #footer-list -->
  </div><!-- .container -->
</footer><!-- .footer -->
