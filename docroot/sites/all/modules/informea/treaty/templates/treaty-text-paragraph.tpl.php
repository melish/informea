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
<div class="paragraph smallipop indent-<?php print $indent; ?><?php print $highlight ? ' highlight' : '' ;?>" id="paragraph-<?php print $paragraph->nid; ?>">
  <p>
    <?php $body = field_view_field('node', $paragraph, 'body', 'teaser'); ?>
    <?php print strip_tags($body[0]['#markup']); // calling render adds unwanted div's @todo ?>
  </p>
  <?php print theme('treaty_text_tags', array('tags' => $tags)); ?>
  <ul class="list-inline actions">
    <?php if (!empty($tags) && is_array($tags)): ?>
      <li>
        <span class="glyphicon glyphicon-tag"></span>
        <?php print t('Tagged terms'); ?>
      </li>
    <?php endif; ?>
    <li>
      <?php if (user_access('administer nodes')): ?>
        <?php print l('<span class="glyphicon glyphicon-pencil"></span> ' . t('Edit paragraph'), 'node/' . $paragraph->nid . '/edit', array('html' => TRUE)); ?>
      <?php endif; ?>
    </li>
    <li>
      <?php
      print l('<span class="glyphicon glyphicon-link"></span> ' . t('Permalink'), 'treaties/cbd', array(
        'attributes' => array('target' => '_blank'),
        'fragment' => 'paragraph-' . $paragraph->nid,
        'html' => TRUE,
        'query' => array(
          'article' => $article->nid,
          'paragraph' => $paragraph->nid
        )
      ));
      ?>
    </li>
  </ul><!-- .list-inline .actions -->
</div><!-- .paragraph .smallipop -->
