<?php
/**
 * @file
 * node--decision--ajax.tpl.php
 */
?>
<?php
$wrapper = entity_metadata_wrapper('node', $node);
$decision = array(
  'number' => field_view_field('node', $node, 'field_decision_number', array('label' => 'inline')),
  'type' => field_view_field('node', $node, 'field_decision_type', array(
    'label' => 'inline',
    'type' => 'i18n_taxonomy_term_reference_plain'
  )),
  'meeting_url' => field_view_field('node', $node, 'field_meeting_url', array('label' => 'inline')),
  'status' => field_view_field('node', $node, 'field_decision_status', array(
    'label' => 'inline',
    'type' => 'i18n_taxonomy_term_reference_plain'
  )),
  'published' => field_view_field('node', $node, 'field_decision_published', array('label' => 'inline')),
  'files' => field_view_field('node', $node, 'field_files', array('label' => 'inline')),
  'text' => field_view_field('node', $node, 'body', array('label' => 'hidden'))
);
?>
<div class="modal-header">
  <button type="button" class="close" data-dismiss="modal" aria-label="<?php print t('Close'); ?>"><span aria-hidden="true"><?php print t('&times;'); ?></span></button>
  <h4 class="modal-title" id="modal-decision-label"><?php print $wrapper->label(); ?></h4>
</div><!-- .modal-header -->
<div class="modal-body">
  <?php print render($decision['number']); ?>
  <?php print render($decision['type']); ?>
  <?php print render($decision['meeting_url']); ?>
  <?php print render($decision['status']); ?>
  <?php print render($decision['published']); ?>
  <?php print render($decision['files']); ?>
  <hr>
  <?php print render($decision['text']); ?>
</div><!-- .modal-body -->
<div class="modal-footer">
  <button type="button" class="btn btn-default" data-dismiss="modal"><?php print t('Close'); ?></button>
</div><!-- .modal-footer -->
