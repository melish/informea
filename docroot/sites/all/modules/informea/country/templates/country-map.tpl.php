<div id="map-canvas" style="width: 815px; height: 450px;"></div>
<h3><?php print t('Legend'); ?></h3>
<ul class="list-inline">
  <li>
    <img src="/sites/all/themes/informea.theme/img/blue-pin.png">
    <?php print t('Ramsar site'); ?>
  </li>
  <li>
    <img src="/sites/all/themes/informea.theme/img/red-pin.png">
    <?php print t('WHC site'); ?>
  </li>
</ul>
<?php
  // Render the map disclaimer block (map_disclaimer)
  $block = module_invoke('block', 'block_view', 3);
  print render($block['content']);
?>
