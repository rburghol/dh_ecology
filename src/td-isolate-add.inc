<?php
// use: module_load_include('inc', 'dh_ecology', 'src/td-isolate-add');
function dh_lab_isolate_form($form, &$form_state, $dh_ecology_isolate = null, $op = 'edit') {
  if ($op == 'clone') {
    $dh_ecology_isolate->name .= ' (cloned)';
    $dh_ecology_isolate->bundle = '';
  }
  $form['isolate'] = array(
    '#title' => t('Isolate Code'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->isolate,
    '#description' => t('Unique Isolate Text ID code for sample.'),
    '#required' => TRUE,
    '#size' => 64,
  );
  $form['genus'] = array(
    '#title' => t('Fungal Genus Name'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->genus,
    '#description' => t('Identified Genus of sample DNA.'),
    '#required' => FALSE,
    '#size' => 64,
  );
  $form['species'] = array(
    '#title' => t('Fungal Species Name'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->species,
    '#description' => t('Identified Specific Epithet of sample DNA.'),
    '#required' => FALSE,
    '#size' => 64,
  );
  $form['ecology'] = array(
    '#title' => t('Ecology'),
    '#type' => 'select',
    '#default_value' => $dh_ecology_isolate->ecology,
    '#options' => array(
      'unknown' => t('Unknown'),
      'pathogen' => t('Pathogen'),
      'nonpathogen' => t('Non-pathogen'),
      'test' => t('Testing'),
    ),
    '#description' => t('Ecology'),
    '#required' => FALSE,
  );

  $form['host_organism'] = array(
    '#title' => t('Host common name'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->host_organism,
    '#description' => t('Common name of the host plant from which this organism was obtained.'),
    '#required' => FALSE,
    '#size' => 64,
  );

  $form['source'] = array(
    '#title' => t('Sample Source'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->source,
    '#description' => t('Sample Source (Accession #, Lab name, DOI, or other identifier).'),
    '#required' => FALSE,
    '#size' => 64,
  );

  $form['acquisition_num'] = array(
    '#title' => t('NCBI Accession number'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->acquisition_num,
    '#description' => t('GenBank Accession Number (if registered).'),
    '#required' => FALSE,
    '#size' => 64,
  );

  $form['sequence'] = array(
    '#title' => t('Sequence'),
    '#type' => 'textarea',
    '#default_value' => $dh_ecology_isolate->sequence,
    '#description' => t('DNA Sequence.'),
    '#required' => FALSE,
    '#size' => 5,
  );
  if ( ($dh_ecology_isolate->sequence_location === null) or ($dh_ecology_isolate->sequence_location == '') ) {
    if ($dh_ecology_isolate->bundle == 'dh_ecology_isolate') {
      $dh_ecology_isolate->sequence_location = 'unknown';
    } else {
      $dh_ecology_isolate->sequence_location = $dh_ecology_isolate->bundle;
    }
  }
  $locs = array(
    'UNK' => 'Unknown',
    'LSU' => 'LSU',
    'SSU' => 'SSU',
    'COX2' => 'COX2',
    'ACT' => 'ACT',
    'APN2' => 'APN2',
    'CAL' => 'CAL',
    'TUB2' => 'TUB2',
    'CHS-1' => 'CHS-1',
    'CO1' => 'CO1',
    'GAPDH' => 'GAPDH',
    'GS' => 'GS',
    'TEF' => 'TEF',
    'HIS3' => 'HIS3',
    'SPD2' => 'SPD2',
    'Ypt1' => 'Ypt1',
    'MAT' => 'MAT',
    'RPB1' => 'RPB1',
    'RPB2' => 'RPB2',
    'ITS' => 'ITS',
    'IGS1' => 'IGS1',
  );
  $form['sequence_location'] = array(
    '#title' => t('Locus'),
    '#type' => 'select',
    '#default_value' => $dh_ecology_isolate->sequence_location,
    '#description' => t("Sequence Location (use 'unknown' if unknown)."),
    '#options' => $locs,
    '#required' => FALSE,
    '#maxlength' => 64,
  );
  $form['type_specimen'] = array(
    '#title' => t('Type Specimen?'),
    '#type' => 'select',
    '#default_value' => $dh_ecology_isolate->type_specimen,
    '#description' => t("When a study is published describing a species, the authors designate a single isolate as the essential member of that species, to which all other purported members of that species must be compared in order to confirm their identity."),
    '#options' => array(0 => 'False', 1 => 'True'),
    '#required' => FALSE,
    '#maxlength' => 64,
  );
  // Machine-readable type name.
  //$form['bundle'] = array(
  //  '#title' => t('Bundle Name'),
	//  '#type' => 'machine_name',
  //  '#default_value' => isset($dh_ecology_isolate->bundle) ? $dh_ecology_isolate->bundle : '',
  //  '#maxlength' => 32,
  //  '#machine_name' => array(
  //    'exists' => 'dh_ecology_isolate_get_types',
  //    'source' => array('label'),
  //  ),
  //  '#description' => t('A unique machine-readable name for this type. It must only contain //lowercase letters, numbers, and underscores.'),
  //);
  field_attach_form('dh_ecology_isolate', $dh_ecology_isolate, $form, $form_state);
  $form['dh_link_isolate_mps']['#type'] = 'hidden';
  $form['data']['#tree'] = TRUE;
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Isolate'),
    '#weight' => 40,
  );
  switch ($op) {
    case 'add':
    $form['actions']['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('dh_lab_isolate_form_submit_cancel')
    );
    break;
    case 'edit':
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('dh_lab_isolate_form_submit_delete')
    );
    break;
  }
  return $form;
}

function dh_lab_isolate_form_submit_cancel($form, &$form_state) {
  $url = $form_state['redirect'] ? $form_state['redirect'] : '';
  drupal_goto($url);
}

/**
 * Form API submit callback for the type form.
 */
function dh_lab_isolate_form_submit(&$form, &$form_state) {
  form_load_include($form_state, 'inc', 'entity', 'includes/entity.ui');
  form_load_include($form_state, 'inc', 'dh_ecology', 'dh_ecology.admin');
  $dh_ecology_isolate = entity_ui_form_submit_build_entity($form, $form_state);
  $dh_ecology_isolate->save();
  $form_state['redirect'] = 'td-lab-home';
}

/**
 * Form API submit callback for the delete button.
 */
function dh_lab_isolate_form_submit_delete(&$form, &$form_state) {
  //dpm($form_state,'form state');
  //dpm($_GET,'form state');
  //$form_state['redirect'] = 'admin/content/dh_ecology_isolate/manage/' . $form_state['dh_ecology_isolate']->iid . '/delete';
  //$form_state['redirect'] = 'admin/content/dh_ecology_isolate/manage/' . $form_state['dh_ecology_isolate']->iid . '/delete';
  list($pg, $us, $id) = explode('/', $_GET['destination']);
  //$_GET['destination'] = 'admin/content/dh_ecology_isolate/manage/' . $form_state['dh_ecology_isolate']->iid . '/delete&destination=' . $pg;
  unset($_GET['destination']);
  drupal_goto(
    'admin/content/dh_ecology_isolate/manage/' . $form_state['dh_ecology_isolate']->iid . '/delete',
    array('query' => array(
      'destination' => $pg
      )
    )  
  );
}

global $user;
$isolate = NULL;
$op = 'add';
$a = arg();
$iid = $a[1];
$sampleid = NULL;
if (isset($a[2])) {
  if (intval($a[2])) {
    $sampleid = $a[2];
  }
}
if ($iid > 0) {
  $result = entity_load('dh_ecology_isolate', array($iid));
  $isolate = $result[$iid];
  $op = 'edit';
} else {
  $isolate = entity_create('dh_ecology_isolate', 
    array(
      'bundle' => 'dh_ecology_isolate',
      'dh_link_isolate_mps' => array('und' => array( 0 => array('target_id' => $sampleid) )),
    )
  );
}
$form_state = array();
$form_state['wrapper_callback'] = 'entity_ui_main_form_defaults';
$form_state['entity_type'] = 'dh_ecology_isolate';
$form_state['bundle'] = 'dh_ecology_isolate';
$form_state['values']['name'] = 'New Isolate';
$form_state['redirect'] = 'td-lab-home';
form_load_include($form_state, 'inc', 'entity', 'includes/entity.ui');
// set things before initial form_state build
$form_state['build_info']['args'] = array($isolate, $op, 'dh_ecology_isolate');

// **********************
// Load the form
// **********************
//$elements = drupal_get_form('dh_lab_isolate_form');
$elements = drupal_build_form('dh_lab_isolate_form', $form_state);
//$elements = entity_ui_get_bundle_add_form('dh_ecology_isolate', 'dh_ecology_isolate');
// entity_ui_get_form($entity_type, $entity, $op = 'edit', $form_state = array())

error_reporting(E_ALL);
// just grab the regular form for proof of concept
$form = drupal_render($elements);
echo $form;
?>