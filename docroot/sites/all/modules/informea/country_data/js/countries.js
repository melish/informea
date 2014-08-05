(function ($) {
  // This method allows to create charts with a single config.
  var map = AmCharts.makeChart('ammap', {
    areasSettings: {
      color: '#0099d5',
      rollOverColor: '#ffcc66',
      selectable: true,
      selectedColor: '#ffcc66'
    },
    backgroundZoomsToTop : true,
    dataProvider: {
      areas: [],
      map: 'worldHigh'
    },
    pathToImages: 'http://www.amcharts.com/lib/3/images/',
    theme: 'light',
    type: 'map',
    zoomControl: {
      buttonFillColor: '#0099d5',
      buttonRollOverColor: '#ffcc66',
      zoomFactor: 4
    }
  });

  // Dispatched when user clicks on a map object.
  map.addListener('clickMapObject', function (event) {
    if (event.mapObject.id) {
      window.location.href = Drupal.settings.basePath + 'countries/' + event.mapObject.id;
    }
  });
})(jQuery);
