#!/user/bin/env drush
<?php
  //module_load_include('inc', 'dh', 'plugins/dh.display');
  $file = "/var/www/d.live/modules/dh_ecology/data/type_specs.txt";
  $handle = fopen($file, 'r');
  $update_props = TRUE;
  $i = 0;
  while ($values = fgetcsv($handle, 0, "\t")) {
    $i++;
    error_log( "Record # $i");
    if ($i == 1) {
      // skip a header 
      continue;
    }
    list($isolate, $source, $type_specimen) = $values;
    // sql to search for record 
    $q = "  select iid from dh_ecology_isolate ";
    $q .= " where isolate = '$isolate'  ";
    error_log( $q);
    // Load some entity.
    $rez = db_query(
      $q, 
      array(), 
      array('fetch' => PDO::FETCH_ASSOC)
    );
    $recs = $rez->fetchAllAssoc('tid');
    //dpm($recs, 'recs');
    if (count($recs) == 1) {
      $iirec = array_shift($recs);
      $isolate_record = entity_load_single('dh_ecology_isolate', $iirec->iid);
      error_log("Loaded record iid = " . $isolate_record->iid . " for '$isolate'. ");
    } else {
      error_log("Found " . count($recs) . " records for '$isolate'. Skipping.");
    }
    
    //$dh_adminreg_feature->save();
    //echo "saved $record->name \n";
  }
  
?>
