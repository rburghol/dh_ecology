<?php
// dh_ecology.views.inc


// Implements hook_view_data_alter().

function dh_ecology_views_data_alter(&$data) {

  // do date setups
  $defaults_date = array(
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $defaults_numeric = array(
    'title' => t('Numeric Field'),
    'help' => t('Numeric Field.'), // The help that appears on the UI,
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
      'float' => TRUE, // enables advanced formatting options
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );

  $numcols = array();
  $strcols = array(
    'isolate',
    'bundle',
    'species',
    'source',
    'ecology',
    'genus',
    'host_organism',
    'primer_f',
    'primer_r',
    'acquisition_num',
    'sequence'
  );
  $datecols = array('modified');
  foreach ($strcols as $thiscol) {
    $data['dh_ecology_isolate'][$thiscol] = $defaults_string;
    $data['dh_ecology_isolate'][$thiscol]['title'] = t("Ecology Data $thiscol");
    $data['dh_ecology_isolate'][$thiscol]['help'] = t("Ecology $thiscol");
  }
  foreach ($numcols as $thiscol) {
    $data['dh_ecology_isolate'][$thiscol] = $defaults_numeric;
    $data['dh_ecology_isolate'][$thiscol]['title'] = t("Ecology $thiscol");
    $data['dh_ecology_isolate'][$thiscol]['help'] = t("Ecology $thiscol");
  }
  foreach ($datecols as $thiscol) {
    $data['dh_ecology_isolate'][$thiscol]['field'] = $defaults_date['field'];
    $data['dh_ecology_isolate'][$thiscol]['sort'] = $defaults_date['sort'];
    $data['dh_ecology_isolate'][$thiscol]['filter'] = $defaults_date['filter'];
  }

	// join Property to dH_feature 
  $data['dh_properties']['table']['join']['dh_ecology_isolate'] = array(
    'left_table' => 'dh_ecology_isolate',
    'left_field' => 'iid',
    'field' => 'featureid'
    'extra' => array(
      0 => array('right_table' => 'dh_properties', 'field' => 'entity_type', 'value' => 'dh_ecology_isolate') 
    ),
  );	
	// join Property to dH_feature 
  $data['dh_timeseries']['table']['join']['dh_ecology_isolate'] = array(
    'left_table' => 'dh_ecology_isolate',
    'left_field' => 'iid',
    'field' => 'featureid'
    'extra' => array(
      0 => array('right_table' => 'dh_timeseries', 'field' => 'entity_type', 'value' => 'dh_ecology_isolate') 
    ),
  );	
  // dh feature vars - creates a matrix of features and variables for use 
  // in present/absent tables
  $q = "  create or replace view dh_ecology_vars as ";
  $q .= " select a.hydroid as varid, a.varkey as varkey, ";
  $q .= " a.vocabulary as vocabulary, a.vardesc, b.hydroid as featureid ";
  $q .= " from dh_variabledefinition as a ";
  $q .= " CROSS JOIN dh_ecology_isolate as b ";
  db_query($q);
 
  // dh_variabledefinition to dh_feature extra join
  $data['dh_ecology_vars']['table'] = array(
    'group' => 'dH Feature',
    'title' => t('All dH Feature:Variable Combos'),
    'help' => t('All dH Feature:Variable Combos.')
  );
	// join to var def
   $data['dh_ecology_vars']['varid'] = $defaults_numeric;
   $data['dh_ecology_vars']['varid']['title'] = 'dH Ecology-Vars Variable ID';
   $data['dh_ecology_vars']['varid']['help'] = 'dH Ecology-Vars Variable ID';
   $data['dh_ecology_vars']['featureid'] = $defaults_numeric;
   $data['dh_ecology_vars']['featureid']['title'] = 'dH Ecology-Vars Feature ID';
   $data['dh_ecology_vars']['featureid']['help'] = 'dH Ecology-Vars Feature ID';
   $data['dh_ecology_vars']['varkey'] = $defaults_string;
   $data['dh_ecology_vars']['varkey']['title'] = 'dH Ecology-Vars VarKey';
   $data['dh_ecology_vars']['varkey']['help'] = 'dH Ecology-Vars VarKey';
   $data['dh_ecology_vars']['vardesc'] = $defaults_string;
   $data['dh_ecology_vars']['vardesc']['title'] = 'dH Ecology-Vars Description';
   $data['dh_ecology_vars']['vardesc']['help'] = 'dH Ecology-Vars Description';
   $data['dh_ecology_vars']['vocabulary'] = $defaults_string;
   $data['dh_ecology_vars']['vocabulary']['title'] = 'dH Ecology-Vars Vocabulary';
   $data['dh_ecology_vars']['vocabulary']['help'] = 'dH Ecology-Vars Vocabulary';
   // is this an error? I think it should be "table" not "vocabulary" here
   //$data['dh_ecology_vars']['vocabulary']['join']['dh_variabledefinition'] = array(
   $data['dh_ecology_vars']['table']['join']['dh_variabledefinition'] = array(
     'left_table' => 'dh_variabledefinition',
     'left_field' => 'hydroid',
     'field' => 'varid'
   );
	// join to dH AdminReg Features
   $data['dh_ecology_vars']['table']['join']['dh_feature'] = array(
     'left_table' => 'dh_feature',
     'left_field' => 'hydroid',
     'field' => 'featureid'
   );

}
