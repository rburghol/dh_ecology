<?php


function dh_ecology_webform_getmap() {
  global $wfmap;
  // dH Webform integration
  if (!isset($wfmap)) {
    $wfmap = array(); // keyed on name from webform table 
  }
  $wfmap['grower_info'] = dh_webform_grower_info();
  $wfmap['vitis_site_desc'] = dh_webform_vitis_site_desc();
  $wfmap['td_recent_activity'] = dh_webform_vitis_recent();
  $wfmap['td_sample_submittal'] = dh_webform_trunk_disease_sample();
  $wfmap['td_full_submittal'] = dh_webform_td_full_submittal();

  return $wfmap;
}

function dh_webform_grower_info() {
  $wfmap = array();
  $wfmap[] = array(
    'entity' => 'dh_adminreg_contact',
    'description' => 'dH Contact',
    'bundle' => 'dh_adminreg_contact',
    'debug' => FALSE,
    'fields' => array( 
      array('webform_reftype' => 'constant', 'refvalue' => 'grower', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_firstname', 'fieldname' => 'firstname'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_lastname', 'fieldname' => 'lastname'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_address', 'fieldname'=> 'address1'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_address2', 'fieldname'=> 'address2'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_city', 'fieldname' => 'city'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_state', 'fieldname' => 'state'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_zip', 'fieldname' => 'postal_code'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_e_mail_address', 'fieldname'=> 'email'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_phone_number', 'fieldname'=> 'phone'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_vineyard_coordinates', 'fieldname' => 'description'),
      // will have a link to the user dh_link_user_contact
      array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'userid', 'fieldname'=> 'dh_link_user_contact'),
    ),
    'resultid' => 'contactid',
    'writeback' => array(
      'contact_id' => 'contactid',
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Local Extension Office',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'notnull_fields' => array('proptext'),
    'handler' => 'dh_webform_insert_property', // a function to handle this record type. we should have a default function to handle easy cases for each dH Entity Type, but allow custom functions too
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'orgid', 'fieldname' => 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'local_extension_office', 'fieldname'=> 'propname'),
      array('webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'entity' => 'dh_variabledefinition', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_local_extension_offices', 'fieldname'=> 'proptext', 'concat' => ','),
    ),
    'resultid' => 'local_extension_pid',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Plant Disease Clinic',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'notnull_fields' => array('proptext'),
    'handler' => 'dh_webform_insert_property', // a function to handle this record type. we should have a default function to handle easy cases for each dH Entity Type, but allow custom functions too
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'orgid', 'fieldname' => 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'plant_disease_clinic', 'fieldname'=> 'propname'),
      array('webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'entity' => 'dh_variabledefinition', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_plant_disease_clinic', 'fieldname'=> 'proptext', 'concat' => ','),
    ),
    'resultid' => 'plant_disease_clinic_pid',
  );
  return $wfmap;
}

function dh_webform_vitis_site_desc() {
  $wfmap = array();
  $wfmap[] = array(
    'entity' => 'dh_adminreg_feature',
    'description' => 'Vineyard or Block',
    'bundle' => 'registration',
    'debug' => FALSE,
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_vineyard_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => 'vineyard', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'userid', 'fieldname'=> 'dh_link_admin_record_mgr_id'),
    ),
    'resultid' => 'vid',
    'writeback' => array(
      'vineyard_adminid' => 'vid',
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_feature',
    'description' => 'Vineyard or Block Land Unit (stored as block)',
    'bundle' => 'landunit',
    'debug' => FALSE,
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_vineyard_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => 'block', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'constant', 'refvalue' => 'test description', 'fieldname' => 'description'),
      array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'userid', 'fieldname'=> 'dh_link_feature_mgr_id'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'vid', 'fieldname'=> 'dh_link_admin_location'),
    ),
    'resultid' => 'blockid',
    'writeback' => array(
      'block_hydroid' => 'blockid',
    ),
  );
  
  // Site Profile: 
  //   As Prop: soil, slope, drainage, exposure, elevation, 
  
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Soil texture',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'soil_prop_texture'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_soil_texture', 'fieldname'=> 'proptext'),
    ),
    'resultid' => 'soil_texture_pid',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Slope',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'site_slope'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_terrain', 'fieldname'=> 'proptext'),
    ),
    'resultid' => 'terrain_pid',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Drainage',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'site_drainage'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_drainage', 'fieldname'=> 'propvalue'),
    ),
    'resultid' => 'drainage_pid',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Exposure',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'site_sun_exposure'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_site_exposure', 'fieldname'=> 'proptext'),
    ),
    'resultid' => 'exposure_pid',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Elevation',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'site_elevation'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_elevation', 'fieldname'=> 'proptext'),
    ),
    'resultid' => 'exposure_pid',
  );
  
  // crop, varietal, rootstock - dh properties on block
  // symptoms, brief desc, specific questions - dh properties on sample feature
  $wfmap[] = array(
    'entity' => 'dh_adminreg_feature',
    'description' => 'Trunk Disease Site Description Submittal',
    'bundle' => 'submittal',
    'debug' => FALSE,
    'fields' => array(
      // this link is not yet active
      //array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'organization_id', 'fieldname' => 'dh_link_admin_submittal_org'),
      array('webform_reftype' => 'constant', 'refvalue' => 'td_site_form', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_vineyard_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => '', 'fieldname' => 'description'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'vid', 'fieldname'=> 'dh_link_admin_submittal_pr'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'blockid', 'fieldname'=> 'dh_link_feature_submittal'),
      array('webform_reftype' => 'env', 'refvalue' => 'now', 'fieldname'=> 'modified'),
      array('webform_reftype' => 'constant', 'refvalue' => 'Webform Form', 'fieldname' => 'formtype'),
    ),
    'resultid' => 'td_submittal_id',
    'writeback' => array(
      'td_submittal_id' => 'td_submittal_id',
    ),
  ); 
  
  $wfmap[] = array(
    'entity' => 'dh_adminreg_feature',
    'description' => 'Site Description Submittal Link to Original Form',
    'bundle' => 'submittal',
    'hook' => 'insert',
    'debug' => FALSE,
    'notnull_fields' => array('dh_link_webform_submittal'),
    'fields' => array(
      // this link is not yet active
      //array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'organization_id', 'fieldname' => 'dh_link_admin_submittal_org'),
      array('webform_reftype' => 'result', 'refvalue' => 'td_submittal_id', 'fieldname' => 'adminid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'Webform Form', 'fieldname' => 'formtype'),
      array('webform_reftype' => 'entity_reference_env', 'refvalue' => 'sid', 'fieldname'=> 'dh_link_webform_submittal'),
      array('webform_reftype' => 'env', 'refvalue' => 'sid', 'fieldname' => 'formid'),
    ),
    'resultid' => '',
  ); 
  
  return $wfmap;
} 

function dh_webform_vitis_recent() {
  $wfmap = array();
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Spring Weather',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'form_key', 'refvalue' => 'block_hydroid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'weather_pd_sum_season'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'spring', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_spring', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'spring_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Summer Weather',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'form_key', 'refvalue' => 'block_hydroid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'weather_pd_sum_season'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'summer', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_summer', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'summer_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Fall Weather',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'form_key', 'refvalue' => 'block_hydroid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'weather_pd_sum_season'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'fall', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_fall', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'fall_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Winter Weather',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'form_key', 'refvalue' => 'block_hydroid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'weather_pd_sum_season'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'winter', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_winter', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'winter_tsid',
  );
  
  // Management Actions
  //   As TS: cover crop, weed management, nutrient application (tstime is spring, tstext is nutrients), soil water status (date of submittal)
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Cover Crop',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'form_key', 'refvalue' => 'block_hydroid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'agman_cover_crop'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'spring', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_cover_crop', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'covercrop_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Weed Management',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'form_key', 'refvalue' => 'block_hydroid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'agman_weeding'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'winter', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_weed_management', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'weeding_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Nutrient Application',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'form_key', 'refvalue' => 'block_hydroid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'agchem_apply_fert'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_nutrient_application_timing', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_nutrient_application', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => null, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'nutrient_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Soil Water Status',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'form_key', 'refvalue' => 'block_hydroid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'soil_prop_wc'), 
        ),
      ),
      array('webform_reftype' => 'env', 'refvalue' => 'now', 'fieldname'=> 'tstime'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_soil_water_status', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'soilwater_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_adminreg_feature',
    'description' => 'Site Description Submittal Link to Original Form',
    'bundle' => 'submittal',
    'hook' => 'insert',
    'debug' => FALSE,
    'fields' => array(
      // this link is not yet active
      //array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'organization_id', 'fieldname' => 'dh_link_admin_submittal_org'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'td_submittal_id', 'fieldname' => 'adminid'),
      array('webform_reftype' => 'entity_reference_env', 'refvalue' => 'sid', 'fieldname'=> 'dh_link_webform_submittal'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'spring_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'summer_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'fall_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'winter_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'soilwater_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'nutrient_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'weeding_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'covercrop_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
    ),
    'resultid' => '',
  ); 
  
  return $wfmap;
} 

function dh_webform_trunk_disease_sample() {
  $wfmap = array();
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Sample Submitted',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_sampleid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'sample_event'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vsample_date', 'fieldname'=> 'tstime'),
    ),
    'resultid' => 'sample_event_tid',
  );
  
  // crop, varietal, rootstock - dh properties on block
  // symptoms, brief desc, specific questions - dh properties on sample feature
  
  // submittal record that ties together the submission event, the submission sample location (block), and the vineyard (admin registration record)
  $wfmap[] = array(
    'entity' => 'dh_adminreg_feature',
    'description' => 'Sample Submittal Link to Original Form',
    'bundle' => 'submittal',
    'hook' => 'insert',
    'debug' => FALSE,
    'fields' => array(
      // this link is not yet active
      //array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'organization_id', 'fieldname' => 'dh_link_admin_submittal_org'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'td_submittal_id', 'fieldname' => 'adminid'),
      array('webform_reftype' => 'entity_reference_env', 'refvalue' => 'sid', 'fieldname'=> 'dh_link_webform_submittal'),
    ),
    'resultid' => '',
  ); 
  
  
  return $wfmap;
} 


function dh_webform_td_full_submittal() {
  $wfmap = array();
  $wfmap[] = array(
    'entity' => 'dh_adminreg_feature',
    'description' => 'Vineyard or Block',
    'bundle' => 'registration',
    'debug' => FALSE,
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_vineyard_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => 'vineyard', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'userid', 'fieldname'=> 'dh_link_admin_record_mgr_id'),
    ),
    'resultid' => 'vid',
    'writeback' => array(
      'vineyard_adminid' => 'vid',
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_feature',
    'description' => 'Vineyard or Block Land Unit (stored as block)',
    'bundle' => 'landunit',
    'debug' => FALSE,
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_vineyard_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => 'block', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'constant', 'refvalue' => 'test description', 'fieldname' => 'description'),
      array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'userid', 'fieldname'=> 'dh_link_feature_mgr_id'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'vid', 'fieldname'=> 'dh_link_admin_location'),
    ),
    'resultid' => 'blockid',
    'writeback' => array(
      'block_hydroid' => 'blockid',
    ),
  );
  
  // Site Profile: 
  //   As Prop: soil, slope, drainage, exposure, elevation, area
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Area (acres)',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'area_ac', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'area_ac'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_acreage_block_size', 'fieldname'=> 'proptext'),
    ),
  );
  //   As Prop: soil, slope, drainage, exposure, elevation, area
  
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Soil texture',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'soil_texture', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'soil_prop_texture'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_soil_texture', 'fieldname'=> 'proptext'),
    ),
    'resultid' => 'soil_texture_pid',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Slope',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'slope', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'site_slope'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_terrain', 'fieldname'=> 'proptext'),
    ),
    'resultid' => 'terrain_pid',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Drainage',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'drainage', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'site_drainage'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_drainage', 'fieldname'=> 'propvalue'),
    ),
    'resultid' => 'drainage_pid',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Exposure',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'exposure', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'site_sun_exposure'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_site_exposure', 'fieldname'=> 'proptext'),
    ),
    'resultid' => 'exposure_pid',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Elevation',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'elevation', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'site_elevation'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_elevation', 'fieldname'=> 'proptext'),
    ),
    'resultid' => 'exposure_pid',
  );
  
  // weather and management
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Spring Weather',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'weather_pd_sum_season'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'spring', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_spring', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'spring_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Summer Weather',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'weather_pd_sum_season'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'summer', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_summer', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'summer_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Fall Weather',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'weather_pd_sum_season'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'fall', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_fall', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'fall_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Winter Weather',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'weather_pd_sum_season'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'winter', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_winter', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'winter_tsid',
  );
  
  // Management Actions
  //   As TS: cover crop, weed management, nutrient application (tstime is spring, tstext is nutrients), soil water status (date of submittal)
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Cover Crop',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'agman_cover_crop'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'spring', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_cover_crop', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'covercrop_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Weed Management',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'agman_weeding'), 
        ),
      ),
      array('webform_reftype' => 'constant', 'refvalue' => 'winter', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_weed_management', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'weeding_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Nutrient Application',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'agchem_apply_fert'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_nutrient_application_timing', 'fieldname'=> 'season'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_nutrient_application', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => null, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'nutrient_tsid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Soil Water Status',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'soil_prop_wc'), 
        ),
      ),
      array('webform_reftype' => 'env', 'refvalue' => 'now', 'fieldname'=> 'tstime'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_soil_water_status', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
    'resultid' => 'soilwater_tsid',
  );
  
  // Viticulture specific block info
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Crop',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'crop', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'agman_crop'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'crop', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Vine Age',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'vine_age', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vitis_misc', 'fieldname'=> 'propvalue'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Vinifera Planted',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'vitis_vinifera', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vitis_vinifera', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Hybrid Planted',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'hybrid_variety', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'hybrid_variety', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Other Variety Planted',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'other_variety_names', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'other_variety_names', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Rootstock',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'rootstock', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'rootstock', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Other Rootstock',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'blockid', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'other_rootstock', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'other_rootstock', 'fieldname'=> 'proptext'),
    ),
  );
  
  // sample location - a monitoring point
  $wfmap[] = array(
    'entity' => 'dh_feature',
    'description' => 'Sampling Point Location',
    'bundle' => 'plant_tissue_sample',
    'debug' => FALSE,
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_vineyard_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => 'trunk', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vsample_image', 'fieldname' => 'field_image'),
      array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'userid', 'fieldname'=> 'dh_link_feature_mgr_id'),
    ),
    'resultid' => 'vsample_mp',
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Affected Tissue',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'plant_tissue_affected', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'plant_tissue_affected', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Trunk Symptoms',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'trunk', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'trunk', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Shoot symptoms',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'shoots', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'shoots', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Leaf symptoms',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'leaves', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'leaves', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Cluster symptoms',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'clusters', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'clusters', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Symptom Distribution within Canopy',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'symptom_distribution_within_canopy', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'symptom_distribution_within_canopy', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Symptom Distribution within Vineyard',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'symptom_distribution_within_vineyard', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'symptom_distribution_within_vineyard', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Percent planting affected',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'percent_planting_affected', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'percent_planting_affected', 'fieldname'=> 'propvalue'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Symptom Appearance',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'notnull_fields' => array('tstime'),
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'ipm_event'), 
        ),
      ),
      array('webform_reftype' => 'env', 'refvalue' => 'approximate_date_symptoms_appeared', 'fieldname'=> 'tstime'),
      array('webform_reftype' => 'constant', 'refvalue' => 'briefly_describe_the_symptom', 'fieldname'=> 'tstext'),
      array('webform_reftype' => 'constant', 'refvalue' => 1, 'fieldname'=> 'tsvalue'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Growth stage at appearance',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'growth_stage_when_symptoms_first_appearred', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'growth_stage_when_symptoms_first_appearred', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Previously observed?',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'have_you_seen_the_same_symptom_in_previous_years_', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'have_you_seen_the_same_symptom_in_previous_years_', 'fieldname'=> 'proptext'),
    ),
  );
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'Increasing incidence?',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'has_the_number_of_symptomatic_plants_increased_in_the_past_years', 'fieldname'=> 'propname'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'has_the_number_of_symptomatic_plants_increased_in_the_past_years', 'fieldname'=> 'proptext'),
    ),
  );
  
  // sample info  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Sample Submitted',
    'bundle' => 'dh_timeseries',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_timeseries', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_sampleid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'sample_event'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vsample_date', 'fieldname'=> 'tstime'),
    ),
    'resultid' => 'sample_event_tid',
  );
  
  // crop, varietal, rootstock - dh properties on block
  // symptoms, brief desc, specific questions - dh properties on sample feature
  
  // submittal record that ties together the submission event, the submission sample location (block), and the vineyard (admin registration record)
  $wfmap[] = array(
    'entity' => 'dh_adminreg_feature',
    'description' => 'Trunk Disease Site Description Submittal',
    'bundle' => 'submittal',
    'debug' => FALSE,
    'fields' => array(
      // this link is not yet active
      //array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'organization_id', 'fieldname' => 'dh_link_admin_submittal_org'),
      array('webform_reftype' => 'constant', 'refvalue' => 'td_site_form', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_vineyard_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => '', 'fieldname' => 'description'),
      array('webform_reftype' => 'env', 'refvalue' => 'now', 'fieldname'=> 'modified'),
      array('webform_reftype' => 'constant', 'refvalue' => 'Webform Form', 'fieldname' => 'formtype'),
      // attached properties and references
      // link to site registration and field/vineyard/block feature
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'vid', 'fieldname'=> 'dh_link_admin_submittal_pr'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'blockid', 'fieldname'=> 'dh_link_feature_submittal'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'vsample_mp', 'fieldname'=> 'dh_link_feature_submittal'),
      // timeseries stuff
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'spring_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'summer_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'fall_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'winter_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'soilwater_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'nutrient_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'weeding_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
      array('webform_reftype' => 'entity_reference_rid', 'refvalue' => 'covercrop_tsid', 'fieldname'=> 'dh_link_admin_timeseries'),
    ),
    'resultid' => 'td_submittal_id',
    'writeback' => array(
      'td_submittal_id' => 'td_submittal_id',
    ),
  ); 
  
  $wfmap[] = array(
    'entity' => 'dh_adminreg_feature',
    'description' => 'Sample Submittal Link to Original Form',
    'bundle' => 'submittal',
    'hook' => 'insert',
    'debug' => FALSE,
    'fields' => array(
      // this link is not yet active
      //array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'organization_id', 'fieldname' => 'dh_link_admin_submittal_org'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'td_submittal_id', 'fieldname' => 'adminid'),
      array('webform_reftype' => 'entity_reference_env', 'refvalue' => 'sid', 'fieldname'=> 'dh_link_webform_submittal'),
    ),
    'resultid' => '',
  ); 
  
  return $wfmap;
} 

function dh_webform_td_isolate() {
  $wfmap = array();
  // isolate entity - name, code, dna, 
    // iid: autointeger
    // Isolate: text?
    // Ecology/species - select-list
    // its_sequence: long text
    // source: text or foreign key
    // acquisition_num: AF1979…(blast)
    // Sample: dh_link_isolate_mps - links back to sample, ID provided via URL
  // isolate dH Properties:
    // spore_type
    // spore_length
    // spore_width
    // spore_characteristics
    // culture_morphology
    // mycelial_morphology
  
  // the actual sample
  $wfmap[] = array(
    'entity' => 'dh_ecology_isolate',
    'description' => 'Sample',
    'bundle' => 'dh_ecology_isolate',
    'debug' => false,
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'td_isolate_isolate', 'fieldname' => 'isolate'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'td_isolate_source', 'fieldname' => 'source'),
      array('webform_reftype' => 'constant', 'refvalue' => 'td_isolate_its', 'fieldname' => 'its_sequence'),
      array('webform_reftype' => 'entity_reference_formkey', 'refvalue' => 'vsample_mp', 'fieldname'=> 'dh_link_isolate_mps'),
    ),
    'resultid' => 'td_isolate_iid',
  );
  // isolate attached properties
  $wfmap[] = array(
    'entity' => 'dh_properties',
    'description' => 'spore_type',
    'bundle' => 'dh_properties',
    'debug' => FALSE,
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'result', 'refvalue' => 'vsample_mp', 'fieldname'=> 'featureid'),
      array('webform_reftype' => 'constant', 'refvalue' => 'spore_type', 'fieldname'=> 'propname'),
      array('webform_reftype' => 'constant', 'refvalue' => 'dh_ecology_isolate', 'fieldname'=> 'entity_type'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property', 'property' => 'varkey', 'value' => 'vitis_misc'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'td_isolate_spore_type', 'fieldname'=> 'proptext'),
    ),
  );
  
  return $wfmap;
}


function dh_webform_td_prop() {
  $wfmap = array();
  $wfmap['dh_webform_prop'][] = array(
    'entity' => 'dh_properties',
    'description' => 'Prop',
    'debug' => false,
    'bundle' => 'dh_properties',
    'handler' => 'dh_webform_insert_property', // NOT USED YET - could later add custom functions
    'fields' => array(
      array('webform_reftype' => 'form_key', 'refvalue' => 'featureid', 'fieldname'=> 'featureid'),
      array('entity' => 'dh_variabledefinition', 'webform_reftype' => 'EntityFieldQuery', 'fieldname'=> 'varid', 'queryfield' => 'hydroid', 'queryparams' => array(
        array('type' => 'property_webformkey', 'property' => 'varkey', 'value' => 'varkey'), 
        ),
      ),
      array('webform_reftype' => 'form_key', 'refvalue' => 'varkey', 'fieldname'=> 'propname'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'propvalue', 'fieldname'=> 'propvalue'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'proptext', 'fieldname'=> 'proptext'),
    ),
    'resultid' => 'pid',
  );
  return $wfmap;
}
?>
