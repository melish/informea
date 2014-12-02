<?php
/**
 * @file
 * header.tpl.php
 */
?>
<header role="banner">
  <div id="header-nav" class="clearfix">
    <ul id="header-languages" class="list-inline">
      <li><?php print l(t('العربية'), 'arabic'); ?></li>
      <li><?php print l(t('中文'), 'chinese'); ?></li>
      <li><?php print l(t('English'), '<front>'); ?></li>
      <li><?php print l(t('Français'), 'french'); ?></li>
      <li><?php print l(t('Pусский'), 'russian'); ?></li>
      <li><?php print l(t('Español'), 'spanish'); ?></li>
    </ul><!-- #header-languages .list-inline -->
    <ul id="header-links" class="list-inline">
      <li><?php print l(t('About'), 'about'); ?></li>
      <li><?php print l(t('Calendar'), 'ecalendar'); ?></li>
      <li><?php print l(t('Multimedia'), 'newscentre/multimedia'); ?></li>
      <li><?php print l(t('News'), 'newscentre'); ?></li>
      <li><?php print l(t('Outreach'), 'outreach'); ?></li>
      <li><?php print l(t('Publications'), 'publications'); ?></li>
      <li><?php print l(t('Vacancies'), 'vacancies'); ?></li>
    </ul><!-- #header-links .list-inline -->
  </div><!-- #header-nav .clearfix -->
  <div id="header-unep" class="clearfix">
    <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" class="header-logo" title="<?php print t('UNEP'); ?>">
        <img src="<?php print $logo; ?>" alt="<?php print t('UNEP'); ?>">
      </a><!-- .header-logo -->
    <?php endif; ?>
    <?php if (!empty($site_name) || !empty($site_slogan)): ?>
      <div class="header-info">
        <?php if (!empty($site_name)): ?>
          <strong><?php print $site_name; ?></strong>
        <?php endif; ?>
        <?php if (!empty($site_slogan)): ?>
          <br><?php print $site_slogan; ?>
        <?php endif; ?>
      </div><!-- .header-info -->
    <?php endif; ?>
    <ul class="list-inline pull-right">
      <li>
        <a href="#">
          <span class="icon icon-cc"></span>
          <br>
          Climate<br>Change
        </a>
      </li>
      <li>
        <a href="#">
          <span class="icon icon-dnc"></span>
          <br>
          Disasters<br>&amp; Conflicts
        </a>
      </li>
      <li>
        <a href="#">
          <span class="icon icon-em"></span>
          <br>
          Ecosystem<br>Management
        </a>
      </li>
      <li>
        <a href="#">
          <span class="icon icon-eg"></span>
          <br>
          Environmental<br>Governance
        </a>
      </li>
      <li>
        <a href="#">
          <span class="icon icon-hs"></span>
          <br>
          Chemicals<br>&amp; Waste
        </a>
      </li>
      <li>
        <a href="#">
          <span class="icon icon-re"></span>
          <br>
          Resource<br>Efficiency
        </a>
      </li>
      <li>
        <a href="#">
          <span class="icon icon-eur"></span>
          <br>
          Environment<br>Under Review
        </a>
      </li>
    </ul><!-- .list-inline .pull-right -->
  </div><!-- #header-unep .clearfix -->
  <div id="header-leo" class="clearfix">
    <a href="<?php print $front_page; ?>" class="header-logo" title="<?php print t('UNEP'); ?>">
      <img src="<?php print $directory; ?>/img/logo-leo.png" alt="<?php print t('LEO'); ?>">
    </a><!-- .header-logo -->
    <div class="header-info">
      <?php print t('Law &amp; Environment Outlook'); ?>
    </div><!-- .header-info -->
    <div id="toolbar-leo">
      <ul class="nav nav-pills">
        <li role="presentation" class="active"><a href="#"><?php print('Legislation'); ?></a></li>
        <li role="presentation"><a href="#"><?php print('Treaties'); ?></a></li>
        <li role="presentation"><a href="#"><?php print('Countries'); ?></a></li>
        <li role="presentation"><a href="#"><?php print('Terms'); ?></a></li>
        <li role="presentation"><a href="#"><?php print('Goals'); ?></a></li>
        <li role="presentation"><a href="#"><?php print('Publications'); ?></a></li>
      </ul><!-- .nav .nav-pills -->
    </div><!-- #toolbar-leo -->
  </div><!-- #header-leo .clearfix -->
</header>
