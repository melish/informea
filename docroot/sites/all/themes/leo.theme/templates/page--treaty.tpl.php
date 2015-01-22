<?php
/**
 * @file
 * Default theme implementation to display the treaty page.
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
<?php $wrapper = entity_metadata_wrapper('node', $node); ?>
<div class="container">
  <?php include 'header.tpl.php'; ?>
  <?php if (!empty($page['header'])): ?>
    <header id="page-header" role="banner">
      <?php print render($page['header']); ?>
    </header><!-- #page-header -->
  <?php endif; ?>
  <?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>
  <div class="row">
    <?php if (!empty($page['sidebar_first'])): ?>
      <aside id="sidebar-first" class="col-sm-3" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside><!-- #sidebar-first .col-sm-3 -->
    <?php endif; ?>
    <section<?php print $content_column_class; ?>>
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted jumbotron">
          <?php print render($page['highlighted']); ?>
        </div><!-- .highlighted .jumbotron -->
      <?php endif; ?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if (!empty($title)): ?>
        <div class="page-header">
          <div class="treaty-selector">
            <form role="form">
              <select class="form-control">
                <option value=""><?php print t('Select a treaty&hellip;'); ?></option>
              </select><!-- .form-control -->
            </form>
          </div><!-- .treaty-selector -->
          <h1>
            <?php print $title; ?>
          </h1>
        </div><!-- .page-header -->
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php if (!empty($tabs)): ?>
        <?php
        // Secondary local task in sidebar_second see hook_preprocess_page().
        hide($tabs['#secondary']);
        print render($tabs);
        ?>
      <?php endif; ?>
      <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
      <?php endif; ?>
      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
    </section>
    <?php if (!empty($page['sidebar_second'])): ?>
      <aside id="sidebar-second" class="col-sm-3" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside><!-- #sidebar-second .col-sm-3 -->
    <?php endif; ?>
  </div><!-- .row -->
  <?php include 'footer.tpl.php'; ?>
</div><!-- .container -->
<div class="modal fade" id="modal-downloads" tabindex="-1" role="dialog" aria-labelledby="modal-downloads-label" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="<?php print t('Close'); ?>"><span aria-hidden="true"><?php print t('&times;'); ?></span></button>
        <h4 class="modal-title" id="modal-downloads-label"><?php print t('Downloads'); ?></h4>
      </div><!-- .modal-header -->
      <div class="modal-body">
        <div class="alert alert-warning" role="alert"><?php print t('<strong>Warning!</strong> This section is under development.'); ?></div>
      </div><!-- .modal-body -->
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal"><?php print t('Close'); ?></button>
      </div><!-- .modal-footer -->
    </div><!-- .modal-content -->
  </div><!-- .modal-dialog -->
</div><!-- .modal.fade #modal-downloads -->
