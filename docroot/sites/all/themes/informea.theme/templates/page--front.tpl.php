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
    <div class="broadcast">
      <div class="broadcast-body">
        <p>
          <em><?php print t('The new InforMEA learning platform is now live!'); ?></em>
          <?php print l(t('Start learning'), 'http://e-learning.informea.org/', array('attributes' => array('class' => array('btn', 'btn-outline')), 'external' => TRUE)); ?>
        </p>
      </div><!-- .broadcast-body -->
    </div><!-- .broadcast -->
    <div class="row">
      <div class="col-md-6">
        <?php if (!empty($site_slogan)): ?>
          <p class="lead"><?php print $site_slogan; ?></p>
        <?php endif; ?>
        <p><?php print t('InforMEA harvests COP decisions, news, meetings, membership, national focal points and reports from MEAs. Information is organised by terms from MEA COP agendas.'); ?></p>
        <p><?php print t('InforMEA is a project of the MEA Information and Knowledge Management (IKM) Initiative with the support from the United Nations Environment Programme (UNEP).'); ?></p>
        <p><?php print l(t('Learn more about InforMEA') . ' <span class="glyphicon glyphicon-arrow-right"></span>', 'about', array('html' => TRUE)); ?></p>
      </div><!-- .col-md-6 -->
      <div class="col-md-6">
        todo: carousel
      </div><!-- .col-md-6 -->
    </div><!-- .row -->
  </div><!-- .container -->
</div><!-- .hero-unit -->
<div class="container">
  <div class="row" id="row-features">
    <div class="col-md-4" id="col-terms">
      <div class="well well-transparent well-hover text-center">
        <h3><?php print t('Glossary'); ?></h3>
        <p><?php print theme('image', array('path' => $directory . '/img/glossary.gif', 'attributes' => array('class' => array('img-responsive', 'center-block')))); ?></p>
        <p class="description"><?php print t('Browse the MEA unified glossary of terms to see tagged information across multiple MEAs.'); ?></p>
        <p><?php print l(t('Open the glossary'), 'terms'); ?></p>
      </div><!-- .well .text-center -->
    </div><!-- .col-md-4 #terms -->
    <div class="col-md-4" id="col-treaties">
      <div class="well well-hover text-center">
        <h3><?php print t('Treaties'); ?></h3>
        <p class="description"><?php print t('Browse more than 50 global and regional &ndash; environmental related treaties. Read texts, decisions, consult the list of parties and focal points. Print nice reports about treaties with geographical coverage maps and figures.'); ?></p>
        <ul class="list-inline regions">
          <li><strong><?php print t('Regions:'); ?></strong></li>
          <li><?php print l(t('Global'), 'treaties', array('fragment' => t('Global'))); ?></li>
          <li><?php print l(t('Africa'), 'treaties', array('fragment' => t('Africa'))); ?></li>
          <li><?php print l(t('Asia and the Pacific'), 'treaties', array('fragment' => t('Asia and the Pacific'))); ?></li>
          <li><?php print l(t('Europe'), 'treaties', array('fragment' => t('Europe'))); ?></li>
          <li><?php print l(t('Latin America and the Caribbean'), 'treaties', array('fragment' => t('Latin America and the Caribbean'))); ?></li>
          <li><?php print l(t('North America'), 'treaties', array('fragment' => t('North America'))); ?></li>
          <li><?php print l(t('West Asia'), 'treaties', array('fragment' => t('West Asia'))); ?></li>
        </ul><!-- .list-inline .regions -->
        <p><?php print l(t('Browse all treaties'), 'treaties'); ?></p>
      </div><!-- .well .text-center -->
    </div><!-- .col-md-4 #col-treaties -->
    <div class="col-md-4" id="col-countries">
      <div class="well well-transparent well-hover text-center">
        <h3><?php print t('Countries'); ?></h3>
        <div class="country-selector">
          <p><?php print theme('image', array('path' => $directory . '/img/countries.gif', 'attributes' => array('class' =>  array('img-responsive', 'center-block')))); ?></p>
          <form role="form">
            <select class="form-control input-sm">
              <option value=""><?php print t('Select a country&hellip;'); ?></option>
              <?php foreach ($countries as $iso2 => $country): ?>
                <option value="<?php print $iso2; ?>"><?php print $country; ?></option>
              <?php endforeach; ?>
            </select><!-- .form-control .input-sm -->
          </form>
        </div><!-- .country-selector -->
        <p class="description"><?php print t('Visualise MEA related information into geographical context. Countries that are parties to treaties and protocols have focal points, national reports and action plans.'); ?></p>
        <p><?php print l(t('See all countries'), 'countries'); ?></p>
      </div><!-- .well .text-center -->
    </div><!-- .col-md-4 #col-countries -->
  </div><!-- .row #row-features -->
</div><!-- .container -->
<?php include 'footer.tpl.php'; ?>
