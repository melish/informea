<?php
/**
 * @file
 * informea-bootstrap-tabs.tpl.php
 */
?>
<?php
$id = isset($variables['id']) ? $variables['id'] : 'tabpanel';
$elements = $variables['elements'];
if ($variables['active'] === FALSE && !empty($_GET['active_bootstrap_tab'])) {
	$variables['active'] = $_GET['active_bootstrap_tab'];
}

?>
<?php ?>
<div role="tabpanel" id="<?php print $id; ?>">
	<!-- Nav tabs -->
	<ul class="nav nav-tabs" role="tablist">
	<?php
		foreach($elements as $eid => $element):
      $header_attributes = array();
      if(!empty($element['header-attributes'])) {
        $header_attributes = $element['header-attributes'];
      }
			$active = !empty($element['active']) || (isset($variables['active']) && $eid == $variables['active']) ? ' class="active"' : '';
	?>
		<li role="presentation"<?php print $active; ?>><a href="#tab-<?php print $eid; ?>" aria-controls="tab-<?php print $eid; ?>" role="tab" data-toggle="tab" <?php print drupal_attributes($header_attributes); ?>><?php print $element['header']; ?></a></li>
		<?php endforeach; ?>
	</ul>
	<!-- Tab panes -->
	<div class="tab-content">
	<?php
		foreach($elements as $eid => $element):
			$active = !empty($element['active']) || (isset($variables['active']) && $eid == $variables['active']) ? ' active' : '';
	?>
		<div role="tabpanel" class="tab-pane<?php print $active; ?>" id="tab-<?php print $eid; ?>"><?php print $element['body']; ?></div>
		<?php endforeach; ?>
	</div>
</div>
