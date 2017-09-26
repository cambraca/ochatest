(function ($) {

  Drupal.behaviors.ochaCerfMap = {
    attach: function (context, settings) {
      $('.ocha_cerf_map', context).once('ochaCerfMap', function () {
        var id = this.id;
        var data = [{
          type: 'choropleth',
          locations: settings.ocha_data[id].countries,
          z: settings.ocha_data[id].values,
          text: settings.ocha_data[id].labels,
          autocolorscale: true
        }];

        var layout = {
          title: settings.ocha_data[id].title,
          geo: {
            projection: {
              type: 'natural earth'
            },
            showcountries: true
          }
        };

        Drupal.behaviors.ochaCharts.add(id);
        Plotly.plot($(this).get(0), data, layout, {showLink: false});
      });
    }
  };

})(jQuery);
