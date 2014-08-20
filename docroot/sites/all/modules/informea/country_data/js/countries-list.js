jQuery(document).ready(function ($) {
  $('[data-filter="index"]').click(function (event) {
    event.preventDefault();

    var $parent = $(this).parent();
    var $target = $(this).data('target');

    $parent.addClass('active').siblings().removeClass('active');

    $('> .country-group', $target).hide().filter(this.hash || '*').show();
  });
});
