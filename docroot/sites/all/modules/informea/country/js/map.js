var map;
function initialize() {
    var mapOptions = {
        zoom: parseInt(Drupal.settings.map.zoom),
        center: new google.maps.LatLng(Drupal.settings.map.latitude, Drupal.settings.map.longitude)
    };
    console.log(Drupal.settings.map.zoom);
    map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);
    var sites = Drupal.settings.map.sites;
    for (idx = 0; idx < sites.length; idx++) {
        var ob = sites[idx];
        new google.maps.Marker({
            position: new google.maps.LatLng(ob.field_latitude.und[0].value, ob.field_longitude.und[0].value),
            map: map,
            title: ob.title
        });
    }
}
google.maps.event.addDomListener(window, 'load', initialize);
