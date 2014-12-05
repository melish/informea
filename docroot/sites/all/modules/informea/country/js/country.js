jQuery(document).ready(function ($) {
  // This method allows to create charts with a single config.
  AmCharts.makeChart('chart-bar', {
    'type': 'serial',
    'pathToImages': 'http://cdn.amcharts.com/lib/3/images/',
    'categoryField': 'category',
    'rotate': true,
    'startDuration': 1,
    'theme': 'light',
    'categoryAxis': {
      'gridPosition': 'start'
    },
    'graphs': [{
      'fillAlphas': 1,
      'type': 'column',
      'valueField': 'column-1'
    }],
    'valueAxes': [{
      'id': 'ValueAxis-1',
      'title': ''
    }],
    'dataProvider': [{
      'category': 'Judical decision',
      'column-1': 625
    },
    {
      'category': 'Judical decision of a inferior court',
      'column-1': 720
    },
    {
      'category': 'Preliminary decision',
      'column-1': 120
    },
    {
      'category': 'Judical notice',
      'column-1': 440
    },
    {
      'category': 'Judical decision of a superior court',
      'column-1': 210
    },
    {
      'category': 'Other',
      'column-1': 320
    }]
  });
});
