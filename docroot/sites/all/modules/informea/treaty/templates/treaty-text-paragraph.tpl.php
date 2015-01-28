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
$permalink = url('treaties/cbd', array(
  'absolute' => TRUE,
  'fragment' => 'paragraph-' . $paragraph->nid,
  'query' => array('article' => $article->nid)
));
?>
<div class="paragraph indent-<?php print $indent; ?>" id="paragraph-<?php print $paragraph->nid; ?>">
  <p class="smallipop">
    <?php
    $body = field_view_field('node', $paragraph, 'body', 'teaser');

    print strip_tags($body[0]['#markup']); // calling render adds unwanted div's @todo
    ?>
    <a target="_blank" class="permalink" href="<?php print $permalink; ?>"><i class="glyphicon glyphicon-link"></i></a>
    <?php print theme('treaty_text_tags', array('tags' => $tags)); ?>
  </p><!-- .smallipop -->
</div><!-- .paragraph -->
