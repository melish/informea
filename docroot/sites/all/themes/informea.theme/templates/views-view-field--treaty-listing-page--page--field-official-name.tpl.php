<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php
print $output;
?>
<?php if (!empty($row->children)): ?>
<ul>
<?php
foreach($row->children as $child):
  $field_year = field_view_field('node', $child, 'field_entry_into_force', 'treaty_listing');
  $field_region = field_view_field('node', $child, 'field_region', 'treaty_listing');
?>
<li>
  <h2><?php print l($child->title, 'node/' . $child->nid); ?></h2>
  <div class="year"><?php print drupal_render($field_year); ?></div>
  <div class="coverage"><?php print drupal_render($field_region); ?></div>
</li>
<?php endforeach ?>
</ul>
<?php endif; ?>
