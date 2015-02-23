jQuery(document).ready(function ($) {
  $('#selector-country').change(function () {
    var iso2 = $(this).val();

    if (iso2) {
      window.location.href = Drupal.settings.basePath + 'countries/' + iso2;
    }
  });
});
