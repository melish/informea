<?php
/**
 * @file
 * treaty-text-content.tpl.php
 */
?>
<?php if (!empty($tags) && is_array($tags)): ?>
  <span class="smallipop-hint">
    <?php print t('Tagged terms:'); ?>
    <?php
    $terms = array();

    foreach ($tags as $tag) {
      $tw = entity_metadata_wrapper('taxonomy_term', $tag);
      $tl = $tw->label();
      if(!empty($tl)) {
        $terms[] = l($tl, 'taxonomy/term/' . $tag->tid);
      }
    }
    ?>
    <?php print implode(', ', $terms); ?>
  </span><!-- .smallipop-hint -->
<?php endif; ?>
