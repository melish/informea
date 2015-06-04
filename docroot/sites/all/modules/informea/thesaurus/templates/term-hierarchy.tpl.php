<?php

/** @var array $variables */
$parents = $variables['parents'];
$children = $variables['children'];
$term = $variables['term'];
?>
<div class="well">
  <h4><?php print t('Hierarchy'); ?></h4>
  <div class="small">
    <?php if(!empty($parents)): $last = end($parents); ?>
    <ul>
      <?php foreach($parents as $parent): ?>
      <li>
        <?php print l($parent->name, 'taxonomy/term/' . $parent->tid); ?>
        <?php if ($parent->tid == $last->tid): ?>
          <ul>
            <li><?php print $term->name; ?>
          <?php if(!empty($children)): ?>
          <ul>
            <?php foreach($children as $child): ?>
            <li><?php print l($child->name, 'taxonomy/term/' . $child->tid); ?></li>
            <?php endforeach; ?>
          </ul>
            </li>
          <?php endif; ?>
          </ul>
        <?php endif; ?>
      </li>
      <?php endforeach; ?>
    </ul>
    <?php else: ?>
    <?php endif; ?>
  </div>
</div>
