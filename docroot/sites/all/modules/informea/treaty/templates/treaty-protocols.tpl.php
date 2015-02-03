<?php
/**
 * @file
 * treaty-decisions.tpl.php
 */
?>
<?php if (count($protocols)): ?>
<ul class="media-list">
<?php foreach ($protocols as $id => $treaty): ?>
<?php $w = entity_metadata_wrapper('node', $treaty); ?>
  <li class="media">
    <div class="media">
      <div class="media-left">
        <a href="<?php print(url('node/' . $treaty->nid)) ;?>">
          <img class="media-object" src="http://placehold.it/64x64" alt="<?php print $w->field_official_name->value() ;?>">
        </a>
      </div>
      <div class="media-body">
        <h4 class="media-heading"><?php print $w->label(); ?></h4>
        <?php if (!empty($treaty->protocols)): ?>
        <?php
          $protocol = current($treaty->protocols);
          $pw = entity_metadata_wrapper('node', $protocol->nid);
        ?>
          <div class="media">
            <div class="media-left">
              <a href="<?php print(url('node/' . $protocol->nid)) ;?>">
                <img class="media-object" src="http://placehold.it/64x64" alt="<?php print $pw->field_official_name->value() ;?>">
              </a>
            </div>
            <div class="media-body">
              <h4 class="media-heading"><?php print $pw->label(); ?></h4>
              <?php print $pw->label(); ?>
            </div>
          </div> <!-- .media -->

        <?php endif; ?>
      </div>
    </div> <!-- .media -->
  </li>
<?php endforeach; ?>
</ul> <!-- .media-list -->
<?php endif; ?>
