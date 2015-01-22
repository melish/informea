<?php
/**
 * @filef
 * treaty-text-article.tpl.php
 */
?>
<?php if (isset($article)): ?>
<?php
  $aw = entity_metadata_wrapper('node', $article);
  $tags = $aw->field_informea_tags->value();
?>
<div class="panel panel-default">
  <div class="panel-heading smallipop">
    <h4 class="panel-title">
      <a data-toggle="collapse" href="#article_<?php echo $article->nid; ?>">
        <?php echo $article->official_title; ?>
        <a target="_blank" class="permalink pull-right" href="#"><i class="glyphicon glyphicon-link"></i></a>
      </a>
    </h4>
    <?php print theme('treaty_text_tags', array('tags' => $tags)); ?>
  </div>
  <div id="article_<?php echo $article->nid; ?>" class="panel-collapse collapse">
    <div class="panel-body">
      <?php if(!empty($article->paragraphs)): ?>
        <?php foreach ($article->paragraphs as $paragraph): ?>
          <?php print theme('treaty_text_paragraph', array('paragraph' => $paragraph, 'article' => $article)); ?>
        <?php endforeach; ?>
      <?php else: ?>
        <div class="article tagged-content content">
        <?php
          $body = field_view_field('node', $article, 'body', 'teaser');
          print drupal_render($body);
        ?>
        </div><!-- .article -->
      <?php endif; ?>
    </div><!-- .panel-body -->
  </div><!-- .panel-collapse -->
</div><!-- .panel -->
<?php endif; ?>
