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
  $permalink = url('treaties/cbd', array(
    'absolute' => TRUE,
    'fragment' => 'article-' . $article->nid,
    'query' => array('article' => $article->nid)
  ));
  $expanded = isset($_GET['article']) ? $_GET['article'] == $article->nid : FALSE;
  $highlight = $expanded && !isset($_GET['paragraph']) ? ' highlight' : '';
  ?>
  <div class="panel panel-default">
    <div class="panel-heading smallipop<?php print $expanded ? '' : ' collapsed' ;?>" role="tab" id="heading-<?php echo $article->nid; ?>" data-toggle="collapse" data-parent="#treaty-text" data-target="#article-<?php echo $article->nid; ?>" aria-expanded="<?php print $expanded ? 'true' : 'false' ;?>" aria-controls="article-<?php echo $article->nid; ?>">
      <h4 class="panel-title">
        <a target="_blank" class="permalink pull-right" href="<?php echo $permalink; ?>"><i class="glyphicon glyphicon-link"></i></a>
        <?php echo $article->official_title; ?>
      </h4><!-- .panel-title -->
      <?php print theme('treaty_text_tags', array('tags' => $tags)); ?>
    </div><!-- .panel-heading .smallipop -->
    <div id="article-<?php echo $article->nid; ?>" class="panel-collapse collapse<?php print $expanded ? ' in' . $highlight : '' ;?>" role="tabpanel" aria-labelledby="heading-<?php echo $article->nid; ?>">
      <div class="panel-body">
        <?php if (!empty($article->paragraphs)): ?>
          <?php foreach ($article->paragraphs as $paragraph): ?>
            <?php print theme('treaty_text_paragraph', array('paragraph' => $paragraph, 'article' => $article)); ?>
          <?php endforeach; ?>
        <?php else: ?>
          <div class="article tagged-content content">
            <?php print drupal_render(field_view_field('node', $article, 'body', 'teaser')); ?>
          </div><!-- .article .tagged-content .content -->
        <?php endif; ?>
      </div><!-- .panel-body -->
    </div><!-- .panel-collapse .collapse -->
  </div><!-- .panel .panel-default -->
<?php endif; ?>
