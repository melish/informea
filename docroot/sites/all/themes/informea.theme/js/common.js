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

  $.widget('custom.catcomplete', $.ui.autocomplete, {
    _create: function() {
      this._super();
      this.widget().menu('option', 'items', '> :not(.ui-autocomplete-category)');
    },
    _renderMenu: function(ul, items) {
      var that = this,
        currentCategory = '';
      $.each(items, function(index, item) {
        var li;

        if (item.category != currentCategory) {
          ul.append('<li class="ui-autocomplete-category">' + item.category + '</li>');
          currentCategory = item.category;
        }

        li = that._renderItemData(ul, item);

        if (item.category) {
          li.attr('aria-label', item.category + ' : ' + item.label);
        }
      });
    }
  });

  // TODO
  var data = [
    { category: '', label: 'anders', value: 'anders' },
    { category: '' , label: 'andreas', value: 'andreas' },
    { category: '' , label: 'antal', value: 'antal'},
    { category: 'Products' , label: 'annhhx10', value: 'annhhx10' },
    { category: 'Products' , label: 'annk K12', value: 'annk K12' },
    { category: 'Products' , label: 'annttop C13', value: 'annttop C13' },
    { category: 'People' , label: 'anders andersson', value: 'anders andersson' },
    { category: 'People' , label: 'andreas andersson', value: 'andreas andersson' },
    { category: 'People', label: 'andreas johnson', value: 'andreas johnson' }
  ];

  $('#edit-keys').catcomplete({
    delay: 0,
    source: data
  });
});
