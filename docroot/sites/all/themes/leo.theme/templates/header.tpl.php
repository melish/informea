<?php
/**
 * @file
 * header.tpl.php
 */
?>
<header role="banner">
  <div id="nav-header" class="clearfix" role="navigation">
    <ul class="list-inline list-languages">
      <li><?php print l(t('العربية'), 'arabic'); ?></li>
      <li><?php print l(t('中文'), 'chinese'); ?></li>
      <li><?php print l(t('English'), '<front>'); ?></li>
      <li><?php print l(t('Français'), 'french'); ?></li>
      <li><?php print l(t('Pусский'), 'russian'); ?></li>
      <li><?php print l(t('Español'), 'spanish'); ?></li>
    </ul><!-- .list-inline .list-languages -->
    <ul class="list-inline list-quicklinks">
      <li><?php print l(t('About'), 'about'); ?></li>
      <li><?php print l(t('Calendar'), 'ecalendar'); ?></li>
      <li><?php print l(t('Multimedia'), 'newscentre/multimedia'); ?></li>
      <li><?php print l(t('News'), 'newscentre'); ?></li>
      <li><?php print l(t('Outreach'), 'outreach'); ?></li>
      <li><?php print l(t('Publications'), 'publications'); ?></li>
      <li><?php print l(t('Vacancies'), 'vacancies'); ?></li>
    </ul><!-- .list-inline .list-quicklinks -->
  </div><!-- #nav-header .clearfix -->
  <nav class="navbar navbar-default navbar-unep" role="navigation">
    <div class="container-fluid">
      <div class="navbar-header">
        <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar-collapse-unep">
          <span class="sr-only">Toggle navigation</span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
        </button><!-- .navbar-toggle .collapsed -->
        <?php if ($logo): ?>
          <a class="navbar-brand" href="<?php print $front_page; ?>">
            <img src="<?php print $logo; ?>" alt="<?php print t('UNEP'); ?>">
          </a><!-- .navbar-brand -->
        <?php endif; ?>
        <?php if (!empty($site_name) || !empty($site_slogan)): ?>
          <p class="navbar-text">
            <?php if (!empty($site_name)): ?>
              <strong><?php print $site_name; ?></strong>
            <?php endif; ?>
            <?php if (!empty($site_slogan)): ?>
              <br><?php print $site_slogan; ?>
            <?php endif; ?>
          </p><!-- .navbar-text -->
        <?php endif; ?>
      </div><!-- .navbar-header -->
      <div id="navbar-collapse-unep" class="collapse navbar-collapse">
        <form class="navbar-form navbar-right" action="http://www.unep.org/search.asp" target="_blank" role="search">
          <div class="input-group input-group-sm">
            <input type="text" class="form-control" placeholder="Search">
            <span class="input-group-btn">
              <button type="submit" class="btn btn-default">
                <span class="glyphicon glyphicon-search"></span>
              </button><!-- .btn .btn-default -->
            </span><!-- .input-group-btn -->
          </div><!-- .input-group .input-group-sm -->
        </form><!-- .navbar-form .navbar-right -->
        <ul class="nav navbar-nav navbar-right">
          <li>
            <a href="#">
              <span class="navicon navicon-cc"></span>
              <?php print t('Climate Change'); ?>
            </a>
          </li>
          <li>
            <a href="#">
              <span class="navicon navicon-dnc"></span>
              <?php print t('Disasters &amp; Conflicts'); ?>
            </a>
          </li>
          <li>
            <a href="#">
              <span class="navicon navicon-em"></span>
              <?php print t('Ecosystem Management'); ?>
            </a>
          </li>
          <li>
            <a href="#">
              <span class="navicon navicon-eg"></span>
              <?php print t('Environmental Governance'); ?>
            </a>
          </li>
          <li>
            <a href="#">
              <span class="navicon navicon-cnw"></span>
              <?php print t('Chemicals &amp; Waste'); ?>
            </a>
          </li>
          <li>
            <a href="#">
              <span class="navicon navicon-re"></span>
              <?php print t('Resource Efficiency'); ?>
            </a>
          </li>
          <li>
            <a href="#">
              <span class="navicon navicon-eur"></span>
              <?php print t('Environment Under Review'); ?>
            </a>
          </li>
        </ul><!-- .nav .navbar-nav .navbar-right -->
      </div><!-- #navbar-collapse-unep .collapse .navbar-collapse -->
    </div><!-- .container-fluid -->
  </nav><!-- .navbar .navbar-default .navbar-unep -->
  <nav class="navbar navbar-default navbar-leo" role="navigation">
    <div class="container-fluid">
      <div class="navbar-header">
        <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar-collapse-leo">
          <span class="sr-only">Toggle navigation</span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
        </button><!-- .navbar-toggle .collapsed -->
        <?php if ($logo): ?>
          <a class="navbar-brand" href="<?php print $front_page; ?>">
            <?php print theme('image', array('path' => $directory . '/img/logo-leo.png', 'alt' => t('LEO'))); ?>
          </a><!-- .navbar-brand -->
        <?php endif; ?>
        <p class="navbar-text">
          <?php print t('Law &amp; Environment Outlook'); ?>
        </p><!-- .navbar-text -->
      </div><!-- .navbar-header -->
      <div id="navbar-collapse-leo" class="collapse navbar-collapse">
        <ul class="nav navbar-nav navbar-right">
          <li><a href="/search?f[0]=type%3Alegislation"><?php print('Legislation'); ?></a></li>
          <li><a href="/search?f[0]=type%3Atreaty"><?php print('Treaties'); ?></a></li>
          <li><a href="/search?f[0]=type%3Acountry"><?php print('Countries'); ?></a></li>
          <li><a href="/terms"><?php print('Terms'); ?></a></li>
          <li>
            <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false">
              <?php print('Goals'); ?>
              <span class="caret"></span>
            </a><!-- .dropdown-toggle -->
            <ul class="dropdown-menu" role="menu">
              <li><a href="/search?f[0]=type%3Agoal"><?php print('All goals'); ?></a></li>
              <li><a href="/goals/aichi-targets">Aichi targets</a></li>
            </ul><!-- .dropdown-menu -->

          </li>
          <li><a href="/search?f[0]=type%3Aliterature"><?php print('Publications'); ?></a></li>
          <li class="dropdown">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false">
              <?php print('More'); ?>
              <span class="caret"></span>
            </a><!-- .dropdown-toggle -->
            <ul class="dropdown-menu" role="menu">
              <li><a href="#">Action</a></li>
              <li><a href="#">Another action</a></li>
              <li><a href="#">Something else here</a></li>
              <li class="divider"></li>
              <li><a href="#">Separated link</a></li>
            </ul><!-- .dropdown-menu -->
          </li><!-- .dropdown -->
        </ul><!-- .nav .navbar-nav .navbar-right -->
        <form class="navbar-form navbar-right" action="/search" role="search">
          <div class="input-group input-group-sm">
            <input type="text" class="form-control" placeholder="Search" name="search_api_views_fulltext">
            <span class="input-group-btn">
              <button type="submit" class="btn btn-default">
                <span class="glyphicon glyphicon-search"></span>
              </button><!-- .btn .btn-default -->
            </span><!-- .input-group-btn -->
          </div><!-- .input-group .input-group-sm -->
        </form><!-- .navbar-form .navbar-right -->
      </div><!-- #navbar-collapse-leo .collapse .navbar-collapse -->
    </div><!-- .container-fluid -->
  </nav><!-- .navbar .navbar-default .navbar-leo -->
</header>
