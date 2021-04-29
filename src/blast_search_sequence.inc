<?php
$gensearch = l("General Search", 'td-lab-isolates');
echo "<p>Enter a DNA sequence to search for BLAST matches on the local database.  To view search for records in the local database go here: $gensearch</p>" ;
$debug = FALSE;

function dhe_sort_ipct($a, $b) {
  global $srt;
  $a_weight = (is_array($a) && isset($a['ident_pct'])) ? $a['ident_pct'] : 0;
  $b_weight = (is_array($b) && isset($b['ident_pct'])) ? $b['ident_pct'] : 0;
  $srt[] = "$a_weight == $b_weight";
  if (floatval($a_weight) == floatval($b_weight)) {
    return 0;
  }
  return (floatval($a_weight) > floatval($b_weight)) ? -1 : 1;
}
function dhe_sort_evalue($a, $b) {
  $a_weight = (is_array($a) && isset($a['evalue'])) ? $a['evalue'] : 0;
  $b_weight = (is_array($b) && isset($b['evalue'])) ? $b['evalue'] : 0;
  if (floatval($a_weight) == floatval($b_weight)) {
    return 0;
  }
  return (floatval($a_weight) > floatval($b_weight)) ? -1 : 1;
}

function dh_ecology_blast_form($form, &$form_state, $test_entity = null, $op = 'edit') {

  $form['sequence'] = array(
    '#title' => t('Sequence'),
    '#type' => 'textarea',
    '#default_value' => '',
    '#description' => t('Sequence to search against.'),
    '#required' => TRUE,
    '#rows' => 5,
    '#cols' => 60,
  );  
  $form['data']['#tree'] = TRUE;
  $form['program'] = array(
    '#title' => t('Program'),
    '#type' => 'select',
    '#options' => array(
      'blastn' => t('BlastN'),
      'blastp' => t('BlastP'),
      'blastx' => t('BlastX'),
    ),
    '#default_value' => 'blastn',
    '#required' => TRUE,
    '#multiple' => FALSE,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('BLAST Search'),
    '#weight' => 40,
  );
  
  return $form;
}

function dh_ecology_flag_its_info(&$info) {
  $txt = "For genera belonging in the Botryosphaeriaceae (Botryosphaeria, Diplodia, Dothiorella, Lasiodiplodia, Neofusicoccum, Neoscytalidium, and Spencermartinsia) we suggest PCR amplification of a portion of the translation elongation factor 1-alpha (TEF) locus using the primer pair EF1-728F and EF1-986R (Carbone & Kohn 1999) to generate a secondary barcode for greater resolution of species identification. ";
  $txt .= "\n\nFor genera belonging in the Diatrypaceae and Togniniaceae (Anthostoma, Cryptosphaeria, Cryptovalsa, Diatrype, Diatrypella, Eutypa, Eutypella, and Phaeoacremonium) we suggest PCR amplification of a portion of the beta-tubulin (TUB2) locus using the primer pairs T1 (O’Donnell & Cigelnik 1997) and Bt2b (Glass & Donaldson 1995) to generate a secondary barcode for greater resolution of species identification.";
  $txt .= "\n\nFor genera belonging in the Nectriaceae (Campylocarpon, Cylindrocarpon, Dactylonectria, and Ilyonectria) we suggest PCR amplification of a portion of the histone 3 (HIS) locus using the primer pairs CYLH3F and CYLH3R (Crous et al. 2004) to generate a secondary barcode for greater resolution of species identification. ";
  $txt = "<ul><li>For genera belonging in the Botryosphaeriaceae (Botryosphaeria, Diplodia, Dothiorella, Lasiodiplodia, Neofusicoccum, Neoscytalidium, and Spencermartinsia) we suggest PCR amplification of a portion of the translation elongation factor 1-alpha (TEF) locus using the primer pair EF1-728F and EF1-986R (Carbone & Kohn 1999) to generate a secondary barcode for greater resolution of species identification. ";
  $txt .= "<li>For genera belonging in the Diatrypaceae and Togniniaceae (Anthostoma, Cryptosphaeria, Cryptovalsa, Diatrype, Diatrypella, Eutypa, Eutypella, and Phaeoacremonium) we suggest PCR amplification of a portion of the beta-tubulin (TUB2) locus using the primer pairs T1 (O’Donnell & Cigelnik 1997) and Bt2b (Glass & Donaldson 1995) to generate a secondary barcode for greater resolution of species identification.";
  $txt .= "<li>For genera belonging in the Nectriaceae (Campylocarpon, Cylindrocarpon, Dactylonectria, and Ilyonectria) we suggest PCR amplification of a portion of the histone 3 (HIS) locus using the primer pairs CYLH3F and CYLH3R (Crous et al. 2004) to generate a secondary barcode for greater resolution of species identification. </ul>";
  //$txt = l('click me', 'modal/link', array( 'attributes' => array('class' => array( 'ctools-use-modal' )) ));
  //$info .= "<br><i>Note: ITS BLAST hits with an '*' should be considered putative.  We recommend querying the database with a secondary barcode as detailed in <span title='$txt'><u>this comment box</u></span>.</i>";
  $info .= "<br><i>Note: ITS BLAST hits with an '*' should be considered putative.  We recommend querying the database with a secondary barcode as detailed below:$txt</i>";
}

function dh_ecology_flag_its_row(&$row) {
  $flag_ident = 98;
  if (floatval($row['ident_pct']) >= $flag_ident) {
    $row['ident_pct'] .= ' *';
  }
}

function dh_ecology_flag_its_Nectriaceae_row(&$row) {
  $flag_ident = 98;
  if (floatval($row['ident_pct']) >= $flag_ident) {
    $generas = array('Anthostoma', 'Cryptosphaeria', 'Cryptovalsa', 'Diatrype', 'Diatrypella', 'Eutypa', 'Eutypella', 'Phaeoacremonium');
    $msg = "For genera belonging in the Nectriaceae (Campylocarpon, Cylindrocarpon, Dactylonectria, and Ilyonectria) we suggest PCR amplification of a portion of the histone 3 (HIS) locus using the primer pairs CYLH3F and CYLH3R (Crous et al. 2004) to generate a secondary barcode for greater resolution of species identification. ";
    $match = FALSE;
    foreach ($generas as $genera) {
      if (!(strpos($row['url'], $genera) === FALSE)) {
        $match = "<span title='$msg'>$row[ident_pct]<sup>1</sup></span>";
      }
    }
    if ($match) {
      $row['ident_pct'] = $match;
    }
  }
}

function dh_ecology_flag_its_Diatrypaceae_Togniniaceae_row(&$row) {
  $flag_ident = 98;
  if (floatval($row['ident_pct']) >= $flag_ident) {
    $generas = array('Anthostoma', 'Cryptosphaeria', 'Cryptovalsa', 'Diatrype', 'Diatrypella', 'Eutypa', 'Eutypella', 'Phaeoacremonium');
    $msg = "For genera belonging in the Diatrypaceae and Togniniaceae (Anthostoma, Cryptosphaeria, Cryptovalsa, Diatrype, Diatrypella, Eutypa, Eutypella, and Phaeoacremonium) we suggest PCR amplification of a portion of the beta-tubulin (TUB2) locus using the primer pairs T1 (O’Donnell & Cigelnik 1997) and Bt2b (Glass & Donaldson 1995) to generate a secondary barcode for greater resolution of species identification. ";
    $match = FALSE;
    foreach ($generas as $genera) {
      if (!(strpos($row['url'], $genera) === FALSE)) {
        $match = "<span title='$msg'>$row[ident_pct]<sup>2</sup></span>";
      }
    }
    if ($match) {
      $row['ident_pct'] = $match;
    }
  }
}

function dh_ecology_flag_its_Botryosphaeriaceae_row(&$row) {
  $flag_ident = 98;
  if (floatval($row['ident_pct']) >= $flag_ident) {
    $generas = array('Botryosphaeria', 'Diplodia', 'Dothiorella', 'Lasiodiplodia', 'Neofusicoccum', 'Neoscytalidium', 'Spencermartinsia');
    $msg = "For genera belonging in the Botryosphaeriaceae (Botryosphaeria, Diplodia, Dothiorella, Lasiodiplodia, Neofusicoccum, Neoscytalidium, and Spencermartinsia) we suggest PCR amplification of a portion of the translation elongation factor 1-alpha (TEF) locus using the primer pair EF1-728F and EF1-986R (Carbone & Kohn 1999) to generate a secondary barcode for greater resolution of species identification. ";
    $match = FALSE;
    foreach ($generas as $genera) {
      if (!(strpos($row['url'], $genera) === FALSE)) {
        $match = "<span title='$msg'>$row[ident_pct]<sup>3</sup></span>";
      }
    }
    if ($match) {
      $row['ident_pct'] = $match;
    }
  }
}

/**
 * Form API submit callback for the type form.
 */
function dh_ecology_blast_form_submit(&$form, &$form_state) {
  // do the search here
  global $srt;
  $srt = array();
  $a = $form_state['extra_args'];
  $program = $form_state['values']['program'];
  //dpm($program);
  $form_state['rebuild'] = TRUE;
  $info_plugins = array(
    'its' => array(
      'function' => 'dh_ecology_flag_its_info',
      'enabled' => !(strpos($form_state['values']['sequence'], 'CGATGAAGAACGCA') === FALSE),
    ),
  );    
  $row_plugins = array(
    'its' => array(
      'function' => 'dh_ecology_flag_its_row',
      'enabled' => !(strpos($form_state['values']['sequence'], 'CGATGAAGAACGCA') === FALSE),
    ),
    'Botryosphaeriaceae' => array(
      'function' => 'dh_ecology_flag_its_Botryosphaeriaceae_row',
      'enabled' => !(strpos($form_state['values']['sequence'], 'CGATGAAGAACGCA') === FALSE),
    ),
    'Diatrypaceae_Togniniaceae' => array(
      'function' => 'dh_ecology_flag_its_Diatrypaceae_Togniniaceae_row',
      'enabled' => !(strpos($form_state['values']['sequence'], 'CGATGAAGAACGCA') === FALSE),
    ),
    'Nectriaceae' => array(
      'function' => 'dh_ecology_flag_its_Nectriaceae_row',
      'enabled' => !(strpos($form_state['values']['sequence'], 'CGATGAAGAACGCA') === FALSE),
    ),
  );    
  if (strlen(trim($form_state['values']['sequence'])) > 0) {
    $begin = substr($form_state['values']['sequence'], 1, 24);
    echo "Performing BLAST search for sequence beginning with " . $begin . "...<br>";
    $now = date();
    $sequence = $form_state['values']['sequence'];
    $seq = array();
    $isos = array();
    $sample_fasta = array();
    $seq[] = ">www|user submitted beginning $begin|$now\n";
    //$seq[] = trim($sequence) . "\n";
    $seq[] = chunk_split(trim($sequence),80,"\n");
    $base = "/var/www/R/fasta";
    $sid = "www$begin";
    $seqn = $sid . ".fa";
    $seqf = "$base/$seqn";
    file_put_contents($seqf, $seq);
    $recs = 0;
    $rez = db_query("select iid, genus, species, CASE WHEN acquisition_num is NULL THEN 'no acqu_num' || iid WHEN acquisition_num = '' THEN 'no acqu_num ' || iid ELSE acquisition_num END as acquisition_num, sequence from {dh_ecology_isolate} where sequence is not null and sequence <> '' and bundle <> 'primer';");
    foreach ($rez as $iso) {
      $recs++;
      $isos[] = ">gnl|$iso->iid|$iso->genus $iso->species|$iso->acquisition_num\n";
      //$isos[] = trim($iso->sequence) . "\n";
      $isos[] = chunk_split(trim($iso->sequence),80,"\n");
      if (count($isos) <= 20) {
        $sample_fasta[] = ">gnl|$iso->iid|$iso->genus $iso->species|$iso->acquisition_num\n";
        $sample_fasta[] = chunk_split(trim($iso->sequence),80,"\n");
      }
    }
    $isodbf = "$base/isodb.faa";
    file_put_contents($isodbf, $isos);
    $sh = array();
    $sh[] = "cd $base";
    $sh[] = "rm -f out-$sid.out";
    $sh[] = "formatdb -i $isodbf -o T -p F";
    //$sh[] = "blastall -i $seqn -d isodb.faa -p $program -o out-$sid.out -e 1e-6 -W 28 -F \"L;m;D\"";
    $sh[] = "blastall -i $seqn -d isodb.faa -p $program -o out-$sid.out -e 1e-6 -W 28 -F \"L;m\"";
    $sh[] = "echo \"target,match\" > matches-$sid.csv";
    $sh[] = "python ngs-scripts/blast/blast-to-csv.py out-$sid.out >> matches-$sid.csv";
    $sh[] = "cat matches-$sid.out";
    $sh[] = "cat out-$sid.out";
    $shout = shell_exec(implode(";", $sh));
    $matches = array();
    $umatches = array(); // holds unique matches
    $urls = array();
    print("Assembled fasta file with $recs records.<br>" );
    //print("BLAST <pre>" . implode(";\n", $sh) . "</pre><br>" );
    if (file_exists("$base/matches-$sid.csv")) {
      echo l('View Detailed Output from BLAST', "http://www.grapeipm.org/R/fasta/out-$sid.out", array('attributes'=> array('target'=>'_new')) );
      $f = fopen("$base/matches-$sid.csv", 'r');
      //print("opening $base/matches-$sid.csv<br>");
      $i = 0;
      while ($matches[] = fgetcsv($f)) {
        list($src, $dest, $score, $evalue, $ident_pct) = $matches[$i];
        $target_info = explode('|', $dest);
        if (!($target_info[1] > 0)) {
          $i++;
          continue;
        }
        if (!isset($umatches[$target_info[1]])) {
          $tname = $target_info[2];
          $e = entity_load_single('dh_ecology_isolate',$target_info[1]);
          if (is_object($e)) {
            $tname = ucwords($e->genus) . " " . $e->species;
            $host = $e->host_organism;
            $ecology = $e->ecology;
            $acquisition_num = $e->acquisition_num;
          } else {
            $tname = '';
            $host = '';
            $ecology = '';
          }
          $url = "<a href='" . base_path() . "?q=td-lab-isolates/0/" . $target_info[1] . "'>$tname</a>";
          $urls[] = $url;
          $umatches[$target_info[1]] = array(
            'url'=>$url,
            'host'=>$host,
            'ecology'=>$ecology,
            'acquisition_num'=>'',
            //'hit_count'=>0,
            'score'=>array($score),
           // 'coverage'=>'',
            'evalue'=>array(trim($evalue)),
            'ident_pct'=>array(trim($ident_pct . ' %')),
          );
          if (strlen($acquisition_num) > 0) {
            $umatches[$target_info[1]]['acquisition_num'] = "<a href='http://www.ncbi.nlm.nih.gov/nuccore/$acquisition_num' target=_new>$acquisition_num</a>";
          }
        } else {
          // we used to support multiple matches, but for now we do not
          /*
          $umatches[$target_info[1]]['hit_count'] += 1;
          $umatches[$target_info[1]]['score'][] = $score;
          $umatches[$target_info[1]]['evalue'][] = $evalue;
          $umatches[$target_info[1]]['ident_pct'][] = $ident_pct;
          */
        }
        $i++;
      }
      $matches = array_unique($matches);
      $info = "<br><strong>Local Database Matches:</strong>";
      foreach ($info_plugins as $plug) {
        $fn = $plug['function'];
        if ($plug['enabled']) {
          if (function_exists($fn)) {
            $fn($info);
          } else {
            if ($debug) watchdog('dh_ecology', "Undefined info plugin function $fn in BLAST");
          }
        } else {
          if ($debug) watchdog('dh_ecology', "Plugin info function $fn disabled");
        }
      }
      print($info);
      //print("raw:<pre>" . print_r($umatches,1) . "</pre>");
      $header = array(
        'url'=>'BLAST Matches',
        'host'=>'Host Plant',
        'ecology'=>'Ecology',
        'acquisition_num'=>'NCBI #',
        //'hit_count'=>'# Matches',
        'score'=>'Score (bits)',
       // 'coverage'=>'Query Coverage',
        'evalue'=>'E value',
        'ident_pct'=>'Identity',
      );
      foreach($umatches as $key=>$row) {
        if (count($umatches[$key]['score']) > 1) {
          $umatches[$key]['score'] = max($umatches[$key]['score']) . " / " . min($umatches[$key]['score']);
          $umatches[$key]['evalue'] = min($umatches[$key]['evalue']) . "/" . max($umatches[$key]['evalue']);
          $umatches[$key]['ident_pct'] = max($umatches[$key]['ident_pct']) . "/" . min($umatches[$key]['ident_pct']);
        } else {
          $umatches[$key]['score'] = max($umatches[$key]['score']);
          $umatches[$key]['evalue'] = min($umatches[$key]['evalue']);
          $umatches[$key]['ident_pct'] = max($umatches[$key]['ident_pct']);
        }
        $umatches[$key]['evalue'] = sprintf('%.2E', $umatches[$key]['evalue']);
        foreach ($row_plugins as $plug) {
          $fn = $plug['function'];
          if ($plug['enabled']) {
            if (function_exists($fn)) {
              $fn($umatches[$key]);
            } else {
              if ($debug) watchdog('dh_ecology', "Undefined plugin function $fn in BLAST");
            }
          } else {
            if ($debug) watchdog('dh_ecology', "Plugin function $fn disabled");
          }
        }
      }
      // sort
      //uasort($umatches, 'dhe_sort_evalue');
      //uasort($umatches, 'dhe_sort_ipct');
      //dpm($srt,'sort comparisons');
      echo theme('table', array('header' => $header, 'rows' => $umatches));
      // log request
      $ip = "http://freegeoip.net/json/" . ip_address();
      $ip_json = file_get_contents($ip);
      //dpm($ip_json, "$ip");
      if ($ip_json) {
        $ip_loc = json_decode($ip_json);
        //dpm($ip_loc,'decoded');
      }
    }
    //print("Sample 1st 10 recs from FASTA file <pre>" . implode("", $sample_fasta) . "</pre><br>" );
  }
}

// **********************
// Load the form
// **********************
$form_state = array();
$form_state['extra_args'] = arg();
$elements = drupal_build_form('dh_ecology_blast_form', $form_state);
$form = drupal_render($elements);
echo $form;
?>