<?php

/**
 * @file
 * Model editing UI.
 *
 */
 
/**
 * UI controller.
 */
 
//****************************
// Isolate Table
//****************************

class dHEcologyIsolateTypeUIController extends EntityDefaultUIController {
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage dH Ecology Isolate type bundles.';
    return $items;
  }

}
class dHEcologyIsolateUIController extends EntityDefaultUIController {
  public function hook_menu() {
    $items = parent::hook_menu();

    // Change the overview menu type for the list of models.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Extend the 'add' path.
    $items[$this->path . '/add'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType),
      'page callback' => 'entity_ui_bundle_add_page',
      'page arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
      'type' => MENU_LOCAL_ACTION,
    );
    $items[$this->path . '/add/%'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType, $this->id_count + 1),
      'page callback' => 'entity_ui_get_bundle_add_form',
      'page arguments' => array($this->entityType, $this->id_count + 1),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    if (!empty($this->entityInfo['admin ui']['file'])) {
      // Add in the include file for the entity form.
      foreach (array('/add', '/add/%') as $path_end) {
        $items[$this->path . $path_end]['file'] = $this->entityInfo['admin ui']['file'];
        $items[$this->path . $path_end]['file path'] = isset($this->entityInfo['admin ui']['file path']) ? $this->entityInfo['admin ui']['file path'] : drupal_get_path('module', $this->entityInfo['module']);
      }
    }
      
    return $items;
  }	
}

function dh_ecology_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'om_data_table-om_data_table-field_om_data_starttime'
  $field_instances['dh_ecology_isolate-modified'] = array(
    'bundle' => 'dh_ecology_isolate',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'dh_ecology_isolate',
    'field_name' => 'modified',
    'label' => 'Time',
    'required' => 0,
    'settings' => array(
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'display_all_day' => 0,
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => 1,
    ),
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Start Time');

  return $field_instances;
}


// FORM Stuff

/**
 * dH Isolate Type editing form.
 */
function dh_ecology_isolate_type_form($form, &$form_state, $dh_ecology_isolate_type, $op = 'edit') {

  if ($op == 'clone') {
    $dh_ecology_isolate_type->name .= ' (cloned)';
    $dh_ecology_isolate_type->bundle = '';
  }

  $form['name'] = array(
    '#title' => t('Admin Entity Name'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate_type->name,
    '#description' => t('The human-readable name of this dH Feature type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['bundle'] = array(
    '#title' => t('Bundle Name'),
	  '#type' => 'machine_name',
    '#default_value' => isset($dh_ecology_isolate_type->bundle) ? $dh_ecology_isolate_type->bundle : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'dh_ecology_isolate_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate_type->description,
    '#description' => t('Detailed description of this dH Isolate type.'),
    '#required' => FALSE,
    '#size' => 255,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save dH Isolate type'),
    '#weight' => 40,
  );

  return $form;
}
/**
 * Form API submit callback for the type form.
 */
function dh_ecology_isolate_type_form_submit(&$form, &$form_state) {
  $dh_ecology_isolate_type = entity_ui_form_submit_build_entity($form, $form_state);
  $dh_ecology_isolate_type->save();
  $form_state['redirect'] = 'admin/structure/dh_ecology_isolate_type';
}
/**
 * dH Ecology editing form.
 */

function dh_ecology_isolate_form($form, &$form_state, $dh_ecology_isolate, $op = 'edit') {
  if ($op == 'clone') {
    $dh_ecology_isolate->name .= ' (cloned)';
    $dh_ecology_isolate->bundle = '';
  }

/*  $form['iid'] = array(
    '#title' => t('Isolate ID'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->iid,
    '#description' => t('Primary key for Variables'),
    '#required' => TRUE,
    '#size' => 64,
  );
*/

  $form['isolate'] = array(
    '#title' => t('Isolate Code'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->isolate,
    '#description' => t('Unique Isolate Text ID code for sample.'),
    '#required' => TRUE,
    '#size' => 64,
  );
  $form['genus'] = array(
    '#title' => t('Genus'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->genus,
    '#description' => t('Identified Genus of sample DNA.'),
    '#required' => FALSE,
    '#size' => 64,
  );
  $form['species'] = array(
    '#title' => t('Species'),
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
    ),
    '#description' => t('Ecology'),
    '#required' => FALSE,
  );

  $form['source'] = array(
    '#title' => t('Sample Source'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->source,
    '#description' => t('Sample Source.'),
    '#required' => FALSE,
    '#size' => 64,
  );

  $form['acquisition_num'] = array(
    '#title' => t('Acquisition Number'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->acquisition_num,
    '#description' => t('Acquisition Number.'),
    '#required' => FALSE,
    '#size' => 64,
  );

  $form['sequence'] = array(
    '#title' => t('DNA Sequence'),
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
    '#title' => t('Sequence Location'),
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
  return $form;

}

function dh_ecology_isolate_form_submit(&$form, &$form_state) {
  // Form API submit callback for the type form.
  $dh_ecology_isolate = entity_ui_form_submit_build_entity($form, $form_state);
  $dh_ecology_isolate->save();
  $form_state['redirect'] = 'admin/content/dh_ecology_isolate/';
}

?>
