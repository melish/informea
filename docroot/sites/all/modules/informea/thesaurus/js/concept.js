jQuery(document).ready(function ($) {
  $('a[data-toggle="tab"]').on('shown.bs.tab', function (e) {
    var t = '#' + $(e.target).attr('aria-controls');
    var url = $(e.target).attr('data-source');
    if (!$(t).hasClass('ajax-processed')) {
      $(t).load(url, '', function() {
        $(this).addClass('ajax-processed');
      });
    }
  });
  console.log($('a[data-toggle="tab"]:first').tab('show'));
});

function ecolexAjaxReload(url) {
  alert(url);
}