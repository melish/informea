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
        <?php $url = $treaty->url->value(); ?>
        <a href="<?php print $url; ?>" class="brand brand-<?php print basename($url); ?>">
          <div class="image"></div>
          <?php print $treaty->label(); ?>
        </a><!-- .brand -->
      <?php endforeach; ?>
    </div><!-- .brand-group -->
  <?php endforeach; ?>
</div><!-- .text-center -->
