<?php
/**
 * @filef
 * treaty-text-content.tpl.php
 */
?>
<?php
$pw = entity_metadata_wrapper('node', $paragraph);
$tags = $pw->field_informea_tags->value();
$indent = $pw->field_paragraph_indentation->value();
$highlight = isset($_GET['paragraph']) ? $_GET['paragraph'] == $paragraph->nid : FALSE;
?>
<div class="paragraph indent-<?php print $indent; ?><?php print $highlight ? ' highlight' : '' ;?>" id="paragraph-<?php print $paragraph->nid; ?>">
  <p class="smallipop">
    <span class="pull-right">
      <?php if (user_access('administer nodes')): ?>
        <?php
        print l('<i class="glyphicon glyphicon-pencil"></i>', 'node/' . $paragraph->nid . '/edit', array(
          'attributes' => array('class' => array('permalink')),
          'html' => TRUE
        ));
        ?>
      <?php endif; ?>
      <?php
      print l('<i class="glyphicon glyphicon-link"></i>', 'treaties/cbd', array(
        'attributes' => array('class' => array('permalink'), 'target' => '_blank'),
        'fragment' => 'paragraph-' . $paragraph->nid,
        'html' => TRUE,
        'query' => array(
          'article' => $article->nid,
          'paragraph' => $paragraph->nid
        )
      ));
      ?>
    </span>
    <?php
    $body = field_view_field('node', $paragraph, 'body', 'teaser');

    print strip_tags($body[0]['#markup']); // calling render adds unwanted div's @todo
    ?>
    <?php print theme('treaty_text_tags', array('tags' => $tags)); ?>
  </p><!-- .smallipop -->
</div><!-- .paragraph -->
