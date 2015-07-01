<?php
/**
 * @file
 * Default theme implementation to display the front page.
 *
 * All the available variables are mirrored in page.tpl.php.
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
    <?php if(!empty($page['front_page_announcements'])): ?>
    <div class="broadcast">
      <div class="broadcast-body">
      <?php print render($page['front_page_announcements']); ?>
      </div><!-- .broadcast-body -->
    </div><!-- .broadcast -->
    <?php endif; ?>
    <div class="row">
      <div class="col-md-6" id="col-about">
        <?php if (!empty($site_slogan)): ?>
          <p class="lead"><?php print $site_slogan; ?></p>
        <?php endif; ?>
        <p><?php print t('InforMEA harvests COP decisions, news, meetings, membership, national focal points and reports from MEAs. Information is organised by terms from MEA COP agendas.'); ?></p>
        <p><?php print t('InforMEA is a project of the MEA Information and Knowledge Management (IKM) Initiative with the support from the United Nations Environment Programme (UNEP).'); ?></p>
        <p><?php print l(t('Learn more about InforMEA') . ' <span class="glyphicon glyphicon-arrow-right"></span>', 'about', array('html' => TRUE)); ?></p>
      </div><!-- .col-md-6 #col-about -->
      <?php print informea_theme_slider(); ?>
    </div><!-- .row -->
  </div><!-- .container -->
</div><!-- .hero-unit -->
<div class="container">
  <?php if (!user_is_anonymous()) { print $messages; } ?>
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
          <li><strong><?php print t('Regions'); ?>:</strong></li>
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
