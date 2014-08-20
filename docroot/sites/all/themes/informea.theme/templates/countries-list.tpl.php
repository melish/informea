<ul class="nav nav-pills">
  <li class="active"><a data-filter="index" data-target="#index" href="#"><?php print t('All'); ?></a></li>
  <?php foreach (array_keys($index) as $key): ?>
    <li><a data-filter="index" data-target="#index" href="#<?php print $key; ?>"><?php print $key; ?></a></li>
  <?php endforeach; ?>
</ul><!-- .nav .nav-pills -->
<div id="index">
  <?php foreach ($index as $key => $countries): ?>
    <div id="<?php print $key ?>" class="country-group">
      <h2 class="page-header"><?php print $key; ?></h2>
      <div class="row">
        <?php foreach ($countries as $iso2 => $name): ?>
          <div class="col-xs-6 col-sm-4 col-md-3 col-lg-2">
            <a href="#" class="country">
              <img src="/<?php print $directory; ?>/img/flags/flag-<?php print strtolower($iso2); ?>-sm.png" alt="<?php print $name; ?>">
              <div class="country-name">
                <?php print $name; ?>
              </div><!-- .country-name -->
            </a><!-- .country -->
          </div><!-- .col-xs-6 .col-sm-4 .col-md-3 .col-lg-2 -->
        <?php endforeach; ?>
      </div><!-- .row -->
    </div><!-- .country-group -->
  <?php endforeach; ?>
</div><!-- .index -->
