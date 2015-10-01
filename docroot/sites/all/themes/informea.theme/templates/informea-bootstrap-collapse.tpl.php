<?php
$id = isset($variables['id']) ? $variables['id'] : 'accordion';
$elements = $variables['elements'];
$add_data_parent = empty($variables['no-data-parent']);
$add_data_parent_text = $add_data_parent ? (' data-parent="#' . $id . '"') : '';
$show_expand_button = isset($variables['show-expand-button']) ? $variables['show-expand-button'] : FALSE;
?>
<?php if (!empty($elements)): ?>
  <?php if ($show_expand_button): ?>
  <button type="button" class="btn btn-default pull-right" data-toggle="informea-bootstrap-collapse" data-target="#<?php print $id; ?>"><?php print t('Show all'); ?></button>
  <?php endif; ?>
  <div class="accordion panel-group" id="<?php print $id; ?>" role="tablist" aria-multiselectable="true">
    <div class="list">
    <?php
  foreach($elements as $eid => $element):
    $collapsed = empty($element['in']) ? ' collapsed' : '';
    $in = empty($collapsed) ? ' in' : '';

    // Global property
    $add_panel_body = empty($variables['no-panel-body']);

    // Override with local property
    if (!empty($element['no-panel-body'])) {
      $add_panel_body = FALSE;
    }
  ?>
  <div class="panel panel-default">
    <div id="heading-<?php print $eid; ?>" class="panel-heading<?php print $collapsed; ?> <?php print $element['tags'] ? 'smallipop' : ''; ?>" data-toggle="collapse"<?php print $add_data_parent_text; ?> data-target="#collapse-<?php print $eid; ?>" aria-expanded="false" aria-controls="collapse-<?php print $eid; ?>" role="tab">
      <?php print $element['tags']; ?>
      <i class="glyphicon glyphicon-plus-sign"></i> <h4 class="panel-title"><?php print $element['header']; ?></a></h4>
    </div>
    <div id="collapse-<?php print $eid; ?>" class="panel-collapse collapse<?php print $in; ?>" role="tabpanel" aria-labelledby="heading-<?php print $eid; ?>" aria-expanded="false">
      <?php if ($add_panel_body): ?>
      <div class="panel-body">
        <?php endif; ?>
        <?php
          if (isset($element['body'])) {
            print $element['body'];
          }
          if (isset($element['#children'])) {
            print drupal_render($element['#children']);
          }
        ?>
        <?php if ($add_panel_body): ?>
      </div>
    <?php endif; ?>
    </div>
  </div>
  <?php endforeach; ?>
    </div>
</div>
<?php endif; ?>
