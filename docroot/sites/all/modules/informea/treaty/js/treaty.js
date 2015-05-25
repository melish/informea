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

  $('#selector-treaty').change(function () {
    var odata_name = $(this).val();
    if (odata_name) {
      window.location.href = Drupal.settings.basePath + 'treaties/' + odata_name;
    }
  });

  var smallIpop = $('.smallipop');
  if (smallIpop.length > 0) {
    smallIpop.smallipop({
      invertAnimation: true,
      preferredPosition: 'left',
      theme: 'default',
      popupOffset: 0
    });
  }

  var target;
  if (target = window.location.hash) {
    var el = $(target);
    if (el.length) {
      $.scrollTo(0).scrollTo(target, 'slow', {
        offset: -200
      });
      el.addClass('highlight');

    }
  }

  $('.panel-heading > .actions a').click(function (event) {
    event.stopPropagation();
  });

  var dlgModalDecision = $('#modal-decision');
  dlgModalDecision.on('loaded.bs.modal', function () {
    $(window).trigger('resize');
  });

  dlgModalDecision.on('hidden.bs.modal', function () {
    $(this).removeData('bs.modal');
  });

  $('[data-toggle="group"]').click(function () {
    var $element = $(this);
    var target = $element.data('target');
    if ($element.data('pressed')) {
      $element.data('pressed', false);
      $element.html('Expand all');
      $('.panel-collapse', target).collapse('hide');
    } else {
      $element.data('pressed', true);
      $element.html('Close all');
      $('.panel-collapse', target).collapse('show');
    }
  });
});
