var map;
var infoWindow;

function initialize() {
  var pinW = new google.maps.MarkerImage("/sites/all/themes/informea.theme/img/red-pin.png",
    new google.maps.Size(21, 34),
    new google.maps.Point(0,0),
    new google.maps.Point(10, 34));

  var pinR = new google.maps.MarkerImage("/sites/all/themes/informea.theme/img/blue-pin.png",
    new google.maps.Size(21, 34),
    new google.maps.Point(0,0),
    new google.maps.Point(10, 34));

  var pinShadow = new google.maps.MarkerImage("/sites/all/themes/informea.theme/img/pin-shadow.png",
    new google.maps.Size(40, 37),
    new google.maps.Point(0, 0),
    new google.maps.Point(12, 35));

  var mapOptions = {
    zoom: parseInt(Drupal.settings.map.zoom),
    center: new google.maps.LatLng(Drupal.settings.map.latitude, Drupal.settings.map.longitude)
  };

  map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);
  infoWindow = new google.maps.InfoWindow();

  var sites = Drupal.settings.map.sites;

  for (idx = 0; idx < sites.length; idx++) {
    function initMarker() {
      var ob = sites[idx];
      var marker = new google.maps.Marker({
        position: new google.maps.LatLng(ob.field_latitude.und[0].value, ob.field_longitude.und[0].value),
        map: map,
        title: ob.title,
        icon: ob.field_treaty.und[0].target_id == "272" ? pinR : pinW, // 272 - Ramsar
        shadow: pinShadow
      });

      google.maps.event.addListener(marker, 'click', function () {
        var content = '<a href="' + ob.field_url.en[0].url + '" target="_blank">' + ob.title + '</a>';

        infoWindow.setContent(content);
        infoWindow.open(map, marker);
      });
    }

    initMarker();
  }
}

google.maps.event.addDomListener(window, 'load', initialize);
