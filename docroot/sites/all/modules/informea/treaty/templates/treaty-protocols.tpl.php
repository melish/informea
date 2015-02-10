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
        <div class="media-left">
          <a href="<?php print(url('node/' . $treaty->nid)) ;?>">
            <?php
            print theme('image', array(
              'path' => $w->field_logo->value() ? $w->field_logo->file->url->value() : 'http://placehold.it/64x64',
              'alt' => $w->field_official_name->value(),
              'attributes' => array('class' => 'media-object')
            ));
            ?>
          </a>
        </div><!-- .media-left -->
        <div class="media-body">
          <h4 class="media-heading">
            <?php print l($w->field_official_name->value(), 'node/' . $treaty->nid); ?>
            <br>
            <small><?php print $w->label(); ?></small>
          </h4>
          <?php if (!empty($treaty->protocols)): ?>
            <?php
            $protocol = current($treaty->protocols);
            $pw = entity_metadata_wrapper('node', $protocol->nid);
            ?>
            <div class="media">
              <div class="media-left">
                <a href="<?php print(url('node/' . $protocol->nid)) ;?>">
                  <?php
                  print theme('image', array(
                    'path' => $pw->field_logo->value() ? $pw->field_logo->file->url->value() : 'http://placehold.it/64x64',
                    'alt' => $pw->field_official_name->value(),
                    'attributes' => array('class' => 'media-object')
                  ));
                  ?>
                </a>
              </div><!-- .media-left -->
              <div class="media-body">
                <h4 class="media-heading">
                  <?php print l($pw->label(), 'node/' . $protocol->nid); ?>
                  <br>
                  <small><?php print $pw->label(); ?></small>
                </h4>
              </div><!-- .media-body -->
            </div><!-- .media -->
          <?php endif; ?>
        </div><!-- .media-body -->
      </li><!-- .media -->
    <?php endforeach; ?>
  </ul><!-- .media-list -->
<?php endif; ?>
