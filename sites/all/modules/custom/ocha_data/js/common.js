(function ($) {

  Drupal.behaviors.ochaCharts = {
    html_ids: [],
    init: false,
    attach: function (context, settings) {
      if (this.init)
        return;
      this.init = true;

      $(window).resize(function() {
        for (var i = 0; i < Drupal.behaviors.ochaCharts.html_ids.length; i++)
          Plotly.Plots.resize($('#' + Drupal.behaviors.ochaCharts.html_ids[i]).get(0));
      });
    },
    add: function(html_id) {
      this.html_ids[this.html_ids.length] = html_id;
    }
  };

})(jQuery);
