<?php
/**
 * @file
 * treaty-text.tpl.php
 */
?>
<?php if (isset($articles) && is_array($articles)): ?>
  <div class="panel-group tagged-content" id="treaty-text" role="tablist" aria-multiselectable="true">
    <?php foreach ($articles as $article) : ?>
      <?php print theme('treaty_text_article', array('article' => $article)); ?>
    <?php endforeach; ?>
  </div>
  <?php if (user_access('administer nodes')): ?>
    <?php
    print l('<i class="glyphicon glyphicon-plus"></i> ' . t('Add article'), 'node/add/treaty-article', array(
      'html' => TRUE,
      'query' => array('edit' => array(
        'field_treaty' => array('und' => entity_metadata_wrapper('node', $article)->field_treaty->value()[0]->nid)
      ))
    ));
    ?>
  <?php endif; ?>
<?php endif; ?>
