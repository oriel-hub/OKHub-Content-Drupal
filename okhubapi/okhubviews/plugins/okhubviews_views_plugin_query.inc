<?php
// $Id;

/**
 * @file
 *   Views query plugin for the OKHUB API.
 */

class okhubviews_views_plugin_query extends views_plugin_query_default {
  var $okhub_wrapper;
  var $orderby;
  /**
   * @var bool If the data set (site) has been set then we will handle the request execution differently
   */
  protected $hasDataset = false;

  /**
   * Constructor; Create the basic query object and fill with default values.
   */
  function init($base_table, $base_field, $options) {
    parent::init($base_table, $base_field, $options);
    $this->okhub_wrapper = new OkhubApiWrapper();
    $this->okhub_wrapper->setPriorityDatasource(variable_get('okhubimport_priority_datasource', ''));
    $this->okhub_wrapper->setPriorityLanguage(variable_get('okhubimport_priority_language', ''));
  }

  /**
   * Set the dataset that we should be using to make requests from the API (e.g. bridge or eldis).
   *
   * @param $dataset
   */
  function add_dataset($dataset) {
    if (isset($dataset)) {
      // A dataset has been set from an external source, so we update our object's state to reflect that.
      $this->hasDataset = true;
      $this->okhub_wrapper->setSite($dataset);
    }
  }

  function add_filter($group, $filter, $value) {
    if ($this->check_filter($group, $filter)) {
      $value = preg_replace('/\s*(\&|AND)\s*/i','&',$value); 
      $value = preg_replace('/\s*(\||OR)\s*/i','|',$value);
      $this->where[$group]['conditions'][] = array(
            'field' => $filter,
            'value' => $value
          );
    }
    else {
      watchdog('okhubviews', 'Filter !filter cannot be added to more than one group. Filter ignored.', array('!filter' => $filter), WATCHDOG_NOTICE);
    }
  }

  function check_filter($group, $filter) {
    $found = FALSE;
    $groups = array_keys($this->where);
    while (($group_key = current($groups)) && (!$found)) {
      if (($group_key !== $group) && (!empty($this->where[$group_key]['conditions']))) {
        while ((list($field_key, $field_array) = each($this->where[$group_key]['conditions'])) && (!$found)) {
          $found = ($field_array['field'] === $filter);
        }
      }
      next($groups);
    }
    return (!$found);
  }

  function add_field($table, $field, $alias = '', $params = array()) {
    $field_info = array(
      'field' => $field,
      'table' => $table,
      'alias' => $field,
    ) + $params;
    if (empty($this->fields[$field])) {
      $this->fields[$field] = $field_info;
    }
    return $field;
  }

  public function add_orderby($table, $field = NULL, $order = "ASC", $alias = '', $params = array()){
    $this->orderby = array(
      'order' => $order,
      'orderby_field' => $field,
    );
  }

  public function build(&$view) {
    $view->init_pager();
  }

  /**
   * Executes the query and fills the associated view object with according
   * values.
   * @param view $view
   *   The view which is executed.
   */
  function execute(&$view) {
    $type = str_replace("okhubviews_", "", $view->base_table);
    $this->okhub_wrapper->setApiKey(variable_get('okhubapi_api_key', ''));
    $this->okhub_wrapper->setNumRequested($this->pager->options['items_per_page']);
    $this->okhub_wrapper->setOffset($this->pager->current_page * $this->pager->options['items_per_page']);
    $this->okhub_wrapper->setObjectType($type);
    $this->okhub_wrapper->setFormat('full');
    $this->set_url();
    $start = microtime();
    $response = $this->okhub_wrapper->makeRequest();
    $view->execute_time = microtime() - $start;
    $view->result = $response->getResults();
    $this->pager->total_items = $view->total_rows = $response->getTotalResults();
    $this->pager->update_page_info();
  }

  /**
   * Modify the request object so that we are making the correct query based on the parameters and query terms.
   */
  function set_url() {
    if (isset($this->where)) {
      foreach ($this->where as $group) {
        $params = array();
        if (isset($group['type'])) {
          if (strcasecmp($group['type'],"AND") == 0) {
            $oper = '&';
          }
          elseif (strcasecmp($group['type'],"OR") == 0) {
            $oper = '|';
          }
        }
        foreach ($group['conditions'] as $condition) {
          $field = $condition['field'];
          $value = $condition['value'];
          $field = $this->okhub_parameter($field);
          $params[$field][] = $value;
        }
        foreach ($params as $param => $values) {
          $value = implode($oper, $values);
          if ($param === 'object_id') {
            $this->okhub_wrapper->setObjectId($value);
            $this->okhub_wrapper->setTypeRequest('get');
          }
          else {
            $this->okhub_wrapper->setParam($param, $value);
          }
        }
      }
    }
    if (isset($this->orderby['order']) && (isset($this->orderby['orderby_field']))) {
      $order = 'sort_' . strtolower($this->orderby['order']);
      $this->okhub_wrapper->setParam($order, $this->orderby['orderby_field']);
    }
    // Check whether we have set a dataset already, if not then we will set using the default/configured one
    if (!$this->hasDataset){
      $dataset = variable_get('okhubapi_default_dataset', OKHUB_API_DEFAULT_DATASET);
      $this->okhub_wrapper->setSite($dataset);
    }
  }

  function okhub_parameter($field) {
    if ($field === 'query_filter') {
      $field = 'q';
    }
    else {
      $field = str_replace('_filter','',$field);
    }
    return $field;
  }

}
