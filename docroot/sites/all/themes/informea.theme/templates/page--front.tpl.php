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
      <div class="col-md-6" id="col-about">
        <?php if (!empty($site_slogan)): ?>
          <p class="lead"><?php print $site_slogan; ?></p>
        <?php endif; ?>
        <p><?php print t('InforMEA harvests COP decisions, news, meetings, membership, national focal points and reports from MEAs. Information is organised by terms from MEA COP agendas.'); ?></p>
        <p><?php print t('InforMEA is a project of the MEA Information and Knowledge Management (IKM) Initiative with the support from the United Nations Environment Programme (UNEP).'); ?></p>
        <p><?php print l(t('Learn more about InforMEA') . ' <span class="glyphicon glyphicon-arrow-right"></span>', 'about', array('html' => TRUE)); ?></p>
      </div><!-- .col-md-6 #col-about -->
      <div class="col-md-6" id="col-carousel">
        <div class="carousel-container">
          <div class="carousel slide" data-ride="carousel" id="carousel-updates">
            <ol class="carousel-indicators">
              <li class="active" data-target="#carousel-updates" data-slide-to="0"></li>
              <li data-target="#carousel-updates" data-slide-to="1"></li>
              <li data-target="#carousel-updates" data-slide-to="2"></li>
              <li data-target="#carousel-updates" data-slide-to="3"></li>
              <li data-target="#carousel-updates" data-slide-to="4"></li>
              <li data-target="#carousel-updates" data-slide-to="5"></li>
              <li data-target="#carousel-updates" data-slide-to="6"></li>
            </ol><!-- .carousel-indicators -->
            <div class="carousel-inner">
              <div class="item active">
                <img alt="" src="http://www.informea.org/wp-content/uploads/images/syndication/biological-diversity/guillemot-uria-aalge.jpg">
                <div class="carousel-caption">
                  <div class="media">
                    <div class="media-left">
                      <a href="http://www.informea.org/treaties/cbd">
                        <img alt="CBD" src="http://www.informea.org/wp-content/uploads/images/treaty/logo_cbd.png">
                      </a>
                    </div><!-- .media-left -->
                    <div class="media-body">
                      <span>27 Oct, 2014</span>
                      <p><a href="http://www.cbd.int/doc/press/2014/pr-2014-10-17-CPW-en.pdf">Recognizing that wildlife is an important renewable natural resource, with ...</a></p>
                    </div><!-- .media-body -->
                  </div><!-- .media -->
                </div><!-- .carousel-caption -->
              </div><!-- .item .active -->
              <div class="item">
                <img alt="" src="http://www.informea.org/wp-content/uploads/images/syndication/chemicals-waste/icebergs.jpg">
                <div class="carousel-caption">
                  <div class="media">
                    <div class="media-left">
                      <a href="http://www.informea.org/treaties/basel">
                        <img alt="Basel Convention" src="http://www.informea.org/wp-content/uploads/images/treaty/logo_basel.png">
                      </a>
                    </div><!-- .media-left -->
                    <div class="media-body">
                      <span>16 Oct, 2014</span>
                      <p><a href="http://www.basel.int/Implementation/PublicAwareness/NewsFeatures/RepublicofCongoratifiestheBanAmendment/tabid/4165/Default.aspx">Republic of Congo ratifies the Ban Amendment</a></p>
                    </div><!-- .media-body -->
                  </div><!-- .media -->
                </div><!-- .carousel-caption -->
              </div><!-- .item -->
              <div class="item">
                <img alt="" src="http://www.informea.org/wp-content/uploads/images/syndication/financing-trade/international.jpg">
                <div class="carousel-caption">
                  <div class="media">
                    <div class="media-body">
                      <span>29 Oct, 2014</span>
                      <p><a href="http://www.thegef.org/gef/node/10927">Women, key partners in promoting biodiversity and environmental farming practices</a></p>
                    </div><!-- .media-body -->
                  </div><!-- .media -->
                </div><!-- .carousel-caption -->
              </div><!-- .item -->
              <div class="item">
                <img alt="" src="http://www.informea.org/wp-content/uploads/images/syndication/species/african-bush-elephants.jpg">
                <div class="carousel-caption">
                  <div class="media">
                    <div class="media-left">
                      <a href="http://www.informea.org/treaties/aewa">
                        <img alt="AEWA" src="http://www.informea.org/wp-content/uploads/images/treaty/logo_aewa.png">
                      </a>
                    </div><!-- .media-left -->
                    <div class="media-body">
                      <span>30 Oct, 2014</span>
                      <p><a href="http://www.unep-aewa.org/en/news/boost-waterbird-conservation-project-senegal-aewa-small-grants-fund">Boost for Waterbird Conservation Project in Senegal from AEWA Small ...</a></p>
                    </div><!-- .media-body -->
                  </div><!-- .media -->
                </div><!-- .carousel-caption -->
              </div><!-- .item -->
              <div class="item">
                <img alt="" src="http://www.informea.org/wp-content/uploads/images/syndication/species/slide-jaguar.jpg">
                <div class="carousel-caption">
                  <div class="media">
                    <div class="media-left">
                      <a href="http://www.informea.org/treaties/cbd">
                        <img alt="CBD" src="http://www.informea.org/wp-content/uploads/images/treaty/logo_cbd.png">
                      </a>
                    </div><!-- .media-left -->
                    <div class="media-body">
                      <span>02-03 Nov, 2014</span>
                      <p><a href="http://www.cms.int/node/4499">42nd Standing Committee Meeting</a></p>
                    </div><!-- .media-body -->
                  </div><!-- .media -->
                </div><!-- .carousel-caption -->
              </div><!-- .item -->
              <div class="item">
                <img alt="" src="http://www.informea.org/wp-content/uploads/images/syndication/species/slide-bird.jpg">
                <div class="carousel-caption">
                  <div class="media">
                    <div class="media-left">
                      <a href="http://www.informea.org/treaties/cbd">
                        <img alt="CBD" src="http://www.informea.org/wp-content/uploads/images/treaty/logo_cbd.png">
                      </a>
                    </div><!-- .media-left -->
                    <div class="media-body">
                      <span>04-09 Nov, 2014</span>
                      <p><a href="http://www.cms.int/node/4498">Eleventh Meeting of the Conference of the Parties to CMS</a></p>
                    </div><!-- .media-body -->
                  </div><!-- .media -->
                </div><!-- .carousel-caption -->
              </div><!-- .item -->
              <div class="item">
                <img alt="" src="http://www.informea.org/wp-content/uploads/images/syndication/species/rottumerplaat-dutch-wadden-sea.jpg">
                <div class="carousel-caption">
                  <div class="media">
                    <div class="media-left">
                      <a href="http://www.informea.org/treaties/cbd">
                        <img alt="CBD" src="http://www.informea.org/wp-content/uploads/images/treaty/logo_cbd.png">
                      </a>
                    </div><!-- .media-left -->
                    <div class="media-body">
                      <span>09-09 Nov, 2014</span>
                      <p><a href="http://www.cms.int/node/4500">43rd Standing Committee Meeting</a></p>
                    </div><!-- .media-body -->
                  </div><!-- .media -->
                </div><!-- .carousel-caption -->
              </div><!-- .item -->
            </div><!-- .carousel-inner -->
            <a class="left carousel-control" href="#carousel-updates" data-slide="prev" role="button">
              <i class="glyphicon glyphicon-chevron-left"></i>
            </a>
            <a class="right carousel-control" href="#carousel-updates" data-slide="next" role="button">
              <i class="glyphicon glyphicon-chevron-right"></i>
            </a>
          </div><!-- #carousel-updates .carousel .slide -->
        </div><!-- .carousel-container -->
      </div><!-- .col-md-6 #col-carousel -->
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
