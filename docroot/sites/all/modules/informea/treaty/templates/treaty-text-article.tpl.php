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
  $expanded = isset($_GET['article']) ? $_GET['article'] == $article->nid : FALSE;
  ?>
  <div class="panel <?php print $expanded ? 'panel-warning' : 'panel-default'; ?>">
    <div class="panel-heading smallipop<?php print $expanded ? '' : ' collapsed' ;?>" role="tab" id="heading-<?php echo $article->nid; ?>" data-toggle="collapse" data-target="#article-<?php echo $article->nid; ?>" aria-expanded="<?php print $expanded ? 'true' : 'false' ;?>" aria-controls="article-<?php echo $article->nid; ?>">
      <h4 class="panel-title">
        <a href="javascript:void(0);"><?php echo $article->official_title; ?></a>
        <?php
        print l('<i class="glyphicon glyphicon-link"></i>', 'treaties/cbd', array(
          'attributes' => array(
            'data-toggle' => 'tooltip', 'data-placement' => 'top',
            'title' => t('Permalink'),
            'class' => array('pull-right permalink'),
            'target' => '_blank'
          ),
          'fragment' => 'article-' . $article->nid,
          'html' => TRUE,
          'query' => array('article' => $article->nid)
        ));
        if (user_access('edit any treaty_article content')):
          print l('<i class="glyphicon glyphicon-pencil"></i>', 'node/' . $article->nid . '/edit', array(
            'attributes' => array('data-toggle' => 'tooltip', 'data-placement' => 'top', 'title' => t('Edit this article'), 'class' => array('pull-right administrative')),
            'html' => TRUE
          ));
        endif;
        if (user_access('create treaty_paragraph content')):
            print l('<i class="glyphicon glyphicon-plus"></i>', 'node/add/treaty-paragraph', array(
              'attributes' => array('data-toggle' => 'tooltip', 'data-placement' => 'top', 'title' => t('Append paragraph to this article'), 'class' => array('pull-right administrative')),
              'html' => TRUE,
              'query' => array('edit' => array(
                'field_parent_treaty_article' => array('und' => $article->nid),
                'field_treaty' => array('und' => $aw->field_treaty->value()[0]->nid)
              ))
            ));
        endif;
        ?>
      </h4><!-- .panel-title -->
      <?php print theme('treaty_text_tags', array('tags' => $tags)); ?>
    </div><!-- .panel-heading .smallipop -->
    <div id="article-<?php echo $article->nid; ?>" class="panel-collapse collapse<?php print $expanded ? ' in' : '' ;?>" role="tabpanel" aria-labelledby="heading-<?php echo $article->nid; ?>">
      <div class="article<?php print $expanded && !isset($_GET['paragraph']) ? ' highlight' : ''; ?>">
        <?php if (!empty($article->paragraphs)): ?>
          <?php foreach ($article->paragraphs as $paragraph): ?>
            <?php print theme('treaty_text_paragraph', array('paragraph' => $paragraph, 'article' => $article)); ?>
          <?php endforeach; ?>
        <?php else: ?>
          <div class="article tagged-content content">
            <?php
              $body = $aw->body->value();
              $body = check_markup($body['safe_value'], 'full_html');
              print $body;
            ?>
          </div><!-- .article .tagged-content .content -->
        <?php endif; ?>
      </div><!-- .article -->
    </div><!-- .panel-collapse .collapse -->
  </div><!-- .panel .panel-default -->
<?php endif; ?>
