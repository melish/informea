<?php
/**
 * @file
 * header.tpl.php
 */
?>
<div class="modal fade" id="dialog-modal-ajax" tabindex="-1" role="dialog" aria-labelledby="modal-label" aria-hidden="true">
  <div class="modal-dialog modal-lg">
    <div class="modal-content"></div>
  </div><!-- .modal-dialog .modal-lg -->
</div><!-- .modal .fade #dialog-modal-ajax -->
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
  <div class="container">
    <div class="navbar-header header-brand">
      <?php if ($logo): ?>
        <a class="logo navbar-btn pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a><!-- .logo .navbar-btn .pull-left -->
      <?php endif; ?>
    </div><!-- .navbar-header -->
    <div class="navbar-header header-content">
      <?php if (!empty($page['navigation'])): ?>
        <?php print render($page['navigation']); ?>
      <?php endif; ?>
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button><!-- .navbar-toggle -->
    </div><!-- .navbar-header -->
    <nav class="navbar-collapse collapse navbar-left" role="navigation">
      <ul class="nav navbar-nav">
        <li class="dropdown dropdown-full-width">
          <?php print l(t('Treaties') . ' <span class="caret"></span>', 'treaties', array('attributes' => array('class' => array('dropdown-toggle')), 'absolute' => TRUE, 'html' => TRUE)); ?>
          <ul class="dropdown-menu row" role="menu">
            <li class="col-sm-3">
              <ul>
                <li class="dropdown-header"><?php print t('Biological Diversity'); ?></li>
                <li><?php print l(t('AEWA'), 'treaties/aewa'); ?></li>
                <li><?php print l(t('ASCOBANS'), 'treaties/ascobans'); ?></li>
                <li>
                  <?php print l(t('CBD'), 'treaties/cbd'); ?>
                  <ul>
                    <li><?php print l(t('Cartagena Protocol'), 'treaties/cartagena'); ?></li>
                    <li><?php print l(t('Nagoya Protocol'), 'treaties/nagoya'); ?></li>
                  </ul>
                </li>
                <li><?php print l(t('CITES'), 'treaties/cites'); ?></li>
                <li><?php print l(t('CMS'), 'treaties/cms'); ?></li>
                <li><?php print l(t('EUROBATS'), 'treaties/eurobats'); ?></li>
                <li><?php print l(t('Plant Treaty'), 'treaties/plant-treaty'); ?></li>
                <li><?php print l(t('Ramsar'), 'treaties/ramsar'); ?></li>
                <li><?php print l(t('WHC'), 'treaties/whc'); ?></li>
              </ul>
            </li><!-- .col-sm-3 -->
            <li class="col-sm-3">
              <ul>
                <li class="dropdown-header"><?php print t('Chemicals/Waste'); ?></li>
                <li><?php print l(t('Basel'), 'treaties/basel'); ?></li>
                <li><?php print l(t('Rotterdam'), 'treaties/rotterdam'); ?></li>
                <li><?php print l(t('Stockholm'), 'treaties/stockholm'); ?></li>
                <li><?php print l(t('Minamata'), 'treaties/minamataunep'); ?></li>
                <li class="dropdown-header"><?php print t('Climate/Atmosphere'); ?></li>
                <li><?php print l(t('UNCCD'), 'treaties/unccd'); ?></li>
                <li>
                  <?php print l(t('UNFCCC'), 'treaties/unfccc'); ?>
                  <ul>
                    <li><?php print l(t('Kyoto Protocol'), 'treaties/kyoto'); ?></li>
                  </ul>
                </li>
                <li>
                  <?php print l(t('Vienna'), 'treaties/vienna'); ?>
                  <ul>
                    <li><?php print l(t('Montreal Protocol'), 'treaties/montreal'); ?></li>
                  </ul>
                </li>
              </ul>
            </li><!-- .col-sm-3 -->
            <li class="col-sm-3">
              <ul>
                <li class="dropdown-header"><?php print t('Regional Treaties'); ?></li>
                <li>
                  <?php print l(t('Barcelona'), 'treaties/barcelona'); ?>
                  <ul>
                    <li><?php print l(t('Barcelona Dumping Protocol'), 'treaties/dumping'); ?></li>
                    <li><?php print l(t('Hazardous Wastes Protocol'), 'treaties/hazardous'); ?></li>
                    <li><?php print l(t('Land-Based Sources Protocol'), 'treaties/land-based'); ?></li>
                    <li><?php print l(t('Offshore Protocol'), 'treaties/offshore'); ?></li>
                    <li><?php print l(t('Prevention and Emergency Protocol'), 'treaties/preventionemergency'); ?></li>
                    <li><?php print l(t('Specially Protected Areas Protocol'), 'treaties/barc-spa'); ?></li>
                  </ul>
                </li>
                <li><?php print l(t('Espoo Convention'), 'treaties/espoo'); ?></li>
                <li><?php print l(t('Jeddah Convention'), 'treaties/jeddah'); ?></li>
                <li><?php print l(t('Long-Range Transboundary Air Pollution'), 'treaties/lrtp'); ?></li>
                <li><?php print l(t('Nairobi Convention'), 'treaties/nairobi'); ?></li>
                <li><?php print l(t('The Kyiv Protocol'), 'treaties/kyivsea'); ?></li>
              </ul>
            </li><!-- .col-sm-3 -->
            <li class="col-sm-3">
              <ul>
                <li>
                  <?php print l(t('Aarhus Convention'), 'treaties/aarhus'); ?>
                  <ul>
                    <li><?php print l(t('Kiev Protocol'), 'treaties/pollutantrelease'); ?></li>
                  </ul>
                </li>
                <li><?php print l(t('Abidjan Convention'), 'treaties/abidjan'); ?></li>
                <li><?php print l(t('Antigua Convention'), 'treaties/antigua'); ?></li>
                <li><?php print l(t('Apia Convention'), 'treaties/apia'); ?></li>
                <li><?php print l(t('Bamako Convention'), 'treaties/bamako'); ?></li>
                <li><?php print l(t('Cartagena Convention'), 'treaties/cartagena-conv'); ?></li>
                <li><?php print l(t('Industrial Accidents Convention'), 'treaties/industrialaccidents'); ?></li>
                <li><?php print l(t('Kuwait Regional Convention'), 'treaties/kuwait'); ?></li>
                <li><?php print l(t('Lusaka Agreement'), 'treaties/lusakaagreement'); ?></li>
                <li><?php print l(t('Noumea Convention'), 'treaties/noumea'); ?></li>
                <li>
                  <?php print l(t('Water Convention'), 'treaties/waterconvention'); ?>
                  <ul>
                    <li><?php print l(t('Protocol on Water and Health'), 'treaties/protocolwaterhealth'); ?></li>
                  </ul>
                </li>
              </ul>
            </li><!-- .col-sm-3 -->
          </ul><!-- .dropdown-menu -->
        </li><!-- .dropdown -->
        <li><?php print l(t('Countries'), 'countries'); ?></li>
        <li><?php print l(t('Glossary'), 'terms'); ?></li>
        <li class="dropdown">
          <?php print l(
            t('Events') . ' <span class="caret"></span>',
            'events',
            array('attributes' => array('class' => array('dropdown-toggle')), 'absolute' => TRUE, 'html' => TRUE)); ?>
          <ul class="dropdown-menu dropdown-menu-right" role="menu">
            <li><?php print l(t('Past events'), 'events/past'); ?></li>
          </ul><!-- .dropdown-menu .dropdown-menu-right -->
        </li>
        <li><?php print l(t('News'), 'news'); ?></li>
        <li class="dropdown">
          <?php print l(
            t('About') . ' <span class="caret"></span>',
            'about',
            array('attributes' => array('class' => array('dropdown-toggle')), 'absolute' => TRUE, 'html' => TRUE)); ?>
          <ul class="dropdown-menu dropdown-menu-right" role="menu">
            <li><?php print l(t('About InforMEA'), 'about'); ?></li>
            <li><?php print l(t('API documentation'), 'about/api'); ?></li>
          </ul><!-- .dropdown-menu .dropdown-menu-right -->
        </li><!-- .dropdown -->
      </ul><!-- .nav .navbar-nav -->
    </nav><!-- .navbar-collapse .collapse -->
  </div><!-- .container -->
</header><!-- #navbar -->
