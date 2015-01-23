<?php
/**
 * @file
 * treaty-decisions.tpl.php
 */
?>
<table class="table">
	<tbody>
<?php
	foreach ($decisions as $id => $decision):
		$w = entity_metadata_wrapper('node', $decision);
?>
	<tr>
		<td class="col-sm-1 nobreak">
			<?php print $w->field_decision_number->value(); ?>
		</td><!-- .col-sm-1 -->
		<td>
			<a data-toggle="modal" href="<?php print url('node/' . $w->getIdentifier(), array('absolute' => TRUE)); ?>"><?php print $w->label(); ?></a>
		</td>
	</tr>
	<?php endforeach; ?>
	</tbody>
</table>
