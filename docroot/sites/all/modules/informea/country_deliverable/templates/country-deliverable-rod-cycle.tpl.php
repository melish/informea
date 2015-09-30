<?php
/**
 * @file
 * country-deliverable-rod-cycle.tpl.php
 */
?>
<?php
$w = entity_metadata_wrapper('node', $cycle);
$fv = field_view_field('node', $cycle, 'field_files', 'default');
$decisions = $w->field_decision->value();
?>

<?php echo render($fv); ?>

<?php
if(count($decisions)): ?>
<p class="decision">
<?php
  $decision = current($decisions);
  if ($decision !== NULL) {
    $dw = entity_metadata_wrapper('node', $decision);
    $number = $dw->field_decision_number->value();
    $number = strpos($number, '.') ? $number : $number . '.';
    echo t('Defined by the decision <em><a href="!link" target="_blank">!number !title</a></em>',
      array(
        '!link' => url('node/' . $decision->nid),
        '!number' => $number,
        '!title' => $dw->label()));

    $paragraphs = $w->field_decision_paragraph->value();
    foreach ($paragraphs as $paragraph):
      $paragraph->title = '';
      $render = node_view($paragraph, 'teaser');
      unset($render['links']['node']['#links']['node-readmore']);
      echo drupal_render($render);
    endforeach;

    $dfv = field_view_field('node', $decision, 'field_files');
    echo render($dfv);
  }
?>
</p>
<?php endif; ?>
