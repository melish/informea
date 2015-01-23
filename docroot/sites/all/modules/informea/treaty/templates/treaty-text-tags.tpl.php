<?php
/**
 * @file
 * treaty-text-content.tpl.php
 */
?>
<?php if(!empty($tags) && is_array($tags)): ?>
<span class="smallipop-hint">
  Tagged Terms: &ensp;
  <?php for($i = 0; $i < count($tags); $i++): ?>
    <?php $tw = entity_metadata_wrapper('taxonomy_term', $tags[$i]); ?>
    <a href="#" target="_blank"><?php print $tw->label(); ?></a><?php if ($i < count($tags) - 1) { echo ', '; } ?>
  <?php endfor; ?>
 </span>
<?php endif; ?>
