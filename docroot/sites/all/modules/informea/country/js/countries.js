jQuery(document).ready(function() {
  var map = AmCharts.makeChart('ammap_div', {
    type: 'map',
    theme: 'light',
    pathToImages: 'https://www.amcharts.com/lib/3/images/',
    dataProvider: {
      alpha: 1,
      map: 'worldHigh',
      getAreasFromMap: true
    },
    backgroundZoomsToTop: true,
    areasSettings: {
      color: '#0099D5',
      rollOverColor: '#ED9F0D',
      selectable: true,
      selectedColor: '#ED9F0D'
    },
    zoomControl: {
      buttonFillColor: '#0099D5',
      buttonRollOverColor: '#FFCC66',
      zoomFactor: 4
    },
    balloonLabelFunction: function (mapObject, ammap) {
      return Drupal.settings.country.stats[mapObject.id];
    }
  });
  map.addListener('clickMapObject', function (event) {
    if (typeof event.mapObject.id != 'undefined') {
      var iso2 = event.mapObject.id;

      window.location = Drupal.settings.basePath + 'countries/' + iso2.toLowerCase();
    }
  });
});
