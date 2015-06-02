<?php
/**
 * @file
 * terms.tpl.php
 *
 * @ingroup themeable
 */
?>
<?php
/** @var array $substantives */
/** @var array $generic */

#dpm($substantives);
#dpm($generic);
?>
<div class="row">
  <div class="col-md-6">
    <div class="section-header">
      <button type="button" class="btn btn-default pull-right" data-toggle="tree" data-target="#terms-substantive"><?php print t('Show all'); ?></button>
      <h3><?php print t('Substantive terms'); ?></h3>
    </div><!-- .section-header -->
    <ul class="list-tree" id="terms-substantive">
    <?php
      foreach($substantives as $term):
        print theme('term-tree', array('term' => $term));
      endforeach;
    ?>
    </ul><!-- .list-tree #terms-substantive -->
  </div>
  <div class="col-md-6">
    <div class="section-header">
      <button type="button" class="btn btn-default pull-right" data-toggle="tree" data-target="#terms-generic"><?php print t('Show all'); ?></button>
      <h3><?php print t('Generic terms'); ?></h3>
    </div><!-- .section-header -->
    <ul class="list-tree" id="terms-generic">
      <?php
      foreach($generic as $term):
        print theme('term-tree', array('term' => $term));
      endforeach;
      ?>
    </ul><!-- .list-tree #terms-generic -->
  </div>
</div>
