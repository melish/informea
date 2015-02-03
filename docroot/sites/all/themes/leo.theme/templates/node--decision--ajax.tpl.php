<?php
/**
 * @file
 * node--decision--ajax.tpl.php
 */
?>
<?php $wrapper = entity_metadata_wrapper('node', $node); ?>
<div class="modal-header">
  <button type="button" class="close" data-dismiss="modal" aria-label="<?php print t('Close'); ?>"><span aria-hidden="true"><?php print t('&times;'); ?></span></button>
  <h4 class="modal-title" id="modal-decision-label"><?php print $wrapper->label(); ?></h4>
</div><!-- .modal-header -->
<div class="modal-body">
  <?php print $wrapper->body->value->value(); ?>
</div><!-- .modal-body -->
<div class="modal-footer">
  <button type="button" class="btn btn-default" data-dismiss="modal"><?php print t('Close'); ?></button>
</div><!-- .modal-footer -->
