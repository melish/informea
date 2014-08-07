<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
  <div class="container">
    <div class="navbar-header">
      <?php if ($logo): ?>
        <a class="logo navbar-btn pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a><!-- .logo .navbar-btn .pull-left -->
      <?php endif; ?>
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button><!-- .navbar-toggle -->
    </div><!-- .navbar-header -->
    <nav class="navbar-collapse collapse" role="navigation">
      <ul class="nav navbar-nav">
        <li class="dropdown dropdown-full-width">
          <?php print l(t('Treaties') . ' <span class="caret"></span>', NULL, array('attributes' => array('class' => 'dropdown-toggle', 'data-toggle' => 'dropdown'), 'external' => TRUE, 'fragment' => FALSE, 'html' => TRUE)); ?>
          <ul class="dropdown-menu row" role="menu">
            <li class="col-sm-3">
              <ul>
                <li class="dropdown-header"><?php print t('Biological Diversity'); ?></li>
                <li><?php print l(t('Cartagena Protocol'), 'treaties/cartagena'); ?></li>
                <li><?php print l(t('CBD'), 'treaties/cbd'); ?></li>
                <li><?php print l(t('CITES'), 'treaties/cites'); ?></li>
                <li><?php print l(t('CMS'), 'treaties/cms'); ?></li>
                <li><?php print l(t('Nagoya Protocol'), 'treaties/nagoya'); ?></li>
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
                <li class="dropdown-header"><?php print t('Climate/Atmosphere'); ?></li>
                <li><?php print l(t('UNCCD'), 'treaties/unccd'); ?></li>
                <li><?php print l(t('UNFCCC'), 'treaties/unfccc'); ?></li>
                <li><?php print l(t('Kyoto Protocol'), 'treaties/kyoto'); ?></li>
                <li><?php print l(t('Montreal Protocol'), 'treaties/montreal'); ?></li>
                <li><?php print l(t('Vienna'), 'treaties/vienna'); ?></li>
              </ul>
            </li><!-- .col-sm-3 -->
            <li class="col-sm-3">
              <ul>
                <li class="dropdown-header"><?php print t('Regional Treaties'); ?></li>
                <li><?php print l(t('Aarhus Convention'), 'treaties/aarhus'); ?></li>
                <li><?php print l(t('Abidjan Convention'), 'treaties/abidjan'); ?></li>
                <li><?php print l(t('AEWA'), 'treaties/aewa'); ?></li>
                <li><?php print l(t('Antigua Convention'), 'treaties/antigua'); ?></li>
                <li><?php print l(t('Apia Convention'), 'treaties/apia'); ?></li>
                <li><?php print l(t('Barcelona'), 'treaties/barcelona'); ?></li>
                <li><?php print l(t('Barcelona Dumping Protocol'), 'treaties/dumping'); ?></li>
                <li><?php print l(t('Bamako Convention'), 'treaties/bamako'); ?></li>
                <li><?php print l(t('Cartagena Convention'), 'treaties/cartagena-conv'); ?></li>
                <li><?php print l(t('Espoo Convention'), 'treaties/espoo'); ?></li>
                <li><?php print l(t('Hazardous Wastes Protocol'), 'treaties/hazardous'); ?></li>
                <li><?php print l(t('Industrial Accidents Convention'), 'treaties/industrialaccidents'); ?></li>
                <li><?php print l(t('Jeddah Convention'), 'treaties/jeddah'); ?></li>
              </ul>
            </li><!-- .col-sm-3 -->
            <li class="col-sm-3">
              <ul>
                <li><?php print l(t('Kiev Protocol'), 'treaties/pollutantrelease'); ?></li>
                <li><?php print l(t('Kuwait Regional Convention'), 'treaties/kuwait'); ?></li>
                <li><?php print l(t('Long-Range Transboundary Air Pollution'), 'treaties/lrtp'); ?></li>
                <li><?php print l(t('Lusaka Agreement'), 'treaties/lusakaagreement'); ?></li>
                <li><?php print l(t('Nairobi Convention'), 'treaties/nairobi'); ?></li>
                <li><?php print l(t('Noumea Convention'), 'treaties/noumea'); ?></li>
                <li><?php print l(t('Land-Based Sources Protocol'), 'treaties/land-based'); ?></li>
                <li><?php print l(t('Offshore Protocol'), 'treaties/offshore'); ?></li>
                <li><?php print l(t('Prevention and Emergency Protocol'), 'treaties/preventionemergency'); ?></li>
                <li><?php print l(t('Specially Protected Areas Protocol'), 'treaties/barc-spa'); ?></li>
                <li><?php print l(t('The Kyiv Protocol'), 'treaties/kyivsea'); ?></li>
                <li><?php print l(t('Protocol on Water and Health'), 'treaties/protocolwaterhealth'); ?></li>
                <li><?php print l(t('Water Convention'), 'treaties/waterconvention'); ?></li>
              </ul>
            </li><!-- .col-sm-3 -->
          </ul><!-- .dropdown-menu -->
        </li><!-- .dropdown -->
        <li><?php print l(t('Countries'), 'countries'); ?></li>
        <li><?php print l(t('Glossary'), 'terms'); ?></li>
        <li class="dropdown">
          <?php print l(t('More') . ' <span class="caret"></span>', NULL, array('attributes' => array('class' => 'dropdown-toggle', 'data-toggle' => 'dropdown'), 'external' => TRUE, 'fragment' => FALSE, 'html' => TRUE)); ?>
          <ul class="dropdown-menu dropdown-menu-right" role="menu">
            <li><?php print l(t('About InforMEA'), 'about'); ?></li>
            <li><?php print l(t('Multimedia'), 'about/multimedia'); ?></li>
            <li class="divider"></li>
            <li><?php print l(t('Latest updates'), 'news'); ?></li>
            <li><?php print l(t('Events'), 'news'); ?></li>
          </ul><!-- .dropdown-menu .dropdown-menu-right -->
        </li><!-- .dropdown -->
      </ul><!-- .nav .navbar-nav -->
      <?php print $search_box; ?>
      <?php if (!empty($page['navigation'])): ?>
        <?php print render($page['navigation']); ?>
      <?php endif; ?>
    </nav><!-- .navbar-collapse .collapse -->
  </div><!-- .container -->
</header><!-- #navbar -->
<div class="hero-unit">
  <div class="container">
    <div class="row">
      <div class="col-md-6 hero-unit-body">
        <?php if (!empty($site_slogan)): ?>
          <p class="lead"><?php print $site_slogan; ?></p>
        <?php endif; ?>
        <p><?php print t('InforMEA harvests COP decisions, news, meetings, membership, national focal points and reports from MEAs. Information is organised by terms from MEA COP agendas.'); ?></p>
        <p><?php print t('InforMEA is a project of the MEA Information and Knowledge Management (IKM) Initiative with the support from the United Nations Environment Programme (UNEP).'); ?></p>
        <p><?php print l(t('Learn more about InforMEA') . ' <span class="glyphicon glyphicon-arrow-right"></span>', 'about', array('html' => TRUE)); ?></p>
      </div><!-- .col-md-6 .hero-unit-body -->
      <div class="col-md-6 latest-updates">
        <div class="media-list list-group list-group-scrollable">
          <a class="media list-group-item" href="#">
            <div class="pull-right">
              <img class="media-object" src="http://placehold.it/48x48" alt="">
            </div><!-- .pull-right -->
            <div class="media-body">
              <p class="list-group-item-text"><?php print t('The Month of Reporting open with special series of webinars on National Reporting'); ?></p>
            </div><!-- .media-body -->
          </a><!-- .media .list-group-item -->
          <a class="media list-group-item" href="#">
            <div class="pull-right">
              <span class="label label-default">28&ndash;30<br>Oct.</span>
            </div><!-- .pull-right -->
            <div class="media-body">
              <p class="list-group-item-text"><?php print t('Tenth meeting of the Compliance Committee under the Protocol on Water and Health'); ?></p>
            </div><!-- .media-body -->
          </a><!-- .media .list-group-item -->
          <a class="media list-group-item" href="#">
            <div class="pull-right">
              <img class="media-object" src="http://placehold.it/48x48" alt="">
            </div><!-- .pull-right -->
            <div class="media-body">
              <p class="list-group-item-text"><?php print t('The Month of Reporting open with special series of webinars on National Reporting'); ?></p>
            </div><!-- .media-body -->
          </a><!-- .media .list-group-item -->
          <a class="media list-group-item" href="#">
            <div class="pull-right">
              <span class="label label-default">28&ndash;30<br>Oct.</span>
            </div><!-- .pull-right -->
            <div class="media-body">
              <p class="list-group-item-text"><?php print t('Tenth meeting of the Compliance Committee under the Protocol on Water and Health'); ?></p>
            </div><!-- .media-body -->
          </a><!-- .media .list-group-item -->
          <a class="media list-group-item" href="#">
            <div class="pull-right">
              <span class="label label-default">28&ndash;30<br>Oct.</span>
            </div><!-- .pull-right -->
            <div class="media-body">
              <p class="list-group-item-text"><?php print t('Tenth meeting of the Compliance Committee under the Protocol on Water and Health'); ?></p>
            </div><!-- .media-body -->
          </a><!-- .media .list-group-item -->
        </div><!-- .media-list .list-group -->
        <a class="btn btn-primary btn-block" href="#">Read the latest MEA updates</a>
      </div><!-- .col-md-6 .latest-updates -->
    </div><!-- .row -->
  </div><!-- .container -->
</div><!-- .hero-unit -->
<div class="container">
  <h1 class="page-header"><?php print t('InforMEA features'); ?></h1>
  <div class="well">
    <div class="row">
      <div class="col-md-4">
        <h2><?php print t('Treaties'); ?></h2>
        <ul>
          <li><?php print t('Read the complete text on any treaty'); ?></li>
          <li><?php print t('See decisions/resolutions with details'); ?></li>
          <li><?php print t('Study map coverage and membership'); ?></li>
        </ul>
      </div><!-- .col-md-4 -->
      <div class="col-md-8">
        <h3><?php print t('Topics'); ?></h3>
        <ul class="list-inline text-muted">
          <li><?php print l(t('Biological Diversity'), 'treaties', array('fragment' => t('Biological Diversity'))); ?></li>
          <li>&middot;</li>
          <li><?php print l(t('Chemicals and Waste Management'), 'treaties', array('fragment' => t('Chemicals and Waste Management'))); ?></li>
          <li>&middot;</li>
          <li><?php print l(t('Climate, Atmosphere and Deserts'), 'treaties', array('fragment' => t('Climate, Atmosphere and Deserts'))); ?></li>
        </ul><!-- .list-inline .text-muted -->
        <h3><?php print t('Regions'); ?></h3>
        <ul class="list-inline text-muted">
          <li><?php print l(t('Global'), 'treaties', array('fragment' => t('Global'))); ?></li>
          <li>&middot;</li>
          <li><?php print l(t('Africa'), 'treaties', array('fragment' => t('Africa'))); ?></li>
          <li>&middot;</li>
          <li><?php print l(t('Asia and the Pacific'), 'treaties', array('fragment' => t('Asia and the Pacific'))); ?></li>
          <li>&middot;</li>
          <li><?php print l(t('Europe'), 'treaties', array('fragment' => t('Europe'))); ?></li>
          <li>&middot;</li>
          <li><?php print l(t('Latin America and the Caribbean'), 'treaties', array('fragment' => t('Latin America and the Caribbean'))); ?></li>
          <li>&middot;</li>
          <li><?php print l(t('North America'), 'treaties', array('fragment' => t('North America'))); ?></li>
          <li>&middot;</li>
          <li><?php print l(t('West Asia'), 'treaties', array('fragment' => t('West Asia'))); ?></li>
        </ul><!-- .list-inline .text-muted -->
        <p><?php print l(t('Browse all treaties'), 'treaties'); ?></p>
      </div><!-- .col-md-8 -->
    </div><!-- .row -->
  </div><!-- .well -->
  <div class="row">
    <div class="col-md-4 text-center">
      <h2><?php print t('Glossary'); ?></h2>
      <p><img src="<?php print $directory; ?>/img/glossary.gif" alt=""></p>
      <p><?php print t('Find the definition of any term related to MEAs as well as all of it&amp;s occurences on this website.'); ?></p>
      <p><?php print l(t('Start searching for definitions'), 'terms'); ?></p>
    </div><!-- .col-md-4 -->
    <div class="col-md-4 text-center">
      <h2><?php print t('Countries'); ?></h2>
      <div class="country-selector">
        <p><img src="<?php print $directory; ?>/img/countries.gif" alt=""></p>
        <form role="form">
          <select class="form-control input-sm">
            <option value=""><?php print t('Select a country&hellip;'); ?></option>
            <?php foreach ($countries as $iso2 => $country): ?>
              <option value="<?php print $iso2; ?>"><?php print $country; ?></option>
            <?php endforeach; ?>
          </select><!-- .form-control .input-sm -->
        </form>
      </div><!-- .country-selector -->
      <p><?php print t('Research MEA related information on a certain country - Membership, Focal Points, National Plans and more.'); ?></p>
      <p><?php print l(t('See all countries'), 'countries'); ?></p>
    </div><!-- .col-md-4 -->
    <div class="col-md-4 text-center">
      <h2><?php print t('Events'); ?></h2>
      <p><img src="<?php print $directory; ?>/img/events.gif" alt=""></p>
      <p><?php print t('Upcoming or past events, MEA news.'); ?></p>
      <p><?php print l(t('See all events'), 'meetings'); ?></p>
    </div><!-- .col-md-4 -->
  </div><!-- .row -->
</div><!-- .container -->
<footer class="footer">
  <div class="container">
    <?php if (!empty($page['footer'])): ?>
      <div class="footer-section">
        <?php print render($page['footer']); ?>
      </div><!-- .footer-section -->
    <?php endif; ?>
    <div class="footer-section">
      <h5 class="text-uppercase"><?php print t('Organizations'); ?></h5>
      <ul class="list-inline">
        <li>
          <a class="logo logo-un" href="http://www.un.org/" target="_blank">
            <div class="image"></div>
            <?php print t('UN'); ?>
          </a><!-- .logo .logo-un -->
        </li>
        <li>
          <a class="logo logo-unep" href="http://www.unep.org/" target="_blank">
            <div class="image"></div>
            <?php print t('UNEP'); ?>
          </a><!-- .logo .logo-un -->
        </li>
        <li>
          <a class="logo logo-fao" href="http://www.fao.org/" target="_blank">
            <div class="image"></div>
            <?php print t('FAO'); ?>
          </a><!-- .logo .logo-un -->
        </li>
        <li>
          <a class="logo logo-unesco" href="http://www.unesco.org/" target="_blank">
            <div class="image"></div>
            <?php print t('UNESCO'); ?>
          </a><!-- .logo .logo-un -->
        </li>
        <li>
          <a class="logo logo-unece" href="http://www.unece.org/" target="_blank">
            <div class="image"></div>
            <?php print t('UNECE'); ?>
          </a><!-- .logo .logo-un -->
        </li>
      </ul><!-- .list-inline -->
    </div><!-- .footer-section -->
    <div class="footer-section">
      <h5 class="text-uppercase"><?php print t('Global treaties'); ?></h5>
      <ul class="list-inline">
        <li>
          <a class="logo logo-unfccc" href="http://unfccc.int/" target="_blank">
            <div class="image"></div>
            <?php print t('UNFCCC'); ?>
          </a><!-- .logo .logo-unfccc -->
        </li>
        <li>
          <a class="logo logo-unccd" href="http://www.unccd.int/" target="_blank">
            <div class="image"></div>
            <?php print t('UNCCD'); ?>
          </a><!-- .logo .logo-unccd -->
        </li>
        <li>
          <a class="logo logo-ozone" href="http://ozone.unep.org/" target="_blank">
            <div class="image"></div>
            <?php print t('OZONE'); ?>
          </a><!-- .logo .logo-ozone -->
        </li>
        <li>
          <a class="logo logo-basel" href="http://www.basel.int/" target="_blank">
            <div class="image"></div>
            <?php print t('BASEL'); ?>
          </a><!-- .logo .logo-basel -->
        </li>
        <li>
          <a class="logo logo-rotterdam" href="http://www.pic.int/" target="_blank">
            <div class="image"></div>
            <?php print t('ROTTERDAM'); ?>
          </a><!-- .logo .logo-rotterdam -->
        </li>
        <li>
          <a class="logo logo-stockholm" href="http://chm.pops.int/" target="_blank">
            <div class="image"></div>
            <?php print t('STOCKHOLM'); ?>
          </a><!-- .logo .logo-stockholm -->
        </li>
        <li>
          <a class="logo logo-cbd" href="http://www.cbd.int/" target="_blank">
            <div class="image"></div>
            <?php print t('CBD'); ?>
          </a><!-- .logo .logo-cbd -->
        </li>
        <li>
          <a class="logo logo-cites" href="http://www.cites.org/" target="_blank">
            <div class="image"></div>
            <?php print t('CITES'); ?>
          </a><!-- .logo .logo-cites -->
        </li>
        <li>
          <a class="logo logo-whc" href="http://whc.unesco.org/" target="_blank">
            <div class="image"></div>
            <?php print t('WHC'); ?>
          </a><!-- .logo .logo-whc -->
        </li>
        <li>
          <a class="logo logo-ramsar" href="http://www.ramsar.org/" target="_blank">
            <div class="image"></div>
            <?php print t('Ramsar'); ?>
          </a><!-- .logo .logo-ramsar -->
        </li>
        <li>
          <a class="logo logo-itpgrfa" href="http://www.planttreaty.org/" target="_blank">
            <div class="image"></div>
            <?php print t('ITPGRFA'); ?>
          </a><!-- .logo .logo-itpgrfa -->
        </li>
        <li>
          <a class="logo logo-cms" href="http://www.cms.int/" target="_blank">
            <div class="image"></div>
            <?php print t('CMS'); ?>
          </a><!-- .logo .logo-cms -->
        </li>
      </ul><!-- .list-inline -->
    </div><!-- .footer-section -->
    <div class="footer-section">
      <h5 class="text-uppercase"><?php print t('Regional treaties'); ?></h5>
      <div class="row">
        <div class="col-md-3">
          <h6><?php print t('UNECE'); ?></h6>
          <ul class="list-unstyled">
            <li><?php print l(t('Aarhus Convention'), 'http://www.unece.org/env/pp/welcome.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Espoo Convention'), 'http://www.unece.org/env/eia/welcome.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Long-Renage Transboundary Air Pollution'), 'http://www.unece.org/env/lrtap/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('The Kyiv Protocol'), 'http://www.unece.org/env/eia/sea_protocol.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Protocol on Water and Health'), 'http://www.unece.org/?id=2975', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Water Convention'), 'http://www.unece.org/env/water/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Kiev Protocol'), 'http://www.unece.org/env/pp/prtr.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Industrial Accidents Convention'), 'http://www.unece.org/env/teia.html', array('attributes' => array('target' => '_blank'))); ?></li>
          </ul><!-- .list-unstyled -->
        </div><!-- .col-md-3 -->
        <div class="col-md-3">
          <h6><?php print t('CMS'); ?></h6>
          <ul class="list-unstyled">
            <li><?php print l(t('ACCOBAMS'), 'http://www.accobams.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('AEWA'), 'http://www.unep-aewa.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('ASCOBANS'), 'http://www.ascobans.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('EUROBATS'), 'http://www.eurobats.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li class="divider"></li>
            <li><?php print l(t('ACAP'), 'http://www.the-acap.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('International Gorilla Conservation Programme'), 'http://www.igcp.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('WADDEN SEA SEALS'), 'http://www.waddensea-secretariat.org/', array('attributes' => array('target' => '_blank'))); ?></li>
          </ul><!-- .list-unstyled -->
        </div><!-- .col-md-3 -->
        <div class="col-md-3">
          <h6><?php print t('Regional Seas'); ?></h6>
          <ul class="list-unstyled">
            <li><?php print l(t('Abidjan Convention'), 'http://abidjanconvention.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Antigua Convention'), 'http://www.iattc.org/IATTCdocumentationENG.htm', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Apia Convention'), 'http://www.sprep.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Barcelona Convention'), 'http://www.unep.ch/regionalseas/regions/med/t_barcel.htm', array('attributes' => array('target' => '_blank'))); ?></li>
            <li class="divider"></li>
            <li><?php print l(t('Jeddah Convention'), 'http://www.unep.ch/regionalseas/main/persga/redconv.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Nairobi Convention'), 'http://www.unep.org/nairobiconvention/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Noumea Convention'), 'http://www2.unitar.org/cwm/publications/cbl/synergy/cat1_agree/noumea.htm', array('attributes' => array('target' => '_blank'))); ?></li>
          </ul><!-- .list-unstyled -->
        </div><!-- .col-md-3 -->
        <div class="col-md-3">
          <h6><?php print t('Regional Treaties'); ?></h6>
          <ul class="list-unstyled">
            <li><?php print l(t('Bamako Convention'), 'http://www.opcw.org/chemical-weapons-convention/related-international-agreements/toxic-chemicals-and-the-environment/bamako-convention/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Lusaka Agreement'), 'http://www.lusakaagreement.org/', array('attributes' => array('target' => '_blank'))); ?></li>
          </ul><!-- .list-unstyled -->
        </div><!-- .col-md-3 -->
      </div><!-- .row -->
    </div><!-- .footer-section -->
    <div class="footer-section">
      <p><?php print t('<a href="@url">Terms and conditions</a> &dash; Portions Copyright &copy; United Nations, FAO, UNEP, UNESCO', array('@url' => url('disclaimer'))); ?></p>
    </div><!-- .footer-section -->
  </div><!-- .container -->
</footer><!-- .footer -->
