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
  'field_image' => '',
  'field_url' => '',
  'field_tags' => '',
);
$extra = array();
foreach($fields as $id => $field) {
  switch($id) {
    case 'field_image':
      $content['field_image'] = $field->content;
      break;
    case 'field_url':
      $content['field_url'] = $field->content;
      break;
    case 'field_tags':
      $content['field_tags'] = $field->content;
      break;
    case 'created':
      $content['created'] = $field->content;
      break;
    default:
      $extra[$id] = $field->content;
  }
}
?>
<div class="media-left">
  <a href="#">
    <?php print $content['field_image']; ?>
  </a>
</div>
<div class="media-body">
  <h4 class="media-heading"><?php print $content['field_url']; ?></h4>

  <div class="media-detail">
    <p><?php print $content['created']; ?></p>
    <span class="tags"><?php print $content['field_tags']; ?></span>
      <span class="extra">
        <?php print implode(", ", $extra); ?>
      </span>
  </div>
</div>
