<?php
/**
 * @filef
 * treaty-text-content.tpl.php
 */
?>
<?php
$pw = entity_metadata_wrapper('node', $paragraph);
$article = $pw->field_parent_treaty_article->value();
$tags = $pw->field_informea_tags->value();
$treaty = $pw->field_treaty->value()[0];
$treaty_wrapper = entity_metadata_wrapper('node', $treaty);
$odata_identifier = $treaty_wrapper->field_odata_identifier->value();
static $i = 1;
$indent = $pw->field_paragraph_indentation->value();
$highlight = isset($_GET['paragraph']) ? $_GET['paragraph'] == $paragraph->nid : FALSE;
?>
<div class="paragraph smallipop indent-<?php print $indent; ?><?php print $highlight ? ' highlight' : '' ;?>" id="paragraph-<?php print $paragraph->nid; ?>">
  <p>
    <?php $body = field_view_field('node', $paragraph, 'body', 'full'); ?>
    <?php print strip_tags($body[0]['#markup']); // calling render adds unwanted div's @todo ?>
    <?php
    if (user_access('edit any treaty_paragraph content')):
      $query = array(
        'destination' => sprintf('/node/%d/text?article=%d&paragraph=%d#paragraph-%d', $treaty->nid, $article->nid, $paragraph->nid, $paragraph->nid),
      );
      print l('<i class="glyphicon glyphicon-pencil"></i>', 'node/' . $paragraph->nid . '/edit', array(
        'attributes' => array('data-toggle' => 'tooltip', 'data-placement' => 'top', 'title' => t('Edit this paragraph'), 'class' => array('administrative')),
        'html' => TRUE, 'query' => $query
      ));
    endif;
    print l('<span class="glyphicon glyphicon-link"></span>', 'treaties/' . $odata_identifier . '/text', array(
      'attributes' => array(
        'data-toggle' => 'tooltip', 'data-placement' => 'top',
        'title' => t('Permalink'),
        'target' => '_blank',
        'class' => array('permalink'),
      ),
      'fragment' => 'paragraph-' . $paragraph->nid,
      'html' => TRUE,
      'query' => array(
        'article' => $article->nid,
        'paragraph' => $paragraph->nid
      )
    ));
    ?>
  </p>
  <?php print theme('treaty_text_tags', array('tags' => $tags)); ?>
</div><!-- .paragraph .smallipop -->
