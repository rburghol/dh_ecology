<?php


function dh_ecology_webform_getmap() {
  // dH Webform integration
  $wfmap = array(); // keyed on name from webform table 
  $wfmap['grower_info'] = dh_webform_grower_info();

  return $wfmap;
}

function dh_webform_grower_info() {
  $wfmap = array();
  $wfmap[] = array(
    'entity' => 'dh_adminreg_feature',
    'description' => 'dH Organization',
    'bundle' => 'organization',
    'fields' => array( 
      array('webform_reftype' => 'form_key', 'refvalue' => 'organization_name', 'fieldname' => 'name'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'type', 'fieldname' => 'ftype'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'address', 'fieldname'=> 'address1'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'address2', 'fieldname'=> 'address2'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'city', 'fieldname' => 'city'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'state', 'fieldname' => 'state'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'zip_code', 'fieldname' => 'postal_code'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'tax_id', 'fieldname' => 'taxid'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'organization_description', 'fieldname' => 'description'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'start_issuance_date', 'fieldname'=> 'startdate'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'end_expiration_date', 'fieldname'=> 'enddate'),
      array('webform_reftype' => 'form_key', 'refvalue' => 'submittal_date', 'fieldname' => 'modified'),
    ),
    'resultid' => 'orgid',
    'writeback' => array(
      'organization_id' => 'orgid',
    ),
  );
  return $wfmap;
}
  
?>
