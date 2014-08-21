<ul class="nav nav-pills">
  <li class="active"><?php print l(t('All'), NULL, array('attributes' => array('data-filter' => 'country', 'data-target' => '#index'), 'fragment' => FALSE, 'external' => TRUE)); ?></li>
  <?php foreach (array_keys($index) as $key): ?>
    <li><?php print l($key, NULL, array('attributes' => array('data-filter' => 'country', 'data-target' => '#index'), 'fragment' => $key, 'external' => TRUE)); ?></li>
  <?php endforeach; ?>
</ul><!-- .nav .nav-pills -->
<div id="index">
  <?php foreach ($index as $key => $countries): ?>
    <div id="<?php print $key ?>" class="country-group">
      <div class="page-header">
        <h2><?php print $key; ?></h2>
      </div><!-- .page-header -->
      <div class="row">
        <?php foreach ($countries as $iso2 => $name): ?>
          <div class="col-xs-6 col-sm-4 col-md-3 col-lg-2">
            <?php
            print l(theme('image', array(
              'path' => $directory . '/img/flags/flag-' . strtolower($iso2) . '-sm.png',
              'width' => 32,
              'height' => 32,
              'alt' => $name
            )) . '<div class="country-name">' . $name . '</div>', 'countries/' . $iso2, array(
              'attributes' => array('class' => 'country', 'title' => $name),
              'html' => TRUE
            ));
            ?>
          </div><!-- .col-xs-6 .col-sm-4 .col-md-3 .col-lg-2 -->
        <?php endforeach; ?>
      </div><!-- .row -->
    </div><!-- .country-group -->
  <?php endforeach; ?>
</div><!-- .index -->
