var parseURL = function(href) {
    var l = document.createElement("a");
    l.href = href;
    return l;
};

function analytics_integration_google_analytics_send_hit(key, target_url, js_identifier, page_title, type) {
    type = typeof type !== 'undefined' ? type : 'pageview';
    var url = parseURL(target_url);
    var host = url.hostname;
    page_title = jQuery.trim(page_title);
    if (typeof ga == 'function') {
        ga('create', key, 'auto', {'name': js_identifier});
        ga(js_identifier + '.set', 'referrer', "http://" + document.domain);
        ga(js_identifier + '.set', 'hostname', host);
        ga(js_identifier + '.set', 'location', target_url);
        ga(js_identifier + '.set', 'title', page_title);
        ga(js_identifier + '.send', type);
    }
    else {
        console.error('Google Analytics is not initialized');
    }
}

function analytics_integration_piwik_send_hit(piwik_url, site_id, page_title) {
    var _paq = _paq || [];
    (function() {
        var u=(("https:" == document.location.protocol) ? "https://" + piwik_url + "/" : "http://" + piwik_url + "/");
        _paq.push(['setSiteId', site_id]);
        _paq.push(['setTrackerUrl', u+'piwik.php']);
        _paq.push(['setDocumentTitle', page_title]);
        _paq.push(['trackPageView']);
        _paq.push(['enableLinkTracking']);
        var script0 = document.getElementsByTagName('script')[0];
        if (script0 != null && !script0.src.match('(.*)piwik.js')) {
            var d = document,
                g = d.createElement('script'),
                s = d.getElementsByTagName('script')[0];
            g.type = 'text/javascript';
            g.defer = true;
            g.async = true;
            g.src = u + 'piwik.js';
            s.parentNode.insertBefore(g, s);
        }
    }
    )();
}
