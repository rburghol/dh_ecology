<?php
  module_load_include('inc', 'dh', 'plugins/dh.display');
  $csv = fopen("/var/www/d.live/modules/dh_ecology/data/type_specs.txt");
  $update_props = TRUE;
  // sql to get records with redundant erefs
  $q = "  select adminid from dh_adminreg_feature ";
  $q .= " where bundle = 'registration' and ftype in ('fungicide', 'herbicide', 'insecticide', 'other', 'fertilizer') ";
  if ($uid <> -1) {
    $q .= " and uid = $uid ";
  }
  if ($elist <> '') {
    $q .= " and adminid in ($elist) ";
  }
  $result = db_query($q);
  // If we want to do a single one uncomment these lines:
  /* 
  $result = array(
    0 => new STDClass,
  );
  $result[0]->adminid = 299;
  */
  echo $q;
  
  foreach ($result as $record) {
    // get events
    // Load some entity.
    $dh_adminreg_feature = entity_load_single('dh_adminreg_feature', $record->adminid);
    if ($update_props) {
      $ipm_vt_pmg_material = array(
        'varkey' => 'ipm_vt_pmg_material',
        'featureid' => $dh_adminreg_feature->adminid,
        'entity_type' => 'dh_adminreg_feature',
        'propcode' => '',
        'propname' => 'ipm_vt_pmg_material'
      );
      //error_log("Saving frac controller " . print_r($frac_group,1));
      om_model_getSetProperty($ipm_vt_pmg_material, 'name');
    }
    //$dh_adminreg_feature->save();
    echo "saved $record->name \n";
  }
  
?>
