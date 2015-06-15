jQuery(document).ready(function ($) {
  $('#dialog-modal-ajax').on('loaded.bs.modal', function () {
    $(window).trigger('resize');
  });

  $('#dialog-modal-ajax').on('hidden.bs.modal', function () {
    $(this).removeData('bs.modal');
  });

  $('.permalink').click(function (event) {
    event.stopPropagation();
  });

  $('[data-toggle="select"]').click(function (event) {
    var $element = $(this);
    var target = $element.attr('href');

    event.preventDefault();

    $('option', target).prop('selected', true);
  });
});
