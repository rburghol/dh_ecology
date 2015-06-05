<?php


function dh_ecology_webform_getmap() {
  global $wfmap;
  // dH Webform integration
  if (!isset($wfmap)) {
    $wfmap = array(); // keyed on name from webform table 
  }
  $wfmap['grower_info'] = dh_webform_grower_info();
  $wfmap['vitis_site_desc'] = dh_webform_vitis_site_desc();

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
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_address', 'fieldname'=> 'address1'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_address2', 'fieldname'=> 'address2'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_city', 'fieldname' => 'city'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_state', 'fieldname' => 'state'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_zip', 'fieldname' => 'postal_code'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_vineyard_coordinates', 'fieldname' => 'description'),
      // will have a link to the user dha_link_rec_uid 
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
    'entity' => 'dh_feature',
    'description' => 'Vineyard or Block',
    'bundle' => 'facility',
    'debug' => FALSE,
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_vineyard_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => 'vineyard', 'fieldname' => 'ftype'),
    ),
    'resultid' => 'vid',
  );
  $wfmap[] = array(
    'entity' => 'dh_feature',
    'description' => 'Vineyard or Block Land Unit (stored as block)',
    'bundle' => 'landunit',
    'debug' => FALSE,
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'vdesc_vineyard_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => 'block', 'fieldname' => 'ftype'),
    ),
    'resultid' => 'blockid',
  );
  
  $wfmap[] = array(
    'entity' => 'dh_timeseries',
    'description' => 'Spring Weather',
    'bundle' => '',
    'debug' => TRUE,
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
  
  return $wfmap;
} 

function dh_webform_trunk_disease_sample() {
  $wfmap = array();
  $wfmap[] = array(
    'entity' => 'dh_feature',
    'description' => 'dH Organization',
    'bundle' => 'organization',
    'debug' => TRUE,
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'constant', 'refvalue' => 'grower', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_address', 'fieldname'=> 'address1'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_address2', 'fieldname'=> 'address2'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_city', 'fieldname' => 'city'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_state', 'fieldname' => 'state'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'grower_zip', 'fieldname' => 'postal_code'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'organization_description', 'fieldname' => 'description'),
    ),
    'resultid' => 'orgid',
    'writeback' => array(
      'organization_id' => 'orgid',
    ),
  );
  return $wfmap;
} 
?>
