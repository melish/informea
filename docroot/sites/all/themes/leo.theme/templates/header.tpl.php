<?php
/**
 * @file
 * header.tpl.php
 */
?>
<header role="banner">
  <div class="container">
    <div class="clearfix" id="header-list">
      <ul class="list-inline pull-left">
        <li><?php print l(t('About'), 'about'); ?></li>
        <li><?php print l(t('Calendar'), 'ecalendar'); ?></li>
        <li><?php print l(t('Multimedia'), 'newscentre/multimedia'); ?></li>
        <li><?php print l(t('News'), 'newscentre'); ?></li>
        <li><?php print l(t('Outreach'), 'outreach'); ?></li>
        <li><?php print l(t('Publications'), 'publications'); ?></li>
        <li><?php print l(t('Vacancies'), 'vacancies'); ?></li>
      </ul><!-- .list-inline .pull-left -->
      <ul class="list-inline pull-right">
        <li><?php print l(t('العربية'), 'arabic'); ?></li>
        <li><?php print l(t('中文'), 'chinese'); ?></li>
        <li><?php print l(t('English'), '<front>'); ?></li>
        <li><?php print l(t('Français'), 'french'); ?></li>
        <li><?php print l(t('Pусский'), 'russian'); ?></li>
        <li><?php print l(t('Español'), 'spanish'); ?></li>
      </ul><!-- .list-inline .pull-right -->
    </div><!-- .clearfix #header-list -->
    <div class="clearfix" id="header-banner">
      <ul class="list-inline pull-left">
        <li>
          <?php if ($logo): ?>
            <a class="" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </a><!--  -->
          <?php endif; ?>
        </li>
        <li>
          <strong>
            <?php if (!empty($site_name)): ?>
              <?php print $site_name; ?>
            <?php endif; ?>
          </strong>
          <br>
          <?php if (!empty($site_slogan)): ?>
            <?php print $site_slogan; ?>
          <?php endif; ?>
        </li>
      </ul><!-- .list-inline .pull-left -->
      <ul class="list-inline pull-right">
        <li>
          <a href="#">
            Climate<br>Change
          </a>
        </li>
        <li>
          <a href="#">
            Disasters<br>&amp; Conflicts
          </a>
        </li>
        <li>
          <a href="#">
            Ecosystem<br>Management
          </a>
        </li>
        <li>
          <a href="#">
            Environmental<br>Governance
          </a>
        </li>
        <li>
          <a href="#">
            Chemicals<br>&amp; Waste
          </a>
        </li>
        <li>
          <a href="#">
            Resource<br>Efficiency
          </a>
        </li>
        <li>
          <a href="#">
            Environment<br>Under Review
          </a>
        </li>
      </ul><!-- .list-inline .pull-right -->
    </div><!-- .clearfix #header-banner -->
  </div><!-- .container -->
</header>
