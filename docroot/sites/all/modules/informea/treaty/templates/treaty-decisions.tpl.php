<?php
/**
 * @file
 * treaty-decisions.tpl.php
 */
?>
<?php
/** @var array $variables */
$decisions = $variables['decisions'];
?>
<table class="table table-hover">
  <tbody>
    <?php foreach ($decisions as $decision): ?>
      <?php $wrapper = entity_metadata_wrapper('node', $decision);?>
      <tr id="decision-<?php print $decision->nid ?>">
        <td class="col-sm-1 text-center"><?php print $wrapper->field_decision_number->value(); ?></td>
        <td>
          <?php
          print l($wrapper->label(), 'node/' . $wrapper->getIdentifier(), array(
            'attributes' => array(
              'data-toggle' => 'modal',
              'data-target' => '#dialog-modal-ajax',
              'data-remote' => url('ajax/modal/node/' . $wrapper->getIdentifier())
            )
          ));
          ?>
        </td>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table><!-- .table .table-hover -->
