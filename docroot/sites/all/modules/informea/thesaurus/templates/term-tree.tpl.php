<?php
/** @var stdClass $term */
?>
<li>
  <?php if(!empty($term->children)): ?>
  <button class="toggle" data-toggle="tree-item" type="button"><span class="glyphicon glyphicon-plus-sign"></span></button>
  <?php endif; ?>
  <a href="<?php thesaurus_url_term($term) ;?>"><?php print $term->name; ?></a>
  <?php if(!empty($term->children)): ?>
  <ul class="list-tree collapse">
    <?php
    foreach($term->children as $child_sk):
      $child = taxonomy_term_load($child_sk->tid);
      if (!empty($child_sk->children)):
        $child->children = $child_sk->children;
      endif;
      print theme('term-tree', array('term' => $child));
    endforeach; ?>
  </ul><!-- .list-tree .collapse -->
  <?php endif; ?>
</li>
