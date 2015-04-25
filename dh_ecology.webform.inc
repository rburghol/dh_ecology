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
