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
<?php include 'header.tpl.php'; ?>
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
  <div class="page-header">
    <h1><?php print t('InforMEA features'); ?></h1>
  </div><!-- .page-header -->
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
      <p><?php print theme('image', array('path' => $directory . '/img/glossary.gif', 'width' => 300, 'height' => 148)); ?></p>
      <p><?php print t('Find the definition of any term related to MEAs as well as all of it&amp;s occurences on this website.'); ?></p>
      <p><?php print l(t('Start searching for definitions'), 'terms'); ?></p>
    </div><!-- .col-md-4 -->
    <div class="col-md-4 text-center">
      <h2><?php print t('Countries'); ?></h2>
      <div class="country-selector">
        <p><?php print theme('image', array('path' => $directory . '/img/countries.gif', 'width' => 300, 'height' => 148)); ?></p>
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
      <p><?php print theme('image', array('path' => $directory . '/img/events.gif', 'width' => 175, 'height' => 150)); ?></p>
      <p><?php print t('Upcoming or past events, MEA news.'); ?></p>
      <p><?php print l(t('See all events'), 'meetings'); ?></p>
    </div><!-- .col-md-4 -->
  </div><!-- .row -->
</div><!-- .container -->
<?php include 'footer.tpl.php'; ?>
