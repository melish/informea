<div id="<?php print $div_id; ?>" style="cursor: pointer;">
</div>
<div id="foamtree-overlay" style="position: absolute; top: 0; left: 0; z-index: 100; width: 100%; height: 100%; display: none;"></div>
<div class="ajax-progress ajax-progress-throbber"><div id="foamtree-throbber" class="throbber" style="position: fixed; left: 50%; top: 50%; display: none;">&nbsp;</div></div>
<script>
  window.addEventListener("load", function() {
    var clicks_on_foamtree = 0;
    var foamtree = new CarrotSearchFoamTree({
      groupFillType: 'plain',
      rainbowColorDistribution: 'linear',
      id: "<?php print $div_id; ?>",
      onGroupClick: function (event) {
        if (!event.secondary) {
          event.preventDefault();
          setTimeout(function(){
            if (clicks_on_foamtree == 0) {
              foamtree.zoom(event.group);
              foamtree.open(event.group);
            }
            else {
              if (event.group != null && event.group.id != 0) {
                var path = 'taxonomy/term/' + event.group.id;
                jQuery('#foamtree-overlay').show();
                jQuery('#foamtree-throbber').show();
                window.location.href = path;
              }
            }
          }, 300);
          clicks_on_foamtree = 0;
        }
      },
      onGroupDoubleClick: function (event) {
        if (!event.secondary) {
          event.preventDefault();
          clicks_on_foamtree++;
        }
      },
      zoomMouseWheelFactor: 1,
      groupColorDecorator: function (opts, params, vars) {
        switch (params.group.label) {
          case 'Air and Climate':
            vars.groupColor = 'rgb(113,188,226)';
            break;
          case 'Biodiversity':
            vars.groupColor = 'rgb(229,163,77)';
            break;
          case 'Chemicals and Wastes':
            vars.groupColor = 'rgb(190,211,91)';
            break;
          case 'Environmental Law and Governance':
            vars.groupColor = 'rgb(98,185,139)';
            break;
          case 'Land':
            vars.groupColor = 'rgb(154,125,104)';
            break;
          case 'Water':
            vars.groupColor = 'rgb(34,111,145)';
            break;
        }
        vars.labelColor = "auto";
      }
    });

    function convert(clusters) {
      return clusters.map(function(cluster) {
        return {
          id:     cluster.id,
          label:  cluster.phrases.join(", "),
          weight: cluster.attributes && cluster.attributes["other-topics"] ? 0 : cluster.size,
          groups: cluster.clusters ? convert(cluster.clusters) : []
        }
      });
    };

    var clusts = Drupal.settings.foamtree.clusters

    foamtree.set({
      dataObject: {
        groups: convert(clusts)
      },
    });

    window.addEventListener("resize", (function() {
      var timeout;
      return function() {
        window.clearTimeout(timeout);
        timeout = window.setTimeout(foamtree.resize, 300);
      };
    })());

  });

</script>