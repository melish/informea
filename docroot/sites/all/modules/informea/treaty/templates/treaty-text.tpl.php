<?php
/**
 * @file
 * treaty-text.tpl.php
 */
?>
<?php if (isset($articles) && is_array($articles)): ?>
<div class="panel-group tagged-content" id="treaty-text">
<?php foreach ($articles as $article) : ?>
  <?php print theme('treaty_text_article', array('article' => $article)); ?>
<?php endforeach; ?>
</div>
<?php endif; ?>
