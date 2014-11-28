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
  </div><!-- .container -->
</header>
