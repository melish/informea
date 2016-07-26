<?php
/**
 * @file
 * treaty-decisions.tpl.php
 */
?>
<?php
/** @var array $variables */
$meetings = $variables['meetings'];
?>
<div id="meetings" class="accordion">
  <?php
  foreach ($meetings as $nid => $meeting):
    $wrapper = entity_metadata_wrapper('node', $meeting);
    $date = new DateTime($wrapper->event_calendar_date->value()['value']);
    $count = !empty($meeting->decisions) ? count($meeting->decisions) : 0;
    ?>
    <div id="meeting-<?php print $nid ?>" class="panel panel-default">
      <div class="panel-heading">
        <?php
        print l($wrapper->label(), 'node/' . $nid);
        if (user_access('edit any event_calendar content')):
          print '&nbsp;&nbsp;' . l('<i class="glyphicon small glyphicon-pencil"></i>', 'node/' . $nid . '/edit', array('attributes' => array('target' => '_blank', 'title' => t('Edit')), 'html' => TRUE));
        endif;
        ?>
        <ul class="list-inline meta">
          <li class="first"><?php print $date->format('d M Y'); ?></li>
          <li><?php print $wrapper->field_country->label(); ?></li>
          <li class="last"><?php print "{$count} " . t('decisions'); ?></li>
        </ul>
      </div>
    </div>
  <?php endforeach; ?>
</div>