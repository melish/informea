<?php
/**
 * @file
 * treaty-global.tpl.php
 */
?>
<div class="text-center">
  <?php foreach ($treaties as $group): ?>
    <div class="brand-group">
      <?php foreach ($group as $treaty): ?>
        <a href="<?php print $treaty->url->value(); ?>" class="brand">
          <div class="image"></div>
          <?php print $treaty->label(); ?>
        </a><!-- .brand -->
      <?php endforeach; ?>
    </div><!-- .brand-group -->
  <?php endforeach; ?>
</div><!-- .text-center -->
