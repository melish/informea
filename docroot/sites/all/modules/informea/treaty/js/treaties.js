jQuery(document).ready(function ($) {
  $('[data-filter="table"]').click(function (event) {
    event.preventDefault();

    $(this).parent().addClass('active').siblings().removeClass('active');

    var selector = $(this).data('selector');
    var target = this.hash;
    var value = $(this).data('value');
    var rows = $('> tbody > tr', target).hide().filter(function () {
      return $(selector, this).text().indexOf(value) > -1;
    }).show().length;

    $('.rows-visible', target).html(rows);
  });
});
