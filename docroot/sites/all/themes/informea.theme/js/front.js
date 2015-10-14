jQuery(document).ready(function ($) {
  $('.country-selector .form-control').change(function () {
    var iso2 = $(this).val();

    if (iso2) {
      window.location.href = Drupal.settings.basePath + 'countries/' + iso2;
    }
  });
});

window.onYouTubeIframeAPIReady = function() {
  jQuery('.youtube-field-player').each(function(idx, iframe) {
    var id = jQuery(iframe).attr('id');
    new YT.Player(id, {
      events: {
        'onStateChange': youTubePlayerChange
      }
    });
  });
};

window.youTubePlayerChange = function(event) {
  if (event.data == 1) {
    jQuery('#carousel-updates').carousel('pause');
  }
  else {
    jQuery('#carousel-updates').carousel('cycle');
  }
};
