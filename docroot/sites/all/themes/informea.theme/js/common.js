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
    {
      category: '',
      label: 'anders',
      link: '#',
      value: 'anders'
    },
    {
      category: '',
      label: 'andreas',
      link: '#',
      value: 'andreas'
    },
    {
      category: '',
      label: 'antal',
      link: '#',
      value: 'antal'
    },
    {
      category: 'Products',
      label: 'annhhx10',
      link: '#',
      value: 'annhhx10'
    },
    {
      category: 'Products',
      label: 'annkK12',
      link: '#',
      value: 'annkK12'
    },
    {
      category: 'Products',
      label: 'annttopC13',
      link: '#',
      value: 'annttopC13'
    },
    {
      category: 'People',
      label: 'andersandersson',
      link: '#',
      value: 'andersandersson'
    },
    {
      category: 'People',
      label: 'andreasandersson',
      link: '#',
      value: 'andreasandersson'
    },
    {
      category: 'People',
      label: 'andreasjohnson',
      link: '#',
      value: 'andreasjohnson'
    }
  ];

  $('#edit-keys').catcomplete({
    delay: 0,
    source: data,
    select: function (event, ui) {
      if (ui.item.link) {
        window.location.href = ui.item.link;
      }
    }
  });
});
