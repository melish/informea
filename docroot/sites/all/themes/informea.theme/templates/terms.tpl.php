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
  <div class="section-header">
    <button type="button" class="btn btn-default pull-right" data-toggle="tree" data-target="#terms-substantive"><?php print t('Show all'); ?></button>
  </div><!-- .section-header -->
  <ul class="list-tree" id="terms-substantive">
  <?php
    foreach($substantives as $term):
      print theme('term-tree', array('term' => $term));
    endforeach;
  ?>
  </ul><!-- .list-tree #terms-substantive -->
</div>
