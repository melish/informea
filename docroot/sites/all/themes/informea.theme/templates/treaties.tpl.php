<?php
/**
 * @file
 * treaties.tpl.php
 *
 * @ingroup themeable
 */
?>
<h3 class="text-center medium"><?php print t('Global treaties and conventions'); ?></h3>
<div class="text-center">
  <div class="brand-group">
    <a class="brand brand-cbd" href="<?php print url('treaties/cbd'); ?>">
      <div class="image"></div>
      <?php print t('CBD'); ?>
    </a><!-- .brand .brand-cbd -->
    <a class="brand brand-cartagena" href="<?php print url('treaties/cartagena'); ?>">
      <div class="image"></div>
      <?php print t('Cartagena'); ?>
    </a><!-- .brand .brand-cartagena -->
    <a class="brand brand-nagoya" href="<?php print url('treaties/nagoya'); ?>">
      <div class="image"></div>
      <?php print t('Nagoya'); ?>
    </a><!-- .brand .brand-nagoya -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-cms" href="<?php print url('treaties/cms'); ?>">
      <div class="image"></div>
      <?php print t('CMS'); ?>
    </a><!-- .brand .brand-cms -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-cites" href="<?php print url('treaties/cites'); ?>">
      <div class="image"></div>
      <?php print t('CITES'); ?>
    </a><!-- .brand .brand-cites -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-plant-treaty" href="<?php print url('treaties/plant-treaty'); ?>">
      <div class="image"></div>
      <?php print t('Plant treaty'); ?>
    </a><!-- .brand .brand-plant-treaty -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-ramsar" href="<?php print url('treaties/ramsar'); ?>">
      <div class="image"></div>
      <?php print t('Ramsar'); ?>
    </a><!-- .brand .brand-ramsar -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-whc" href="<?php print url('treaties/whc'); ?>">
      <div class="image"></div>
      <?php print t('WHC'); ?>
    </a><!-- .brand .brand-whc -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-basel" href="<?php print url('treaties/basel'); ?>">
      <div class="image"></div>
      <?php print t('Basel'); ?>
    </a><!-- .brand .brand-basel -->
    <a class="brand brand-rotterdam" href="<?php print url('treaties/rotterdam'); ?>">
      <div class="image"></div>
      <?php print t('Rotterdam'); ?>
    </a><!-- .brand .brand-rotterdam -->
    <a class="brand brand-stockholm" href="<?php print url('treaties/stockholm'); ?>">
      <div class="image"></div>
      <?php print t('Stockholm'); ?>
    </a><!-- .brand .brand-stockholm -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-minamata" href="<?php print url('treaties/minamata'); ?>">
      <div class="image"></div>
      <?php print t('Minamata'); ?>
    </a><!-- .brand .brand-minamata -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-vienna" href="<?php print url('treaties/vienna'); ?>">
      <div class="image"></div>
      <?php print t('Vienna'); ?>
    </a><!-- .brand .brand-vienna -->
    <a class="brand brand-montreal" href="<?php print url('treaties/montreal'); ?>">
      <div class="image"></div>
      <?php print t('Montreal'); ?>
    </a><!-- .brand .brand-montreal -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-unccd" href="<?php print url('treaties/unccd'); ?>">
      <div class="image"></div>
      <?php print t('UNCCD'); ?>
    </a><!-- .brand .brand-unccd -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-unfccc" href="<?php print url('treaties/unfccc'); ?>">
      <div class="image"></div>
      <?php print t('UNFCCC'); ?>
    </a><!-- .brand .brand-unfccc -->
    <a class="brand brand-kyoto" href="<?php print url('treaties/kyoto'); ?>">
      <div class="image"></div>
      <?php print t('Kyoto'); ?>
    </a><!-- .brand .brand-kyoto -->
  </div><!-- .brand-group -->
</div><!-- .text-center -->
<div class="regional">
<h3 class="pull-right"><?php print t('All treaties'); ?></h3>
<table class="table table-bordered" id="table-treaties">
  <thead>
    <tr>
      <td colspan="2">
        <small class="text-muted">
          <?php
          $total = count($treaties);

          print t('Showing !visible of !total treaties', array('!visible' => '<strong class="rows-visible">' . $total . '</strong>', '!total' => '<strong>' . $total . '</strong>'));
          ?>
        </small><!-- .text-muted -->
      </td>
      <th class="dropdown text-center">
        <a class="text-nowrap" data-toggle="dropdown" href="#">
          <?php print t('Region'); ?>
          <span class="caret"></span>
        </a><!-- .text-nowrap -->
        <ul class="dropdown-menu dropdown-menu-right" role="menu">
          <li class="active"><?php print l(t('All regions'), NULL, array('attributes' => array('data-filter' => 'table', 'data-selector' => '.column-region', 'data-value' => NULL), 'fragment' => 'table-treaties', 'external' => TRUE)); ?></li>
          <?php foreach ($regions as $region): ?>
            <li><?php print l($region->name, NULL, array('attributes' => array('data-filter' => 'table', 'data-selector' => '.column-region', 'data-value' => $region->name), 'fragment' => 'table-treaties', 'external' => TRUE)); ?></li>
          <?php endforeach; ?>
        </ul><!-- .dropdown-menu .dropdown-menu-right -->
      </th><!-- .dropdown .text-center -->
      <th class="text-center"><?php print t('Year'); ?></th>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($treaties as $treaty): ?>
      <tr>
        <td class="text-center">
          <?php
          if (property_exists($treaty, 'logo')) {
            print theme_image(array(
              'path' => $treaty->logo,
              'alt' => $treaty->title,
              'attributes' => array()
            ));
          }
          ?>
        </td><!-- .text-center -->
        <td>
          <h4>
            <?php print l($treaty->official_name, 'node/' . $treaty->nid); ?>
            <br>
            <small><?php print $treaty->title; ?></small>
          </h4>
          <div class="small">
            <strong><?php print t('Topics:'); ?></strong>
            <?php if (property_exists($treaty, 'topics')): ?>
              <?php print $treaty->topics; ?>
            <?php else: ?>
              <?php print t('N/A'); ?>
            <?php endif; ?>
            <?php if (property_exists($treaty, 'protocols')): ?>
              <br>
              <?php print l('Toggle protocols', NULL, array('attributes' => array('class' => 'collapsed', 'data-toggle' => 'collapse'), 'fragment' => 'protocols-' . $treaty->nid, 'external' => TRUE)); ?>
            <?php endif; ?>
          </div><!-- .small -->
          <?php if (property_exists($treaty, 'protocols')): ?>
            <ul class="list-group collapse" id="protocols-<?php print $treaty->nid; ?>">
              <?php foreach ($treaty->protocols as $protocol): ?>
                <li class="list-group-item">
                  <?php print l($protocol->title, 'node/' . $protocol->nid); ?>
                </li><!-- .list-group-item -->
              <?php endforeach; ?>
            </ul><!-- .list-group .collapse -->
          <?php endif; ?>
        </td>
        <td class="column-region text-center">
          <?php if (property_exists($treaty, 'regions')): ?>
            <?php print $treaty->regions; ?>
          <?php else: ?>
            <?php print t('N/A'); ?>
          <?php endif; ?>
        </td><!-- .column-region .text-center -->
        <td class="text-center">
          <?php if (property_exists($treaty, 'year')): ?>
            <?php print $treaty->year; ?>
          <?php else: ?>
            <?php print t('N/A'); ?>
          <?php endif; ?>
        </td><!-- .text-center -->
      </tr>
    <?php endforeach; ?>
  </tbody>
</table><!-- .table .table-bordered #table-treaties -->
</div>