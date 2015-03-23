<?php
/**
 * @file
 * terms.tpl.php
 *
 * @ingroup themeable
 */
?>
<div class="row">
  <div class="col-md-6">
    <div class="section-header">
      <button type="button" class="btn btn-default pull-right" data-toggle="tree" data-target="#terms-substantive"><?php print t('Show all'); ?></button>
      <h3><?php print t('Substantive terms'); ?></h3>
    </div><!-- .section-header -->
    <ul class="list-tree" id="terms-substantive">
      <li>
        <button class="toggle" data-toggle="tree-item" type="button"><span class="glyphicon glyphicon-plus-sign"></span></button>
        <a href="#">Lorem ipsum dolor sit amet</a>
        <ul class="list-tree collapse">
          <li>
            <button class="toggle" data-toggle="tree-item" type="button"><span class="glyphicon glyphicon-plus-sign"></span></button>
            <a href="#">Consectetur adipiscing elit</a>
            <ul class="list-tree collapse">
              <li><a href="#">Integer hendrerit arcu eu</a></li>
              <li><a href="#">Condimentum mattis</a></li>
            </ul><!-- .list-tree -->
          </li>
          <li>
            <button class="toggle" data-toggle="tree-item" type="button"><span class="glyphicon glyphicon-plus-sign"></span></button>
            <a href="#">Donec vestibulum neque consectetur</a>
            <ul class="list-tree collapse">
              <li><a href="#">Sollicitudin elit et</a></li>
            </ul><!-- .list-tree -->
          </li>
        </ul><!-- .list-tree .collapse -->
      </li>
      <li>
        <button class="toggle" data-toggle="tree-item" type="button"><span class="glyphicon glyphicon-plus-sign"></span></button>
        <a href="#">Vulputate tellus</a>
        <ul class="list-tree collapse">
          <li>
            <button class="toggle" data-toggle="tree-item" type="button"><span class="glyphicon glyphicon-plus-sign"></span></button>
            <a href="#">Proin in tortor sed lorem</a>
            <ul class="list-tree collapse">
              <li><a href="#">Feugiat consequat sit</a></li>
            </ul><!-- .list-tree -->
          </li>
        </ul><!-- .list-tree .collapse -->
      </li>
      <li><a href="#">Amet at sem</a></li>
    </ul><!-- .list-tree #terms-substantive -->
  </div>
  <div class="col-md-6">
    <div class="section-header">
      <button type="button" class="btn btn-default pull-right" data-toggle="tree" data-target="#terms-generic"><?php print t('Show all'); ?></button>
      <h3><?php print t('Generic terms'); ?></h3>
    </div><!-- .section-header -->
    <ul class="list-tree" id="terms-generic">
      <li>
        <button class="toggle" data-toggle="tree-item" type="button"><span class="glyphicon glyphicon-plus-sign"></span></button>
        <a href="#">Pellentesque lacinia</a>
        <ul class="list-tree collapse">
          <li><a href="#">Neque volutpat massa</a></li>
          <li><a href="#">Sollicitudin facilisis</a></li>
          <li>
            <button class="toggle" data-toggle="tree-item" type="button"><span class="glyphicon glyphicon-plus-sign"></span></button>
            <a href="#">Vivamus sollicitudin</a>
            <ul class="list-tree collapse">
              <li><a href="#">Velit a metus sodales</a></li>
              <li><a href="#">Vitae rutrum dolor tristique</a></li>
            </ul><!-- .list-tree -->
          </li>
          <li><a href="#">Nunc non ex consequat</a></li>
          <li><a href="#">Feugiat justo sit amet</a></li>
        </ul><!-- .list-tree .collapse -->
      </li>
      <li><a href="#">Commodo augue</a></li>
      <li><a href="#">Nunc non ex consequat</a></li>
    </ul><!-- .list-tree #terms-generic -->
  </div>
</div>
