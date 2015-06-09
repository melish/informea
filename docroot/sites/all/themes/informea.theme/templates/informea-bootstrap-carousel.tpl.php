<?php
$attributes = '';
/** @var array $variables */
$id = $variables['attributes']['id'];
$slides = $variables['slides'];
if (isset($variables['attributes'])) {
  $attributes = drupal_attributes($variables['attributes']);
}
?>
<div<?php print $attributes; ?>>
  <div class="carousel-container">
    <div class="carousel slide" data-ride="carousel" id="carousel-updates">
      <ol class="carousel-indicators">
      <?php
        for($i = 0; $i < count($slides); $i++):
          $la = array('data-target' => '#carousel-updates', 'data-slide-to' => $i);
          if ($i == 0) {
            $la['class'] = 'active';
          }
      ?>
        <li<?php print drupal_attributes($la); ?>></li>
      <?php endfor; ?>
      </ol><!-- .carousel-indicators -->
      <div class="carousel-inner">
      <?php
        foreach($slides as $i => $slide):
          $la = array('class' => array('item'));
          if ($i == 0) {
            $la['class'][] = 'active';
          }
      ?>
          <div<?php print drupal_attributes($la);?>>
            <img alt="" src="<?php print $slide['image']; ?>">
            <div class="carousel-caption">
              <div class="media">
                <div class="media-left">
                  <?php print $slide['logo']; ?>
                </div><!-- .media-left -->
                <div class="media-body">
                  <span><?php print $slide['date']; ?></span>
                  <p><?php print $slide['link']; ?></p>
                </div><!-- .media-body -->
              </div><!-- .media -->
            </div><!-- .carousel-caption -->
          </div><!-- .item .active -->
      <?php endforeach; ?>
      </div><!-- .carousel-inner -->
      <a class="left carousel-control" href="#carousel-updates" data-slide="prev" role="button">
        <i class="glyphicon glyphicon-chevron-left"></i>
      </a>
      <a class="right carousel-control" href="#carousel-updates" data-slide="next" role="button">
        <i class="glyphicon glyphicon-chevron-right"></i>
      </a>
    </div><!-- #carousel-updates .carousel .slide -->
  </div><!-- .carousel-container -->
</div><!-- .col-md-6 #col-carousel -->
