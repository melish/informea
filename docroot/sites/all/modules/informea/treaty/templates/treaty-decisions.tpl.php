<?php
/**
 * @file
 * treaty-decisions.tpl.php
 */
?>
<table class="table table-hover">
  <tbody>
    <?php foreach ($decisions as $id => $decision): ?>
      <tr>
        <td class="col-sm-1">
          <?php $w = entity_metadata_wrapper('node', $decision); ?>
          <?php print $w->field_decision_number->value(); ?>
        </td><!-- .col-sm-1 -->
        <td><?php print l($w->label(), 'node/' . $w->getIdentifier() . '/ajax', array('attributes' => array('data-toggle' => 'modal', 'data-target' => '#modal-decision'))); ?></td>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table><!-- .table .table-hover -->
