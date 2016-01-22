<?php
/**
 * @file
 * treaty-text.tpl.php
 */
?>
<?php
/** @var array $variables */
$treaty = $variables['treaty']; $articles = $variables['articles'];
?>
<html>
<title>Print the text of <?php print $treaty->title; ?></title>
<style type="text/css">
  tr.last td {
    padding-bottom: 20px;
  }
  td.tags {
    color: #666;
  }
  h2 { margin: 2px; }
</style>
<script type="text/javascript">
  window.onload = function() {
    window.print();
  }
</script>
</html>
<body>
<?php if (isset($treaty) && isset($articles) && is_array($articles)): ?>
  <h1><?php print $treaty->title; ?></h1>
  <table>
    <?php
    $ta = count($articles);
    $j = 0;
    foreach ($articles as $article) :
      $order = field_view_field('node', $article, 'field_official_order', 'full');
      $aw = entity_metadata_wrapper('node', $article);
      ?>
      <tr class="article-title">
        <td colspan="2">
          <h2><?php print strip_tags(render($order)) . ' ' . $article->title; ?></h2>
        </td>
      </tr>
      <?php
      if (empty($article->paragraphs)):
        $tags = array();
        if ($atags = $pw->field_informea_tags->value()) {
          foreach($atags as $tag) {
            $tags[] = $tag->name;
          }
        }
        $tags = implode(', ', $tags);
        $tags = $tags ? $tags : '&nbsp;';
        $body = field_view_field('node', $article, 'body', 'full');
        $body = drupal_render($body);
        $pclass = ++$j == $ta ? 'last article-' . $article->nid : 'article-' . $article->nid;
        ?>
        <tr class="article <?php print $pclass; ?>">
          <td><?php print $j . '#' . $ta . '#' . strip_tags($body, INFORMEA_TREATY_TEXT_ALLOWED_TAGS); ?></td>
          <td class="tags"><?php print $tags; ?></td>
        </tr>
      <?php
      else:
        $tp = count($article->paragraphs);
        $i = 0;
        foreach ($article->paragraphs as $paragraph):
          $pw = entity_metadata_wrapper('node', $paragraph);
          $tags = array();
          if ($ptags = $pw->field_informea_tags->value()) {
            foreach($ptags as $tag) {
              $tags[] = $tag->name;
            }
          }
          $tags = implode(', ', $tags);
          $tags = $tags ? $tags : '&nbsp;';

          $body = field_view_field('node', $paragraph, 'body', 'teaser');
          $last = ++$i == $tp ? 'last paragraph-' . $paragraph->nid : 'paragraph-' . $paragraph->nid;
          ?>
          <tr class="paragraph <?php print $last; ?> <?php print $tp . ':' . $i; ?>">
            <td width="70%">
              <?php print strip_tags($body[0]['#markup'], INFORMEA_TREATY_TEXT_ALLOWED_TAGS); ?>
            </td>
            <td class="tags">
              <?php print $tags; ?>
            </td>
          </tr>
        <?php
        endforeach;
      endif;
    endforeach; ?>
  </table>
<?php else: ?>
  Thre is no content available for printing.
<?php endif; ?>
</body>