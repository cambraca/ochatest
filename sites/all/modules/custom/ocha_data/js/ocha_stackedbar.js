(function ($) {

  Drupal.behaviors.ochaStackedbar = {
    attach: function (context, settings) {
      $('.ocha_stackedbar', context).once('ochaStackedbar', function () {
        var id = this.id;
        var data = settings.ocha_data[id].sets;

        var layout = {
          title: settings.ocha_data[id].title,
          barmode: 'stack',
          legend: {orientation: "h", x:0, y:-1}
        };

        Drupal.behaviors.ochaCharts.add(id);
        Plotly.plot($(this).get(0), data, layout, {showLink: false});
      });
    }
  };

})(jQuery);
