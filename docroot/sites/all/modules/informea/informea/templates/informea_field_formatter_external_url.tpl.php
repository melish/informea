<?php
global $base_url;
$icon = $base_url . file_icon_url(file_load($element['fid']));
?>
<img class="file-icon" alt="" title="<?php print $element['filemime']; ?>" src="<?php print $icon; ?>">
<a href="<?php print file_create_url($element['description'] ? $element['description'] : $element['uri']); ?>">
  <?php print $element['filename']; ?>
</a>