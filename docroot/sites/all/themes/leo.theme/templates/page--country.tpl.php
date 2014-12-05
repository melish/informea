<?php
/**
 * @file
 * Default theme implementation to display the country page.
 *
 * All the available variables are mirrored in page.tpl.php.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<div class="container">
  <?php include 'header.tpl.php'; ?>
  <?php if (!empty($page['header'])): ?>
    <header id="page-header" role="banner">
      <?php print render($page['header']); ?>
    </header><!-- #page-header -->
  <?php endif; ?>
  <?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>
  <?php if (!empty($page['highlighted'])): ?>
    <div class="highlighted jumbotron">
      <?php print render($page['highlighted']); ?>
    </div><!-- .highlighted .jumbotron -->
  <?php endif; ?>
  <a id="main-content"></a>
  <?php print render($title_prefix); ?>
  <?php if (!empty($title)): ?>
    <div class="page-header">
      <h1><?php print $title; ?></h1>
    </div><!-- .page-header -->
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php print $messages; ?>
  <?php if (!empty($tabs)): ?>
    <?php print render($tabs); ?>
  <?php endif; ?>
  <?php if (!empty($page['help'])): ?>
    <?php print render($page['help']); ?>
  <?php endif; ?>
  <?php if (!empty($action_links)): ?>
    <ul class="action-links"><?php print render($action_links); ?></ul>
  <?php endif; ?>
  <?php print render($page['content']); ?>
  <?php include 'footer.tpl.php'; ?>
</div><!-- .container -->
