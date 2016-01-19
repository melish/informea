<?php
global $base_url;
$icon = $base_url . file_icon_url(file_load($element['fid']));
?>
<?php if (preg_match('/^http/', $element['description'])): ?>
<img class="file-icon" alt="" title="<?php print $element['filemime']; ?>" src="<?php print $icon; ?>">
<a href="<?php print $element['description']; ?>">
  <?php print $element['filename']; ?>
</a>
<?php else: ?>
  <img class="file-icon" alt="" title="<?php print $element['filemime']; ?>" src="<?php print $icon; ?>">
  <?php print $element['filename']; ?>
<?php endif; ?>
