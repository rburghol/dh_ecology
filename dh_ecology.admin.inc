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

class dHEcologyIsolateUIController extends EntityDefaultUIController {
  public function hook_menu() {
    $items = parent::hook_menu();

    // Change the overview menu type for the list of models.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

	
  // Extend the 'add' path.
  $items[$this->path . '/add'] = array(
    'title' => 'Add DNA Isolate',
    'description' => 'A form to enter Plant tissue DNA Isolate Data',
    'page callback' => 'entity_ui_get_bundle_add_form',
    'page arguments' => array($this->entityType,$this->id_count + 1),
    'access callback' => 'entity_access',
    'access arguments' => array('create', $this->entityType),
    'type' => MENU_LOCAL_ACTION,
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
  return $field_instances;
}


// FORM Stuff

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
    '#description' => t('Isolate Text ID code for sample.'),
    '#required' => TRUE,
    '#size' => 64,
  );

  $form['species'] = array(
    '#title' => t('Species'),
    '#type' => 'textfield',
    '#default_value' => $dh_ecology_isolate->species,
    '#description' => t('Identified Species of sample DNA.'),
    '#required' => FALSE,
    '#size' => 64,
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
    '#description' => t('Aquisition Number.'),
    '#required' => FALSE,
    '#size' => 64,
  );

  $form['its_sequence'] = array(
    '#title' => t('ITS Sequence'),
    '#type' => 'textarea',
    '#default_value' => $dh_ecology_isolate->its_sequence,
    '#description' => t('ITS Sequence.'),
    '#required' => FALSE,
    '#size' => 5,
  );

  field_attach_form('dh_ecology_isolate', $dh_ecology_isolate, $form, $form_state);

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
