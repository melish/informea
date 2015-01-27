<?php
$id = isset($variables['id']) ? $variables['id'] : 'accordion';
$elements = $variables['elements'];
?>
<?php if (!empty($elements)): ?>
<div class="panel-group" id="<?php print $id; ?>" role="tablist" aria-multiselectable="true">
<?php
	foreach($elements as $eid => $element):
		$collapsed = empty($element['in']) ? ' class="collapsed"' : '';
		$in = empty($collapsed) ? ' in' : '';

		// Global property
		$add_panel_body = empty($variables['no-panel-body']);

		// Override with local property
		if (!empty($element['no-panel-body'])) {
			$add_panel_body = FALSE;
		}
?>
	<div class="panel panel-default">
		<div id="heading-<?php print $eid; ?>" class="panel-heading collapsed" data-toggle="collapse" data-parent="#<?php print $id; ?>" data-target="#collapse-<?php print $eid; ?>" aria-expanded="false" aria-controls="collapse-<?php print $eid; ?>" role="tab">
			<h4 class="panel-title"><?php print $element['header']; ?></h4>
		</div>
		<div id="collapse-<?php print $eid; ?>" class="panel-collapse collapse<?php print $in; ?>" role="tabpanel" aria-labelledby="heading-<?php print $eid; ?>" aria-expanded="false">
			<?php if ($add_panel_body): ?>
			<div class="panel-body">
				<?php endif; ?>
				<?php print $element['body']; ?>
				<?php if ($add_panel_body): ?>
			</div>
		<?php endif; ?>
		</div>
	</div>
	<?php endforeach; ?>
</div>
<?php endif; ?>
