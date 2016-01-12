jQuery(document).ready(function ($) {
  if (hash = window.location.hash) {
    region = $('[data-value="' + hash.substr(1) + '"]');

    if (region.length != 0) {
      region.parent().addClass('active').siblings().removeClass('active');

      var selector = region.data('selector');
      var target = '#table-treaties';
      var value = region.data('value');
      var rows = $('> tbody > tr', target).hide().filter(function () {
        return $(selector, this).text().indexOf(value) > -1;
      }).show().length;

      $('.view-treaty-listing-page .total').html(rows);

      // Collapse all protocols
      $('> tbody > tr.active', target).hide();
      $('.glyphicon-minus-sign', target).toggleClass('glyphicon-plus-sign glyphicon-minus-sign');
    }
  }
  $('[data-filter="table"]').click(function (event) {
    event.preventDefault();

    $(this).parent().addClass('active').siblings().removeClass('active');

    var selector = $(this).data('selector');
    var target = this.hash;
    var value = window.location.hash = $(this).data('value');
    var rows = $('> tbody > tr', target).hide().filter(function () {
      return $(selector, this).text().indexOf(value) > -1;
    }).show().length;

    $('.view-treaty-listing-page .total').html(rows);

    // Collapse all protocols
    $('> tbody > tr.active', target).hide();
    $('.glyphicon-minus-sign', target).toggleClass('glyphicon-plus-sign glyphicon-minus-sign');
  });

  $('[data-toggle="protocols"]').click(function (event) {
    event.preventDefault();

    var nid = $(this).data('nid');

    $('.glyphicon', this).toggleClass('glyphicon-plus-sign glyphicon-minus-sign');

    $('[data-parent-treaty=' + nid + ']').toggle();
  });
});
