var map;
function initialize() {
    var mapOptions = {
        zoom: parseInt(Drupal.settings.map.zoom),
        center: new google.maps.LatLng(Drupal.settings.map.latitude, Drupal.settings.map.longitude)
    };
    console.log(Drupal.settings.map.zoom);
    map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);
}
google.maps.event.addDomListener(window, 'load', initialize);
