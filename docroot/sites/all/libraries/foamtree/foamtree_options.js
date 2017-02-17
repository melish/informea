window.addEventListener("resize", (function() {
    var timeout;
    return function() {
        window.clearTimeout(timeout);
        timeout = window.setTimeout(foamtree.resize, 300);
    };
})());