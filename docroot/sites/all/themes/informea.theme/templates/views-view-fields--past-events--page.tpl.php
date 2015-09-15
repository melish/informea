<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<?php
/** @var $fields array */
$content = array(
  'field_logo' => '',
  'field_treaty' => '',
  'title' => '',
  'event_calendar_date' => '',
  'field_event_type' => '',
  'field_event_type_term' => '',
);
$extra = array();
foreach($fields as $id => $field) {
  switch($id) {
    case 'field_logo':
      $content['field_logo'] = $field->content;
      break;
    case 'field_treaty':
      $content['field_treaty'] = $field->content;
      break;
    case 'title':
      $content['title'] = $field->content;
      break;
    case 'event_calendar_date':
      $content['event_calendar_date'] = $field->content;
      break;
    case 'field_event_type':
      $content['field_event_type'] = $field->content;
      if (!empty($row->field_field_event_type[0]['raw']['taxonomy_term'])) {
        $content['field_event_type_term'] = $row->field_field_event_type[0]['raw']['taxonomy_term'];
      }
      break;
    default:
      $extra[$id] = $field->content;
  }
}
?>
<div class="media-left">
  <a href="#">
    <?php print $content['field_logo']; ?>
  </a>
</div>
<div class="media-body">
  <div class="date pull-right"><?php print $content['event_calendar_date']; ?></div>
  <h4 class="media-heading"><?php print $content['title']; ?></h4>

  <div class="media-detail">
    <span class="type"><?php print informea_theme_meeting_type($content['field_event_type_term']); ?></span>
      <span class="extra">
        <?php print implode(", ", $extra); ?>
      </span>
  </div>
</div>
