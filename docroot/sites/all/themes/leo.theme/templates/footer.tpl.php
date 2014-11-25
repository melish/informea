<?php
/**
 * @file
 * footer.tpl.php
 */
?>
<footer class="footer">
  <div class="container">
    <ul class="list-inline" id="footer-list">
      <li><a href="<?php print url('<front>'); ?>"><?php print theme('image', array('path' => $directory . '/img/logo-footer.jpg')); ?></a></li>
      <li class="hidden-xs hidden-sm">
        <?php print t('Copyright &copy; United Nations Environment Programme'); ?>
        |
        <?php print l(t('Privacy'), NULL); ?>
        |
        <?php print l(t('Terms and Conditions'), NULL); ?>
      </li><!-- .hidden-xs .hidden-sm -->
      <li class="hidden-xs hidden-sm">
        <?php print l(t('Contacts'), NULL); ?>
        |
        <?php print l(t('Site Locator'), NULL); ?>
        |
        <?php print l(t('UNEP Intranet'), NULL); ?>
      </li><!-- .hidden-xs .hidden-sm -->
      <li id="footer-social-media">
        <?php print t('Follow UNEP:'); ?>
        <a href="<?php print url('http://www.facebook.com/pages/UNEP/287683225711'); ?>" target="_blank"><?php print theme('image', array('path' => $directory . '/img/icon-facebook.gif')); ?></a>
        <a href="<?php print url('http://twitter.com/unep'); ?>" target="_blank"><?php print theme('image', array('path' => $directory . '/img/icon-twitter.gif')); ?></a>
        <a href="<?php print url('rss'); ?>"><?php print theme('image', array('path' => $directory . '/img/icon-rss.gif')); ?></a>
      </li><!-- #footer-social-media -->
    </ul><!-- .list-inline #footer-list -->
  </div><!-- .container -->
</footer><!-- .footer -->
