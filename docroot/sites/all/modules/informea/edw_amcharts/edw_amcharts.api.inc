<?php

/**
 * hook_amcharts_ajax_access().
 * Provides access to the Ajax endpoint.
 *
 * @return bool
 */
function hook_edw_amcharts_ajax_access_alter() {
  return TRUE;
}

/**
 * hook_edw_amcharts_chart_data().
 * Alter chart before being rendered.
 *
 * @param string $chart_id
 *   ID of the chart
 * @param array $data
 *   amCharts dataProvider
 * @param $options
 *   Additional options to render the chart.
 */
function hook_edw_amcharts_chart_data($data, $chart_id, $options) {

}
