<h3><?php print t('Global treaties and conventions'); ?></h3>
<div class="text-center">
  <div class="brand-group">
    <a class="brand brand-cbd" target="_blank" href="<?php print url('treaties/cbd'); ?>">
      <div class="image"></div>
      <?php print t('CBD'); ?>
    </a><!-- .brand .brand-cbd -->
    <a class="brand brand-cartagena" target="_blank" href="<?php print url('treaties/cartagena'); ?>">
      <div class="image"></div>
      <?php print t('Cartagena'); ?>
    </a><!-- .brand .brand-cartagena -->
    <a class="brand brand-nagoya" target="_blank" href="<?php print url('treaties/nagoya'); ?>">
      <div class="image"></div>
      <?php print t('Nagoya'); ?>
    </a><!-- .brand .brand-nagoya -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-cms" target="_blank" href="<?php print url('treaties/cms'); ?>">
      <div class="image"></div>
      <?php print t('CMS'); ?>
    </a><!-- .brand .brand-cms -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-cites" target="_blank" href="<?php print url('treaties/cites'); ?>">
      <div class="image"></div>
      <?php print t('CITES'); ?>
    </a><!-- .brand .brand-cites -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-plant-treaty" target="_blank" href="<?php print url('treaties/plant-treaty'); ?>">
      <div class="image"></div>
      <?php print t('Plant treaty'); ?>
    </a><!-- .brand .brand-plant-treaty -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-ramsar" target="_blank" href="<?php print url('treaties/ramsar'); ?>">
      <div class="image"></div>
      <?php print t('Ramsar'); ?>
    </a><!-- .brand .brand-ramsar -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-whc" target="_blank" href="<?php print url('treaties/whc'); ?>">
      <div class="image"></div>
      <?php print t('WHC'); ?>
    </a><!-- .brand .brand-whc -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-basel" target="_blank" href="<?php print url('treaties/basel'); ?>">
      <div class="image"></div>
      <?php print t('Basel'); ?>
    </a><!-- .brand .brand-basel -->
    <a class="brand brand-rotterdam" target="_blank" href="<?php print url('treaties/rotterdam'); ?>">
      <div class="image"></div>
      <?php print t('Rotterdam'); ?>
    </a><!-- .brand .brand-rotterdam -->
    <a class="brand brand-stockholm" target="_blank" href="<?php print url('treaties/stockholm'); ?>">
      <div class="image"></div>
      <?php print t('Stockholm'); ?>
    </a><!-- .brand .brand-stockholm -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-minamata" target="_blank" href="<?php print url('treaties/minamata'); ?>">
      <div class="image"></div>
      <?php print t('Minamata'); ?>
    </a><!-- .brand .brand-minamata -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-vienna" target="_blank" href="<?php print url('treaties/vienna'); ?>">
      <div class="image"></div>
      <?php print t('Vienna'); ?>
    </a><!-- .brand .brand-vienna -->
    <a class="brand brand-montreal" target="_blank" href="<?php print url('treaties/montreal'); ?>">
      <div class="image"></div>
      <?php print t('Montreal'); ?>
    </a><!-- .brand .brand-montreal -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-unccd" target="_blank" href="<?php print url('treaties/unccd'); ?>">
      <div class="image"></div>
      <?php print t('UNCCD'); ?>
    </a><!-- .brand .brand-unccd -->
  </div><!-- .brand-group -->
  <div class="brand-group">
    <a class="brand brand-unfccc" target="_blank" href="<?php print url('treaties/unfccc'); ?>">
      <div class="image"></div>
      <?php print t('UNFCCC'); ?>
    </a><!-- .brand .brand-unfccc -->
    <a class="brand brand-kyoto" target="_blank" href="<?php print url('treaties/kyoto'); ?>">
      <div class="image"></div>
      <?php print t('Kyoto'); ?>
    </a><!-- .brand .brand-kyoto -->
  </div><!-- .brand-group -->
</div><!-- .text-center -->
<h3><?php print t('All treaties'); ?></h3>
<table class="table table-bordered" id="treaties-table">
  <thead>
    <tr>
      <td colspan="2">
        <small class="text-muted">
          Showing <strong><?php print count($treaties); ?></strong> of <strong><?php print count($treaties); ?></strong> treaties
        </small><!-- .text-muted -->
      </td>
      <th class="dropdown text-center">
        <a class="text-nowrap" data-toggle="dropdown" href="#">
          Region
          <span class="caret"></span>
        </a><!-- .text-nowrap -->
        <ul class="dropdown-menu dropdown-menu-right" role="menu">
          <li><a href="#">All regions</a></li>
          <?php foreach ($regions as $region): ?>
            <li><?php print l($region->name, NULL, array('fragment' => $region->tid, 'external' => TRUE)); ?></li>
          <?php endforeach; ?>
        </ul><!-- .dropdown-menu .dropdown-menu-right -->
      </th>
      <th class="text-center">Year</th>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($treaties as $treaty): ?>
      <tr>
      <td class="text-center">
        <?php if (property_exists($treaty, 'logo')): ?>
          <?php
          print theme_image(array(
            'path' => $treaty->logo,
            'alt' => $treaty->title,
            'attributes' => array()
          ));
          ?>
        <?php endif; ?>
      </td><!-- .text-center -->
      <td>
        <h4>
          <?php print l($treaty->official_name, 'node/' . $treaty->nid); ?>
          <small><?php print $treaty->title; ?></small>
        </h4>
        <p class="small">
          <strong>Topics:</strong>
          <?php if (property_exists($treaty, 'topics')): ?>
            <?php print $treaty->topics; ?>
          <?php else: ?>
            <?php print t('N/A'); ?>
          <?php endif; ?>
        </p><!-- .small -->
        <?php if (property_exists($treaty, 'protocols')): ?>
          <p class="small">
            <a class="collapsed" data-toggle="collapse" href="#protocols-<?php print $treaty->nid; ?>">Toggle protocols</a>
          </p><!-- .small -->
          <ul class="list-group collapse" id="protocols-<?php print $treaty->nid; ?>">
            <?php foreach ($treaty->protocols as $protocol): ?>
              <li class="list-group-item">
                <?php print l($protocol->title, 'node/' . $protocol->nid); ?>
              </li><!-- .list-group-item -->
            <?php endforeach; ?>
          </ul><!-- .list-group .collapse -->
        <?php endif; ?>
      </td>
      <td class="text-center">
        <?php if (property_exists($treaty, 'regions')): ?>
          <?php print $treaty->regions; ?>
        <?php else: ?>
          <?php print t('N/A'); ?>
        <?php endif; ?>
      </td><!-- .text-center -->
      <td class="text-center">
        <?php if (property_exists($treaty, 'year')): ?>
          <?php print $treaty->year; ?>
        <?php else: ?>
          <?php print t('N/A'); ?>
        <?php endif; ?>
      </td>
    </tr>
    <?php endforeach; ?>
  </tbody>
</table><!-- .table .table-bordered #treaties-table -->
